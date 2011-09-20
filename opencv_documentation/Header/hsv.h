//This header coverts an input image to a HSV image

#include "cv.h"
#include "highgui.h"
#include <stdio.h>

IplImage* hsv(IplImage* image)
{
	CvSize size = cvSize(image->width,image->height);
	IplImage* out = cvCreateImage(size,IPL_DEPTH_8U,3);

	cvCvtColor(image,out, CV_BGR2HSV);
	return(out);
}
