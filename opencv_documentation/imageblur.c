
//This example code takes a given image, blurs it and shows the output image
//Usage ./filename inputimagename outputimagename
#include <stdio.h>
#include "cv.h"
#include "highgui.h"

int main(int argc,char* argv[])
{
//argc gives the number of arguments to the command. Each argument is stored
//as a string. Now argv[1] has the name of the file.
	IplImage* img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	if(!img) 
	{
		printf("Error: Could not open the image file! \n");
		exit(1);
	}
	
//Blur the image
	IplImage* out = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
	int param1 = 3;
	int param2 = 3;
	cvSmooth(img, out, CV_GAUSSIAN, param1, param2, 0, 0);

//Save the blurred image to file
	int p[3];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 95;
	p[2] = 0;

	cvSaveImage(argv[2], img, p);

//Show the blurred image on the screen
	cvNamedWindow("Blurred", CV_WINDOW_AUTOSIZE);
	cvShowImage("Blurred", img);

//Wait for the user to press anything
	cvWaitKey(0);

//Free the resources
	cvDestroyWindow("Blurred");
	cvReleaseImage(&img);

	return 0;
}
