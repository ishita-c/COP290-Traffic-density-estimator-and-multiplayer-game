#takes two text files as input and prints the error value obtained by taking average of absolute difference between the corresponding points

error=[]	# maintains the absolute error between corresponding points
s1=input("Enter filename- output of task2: ")
print("Input parameteras in 6 decimal places");
output= open("utility_m2.txt", 'w')
file3=open("parameters.txt")
line=file3.readline()
while(line):
	l=line.split("x")
	l[1]=l[1].split("\n")[0]
	x=l[0]
	y=l[1]
	s2="output_m2_"+str(x)+"x"+str(y)+".txt"
	# Using readlines()
	file1 = open(s1, 'r')	
	file2 = open(s2, 'r')
	error=0
	line_no=1
	runtime="";
	while True:
		line1 = file1.readline()
		line2 = file2.readline()	
		# end of file is reached
		if not line1 or not line2:
			if not line1 and not line2:
				print("Execution completed")
				output.write(str(x)+"x"+str(y)+", "+ str(runtime)+", "+ str((line_no-1)/error)+"\n") #utility=1/error
				break	
			elif not line1:
				print("Error: output file of task 2 reached an end before output file of task 3")
				break
			elif not line2:
				print("Error: output file of task 3 reached an end before output file of task 2")
				break
		l1=line1.split(",")
		l2=line2.split(",")
		if l1[0]!=l2[0] and len(l1)!=1:
			print("Error: unexpected time mismatch found in output files at"+str(line_no))
			break
		elif len(l1)==1 and len(l2)==1:
			runtime=l2[0]
			continue
		else:
			error+=abs(float(l1[1])-float(l2[1]))
		line_no+=1
	line=file3.readline()
	file1.close()
	file2.close()
file3.close()
output.close()
	
