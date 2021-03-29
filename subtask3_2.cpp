#include <iostream>
#include <sstream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <fstream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;


int main(int argc, char* argv[]){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  if (argc!=3){
  cout<<"input as ./sub3 infilename parameter"<<endl;
  return -1;
  }
  VideoCapture cap(argv[1]); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
  auto start = high_resolution_clock::now();
  int prmtr=atoi(argv[2]);
  float prmt=1/(float) prmtr;
  Mat fgmask2;
  Mat q;
  ofstream output("output_m2_"+to_string(prmtr)+".txt");
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
  if (image.empty()){cout<<"background not present \n";return -1;}
  cvtColor(image, background, cv::COLOR_BGR2GRAY);
  cv::Rect crop_region(472, 52, 328, 778);
  Ptr<BackgroundSubtractor> pBackSub2 = createBackgroundSubtractorMOG2(false);  //pBackSub4
  resize(background, background, cv::Size(background.cols * prmt,background.rows * prmt), 0, 0, cv::INTER_LINEAR); //decreasing resolution
  pBackSub2->apply(background, fgmask2,0);
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
		    Mat im_out,frame;
		    
	  		warpPerspective(cframe, frame, hom, cframe.size());
	  		cvtColor(frame, im_out, cv::COLOR_BGR2GRAY);
	  		Mat croppedImg=im_out(crop_region);
	  		resize(croppedImg, croppedImg, cv::Size(croppedImg.cols * prmt,croppedImg.rows * prmt), 0, 0, cv::INTER_LINEAR); //decreasing resolution
	  		imshow("frame",croppedImg);
	  		pBackSub2->apply(croppedImg,fgmask2,0);
	  		threshold(fgmask2, q, 250, 255, 0); //removing shadows
	  		imshow("static",q);

    		  
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
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - start);
  output<<duration.count();
  cout<<"time taken "<<duration.count()<<endl;
	output.close();
	cout<<"Output saved in output_m2_"+to_string(prmtr)+".txt file"<<endl;
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
