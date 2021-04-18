import matplotlib.pyplot as plt
m=int(input("Enter method number: "))
x = []
y = []
p1=[]
p=[]
for line in open("utility_m"+str(m)+".txt", 'r'):
    lines = [i for i in line.split(",")]
    p.append(int(lines[0]))
    p1.append(int(lines[0])*100/16)
    x.append(float(lines[1]))
    y.append(float(lines[2]))
plt.subplot(2,1,1)
plt.title("Utility vs Runtime plot of Method "+str(m))
plt.xlabel('Runtime(s)')
plt.ylabel('Utility(1/(avg error per frame))')
plt.yticks(y)
plt.scatter(x, y, marker = 'o', c = p1,cmap='viridis')
#plt.colorbar()
plt.subplot(2,1,2)
plt.title("Runtime Vs numThreads plot of Method "+str(m))
plt.xlabel('Number of threads')
plt.ylabel('Runtime(s)')
plt.scatter(p,x)
#plt.legend(loc='upper right', frameon=True)
#j=len(x)
#for i in range(j):
#	plt.annotate(str(p[i]), (x[i], y[i]))
print("Press Ctrl+S to save figure")  
plt.show()

