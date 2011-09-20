//This program is used to detect a blob
//Not working so well needs changes
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	CvCapture* capture = cvCaptureFromCAM(0);	//Use the default camera
	assert(capture);
	IplImage* frame = 0;
	CvMemStorage* storage = cvCreateMemStorage(0);

	frame = cvQueryFrame(capture);
	frame = cvQueryFrame(capture);
	frame = cvQueryFrame(capture);

	CvSize size = cvSize(frame->width,frame->height);
	IplImage* hsv_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U,1);
	IplImage* thresholded2 = cvCreateImage(size, IPL_DEPTH_8U, 1);

	CvScalar hsv_min = cvScalar(0, 80, 220, 0);
        CvScalar hsv_max = cvScalar(50, 140, 256, 0);
        CvScalar hsv_min2 = cvScalar(170, 80, 220, 0);
        CvScalar hsv_max2 = cvScalar(256, 140, 256, 0);
 
	int p[3];
	p[0] = CV_IMWRITE_JPEG_QUALITY;
	p[1] = 95;
	p[2] = 0;
//do {
        frame = cvQueryFrame(capture);
        if (frame != NULL) {
        printf("got frame\n\r");
            // color detection using HSV
        cvCvtColor(frame, hsv_frame, CV_BGR2HSV);
            // to handle color wrap-around, two halves are detected and combined
        cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
        cvInRangeS(hsv_frame, hsv_min2, hsv_max2, thresholded2);
        cvOr(thresholded, thresholded2, thresholded, 0);
 
        cvSaveImage("thresholded.jpg",thresholded,p);
 
            // hough detector works better with some smoothing of the image
        cvSmooth( thresholded, thresholded, CV_GAUSSIAN, 9, 9, 0, 0);
        CvSeq* circles = cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2, thresholded->height/4, 100, 40, 20, 200);
 
	int i;
        for (i = 0; i < circles->total; i++)
        {
        float* p = (float*)cvGetSeqElem( circles, i );
        printf("Ball! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
        cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
        cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
        }
 
        cvSaveImage("frame.jpg", frame, p);
        }
 	else 
	{
        printf("Null frame\n\r");
        }
  //} while (true);
        cvReleaseCapture(&capture);
        return 0;
}
