from flask import Flask
import serial


app = Flask(__name__)

@app.route("/")

def getAllValues():
	sensorValues = "{ \"RWI\" : 71.1, \"RWO\" : 71.2, \"CEH\" : 71.3, \"CLH\" : 71.4, \"CYL\" : 71.5, \"ENR\" : 71.6, \"OIL\" : 71.7, \"EGT\" : 71.8, \"RPM\" : 71.6}"
	return sensorValues



if __name__ == "__main__":
	app.run(host='0.0.0.0', port=81, debug=True)

