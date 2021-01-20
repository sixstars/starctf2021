from exts import db


class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(255), unique=True)
    password = db.Column(db.String(255), nullable=False)
    avatar = db.Column(db.String(255), nullable=False)

    def __repr__(self):
        return '<User %r>' % self.username