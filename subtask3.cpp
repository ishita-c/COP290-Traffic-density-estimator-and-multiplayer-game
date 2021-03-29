#include <iostream>
#include <sstream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <fstream>
#include <pthread.h>

using namespace std;
using namespace cv;
using namespace std::chrono;

Ptr<BackgroundSubtractor> pBackSubList[4];



struct parameters{
	Mat croppedImage;
	Mat fgmask;
	string name;
	int i;
	Ptr<BackgroundSubtractor> pBackSub;
	parameters(){} //default contructor
	parameters(Mat my_croppedImage, Mat my_fgmask,int my_i, string my_name, Ptr<BackgroundSubtractor> my_pBackSub){
		croppedImage=my_croppedImage; fgmask=my_fgmask;i=my_i; name=my_name; pBackSub=my_pBackSub;
	}
};
Mat q[4];
struct parameters  p[4];

void *processframe(void* p1){
	struct parameters* pt=(struct parameters *) p1;
	struct parameters p =*pt;
	Mat frame;
	if(p.croppedImage.empty()){cout <<"empty input to thread\n";pthread_exit(NULL);}
  	cvtColor(p.croppedImage, frame, cv::COLOR_BGR2GRAY);
	  
	  // Display the resulting frame
	  //putText(frame, "Press Esc to exit", Point(5,25),FONT_HERSHEY_DUPLEX, 1, Scalar(0,143,143), 0.7);
	  
	  resize(frame, frame, cv::Size(frame.cols * 0.5,frame.rows * 0.5), 0, 0, cv::INTER_LINEAR); //decreasing resolution
	  
	  //imshow( "Frame", frame);
	  (p.pBackSub)->apply(frame, p.fgmask,0);
	  threshold(p.fgmask, q[p.i], 250, 255, 0); //removing shadows  
	  imshow(p.name,q[p.i]);
	  pthread_exit(NULL);
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
Mat fgmask[4];
Mat croppedImgList[4]; 
  
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
  if (image.empty()){cout<<"background not present \n";return -1;}
  cvtColor(image, background, cv::COLOR_BGR2GRAY);
  cv::Rect crop_region1(472, 52, 164, 389);
  cv::Rect crop_region2(636, 52, 164, 389);
  cv::Rect crop_region3(472, 441, 164, 389);
  cv::Rect crop_region4(636, 441, 164, 389);
  cv::Rect back_region(0,0,164,389);
  cv::Rect back_region2(164,0,164,389);
  Mat background1=background(back_region);
  Mat background2=background(back_region2);
  /*Mat background3=background(crop_region3);
  Mat background4=background(crop_region4);*/
  resize(background1, background1, cv::Size(background1.cols * 0.5,background1.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  resize(background2, background2, cv::Size(background2.cols * 0.5,background2.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  /*resize(background3, background3, cv::Size(background3.cols * 0.5,background3.rows * 0.5), 0, 0, cv::INTER_LINEAR);
  resize(background4, background4, cv::Size(background4.cols * 0.5,background4.rows * 0.5), 0, 0, cv::INTER_LINEAR);*/
  pBackSubList[0] = createBackgroundSubtractorMOG2(false);  //pBackSub1
  pBackSubList[1] = createBackgroundSubtractorMOG2(false);  //pBackSub2
  pBackSubList[2] = createBackgroundSubtractorMOG2(false);  //pBackSub3
  pBackSubList[3] = createBackgroundSubtractorMOG2(false);  //pBackSub4
  pBackSubList[0]->apply(background1, fgmask[0],0);
  pBackSubList[1]->apply(background2,fgmask[1],0);
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
	  		
	  		
		    	croppedImgList[0]=im_out(crop_region1);  //croppedImg1
		    	croppedImgList[1]=im_out(crop_region2);  //croppedImg2
		    	croppedImgList[2]=im_out(crop_region3);  //croppedImg3
		    	croppedImgList[3]=im_out(crop_region4);  //croppedImg4
		    
		    for (int i=0;i<4;i++){
  			if(croppedImgList[i].empty()){cout<<"empty input to a thread";return -1;}
  			p[i]=parameters(croppedImgList[i], fgmask[i],i, "Makestatic"+to_string(i+1), pBackSubList[i]);
  			}
		 
		  /*Mat q1=processframe(croppedImgList[0],fgmask2,"Makestatic1",pBackSubList[0]);
		  Mat q2=processframe(croppedImgList[1],fgmask2,"Makestatic2",pBackSubList[1]);
		  Mat q3=processframe(croppedImgList[2],fgmask2,"Makestatic3",pBackSubList[2]);
		  Mat q=processframe(croppedImgList[4],fgmask2,"Makestatic4",pBackSubList[3]);*/
		  //Mat q=processframe(croppedImg,fgmask2);
    
    		  pthread_t threads[4];
    		  for (int i=0; i<4; i++){
    		  	int p1 = pthread_create(&threads[i], NULL, processframe, &p[i]);
    		  	if (p1){cout<<"unable to create thread";exit(-1);}
    		  }
    		  //until all threads are complete
    		  for (int i=0; i<4; i++){
    		  	pthread_join(threads[i], NULL);
    		  }
    		  
		  int TotalPixelsq = q[0].rows * q[0].cols;
		  int notblackPixelsq = countNonZero(q[0]);
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
