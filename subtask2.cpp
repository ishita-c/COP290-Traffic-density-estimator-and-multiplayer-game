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

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("trafficvideo.mp4"); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
  ofstream output("output.txt");
  Mat fgmask,fgmask2;
  Ptr<BackgroundSubtractor> pBackSub1 = createBackgroundSubtractorMOG2(false);
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
  //video has 5730 frames, fpsXduration
  while(i<5730){

    Mat cframe,frame;
    // Capture frame-by-frame
    cap >> cframe;
    cvtColor(cframe, frame, cv::COLOR_BGR2GRAY);
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;
    
    Mat im_out;
    warpPerspective(frame, im_out, hom, frame.size());
    cv::Rect crop_region(472, 52, 328, 778);
    Mat croppedImg=im_out(crop_region);
    // Display the resulting frame
    imshow( "Frame", croppedImg);
    pBackSub1->apply(croppedImg, fgmask);
    pBackSub2->apply(croppedImg, fgmask2,0);
    imshow("MaskDynamic",fgmask);
    imshow("MaskStatic",fgmask2);
    
    
    int TotalPixelsq = fgmask2.rows * fgmask2.cols;
    int notblackPixelsq = countNonZero(fgmask2);
    double qdensity = (double)notblackPixelsq/(double)TotalPixelsq;
	
    int TotalPixels = fgmask.rows * fgmask.cols;
    int notblackPixels = countNonZero(fgmask);
    double dynadensity = (double)notblackPixels/(double)TotalPixels;
    
    output << i<< ","<< qdensity<< ","<< dynadensity<< endl;
    
    
    
    i=i+3;
    
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
	output.close();
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
