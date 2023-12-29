import sys
import ports2

import serial
import time
import keyboard
from PyQt5.QtWidgets import *
from Interface import *


class MainWindow:

    # private global variables
    __buttonvalue = 0
    __ser = serial.Serial()

    def __init__(self):
        self.pencere = QMainWindow()
        self.arayuz = Ui_MainWindow()
        self.arayuz.setupUi(self.pencere)

        # pushbutton connect function
        self.arayuz.pushButton.clicked.connect(self.click)
        # verticalSlider connect function
        self.arayuz.verticalSlider.valueChanged.connect(self.readslider)
        self.message = QMessageBox(self.pencere)
        ports2.list_ports()
        self.portsadd()
        self.baudrateadd()
        self.pencere.show()

    def readslider(self):

        if self.__ser.isOpen():
            value = self.arayuz.verticalSlider.value()
            data = str(value)
            byte_data = data.encode()
            self.__ser.write(byte_data)
            stm = self.__ser.readline().decode(encoding='utf-8', errors='ignore')
            print(stm, end="")
            
        else:
            self.MessageSet("Not Connected")

    def click(self):

        if self.arayuz.comboBox.currentText() == "default" or self.arayuz.comboBox_2.currentText() == "default":
            self.MessageSet("Enter your missing information!")
        else:
            if self.__buttonvalue == 0:
                self.__buttonvalue = 1
                self.__ser = serial.Serial(self.arayuz.comboBox.currentText(), int(self.arayuz.comboBox_2.currentText()), timeout=1)
                self.arayuz.pushButton.setStyleSheet(
                    "background-color: red;\n"
                    "border-color: rgb(255, 255, 255);\n"
                    "font: 11pt \"Calibri\";\n"
                    "")

                if self.__ser.isOpen() == True:
                    print("port open")

            else:
                self.__buttonvalue = 0
                self.__ser.close()
                self.arayuz.pushButton.setStyleSheet(
                    "background-color: qlineargradient(spread:reflect, x1:0.244, y1:0.21, x2:1, y2:0, stop:0.0447761 rgba(92, 150, 113, 255));\n"
                    "border-color: rgb(255, 255, 255);\n"
                    "font: 11pt \"Calibri\";\n"
                    "")

                if self.__ser.isOpen() == False:
                    print("port close")

    def MessageSet(self, content):
        self.message.setText(content)
        self.message.setStyleSheet("color:white")
        self.message.setWindowTitle("Warning Message")
        self.message.setIcon(self.message.Warning)
        self.message.button(self.message.Ok)
        self.message.show()

    def portsadd(self):
        for i in ports2.result:
            self.arayuz.comboBox.addItem(i)

    def baudrateadd(self):
        self.arayuz.comboBox_2.addItems(["default", "300", "600", "1200", "2400", "4800", "9600", "14400", "19200",
                                        "28800", "38400",
                                        "57600", "115200"])


if __name__ == "__main__":
    app = QApplication(sys.argv)
    dc = MainWindow()
    sys.exit(app.exec())

