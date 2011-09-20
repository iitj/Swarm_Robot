//This program smooths a image using a header file
//Usage ./filename imagefilename
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "./header/blur.h"

int main(int argc, char** argv)
{
	IplImage* img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	IplImage* out = blur(img);
	cvNamedWindow("Example6-In",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example6-Out",CV_WINDOW_AUTOSIZE);

	cvShowImage("Example6-In", img);
	cvShowImage("Example6-Out", out);
	
	cvWaitKey(0);

	cvReleaseImage(&img);
	cvReleaseImage(&out);

	cvDestroyWindow("Example6-In");
	cvDestroyWindow("Example6-Out");
}
