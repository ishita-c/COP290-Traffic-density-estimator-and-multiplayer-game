# COP290 Subtask 1

subtask1.cpp is a C++ code which is used to make the executable sub1 by compiling it. using makefile which is fairly simple as
there is only one dependency for sub1 and nothing complex yet.

Compiling
$make
to create the executable sub1 which uses flags 
-o to make binary executable file directly
-Wall to raise possible warnings
'pkg-config --cflags --libs opencv' to use openCV liabrary

Running the executable
$./sub1 image.jpg 
where image.jpg is to be replaced with the name of the image to be processed (with extension).
It also generates a transformed image (transformed.jpg) and cropped transformed image (cropped.jpg)

Cleaning up
$make clean
this command deletes the executable and the processed images. 
