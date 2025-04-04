from flask import Blueprint, request
from .serial import switch_led, send_text
import json

from .extensions import socketio

bp = Blueprint('index', __name__)

@bp.route("/")
def index():
    return "Hello World"

@bp.route("/led", methods=['POST'])
def led():
    led = json.loads(request.data)
    switch_led(led['led'])
    return "OK"

@socketio.on('connect')
def socket_connect():
    print('Client connected')

@bp.route("/text", methods=['POST'])
def text():
    text = json.loads(request.data)
    send_text(text['text'])
    return "OK"