//This program is used to detect a blob in the hsv method

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	IplImage* frame = cvLoadImage(argv[1],CV_LOAD_IMAGE_UNCHANGED);
	
	CvSize size = cvSize(frame->width,frame->height);
	IplImage* hsv_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U,1);
	IplImage* thresholded2 = cvCreateImage(size, IPL_DEPTH_8U, 1);

	CvScalar hsv_min = cvScalar(0, 80, 220, 0);
        CvScalar hsv_max = cvScalar(50, 140, 256, 0);
        CvScalar hsv_min2 = cvScalar(170, 80, 220, 0);
        CvScalar hsv_max2 = cvScalar(256, 140, 256, 0);
 
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
	int p[3];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 95;
	p[2] = 0;

        cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
        // to handle color wrap-around, two halves are detected and combined
        
	cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
        cvInRangeS(hsv_frame, hsv_min2, hsv_max2, thresholded2);
        cvOr(thresholded, thresholded2, thresholded, 0);
 
        //cvSaveImage("thresholded.jpg",thresholded,p);
 
            // hough detector works better with some smoothing of the image
        cvSmooth( thresholded, thresholded, CV_GAUSSIAN, 9, 9, 0, 0);
        
        //cvSaveImage("frame.jpg", frame, p);
 	

	cvShowImage("Original",thresholded);
	cvShowImage("HSV", hsv_frame);
       
	cvWaitKey(0);
	
	cvDestroyAllWindows();
	cvReleaseImage(&frame);
        return 0;
}
