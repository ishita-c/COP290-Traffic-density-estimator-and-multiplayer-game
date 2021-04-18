The 4 methods of subtask 3 are implemented in 4 seperate cpp files, with file name format as subtask3_METHODNUMBER.cpp. We use makefile to make their respective executables.

To compile the code, run the following in terminal:

$make creates all four executables, i.e., sub3.1, sub3.2, sub3.3 and sub3.4, which uses flags -o to make binary executable file directly -Wall to raise possible warnings 'pkg-config --cflags --libs opencv' to use openCV liabrary. In addition to this, method 3 and 4 uses -pthread also to implement multi-threading.
$make subtask3_1.cpp creates the executable sub3.1 only. Similar commands for rest of the methods.

Running the executable:

METHOD1:
$./sub3.1 videoname parameter
Where videoname should be replaced with the name of the video to be processed (with extension), "trafficvideo.mp4" in this case. If there exists no such file with desired file name, the program throws an error. 
Parameter is an integer, which implies the number of frames dropped while processing a video.
The program processes the video file to generate the queue density for each processed frame. The output is printed on console in the format "time(in secs), queue density". The same is also saved in the output_m1_PARAMETER.txt file in the same directory as well.

METHOD2:
$./sub3.1 videoname parameter
Where videoname should be replaced with the name of the video to be processed (with extension), "trafficvideo.mp4" in this case. If there exists no such file with desired file name, the program throws an error. 
Parameter is an integer, which implies the number of frames dropped while processing a video.
The program processes the video file to generate the queue density for each processed frame. The output is printed on console in the format "time(in secs), queue density". The same is also saved in the output_m1_PARAMETER.txt file in the same directory as well.

METHOD3:
$./sub3.1 videoname parameter1 parameter2
Where videoname should be replaced with the name of the video to be processed (with extension), "trafficvideo.mp4" in this case. If there exists no such file with desired file name, the program throws an error. 
Parameter1 and parameter2 are integers, which implies the reduced resolution of each frame, parameter1 is width (< original width) and parameter 2 is height (< original height). The video is processed at 5 fps.
The program processes the video file to generate the queue density for each processed frame. The output is printed on console in the format "time(in secs), queue density". The same is also saved in the output_m2_PARAMETER1xPARAMETER2.txt file in the same directory as well.

METHOD4:
$./sub3.4 videoname parameter
Where videoname should be replaced with the name of the video to be processed (with extension), "trafficvideo.mp4" in this case. If there exists no such file with desired file name, the program throws an error. 
Parameter is an integer (less than or equal to 16), which implies the number of threads formed for processing the consecutive frames at 5 fps.
The program processes the video file to generate the queue density for each processed frame. The output is printed on console in the format "time(in secs), queue density". The same is also saved in the output_m4_PARAMETER.txt file in the same directory as well.

Cleaning up:

$make clean 
This command deletes the executables and other outputs.