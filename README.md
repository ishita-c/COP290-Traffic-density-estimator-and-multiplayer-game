# COP290 Subtask 1

subtask1.cpp is a C++ code which is used to make the executable sub1 by compiling it. Using makefile which is fairly simple as there is only one dependency for sub1.


To compile the code, run the following in terminal:

$make
to create the executable sub1 which uses flags 
-o to make binary executable file directly
-Wall to raise possible warnings
'pkg-config --cflags --libs opencv' to use openCV liabrary

Running the executable:

$./sub1 image.jpg 
where image.jpg is to be replaced with the name of the image to be processed (with extension).
If there exists no file with desired file name, the program throws an error.
It also generates a transformed image (transformed.jpg with corrected camera angle) and cropped transformed image (cropped.jpg with the area of interest kept and rest is cropped out), and saves both these image files in the same directory. Both the images generated are in grayscale.

Cleaning up:

$make clean
this command deletes the executable and the processed images. 
