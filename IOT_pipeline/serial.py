from serial import Serial
from .extensions import socketio

SERIAL_PORT = '/dev/ttyUSB0'

serial = Serial()
serial.baudrate = 9600
serial.port = SERIAL_PORT
serial.timeout = 1

def open_serial_connection():
    try:
        serial.open()
    except Exception as e:
        print(f"Failed to open serial port: {e}")

def serial_listen():
    if (serial.is_open == False):
        print('Serial is not Open')
        return
    
    while True:
        if serial.in_waiting:
            data = serial.readline().decode('utf8').strip()

            if 'Water Status' in data:
                water_status = data.split(': ')[1]
                message = "water status: " + water_status
                print(message)
                socketio.emit('water_status', message)

def switch_led(led_name):
    if (serial.is_open):
        message = 'led: ' + led_name + "\n"
        serial.write(message.encode())
        print('Sent successfully')
    else:
        print('Serial is not Open.')
    