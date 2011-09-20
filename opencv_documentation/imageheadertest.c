//This program tests the running of various library files 
//This file includes 4 different functions.
//0 - blur,1 - canny,2 - pyre and 3 - grey
//Usage ./filename imagefilename functionno.

#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "./header/blur.h"
#include "./header/pyre.h"
#include "./header/canny.h"
#include "./header/gray.h"


int main(int argc, char** argv)
{
	int arg;
	IplImage* img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	IplImage* out = 0;
	printf("Chose an operation:-\n0 - Blur\n1 - Pyre\n2 - Canny\n3 - Grey");
	scanf("%d",&arg);
	printf("%d\n",arg);
	if(arg == 0)
	out = blur(img);
	else if(arg == 1)
	out = pyre(img, 2,2);
	else if(arg == 2)
	out = canny(img, 10,100,3);
	else
        out = gray(img);
	

	cvNamedWindow("Example7-In",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example7-Out",CV_WINDOW_AUTOSIZE);

	cvShowImage("Example7-In", img);
	cvShowImage("Example7-Out", out);
	
	cvWaitKey(0);

	cvReleaseImage(&img);
	cvReleaseImage(&out);

	cvDestroyWindow("Example7-In");
	cvDestroyWindow("Example7-Out");
	return(0);
}
