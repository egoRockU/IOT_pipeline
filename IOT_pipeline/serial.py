from serial import Serial

SERIAL_PORT = '/dev/ttyUSB0'

serial = Serial()
serial.baudrate = 9600
serial.port = SERIAL_PORT
serial.timeout = 1

def open_serial_connection():
    try:
        serial.open()
        print("Serial Connection Success!")
        return True
    except Exception as e:
        print(f"Failed to open serial port: {e}")
        return False


def switch_led(led_name):
    if (serial.is_open):
        message = 'led: ' + led_name + "\n"
        serial.write(message.encode())
        print('Sent successfully')
    else:
        print('Serial is not Open.')
    