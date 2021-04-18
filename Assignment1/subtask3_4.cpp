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
	  
	  (p.pBackSub)->apply(frame, p.fgmask,0);
	  threshold(p.fgmask, q[p.i], 250, 255, 0); //removing shadows  
	  //imshow(p.name,q[p.i]);
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
  if (numT<1){
  cout<<"parameter must be >= 1\n";
  return -1;
  }
  auto start = high_resolution_clock::now();
  Mat fgmask[numT];
  Mat croppedImgList[numT]; 
  Ptr<BackgroundSubtractor> pBackSubList[numT];
  ofstream output("output_m4_"+to_string(numT)+".txt");
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
  cv::Rect crop_region(472, 52, 328, 778);
  for(int i=0;i<numT;i++){
  pBackSubList[i] = createBackgroundSubtractorMOG2(false);
  pBackSubList[i]->apply(background, fgmask[i],0);
  }
  Mat hom=findHomography(set_1, set_2);
  int t=0;
  Mat cframe;  
  while(1){
  	int last=-1;
  	pthread_t threads[numT];
	for(int j=0;j<numT;j++){	  
		  // Capture frame-by-frame
		  cap >> cframe;
		  // If the frame is empty, break immediately
		  if (cframe.empty()){
		    last=j;
		    break;
		    }
		    Mat im_out;
	  		warpPerspective(cframe, im_out, hom, cframe.size());
	  		
	  		
		    	croppedImgList[j]=im_out(crop_region);  //croppedImg1
		    
  			if(croppedImgList[j].empty()){cout<<"empty input to a thread";return -1;}
  			p[j]=parameters(croppedImgList[j], fgmask[j],j, "Makestatic"+to_string(j+1), pBackSubList[j]);
    		  	int p1 = pthread_create(&threads[j], NULL, processframe, &p[j]);
    		  	if (p1){cout<<"unable to create thread";exit(-1);}
    		  //until all threads are complete
    		  
		  for (int i=0; i<2; i++){
		  	cap>>cframe;
		  	if (cframe.empty()){
		  		last=j+1;
		  		break;
		  		}
		 }
		 if(last!=-1){
    			break;
    			}
		}
		  
		  // Press  ESC on keyboard to exit
		char c=(char)waitKey(25);
		if(c==27)
		    break;
		for (int i=0; i<numT; i++){
		if (last==-1||i<last){
    	  	pthread_join(threads[i], NULL);
    	  	imshow("Makestatic"+to_string(i+1),q[i]);
    	  	int TotalPixelsq = q[i].rows * q[i].cols;
		int notblackPixelsq = countNonZero(q[i]);
		double qdensity = (double)notblackPixelsq/(double)TotalPixelsq;
		double sec=(double)(t+i)/(double)5; //processing at 5fps
		output << sec<< ","<< qdensity<< endl;
		cout << sec<< ","<< qdensity<< endl;
		}
    		}
    		if(last!=-1){
    		break;
    		}
    		t=t+numT;
	}
	auto stop = high_resolution_clock::now();
  	auto duration = duration_cast<seconds>(stop - start);
  	output<<duration.count();
  	cout<<"time taken "<<duration.count()<<endl;
	output.close();
	cout<<"Output saved in output_m4_"+to_string(numT)+".txt file"<<endl;
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();		//pata nahi ye frames ko close karne me dikkat arahi thi bina uske bhi sahi hua to hai 
	
  return 0;
}
