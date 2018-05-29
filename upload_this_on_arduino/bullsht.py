import serial
import time

ser = serial.Serial('COM4', 9600)
time.sleep(3)
ser.timeout = 5
text = 'temp'.encode()
ser.write(text)