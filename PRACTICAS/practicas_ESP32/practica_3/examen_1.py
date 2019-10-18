import serial
from time import sleep

ser = serial.Serial ("/dev/serial0", 115200) #Open port with baud rate
volt = 0.0
kelvin = 0.0
celsius = 0.0

while True:
    received_data = ser.read()              #read serial port
    sleep(0.03)
    data_left = ser.inWaiting()             #check for remaining byte
    received_data += ser.read(data_left)
    dataInfo =  received_data.split(',')

    dataInfo[2] = dataInfo[2].split('\x00')[0] #Clean last character

    try:
        volt = float(dataInfo[0])
        kelvin = float(dataInfo[1])
        celsius = float(dataInfo[2])
    except ValueError:
        print ("Argumentos no valido")
        continue

    ser.write('--- Lectura de Temperatura FI         --\n')
    ser.write('----------------------------------------\n') #transmit data serially
    ser.write('--  %6.2f [mV]                      --\n'% volt)
    ser.write('--  %3.2f [K]                        --\n'% kelvin)
    ser.write('--  %3.2f [C]                         --\n'% celsius)
    ser.write('----------------------------------------\n')