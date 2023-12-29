import serial
import sys

result = []


# Enumerates available ports
def list_ports():
    result.append("default")
    if sys.platform.startswith('win'):                  # check os (windows)
        ports = ['COM%s' % (i + 1) for i in range(256)]
    else:
        raise EnvironmentError("Unsupported platform")

    for port in ports:
        try:
            ser = serial.Serial(port)
            ser.close()                         # All ports closed
            result.append(port)
        except:                                 # Capture Errors
            pass
