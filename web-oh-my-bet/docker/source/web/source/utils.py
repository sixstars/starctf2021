import os
import time
import re
import base64
import random
import hashlib
import urllib.request
from exts import redis_client
from functools import wraps
from flask import session, redirect, url_for
from models import User


def mark_data(id, data):
    expires = int(time.time()) + 240
    p = redis_client.pipeline()
    p.set(id, data)
    p.expireat(id, expires)
    p.execute()


def get_data(id):
    data = redis_client.get(id)
    if not data:
        data = get_avatar(id)
        mark_data(id, data)
    return data.decode()


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kws):
            if not session.get("username"):
               return redirect(url_for('login'))
            return f(*args, **kws)
    return decorated_function


def get_avatar(username):

    dirpath = os.path.dirname(__file__)
    user = User.query.filter_by(username=username).first()

    avatar = user.avatar
    if re.match('.+:.+', avatar):
        path = avatar
    else:
        path = '/'.join(['file:/', dirpath, 'static', 'img', 'avatar', avatar])
    try:
        content = base64.b64encode(urllib.request.urlopen(path).read())
    except Exception as e:
        error_path = '/'.join(['file:/', dirpath, 'static', 'img', 'avatar', 'error.png'])
        content = base64.b64encode(urllib.request.urlopen(error_path).read())
        print(e)

    return content


def random_dice():
    dices = ['1.gif', '2.gif', '3.gif', '4.gif', '5.gif', '6.gif', 'surprise1.gif', 'surprise2.gif']
    return random.choice(dices)


def random_card():
    color = ['♠️️', '❤️ ', '️️🔷', '♣️', '🚩']
    return "%-5s" % random.choice(color) + ' ' + "%-3s" % str(random.randint(1, 15))


def md5(data):
    m = hashlib.md5(data.encode())
    return m.hexdigest()