//This image takes input from a camera and saves a IMAGE

#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"

void cam_im()
{
	CvCapture* capture = NULL;	
	capture = cvCaptureFromCAM(0);
	IplImage* image = cvQueryFrame(capture);
	
	int p[3];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 95;
	p[2] = 0;

	cvSaveImage("cam.jpg", image, p);

	cvReleaseImage(&image);
}
