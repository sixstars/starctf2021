from flask_wtf import FlaskForm
from wtforms import *
from wtforms.validators import DataRequired


class CreateNoteForm(FlaskForm):
    username = StringField('Enter username', validators=[DataRequired()])
    title = StringField('Note Title', validators=[DataRequired()])
    body = TextAreaField('Write something', validators=[DataRequired()])
    private = BooleanField('Private', default='0')
    submit = SubmitField('Post!')


