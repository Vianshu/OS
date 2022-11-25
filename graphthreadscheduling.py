import math
import matplotlib.pyplot as plt
import numpy as np
f1=open("FIFO.txt","r")
f2=open("RR.txt","r")
f3=open("OTHER.txt","r")
#RR PLOTS WHEN FIFO IS 0 AND OTHER IS 0
x=[0,1,10]
y=[1.886691,3.901259,1.901199]
plt.bar(x,y,color=['green','red','blue'])
plt.xlabel("FIFO OTHER AND RR PRIORITIES OF FIFO=OTHER=0 AND RR=10")
plt.ylabel("Runtimes")
plt.show()
x=[0,1,20]
y=[1.502099,4.506152,1.505819]
plt.bar(x,y,color=['green','red','blue'])
plt.xlabel("FIFO OTHER AND RR PRIORITIES OF FIFO=OTHER=0 AND RR=20")
plt.ylabel("Runtimes")
plt.show()
x=[0,1,10]
y=[1.397941,1.398021,2.234742]
plt.bar(x,y,color=['green','red','blue'])
plt.xlabel("RR OTHER AND FIFO PRIORITIES OF RR=OTHER=0 AND FIFO=10")
plt.ylabel("Runtimes")
plt.show()
x=[0,1,20]
y=[1.789066,3.789129,1.77707]
plt.bar(x,y,color=['green','red','blue'])
plt.xlabel("RR OTHER AND FIFO PRIORITIES OF RR=OTHER=0 AND FIFO=20")
plt.ylabel("Runtimes")
plt.show()