//This program takes live input from the video
//Usage ./filename
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int main(int argc, char** argv)
{
	CvCapture* capture = 0;
	capture = cvCreateCameraCapture(0);
	assert(capture != NULL);

	cvNamedWindow("Example8", CV_WINDOW_AUTOSIZE);
	IplImage* frame = 0;
	while(1)
	{
	frame = cvQueryFrame(capture);
	if(!frame)
	break;
	cvShowImage("Example8", frame);
	char c = cvWaitKey(33);
	if(c == 27)
	break;
	}
	
	cvReleaseCapture(&capture);
	cvReleaseImage(&frame);
	cvDestroyWindow("Example8");

}
	
