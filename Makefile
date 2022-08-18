monitor:
	arduino-cli monitor -p /dev/ttyACM0

build: motor_driver.ino
	arduino-cli compile -b arduino:avr:uno motor_driver
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyACM0 motor_driver

compile: motor_driver.ino
	arduino-cli compile -b arduino:avr:uno motor_driver

upload: motor_driver.ino
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyACM0 motor_driver
