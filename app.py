import serial
from flask import Flask, render_template, request
from flask_socketio import SocketIO
import os
fronecnddir = os.path.join("templates","static")
app = Flask(__name__,template_folder="templates",static_folder=fronecnddir)

app.config['SECRET_KEY'] = 'secret-key'
socketio = SocketIO(app)

# Set COM value
port = '/dev/cu.usbmodem1101'  # COM Port
baud_rate = 9600  # Baud rate

# Open port connections
ser = serial.Serial(port, baud_rate)

@app.route('/')
def index():
    return render_template('index.html')


@socketio.on('connect')
def handle_connect():
    print('Client connected')


@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')


@app.route('/send_values', methods=['POST'])
def send_value():
    values = request.get_json()
    number1 = values['number1']
    number2 = values['number2']

    ser.write((str(number1) + "," + str(number2) + "\n").encode())

    return '', 200


@app.route('/send_DOvalues', methods=['POST'])
def send_DOvalue():
    values = request.get_json()
    number1 = values['number3']
    number2 = values['number4']

    ser.write((str(number1) + "," + str(number2) + "\n").encode())

    return '', 200


@app.route('/send_ORPvalues', methods=['POST'])
def send_ORPvalue():
    values = request.get_json()
    number1 = values['number5']
    number2 = values['number6']

    ser.write((str(number1) + "," + str(number2) + "\n").encode())

    return '', 200

# @app.route('/send_WPvalues', methods=['POST'])
# def send_ORPvalue():
#     values = request.get_json()
#     number1 = values['number5']
#     number2 = values['number6']
#     number3 = values['number7']
#     number4 = values['number8']
#     number5 = values['number9']
#     ser.write((str(number1) + "," + str(number2) + ";" +
#               str(number3) + "_" + str(number4) + "=" + str(number5) + "\n").encode())

#     return '', 200



def listen_and_emit_data():
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').rstrip()
            socketio.emit('data', {'value': data})
            print(data)
    ser.close()


if __name__ == '__main__':
    socketio.start_background_task(listen_and_emit_data)
    socketio.run(app)
