from flask import Flask, session, request, render_template, url_for, redirect
from flask_session import Session
from config import Config
from forms import LoginForm
from exts import db, redis_client
from models import User
from utils import mark_data, get_data, login_required, get_avatar, random_dice, random_card, md5

app = Flask(__name__)
app.config.from_object(Config())

Session(app)

db.init_app(app)
redis_client.init_app(app)


@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if session.get('username'):
        return redirect(url_for('shake_and_dice'))
    if request.method == 'GET':
        return render_template('login.html', form=form)
    else:
        username = form.username.data
        password = form.password.data
        password_md5 = md5(password)
        avatar = form.avatar.data

        user = User.query.filter_by(username=username).first()

        if user:

            if password_md5 != user.password:
                return render_template('login.html', form=form, message='Sorry, username or password ERROR!')
            else:
                session['username'] = username
                return redirect(url_for('shake_and_dice'))
        else:
            user = User(username=username, password=password_md5, avatar=avatar)
            db.session.add(user)
            db.session.commit()
            session['username'] = username

        data = get_avatar(username)
        mark_data(username, data)

        return redirect(url_for('shake_and_dice'))


@app.route('/shake_and_dice')
@login_required
def shake_and_dice():
    dice1 = random_dice()
    dice2 = random_dice()
    dice3 = random_dice()
    content = get_data(session['username'])
    return render_template('shake_and_dice.html', username=session['username'], avatar=content,
                           dice1=dice1, dice2=dice2, dice3=dice3)


@app.route('/flag_points_29_points')
@login_required
def flag_points_29_points():
    card1 = random_card()
    card2 = random_card()
    card3 = random_card()
    content = get_data(session['username'])
    return render_template('flag_points_29_points.html', username=session['username'], avatar=content,
                           card1=card1, card2=card2, card3=card3)


@app.route('/logout')
@login_required
def logout():
    session.pop('username')
    return redirect(url_for('login'))

@app.route('/')
def index():
    return redirect(url_for('login'))


if __name__ == '__main__':
    app.run()