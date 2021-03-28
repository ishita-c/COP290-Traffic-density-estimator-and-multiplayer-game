#takes two text files as input and prints the error value obtained by taking average of absolute difference between the corresponding points

error=[]	# maintains the absolute error between corresponding points
s1=input("Enter filename- output of task2: ")
s2=input("Enter filename- output of task3: ")
# Using readlines()
file1 = open(s1, 'r')
file2 = open(s2, 'r')

while True:
	line1 = file1.readline()
	line2 = file2.readline()
	# end of file is reached
	if not line1 or not line2:
		if not line1 and not line2:
			print("Execution completed")
			print(sum(error)/len(error))
			break
		elif not line1:
			print("Error: output file of task 2 reached an end before output file of task 3")
			break
		elif not line2:
			print("Error: output file of task 3 reached an end before output file of task 2")
			break

	l1=line1.split(",")
	l2=line2.split(",")
	if l1[0]!=l2[0]:
		print("Error: unexpected time mismatch found in output files")
		break
	else:
		error.append(abs(int(l1[1])-int(l2[1])))

file1.close()
file2.close()
