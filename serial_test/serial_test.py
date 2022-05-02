import serial
from time import sleep

num_bytes = 30
buffer = ''

if __name__ == '__main__':

    arduino = serial.Serial('/dev/tty.usbmodem1101', 9600, timeout=2)
    arduino.reset_input_buffer()

while True:
    # arduino.write('hello from python'.encode())
    
    # print(str(arduino.readline()))

    temp_string = str(arduino.readline())
    for char in temp_string:
        print(char, end='')
    print('\n')
    sleep(2)
