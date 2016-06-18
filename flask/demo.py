from flask import Flask

app = Flask(__name__)

@app.route('/')
def index_page():
    return "Index Page"

@app.route('/hello')
def hello_world():
    return "Hello, World!"

@app.route('/users/<username>')
def show_user_profile(username):
    return "User %s" % username

@app.route('/posts/<int:post_id>')
def show_post(post_id):
    return "Post %d" % post_id

@app.route('/posts/<int:post_id>/comments/<int:comment_id>')
def show_post_comment(post_id, comment_id):
    return "Post %d Comment %d" % (post_id, comment_id)

@app.route('/pass')
def passssssssssssssssssss():
    pass

@app.route('/comehere')
def here():
    return 'come here'

@app.route('/options', methods=["OPTION"])
def options():
    return "Options"

