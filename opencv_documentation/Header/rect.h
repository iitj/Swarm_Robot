//This program draws a rectagle on input image

#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"

void rect(IplImage* img,CvPoint* point1,CvPoint* point2, CvScalar* scalar)
{
	cvRect(img,point1,point2,scalar);
}
