#takes two text files as input and prints the error value obtained by taking average of absolute difference between the corresponding points
m=int(input("Enter method number: "))
start=int(input("Enter first parameter: "))
end=int(input("Enter last parameter: "))
s=input("Enter filename- output of task2: ")

output=open("utility_m"+str(m)+".txt", "w") # parameter, runtime, utility

for i in range (start, end+1):
	error=0 # maintains the absolute error between corresponding points
	# Using readlines()
	file1 = open("output_m"+str(m)+"_"+str(i)+".txt", 'r')
	file2 = open(s, 'r')
	line_no=1
	while True:
		line1 = file1.readline()
		line2 = file2.readline()
		# end of file is reached
		if not line1 or not line2:
			if not line1 and not line2:
				print("Execution completed")
				output.write(str(i)+", "+ str(runtime)+", "+ str((line_no-1)/error)+"\n") #utility=1/error
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
			runtime=l1[0]
			continue
		else:
			error+=abs(float(l1[1])-float(l2[1]))
		line_no+=1

	file1.close()
	file2.close()
	
output.close()
