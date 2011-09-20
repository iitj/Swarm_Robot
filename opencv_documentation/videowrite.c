// Convert a video to grayscale
//This takes a video and converts it to greyscale
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>

int main( int argc, char* argv[]) 
	{
        CvCapture* capture = 0;
        capture = cvCreateCameraCapture(0);
        if(!capture){
        return -1;
        }
	int i;
        IplImage *frame=0;
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
        int fps = 5;
	int frameW = 320;
	int frameH = 240;
        CvVideoWriter *writer = cvCreateVideoWriter(argv[1],CV_FOURCC('D','I','V','X'), fps, cvSize(frameW,frameH),1);
	cvNamedWindow("Example9",CV_WINDOW_AUTOSIZE);
        while(1) 
	{
	frame = cvQueryFrame(capture);
        cvWriteFrame( writer, frame );
	cvShowImage("Example9",frame);
	char c = cvWaitKey(20);
	if(c == 27)
	break;
        }
	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&frame);
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example9");
	return(0);
	}

