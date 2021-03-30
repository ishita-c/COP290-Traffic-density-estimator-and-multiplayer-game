import matplotlib.pyplot as plt
m=int(input("Enter method number: "))
x = []
y = []
for line in open("utility_m"+str(m)+".txt", 'r'):
    lines = [i for i in line.split(",")]
    x.append(float(lines[1]))
    y.append(float(lines[2]))
      
plt.title("Utility vs Runtime plot of Method "+str(m))
plt.xlabel('Runtime')
plt.ylabel('Utility')
plt.yticks(y)
plt.plot(x, y, marker = 'o', c = 'g')
  
plt.show()
print("Press Ctrl+S to save figure")
