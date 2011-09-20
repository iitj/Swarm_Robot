
//This program smooths a image
//Usage ./filename imagefilename
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int main(int argc, char** argv)
{
	IplImage* image = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("Example5",CV_WINDOW_AUTOSIZE);
	cvShowImage("Example5", image);
	IplImage* out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U,3);

	cvSmooth(image, out, CV_BLUR, 3,3,0,0);
	
	cvNamedWindow("Blur",CV_WINDOW_AUTOSIZE);
	cvShowImage("Blur", out);

	
	cvWaitKey(0);

	cvReleaseImage(&image);
	cvReleaseImage(&out);
	
	cvDestroyWindow("Example5");
	cvDestroyWindow("Blur");

}

