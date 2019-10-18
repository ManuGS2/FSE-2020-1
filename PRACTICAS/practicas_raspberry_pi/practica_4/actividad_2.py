import serial
from time import sleep

ser = serial.Serial ("/dev/serial0", 115200) #Open port with baud rate
while True:
    received_data = ser.read()              #read serial port
    sleep(0.03)
    data_left = ser.inWaiting()             #check for remaining byte
    received_data += ser.read(data_left)

    dataInfo =  received_data.split(',')

    if (len(dataInfo) < 4):
        print ("Argumentos insufcientes")
        continue

    if (str.isdigit(dataInfo[0])):
    if not(int(dataInfo[0]) >= 0 and int(dataInfo[0]) <= 4094):
            print ("Primer argumento no valido, ingrese un entero entre 0 y 4094")
            continue

    if (str.isdigit(dataInfo[2]) and not (int(dataInfo[2]) == 0 or int(dataInfo[2]) == 1)):
        print ("Tercer argumento no valido, ingrese un 1 o 0")
        continue

    try:
        float(dataInfo[3])
        if not(float(dataInfo[3]) >= 0.0 and float(dataInfo[3]) <= 3.3):
            print ("Cuarto argumento no valido, ingrese flotante entre 0.0 y 3.3")
            continue
    except ValueError:
        print ("Cuarto argumento no valido, ingrese flotante entre 0.0 y 3.3")
        continue

    print("Numero entero: " + dataInfo[0])
    print("Iniciales: " + dataInfo[1])
    print("Bandera: " + dataInfo[2])
    print("Voltaje: " + dataInfo[3])
