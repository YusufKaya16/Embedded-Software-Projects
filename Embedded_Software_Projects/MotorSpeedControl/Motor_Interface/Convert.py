from PyQt5 import uic

with open("Interface.py", "w", encoding='utf-8') as fout:
    uic.compileUi("motor_driver.ui", fout)
