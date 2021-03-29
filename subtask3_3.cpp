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
Mat q[16];
struct parameters  p[16];

void *processframe(void* p1){
	struct parameters* pt=(struct parameters *) p1;
	struct parameters p =*pt;
	Mat frame;
	if(p.croppedImage.empty()){cout <<"empty input to thread\n";pthread_exit(NULL);}
  	cvtColor(p.croppedImage, frame, cv::COLOR_BGR2GRAY);
	  
	  // Display the resulting frame
	  //putText(frame, "Press Esc to exit", Point(5,25),FONT_HERSHEY_DUPLEX, 1, Scalar(0,143,143), 0.7);
	  //imshow( "Frame", frame);
	  (p.pBackSub)->apply(frame, p.fgmask,0);
	  threshold(p.fgmask, q[p.i], 250, 255, 0); //removing shadows  
	  imshow(p.name,q[p.i]);
	  pthread_exit(NULL);
}


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
  int numT=atoi(argv[2]);
  if (numT>16){
  cout<<"threads can be max 16"<<endl;
  return -1;
  }
  auto start = high_resolution_clock::now();
  Mat fgmask[numT];
  Mat croppedImgList[numT]; 
  Ptr<BackgroundSubtractor> pBackSubList[numT];
  ofstream output("output_t3.txt");
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
  cv::Rect cropR[numT];
  cv::Rect backR[numT];
  Mat bg[numT];
  int h=(778/numT)+1;
  int y=52;
  int y1=0;
  int i=0;
  while(y<830){
  if (y+h>=830){
  cv::Rect crop_region1(472, y, 328, 830-y-1);
  cropR[i]= crop_region1;
  cv::Rect back_region(0,y1,328,778-y1-1);
  backR[i]= back_region;
  }
  else{
  cv::Rect crop_region1(472, y, 328, h);
  cropR[i]= crop_region1;
  cv::Rect back_region(0,y1,328,h);
  backR[i]= back_region;
  }
  bg[i]=background(backR[i]);
  pBackSubList[i] = createBackgroundSubtractorMOG2(false); 
  pBackSubList[i]->apply(bg[i], fgmask[i],0);
  i++;
  y=y+h;
  y1=y1+h;
  }
  Mat hom=findHomography(set_1, set_2);
 
  i=0;
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
	  		
	  		
		    
		    for (int i=0;i<numT;i++){
		    	croppedImgList[i]=im_out(cropR[i]);
  			if(croppedImgList[i].empty()){cout<<"empty input to a thread";return -1;}
  			p[i]=parameters(croppedImgList[i], fgmask[i],i, "Makestatic"+to_string(i+1), pBackSubList[i]);
  			}
    
    		  pthread_t threads[numT];
    		  for (int i=0; i<numT; i++){
    		  	int p1 = pthread_create(&threads[i], NULL, processframe, &p[i]);
    		  	if (p1){cout<<"unable to create thread";exit(-1);}
    		  }
    		  //until all threads are complete
    		  for (int i=0; i<numT; i++){
    		  	pthread_join(threads[i], NULL);
    		  }
    		  int TotalPixelsq =0;
    		  int notblackPixelsq =0;
    		  for (int i=0;i<numT;i++){
		  TotalPixelsq = +TotalPixelsq+q[i].rows * q[i].cols;
		  notblackPixelsq= notblackPixelsq+ countNonZero(q[i]);
		  }
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
	cout<<"Output saved in output_t3.txt file"<<endl;
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
