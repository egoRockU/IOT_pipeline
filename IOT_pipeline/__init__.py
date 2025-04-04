from flask import Flask
from .routes import bp
from .serial import open_serial_connection

def create_app(test_config=None):
    app = Flask(__name__, instance_relative_config=True)

    app.config.from_mapping(
        SECRET_KEY = 'secret'
    )

    app.register_blueprint(bp)
    open_serial_connection()

    return app

if __name__ == '__main__':
    app = create_app()