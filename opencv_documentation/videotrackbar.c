//This program makes a basic music player
//Usage ./filename videofilename
//Not working properly
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int g_slider_position = 0;
CvCapture* g_capture = 0;

void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES,pos);
}

int main(int argc, char** argv)
{
	cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCaptureFromFile(argv[1]);
	if(!g_capture)
	printf("Error in reading file");

	int frames = (int) cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
	printf("%i",frames);
	if(frames!=0)
	{
	cvCreateTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide);
	}

	IplImage* frame;
	
	while(1)
	{
		frame = cvQueryFrame(g_capture);
	if(!frame)
	{
	printf("Error in loading frame");
	break;
	}
	cvShowImage("Example3",frame);
	char c = cvWaitKey(100);
	if(c == 27);
	break;
	}

	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Example3");
	return(0);
}
