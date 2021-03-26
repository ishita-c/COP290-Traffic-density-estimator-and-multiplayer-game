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
Ptr<BackgroundSubtractor> pBackSub1 = createBackgroundSubtractorMOG2(false);
Ptr<BackgroundSubtractor> pBackSub2 = createBackgroundSubtractorMOG2(false);
Ptr<BackgroundSubtractor> pBackSub3 = createBackgroundSubtractorMOG2(false);
Ptr<BackgroundSubtractor> pBackSub4 = createBackgroundSubtractorMOG2(false);
Mat processframe(Mat cframe,Mat fgmask2,string m,Ptr<BackgroundSubtractor> pBackSub2){
	Mat frame;
  	cvtColor(cframe, frame, cv::COLOR_BGR2GRAY);
	  
	  // Display the resulting frame
	  //putText(frame, "Press Esc to exit", Point(5,25),FONT_HERSHEY_DUPLEX, 1, Scalar(0,143,143), 0.7);
	  
	  resize(frame, frame, cv::Size(frame.cols * 0.5,frame.rows * 0.5), 0, 0, cv::INTER_LINEAR); //decreasing resolution
	  
	  imshow( "Frame", frame);
	  pBackSub2->apply(frame, fgmask2,0);
	  Mat q;
	  threshold(fgmask2, q, 250, 255, 0); //removing shadows  
	  imshow(m,q);
	  return q;
}
int main(int argc, char* argv[]){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  if (argc!=2){
  cout<<"input as ./sub3 infilename "<<endl;
  return -1;
  }
  VideoCapture cap(argv[1]); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
  
  
  
  ofstream output("output_t3.txt");
  Mat fgmask2;
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
  cv::Rect crop_region1(472, 52, 164, 389);
  cv::Rect crop_region2(636, 52, 164, 389);
  cv::Rect crop_region3(472, 441, 164, 389);
  cv::Rect crop_region4(636, 441, 164, 389);
  cv::Rect crop_region(0,0,164,389);
  cv::Rect back_region2(164,0,164,389);
  Mat background1=background(crop_region);
  Mat background2=background(back_region2);
  /*Mat background3=background(crop_region3);
  Mat background4=background(crop_region4);*/
  resize(background1, background1, cv::Size(background1.cols * 0.5,background1.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  resize(background2, background2, cv::Size(background2.cols * 0.5,background2.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  /*resize(background3, background3, cv::Size(background3.cols * 0.5,background3.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  resize(background4, background4, cv::Size(background4.cols * 0.5,background4.rows * 0.5), 0, 0, cv::INTER_LINEAR);*/
  pBackSub1->apply(background1, fgmask2,0);
  pBackSub2->apply(background2,fgmask2,0);
  Mat hom=findHomography(set_1, set_2);
  int i=0;
  Mat cframe;
  while(1){
		  
		  // Capture frame-by-frame
		  cap >> cframe;
		  // If the frame is empty, break immediately
		  if (cframe.empty()){
		    break;
		    }
		    Mat im_out;
	  		warpPerspective(cframe, im_out, hom, cframe.size());
	  		//cv::Rect crop_region(472, 52, 328, 778);
	  		//Mat croppedImg=im_out(crop_region);
		    	Mat croppedImg1=im_out(crop_region1);
		    	Mat croppedImg2=im_out(crop_region2);
		    	Mat croppedImg3=im_out(crop_region3);
		    	Mat croppedImg4=im_out(crop_region4);
		    
		  Mat q1=processframe(croppedImg1,fgmask2,"Makestatic1",pBackSub1);
		  Mat q2=processframe(croppedImg2,fgmask2,"Makestatic2",pBackSub2);
		  Mat q3=processframe(croppedImg3,fgmask2,"Makestatic3",pBackSub3);
		  Mat q=processframe(croppedImg4,fgmask2,"Makestatic4",pBackSub4);
		  //Mat q=processframe(croppedImg,fgmask2);
    
    
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
