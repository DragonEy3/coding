import platform
x=0
if platform.python_version()[0]=='3' and int(platform.python_version()[2])>=2:
	from tkinter import filedialog
	from tkinter import *
	x=1
else :
	from Tkinter import *
	import tkFileDialog

fColor = '#729dbf'

root = Tk()
root.title("Dive Text Editor")
root["bg"] = '#3a3a3a'


def saveas():
    global text  
    t = text.get("1.0", "end-1c")
    if x==1:
    	savelocation=filedialog.asksaveasfilename()

    else :
    	savelocation=tkFileDialog.asksaveasfilename()

    file1=open(savelocation, "w+")
    file1.write(t)
    file1.close()

def openas():
    if x==1:
    	filename = filedialog.askopenfilename()
    else:
    	filename = tkFileDialog.askopenfilename()

    fileHandle = open(filename, 'r')
    text.delete('1.0', END)
    t = fileHandle.readlines()
    for line in t:
    	text.insert(END,line)
    fileHandle.close()

def quit():
	sys.exit()


frame = Frame(root)
frame.pack()

button=Button(frame, text="Save As", bg='#161616', fg=fColor, padx=10,  command=saveas) 
button.pack(side=LEFT)
button=Button(frame, text="Quit", bg='#161616', fg=fColor, padx=10, command=quit) 
button.pack(side=LEFT)
button=Button(frame, text="Open", bg='#161616', fg=fColor, padx=10, command=openas) 
button.pack(side=LEFT)

text = Text(root, bg='#161616', fg=fColor, font='consolas' , selectbackground='#3a3a3a', insertbackground=fColor)
text.pack()


root.mainloop()