
#include<stdio.h>
#include<cv.h>
#include<cvaux.h>   
#include<highgui.h>

int main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
	
	
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	
	IplImage *img = 0;
	img = cvQueryFrame(capture);
	
	
	cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
	
	//initializing a video writer
	CvVideoWriter *writer = NULL;
	
	int isColor = 1;
	int fps = 5;
	int frameW = 320;
	int frameH = 240;
	writer = cvCreateVideoWriter("out.avi",CV_FOURCC('D','I','V','X'),fps,cvSize(frameW,frameH), isColor); 
	
	for(int n = 1; n= 30; n++)
	{
		img = cvQueryFrame(capture);
		
		cvWriteFrame(writer,img);      // add the frame to the file
		
		//show frames while capturing
		cvShowImage("Video", img);
		
		int c = cvWaitKey(20);           // wait 20 ms
		if(c == 27)
			break;
	}
	
	
	cvReleaseVideoWriter(&writer);
	cvDestroyWindow( "Video" );
	cvReleaseCapture(&capture);
	
	return 0;
}


