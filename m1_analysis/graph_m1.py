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
plt.title("Utility vs parameter(x) "+str(m))
plt.xlabel('Number of frames skipped + 1')
plt.ylabel('Utility(1/(avg error per frame))')
plt.yticks(y)
plt.scatter(p, y, marker = 'o', c = p1,cmap='viridis')
#plt.colorbar()
plt.subplot(2,1,2)
plt.title("Runtime Vs parameter(x) "+str(m))
plt.xlabel('Number of frames skipped + 1')
plt.ylabel('Runtime(s)')
plt.scatter(p,x)
print("Press Ctrl+S to save figure")  
plt.show()

