import os

direc = os.getcwd() # Get current working directory
ext = '.txt' # Select your file delimiter
direc=direc+'/samples'
#print direc
#os.system("rm "+"logstatus")

os.system("mkdir "+"logstatus")

txt_files = [i for i in os.listdir(direc) if os.path.splitext(i)[1] == ext]
n=0

os.system("g++ -o fileheading fileheading.cpp")
os.system("g++ -o comparator comparator.cpp")

# Iterate over your txt files
for f in txt_files:
	n=n+1
#print n

for i in range(0,n):
	os.system("./fileheading "+txt_files[i])

for i in range(0,n):
	#print txt_files[i]	
	for j in range(i+1,n):
		os.system("./comparator "+txt_files[i]+" "+txt_files[j])

remove_file1=direc+'/tmp1.txt'
remove_file2=direc+'/tmp2.txt'
os.system("rm "+remove_file1)
os.system("rm "+remove_file2)

########################################################################################################
#				WEIGHTED SCORE
########################################################################################################

direc = os.getcwd() # Get current working directory
ext = '.txt' # Select your file delimiter
direc=direc+'/logstatus'
remove_file1=direc+'/final_logfile.txt'
os.system("rm "+remove_file1)

#print direc

txt_files = [i for i in os.listdir(direc) if os.path.splitext(i)[1] == ext]
n=0

os.system("g++ -o threshold_checker threshold_checker.cpp")

# Iterate over your txt files
for f in txt_files:
	n=n+1
#print n

for i in range(0,n):
	os.system("./threshold_checker "+txt_files[i])

print '\n\nPlagarism Check Completed\n'
print 'Log files can be viewed in "logstatus" folder \n\n'
########################################################################################################
########################################################################################################



















