import serial;
from tkinter import *;
serial_commands = {"a" : 1, "d" : 2, "w" : 3, "s" : 4, "i" : 5, "k" : 6};

def keyup(e):
    if e.char in serial_commands.keys():
        ser.write(bytes([serial_commands[e.char]]));
        

root = Tk();

root.bind("<KeyRelease>", keyup);
try:
    ser = serial.Serial('/dev/ttyUSB1');
    ser.baudrate = 115200;
except:
    print("The program was unable to create a connection with the serial port");
