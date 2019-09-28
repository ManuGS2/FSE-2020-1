import os
import sys

def main():
    if len(sys.argv) != 3:
        print('Argumentos insuficientes.')
        return 1

    usbList = os.listdir('/media/pi')

    if len(usbList) == 0:
        print('No existe ningún USB conectado.')
        return 2

    usbDir = '/media/pi/' + usbList[0] + '/' + sys.argv[1] + '.csv'

    try:
        timesToWrite = int(sys.argv[2])
    except Exception as e:
        print('Segundo argumento no es un numero.')
        return 3

    f = open(usbDir, 'w+')
    for i in range(timesToWrite):
        f.write(str(i)+','+'HolaUSB'+','+'data'+str(i)+'\n')

    f.close()

if __name__ == "__main__":
    main()
