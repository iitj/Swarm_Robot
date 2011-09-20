//This program plays a video file from disk
//Usage ./filename videofilename
#include <stdio.h>
#include "highgui.h"

int main( int argc, char** argv)
{
	cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCaptureFromFile( argv[1]);
	IplImage* frame;
	while(1)
	{
		frame= cvQueryFrame(capture);
		if(!frame)
		{
		printf("Error in reading file: Use AVI File"); 
		break;
		}
		cvShowImage("Example2", frame);
		char c = cvWaitKey(33);
		if(c == 27)
		break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2");

}
