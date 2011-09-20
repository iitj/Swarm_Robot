//This program takes any input image and displays it on the screen
//Simple Example
#include <stdio.h>
#include "highgui.h"

int main(int argc, char** argv)
{
	IplImage* img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	if(!img)
	{
		printf("Error in loading the image. \n");
		exit(1);
	}
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Example1");
}


