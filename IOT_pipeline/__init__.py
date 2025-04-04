from flask import Flask
from .routes import bp
from .serial import open_serial_connection, serial_listen
import threading

from .extensions import socketio

def create_app(test_config=None):
    app = Flask(__name__, instance_relative_config=True)

    app.config.from_mapping(
        SECRET_KEY = 'secret'
    )

    app.register_blueprint(bp)
    open_serial_connection()

    serial_listen_thread = threading.Thread(target=serial_listen, daemon=True)
    serial_listen_thread.start()

    socketio.init_app(app, cors_allowed_origins='*')

    return app

if __name__ == '__main__':
    app = create_app()