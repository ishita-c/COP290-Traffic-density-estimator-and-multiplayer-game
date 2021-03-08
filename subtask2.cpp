#include "opencv2/opencv.hpp"
#include <iostream>

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
	
	Mat hom=findHomography(set_1, set_2);
  int i=0;	
  while(1){

    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
    
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    
    Mat im_out;
    warpPerspective(frame, im_out, hom, frame.size());
    cv::Rect crop_region(472, 52, 328, 778);
    Mat croppedImg=im_out(crop_region);
    // Display the resulting frame
    imshow( "Frame", croppedImg);
    
    i++;

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
