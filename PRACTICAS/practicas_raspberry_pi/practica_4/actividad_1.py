import serial

ser = serial.Serial ("/dev/serial0", 115200) #Open port with baud rate
for i in range(0,16):
	ser.write(str(i) + ': FSE 2020-1 Comunicacion UART RPi - FSE\n') #transmit data serially 