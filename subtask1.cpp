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
	Mat cimage,image;
	cimage= imread("traffic.jpg");
	cvtColor(cimage, image, cv::COLOR_BGR2GRAY);
	putText(image, "Select 4 points which are the corners of road of interest in correct order TL TR BR BL", Point(5,100), FONT_HERSHEY_DUPLEX, 1, Scalar(0,143,143), 2);
	if (image.empty()){cout<<"error loading image"<<endl;return -1;}
	namedWindow("Img",1);
	setMouseCallback("Img",CallBackFunc,NULL);
	imshow("Img",image);
	waitKey(0);
	if (inp.size()!=4){printf("You have not selected exactly 4 points");return -1;}
	if (!(inp[0].y<=inp[2].y&&inp[0].y<=inp[3].y&&inp[1].y<=inp[2].y&&inp[1].y<inp[3].y&&inp[0].x<inp[1].x&&inp[2].x>inp[3].x)){
	printf("Please select the points in correct order TL TR BR BL");
	return -1;}
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
	bool check = imwrite("cropped.jpg", croppedImg);
	if (!check) {printf("unable to save image");return -1;}
	printf("Cropped image saved ");
	
	//return 0;	
}
