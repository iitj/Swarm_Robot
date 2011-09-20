// Convert a video to grayscale
//This takes a video and converts it to greyscale
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "./header/gray.h"

int main( int argc, char* argv[]) 
	{
        CvCapture* capture = 0;
        capture = cvCreateCameraCapture(0);
        if(!capture){
        return -1;
        }
        IplImage *bgr_frame=cvQueryFrame(capture);
        //double fps = cvGetCaptureProperty (capture, CV_CAP_PROP_FPS);

        CvSize size = cvSize(
        (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH),
        (int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT)
        );
	int fps = 5;
        CvVideoWriter *writer = cvCreateVideoWriter(argv[1],CV_FOURCC('D','V','I','X'), fps, size,1);
        IplImage* gray_frame = cvCreateImage(size, IPL_DEPTH_8U, 1);
	cvNamedWindow("Example9",CV_WINDOW_AUTOSIZE);
        while(1) 
	{
        gray_frame = gray(bgr_frame);
        cvWriteFrame( writer, gray_frame );
	cvShowImage("Example9",gray_frame);
	char c = cvWaitKey(33);
	if(c == 27)
	break;
        }
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&gray_frame);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example9");
	return(0);
	}

