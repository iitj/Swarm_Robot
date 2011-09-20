//This file converts an input image to hsv color format
//Usage ./filename inputimagefilename
#include <stdio.h>
#include "highgui.h"
#include "cv.h"
int main(int argc,char** argv)
{
	IplImage* image = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);
	CvSize size = cvSize(image->width,image->height);
	IplImage* out = cvCreateImage(size,IPL_DEPTH_8U,3);
	cvCvtColor(image,out, CV_BGR2HSV);
	int p[3];
	p[0] = CV_IMWRITE_PNG_COMPRESSION;
	p[1] = 3;
	p[2] = 0;
	cvSaveImage("hsv.png",out,p);
}

