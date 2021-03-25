#include <iostream>
#include <sstream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(argv[1]); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
  
  
  
  ofstream output("output_t3.txt");
  Mat fgmask2;
  Ptr<BackgroundSubtractor> pBackSub2 = createBackgroundSubtractorMOG2(false);
  vector<Point2f> set_1;
    	set_1.push_back(Point2f(971,235));
	set_1.push_back(Point2f(1275,234));
	set_1.push_back(Point2f(1491,1000));
	set_1.push_back(Point2f(468, 1016));
    vector<Point2f> set_2;
  	set_2.push_back(Point2f(472, 52));
	set_2.push_back(Point2f(800, 52));
	set_2.push_back(Point2f(800, 830));
	set_2.push_back(Point2f(472, 830));
  Mat image,background;
  image= imread("background.jpg");
  cvtColor(image, background, cv::COLOR_BGR2GRAY);
  pBackSub2->apply(background, fgmask2,0);
		
  Mat hom=findHomography(set_1, set_2);
  int i=0;
  Mat cframe,frame;
  while(1){
		  
		  // Capture frame-by-frame
		  cap >> cframe;
		  // If the frame is empty, break immediately
		  if (cframe.empty())
		    break;
		  
		  cvtColor(cframe, frame, cv::COLOR_BGR2GRAY);
		  Mat im_out;
		  warpPerspective(frame, im_out, hom, frame.size());
		  cv::Rect crop_region(472, 52, 328, 778);
		  Mat croppedImg=im_out(crop_region);
		  
		  // Display the resulting frame
		  putText(croppedImg, "Press Esc to exit", Point(5,25),FONT_HERSHEY_DUPLEX, 0.5, Scalar(0,143,143), 0.7);
		  
		  resize(croppedImg, croppedImg, cv::Size(croppedImg.cols * 0.5,croppedImg.rows * 0.5), 0, 0, cv::INTER_LINEAR); //decreasing resolution
		  
		  imshow( "Frame", croppedImg);
		  pBackSub2->apply(croppedImg, fgmask2,0);
		  Mat q;
		  threshold(fgmask2, q, 250, 255, 0); //removing shadows

		  
		  imshow("MaskStatic",q);
    
    
		  int TotalPixelsq = q.rows * q.cols;
		  int notblackPixelsq = countNonZero(q);
		  double qdensity = (double)notblackPixelsq/(double)TotalPixelsq;
		
		  
		  double sec=(double)i/(double)5; //processing at 5fps
		  
		  output << sec<< ","<< qdensity<< endl;
		  cout << sec<< ","<< qdensity<< endl;
		  
		  for (int i=0; i<2; i++){
		  	cap>>cframe;
		  	if (cframe.empty())
		  		break;
		  }
		  
		  i++;
		  
		  // Press  ESC on keyboard to exit
		  char c=(char)waitKey(25);
		  if(c==27)
		    break;
  }
	output.close();
	cout<<"Output saved in output_t3.txt file"<<endl;
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
