//This header file performs the canny image transform on a Black and White Image

#include <stdio.h>
#include "cv.h"
#include "highgui.h"


IplImage* canny(IplImage* in, double lowThresh, double highThresh, double aperture)
{
	IplImage* out = cvCreateImage(cvSize(in->width,in->height), IPL_DEPTH_8U, 1);
	
	IplImage* out1 = cvCreateImage(cvSize(in->width,in->height), IPL_DEPTH_8U, 1);
	
	cvCvtColor(in, out1, CV_RGB2GRAY);
	

	

	cvCanny(out1 ,out, lowThresh, highThresh, aperture);
	return(out);
}
	
