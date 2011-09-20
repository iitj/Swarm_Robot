
#include <stdio.h>
#include "highgui.h"
#include "cv.h"

IplImage* blur(IplImage* image)
{
	IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U,3);

	cvSmooth(image, out, CV_BLUR, 3,3,0,0);
	
	return(out);
}
