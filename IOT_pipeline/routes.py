from flask import Blueprint, request
from .serial import switch_led, send_text, get_texts
import json
from flask_cors import cross_origin
import time

from .extensions import socketio

bp = Blueprint('index', __name__)

@bp.route("/")
def index():
    return "Hello World"

@bp.route("/led", methods=['POST'])
@cross_origin()
def led():
    led = json.loads(request.data)
    switch_led(led['led'])
    return "OK"

@socketio.on('connect')
def socket_connect():
    print('Client connected')
    get_texts()


@bp.route("/text", methods=['POST'])
@cross_origin()
def text():
    text = json.loads(request.data)
    send_text(text['text'])
    get_texts()
    return "OK"