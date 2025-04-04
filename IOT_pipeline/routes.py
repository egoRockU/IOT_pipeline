from flask import Blueprint, request
from .serial import switch_led
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