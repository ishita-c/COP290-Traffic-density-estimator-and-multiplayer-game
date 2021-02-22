#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


vector<Point2f> inp;

void CallBackFunc(int event,int x,int y,int flags,void* userdata){
	if(event==EVENT_LBUTTONDOWN){
	inp.push_back(Point2f(x,y));
	}
}

int main(int argc, char** argv){
	Mat image;
	image= imread("I1.jpg");
	if (image.empty()){cout<<"error loading image"<<endl;return -1;}
	namedWindow("Img",1);
	setMouseCallback("Img",CallBackFunc,NULL);
	imshow("Img",image);
	waitKey(0);
	print(inp);
	return 0;	
}
