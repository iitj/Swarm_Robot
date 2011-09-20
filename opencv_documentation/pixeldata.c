//This program tests the working of the header pixel.h
//Usage ./filename imagefilename
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "./header/pixel.h"

int main(int argc, char** argv)
{	
	IplImage* img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	
	pixel(img);
}
