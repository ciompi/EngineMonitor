
from flask import Flask
import serial


port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)


app = Flask(__name__)

@app.route("/")



def getValues():
	port.write("get")	
	sensorValues = port.readline()
	return sensorValues



if __name__ == "__main__":
	app.run(host='0.0.0.0', port=80, debug=True)

