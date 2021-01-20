from flask_wtf import FlaskForm
from wtforms import *
from wtforms.validators import DataRequired


class LoginForm(FlaskForm):
    username = StringField('Give me your favourite username', validators=[DataRequired()])
    password = StringField('Give me your password quietly 👻', validators=[DataRequired()])
    avatar = StringField('Choose a cute avatar!', validators=[DataRequired()])
    submit = SubmitField('Go!')


