import matplotlib.pyplot as plt
m=int(input("Enter method number: "))
x = []
y = []
p1=[]
p=[]
factor=0.125
j=1
for line in open("utility_m"+str(m)+".txt", 'r'):
    lines = [i for i in line.split(",")]
    p.append(factor*j)
    #p1.append(int(lines[0])*100/16)
    x.append(float(lines[1]))
    y.append(float(lines[2]))
    j=j+1
plt.subplot(2,1,1)
plt.title("Utility vs sizefactor plot of Method "+str(m))
plt.xlabel('sizefactor')
plt.ylabel('Utility(1/(avg error per frame))')
plt.yticks(y)
plt.plot(p, y, marker = 'o', c = 'g')
plt.subplot(2,1,2)
plt.title("Runtime Vs sizefactor plot of Method "+str(m))
plt.xlabel('size factor')
plt.ylabel('Runtime(s)')
plt.plot(p,x)
print("Press Ctrl+S to save figure")  
plt.show()

