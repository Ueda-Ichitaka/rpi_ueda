import sys
import time
import math
import RPi.GPIO as GPIO
from tkinter import *

class GUI(Frame):
    def __init__(self,parent,**kw):
        Frame.__init__(self,parent,width=150,height=20,relief=SUNKEN,bd=1,padx=5,pady=5)
        self.parent = parent
        self.configure(**kw)

        self.statePin1 = 1
        self.statePin2 = 1
        
        self.lblPin1 = Label(self, text="Pin 1")
        self.lblPin2 = Label(self, text="Pin 2")
        self.lblDur = Label(self, text="Loop Duration")
        self.lblDelay = Label(self, text="Delay")
        self.txbPin1 = Entry(self)
        self.txbPin2 = Entry(self)
        self.txbDur = Entry(self)
        self.txbDelay = Entry(self)
        self.cmdPin1 = Button(self, text="Pin 1 ON/OFF", command=self.togglePin1)
        self.cmdPin2 = Button(self, text="Pin 2 ON/OFF", command=self.togglePin2)
        self.cmdBlink = Button(self, text="Blink", command=self.blink)
        self.cmdSBlink = Button(self, text="Switchblink", command=self.sblink)
        
        self.lblPin1.grid(column=0,row=0)
        self.txbPin1.grid(column=1,row=0)
        self.lblPin2.grid(column=0,row=1)
        self.txbPin2.grid(column=1,row=1)
        self.lblDur.grid(column=2,row=0)
        self.txbDur.grid(column=3,row=0)
        self.lblDelay.grid(column=2,row=1)
        self.txbDelay.grid(column=3,row=1)
        self.cmdPin1.grid(column=1,row=3)
        self.cmdPin2.grid(column=1,row=4)
        self.cmdBlink.grid(column=2,row=3)
        self.cmdSBlink.grid(column=2,row=4)

    def togglePin1(self):
        if(self.statePin1 == 0):
            GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)
            self.statePin1 = 1
            return
        if(self.statePin1 == 1):
            GPIO.output(int(self.txbPin1.get()), GPIO.LOW)
            self.statePin1 = 0
            return
            
    def togglePin2(self):
        if(self.statePin2 == 0):
            GPIO.output(int(self.txbPin2.get()), GPIO.HIGH)
            self.statePin2 = 1
            return
        if(self.statePin2 == 1):
            GPIO.output(int(self.txbPin2.get()), GPIO.LOW)
            self.statePin2 = 0
            return

    def blink(self):
        GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)
        GPIO.output(int(self.txbPin2.get()), GPIO.HIGH)
        for x in range(0, int(self.txbDur.get())):
            GPIO.output(int(self.txbPin1.get()), GPIO.LOW)
            GPIO.output(int(self.txbPin2.get()), GPIO.LOW)
            time.sleep(float(self.txbDelay.get()))
            GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)
            GPIO.output(int(self.txbPin2.get()), GPIO.HIGH)
            time.sleep(float(self.txbDelay.get()))
        return

    def sblink(self):
        GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)
        GPIO.output(int(self.txbPin2.get()), GPIO.HIGH)
        for x in range(0, int(self.txbDur.get())):
            GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)
            GPIO.output(int(self.txbPin2.get()), GPIO.LOW)
            time.sleep(float(self.txbDelay.get()))
            GPIO.output(int(self.txbPin1.get()), GPIO.LOW)
            GPIO.output(int(self.txbPin2.get()), GPIO.HIGH)
            time.sleep(float(self.txbDelay.get()))
        GPIO.output(int(self.txbPin1.get()), GPIO.HIGH)    
        return

class RelayControl(Frame):
    def __init__(self,parent=None,**kw):
        Frame.__init__(self,parent,**kw)
        self.parent = parent    
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(11, GPIO.OUT)
        GPIO.setup(16, GPIO.OUT)
        GPIO.output(11, GPIO.HIGH)
        GPIO.output(16, GPIO.HIGH)
        self.gui = GUI(self)
        self.gui.grid(row=5, column=5)
        
    def onClose(self):
        try:
            GPIO.cleanup()
        except RuntimeWarning as e:
            print(e)
        self.destroy()
        self.parent.destroy()



def main():
    root = Tk()
    root.title("Relay Control")
    rc = RelayControl(root)
    rc.grid()
    root.protocol("WM_DELETE_WINDOW", rc.onClose)
    root.mainloop()

if __name__ == '__main__':
    main()
