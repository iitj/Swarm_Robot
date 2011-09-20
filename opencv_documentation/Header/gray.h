//This header file converts input image to black and white image

#include <stdio.h>
#include "cv.h"
#include "highgui.h"

IplImage* gray(IplImage* image)
{
	IplImage* out = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);

	cvCvtColor(image, out, CV_RGB2GRAY);
	return(out);
}
