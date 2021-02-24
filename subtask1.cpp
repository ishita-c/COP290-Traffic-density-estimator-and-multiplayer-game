#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


vector<Point2f> inp;
vector<Point2f> set_2;
void CallBackFunc(int event,int x,int y,int flags,void* userdata){
	if(event==EVENT_LBUTTONDOWN){
	inp.push_back(Point2f(x,y));
	}
}

int main(int argc, char** argv){
	Mat image;
	image= imread("traffic.jpg");
	if (image.empty()){cout<<"error loading image"<<endl;return -1;}
	namedWindow("Img",1);
	setMouseCallback("Img",CallBackFunc,NULL);
	imshow("Img",image);
	waitKey(0);
	print(inp);
	
	set_2.push_back(Point2f(472, 52));
	set_2.push_back(Point2f(800, 52));
	set_2.push_back(Point2f(800, 830));
	set_2.push_back(Point2f(472, 830));
	
	Mat hom=findHomography(inp, set_2);
	Mat im_out;
	warpPerspective(image, im_out, hom, image.size());
	imshow("Img", image);
	imshow("Output image", im_out);
	cv::Rect crop_region(472, 52, 328, 778);
	Mat croppedImg=im_out(crop_region);
	imshow("crop", croppedImg);
	waitKey(0);
	
	//return 0;	
}
