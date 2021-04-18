import matplotlib.pyplot as plt

m=int(input("Enter method number: "))
x = []
y = []
p1=[]
p=[]

for line in open("cpu_m"+str(m)+".txt", 'r'):
    lines = [i for i in line.split(",")]
    p.append(int(lines[0]))
    p1.append(int(lines[0])*100/16)
    x.append(float(lines[1]))
    y.append(float(lines[2]))
    
plt.subplot(2,1,1)
plt.title("CPU Utilisation vs numThreads plot of Method "+str(m))
plt.xlabel('Number of Threads')
plt.ylabel('CPU Utilization (in %)')
plt.scatter(p, x)

plt.subplot(2,1,2)
plt.title("CPU Utilisation vs Runtime plot of Method "+str(m))
plt.xlabel('Runtime(s)')
plt.ylabel('CPU Utilization (in %)')
plt.scatter(y,x, marker = 'o', c = p1,cmap='viridis')

print("Press Ctrl+S to save figure")  
plt.show()

