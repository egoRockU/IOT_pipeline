from flask import Blueprint, request
from .serial import switch_led
import json
from flask_cors import cross_origin

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