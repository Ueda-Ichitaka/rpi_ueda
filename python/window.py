from tkinter import *
import RelayControl

window = Tk()
window.title("Relay control")
window.geometry("500x500")

txbPin1 = Entry(window)
txbPin2 = Entry(window)
txbDelay = Entry(window)    
txbLoopDur = Entry(window)

lblPin1 = Label(window, text="Pin 1")
lblPin2 = Label(window, text="Pin 2")
lblDelay = Label(window, text="Delay")
lblLoopDur = Label(window, text="Loop duration")



bblink = Button(window, text="Blink", command=blink(11, 16, 1))
bswitchblink = Button(window, text="Switchblink")
ballOn = Button(window, text="All On")
ballOff = Button(window, text="All Off")
bapply = Button(window, text="Apply values")

bblink.pack()
bswitchblink.pack()
ballOn.pack()
ballOff.pack()

lblPin1.pack()
txbPin1.pack()
lblPin2.pack()
txbPin2.pack()
lblDelay.pack()
txbDelay.pack()
lblLoopDur.pack()
txbLoopDur.pack()

bapply.pack()

mainloop()
