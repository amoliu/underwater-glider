import serial;
from tkinter import *;
serial_commands = {"a" : 1, "d" : 2, "w" : 3, "s" : 4, "i" : 5, "k" : 6};

def keyUp(e):
    if e.char in serial_commands.keys():
        ser.write(bytes([serial_commands[e.char]]));

def initialise():
    try:
        ser = serial.Serial('/dev/ttyUSB0');
        ser.baudrate = 115200;
    except Exception as e:
        raise Exception(e);

    root = Tk();
    root.bind("<KeyRelease>", keyUp);

if __name__ == "__main__":
    initialise();
