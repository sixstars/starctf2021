from exts import db


class User(db.Model):

    __tablename__ = 'users'

    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.String(255), unique=True)
    username = db.Column(db.String(255), unique=True)


class Note(db.Model):

    __tablename__ = 'notes'

    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.String(255), unique=True)
    note_id = db.Column(db.String(255), unique=True)
    text = db.Column(db.String(255), unique=False)
    title = db.Column(db.String(255), unique=False)
    post_at = db.Column(db.String(255), unique=False)
    prv = db.Column(db.String(255), unique=False)
