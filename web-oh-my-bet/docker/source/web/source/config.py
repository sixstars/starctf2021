import pymongo
from ftplib import FTP
import json

class Config(object):

    def ftp_login(self):
        ftp = FTP()
        ftp.connect("172.20.0.2", 8877)
        ftp.login("fan", "root")
        return ftp

    def callback(self,*args, **kwargs):
        data = json.loads(args[0].decode())
        self.data = data

    def get_config(self):
        f = self.ftp_login()
        f.cwd("files")
        buf_size = 1024
        f.retrbinary('RETR {}'.format('config.json'), self.callback, buf_size)

    def __init__(self):
        self.get_config()
        data = self.data

        self.secret_key = data['secret_key']
        self.SECRET_KEY = data['secret_key']
        self.DEBUG = data['DEBUG']
        self.SESSION_TYPE = data['SESSION_TYPE']
        remote_mongo_ip = data['REMOTE_MONGO_IP']
        remote_mongo_port = data['REMOTE_MONGO_PORT']
        self.SESSION_MONGODB = pymongo.MongoClient(remote_mongo_ip, remote_mongo_port)
        self.SESSION_MONGODB_DB = data['SESSION_MONGODB_DB']
        self.SESSION_MONGODB_COLLECT = data['SESSION_MONGODB_COLLECT']
        self.SESSION_PERMANENT = data['SESSION_PERMANENT']
        self.SESSION_USE_SIGNER = data['SESSION_USE_SIGNER']
        self.SESSION_KEY_PREFIX = data['SESSION_KEY_PREFIX']

        self.SQLALCHEMY_DATABASE_URI = data['SQLALCHEMY_DATABASE_URI']
        self.SQLALCHEMY_TRACK_MODIFICATIONS = data['SQLALCHEMY_TRACK_MODIFICATIONS']

        self.REDIS_URL = data['REDIS_URL']
