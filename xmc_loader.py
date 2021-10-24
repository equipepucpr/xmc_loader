import serial
from time import time
import sys
import os
from array import array

SERIAL = "COM23"
BAUDRATE = 115200
TIMEOUT = 200

if (len(sys.argv) < 2):
    print("ERROR: Missing .bin file!")
    exit(1)

if (len(sys.argv) > 2):
    print("ERROR: Unexpected arguments!")
    exit(1)

binName = sys.argv[1]
if not(binName.endswith(".bin")):
    print("ERROR: Only .bin files are supported!")
    exit(1)

try:
    binFile = open(binName, "rb")
except Exception:
    print("ERROR: Could not open", binName)
    exit(1)

binFile.seek(0, os.SEEK_END)
binSize = binFile.tell()
binFile.seek(0, 0)

print("File size:", binSize, "bytes")

sizeArray = binSize.to_bytes(4, byteorder='little')

binData = array('B')
binData.fromfile(binFile, binSize)
binFile.close()

ser = serial.Serial(port=SERIAL, baudrate=BAUDRATE, timeout=TIMEOUT/1000.0)

while (ser.read()):
    pass

while (True):
    ser.write(bytearray([0x0, 0x6C]))

    byte = ser.read()
    if (byte):
        if (byte[0] != 0x5d):
            print("ERROR: Expected BSL_ID 0x5d, received:", hex(byte[0]))
            exit(1)
        break
    
print("Sending length...")
ser.write(bytearray(sizeArray))
print("Length: ", sizeArray)

byte = ser.read()
if (byte):
    if (byte[0] != 0x01):
        print("ERROR: Expected BSL_OK 0x01, received:", hex(byte[0]))
        exit(1)
else:
    print("ERROR: No response to length")
    exit(1)

print("Sending program...")
ser.write(binData)

byte = ser.read()
if (byte):
    if (byte[0] != 0x01):
        print("ERROR: Expected BSL_OK 0x01, received:", hex(byte[0]))
        exit(1)
else:
    print("ERROR: No response to program flash")
    exit(1)

print("Success!")