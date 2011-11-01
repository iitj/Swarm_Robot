//This program tests the working of the HSV Format
//Five Windows wil pop up. 1 - Original Image
//2 - HSV, 3 - H, 4 - S, 5 - V
//Things Noticed
//Hue and Saturation are very noisy
//Value is exactly similar to the actual image
//There is some problem in the computation of Hue and Saturation

#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <cxcore.h>
#include <math.h>

int main(int argc, char* argv[])
{
  CvSize size = cvSize(640,480);
  CvCapture* capture = cvCaptureFromCAM(0);
  if(!capture)
    {
      fprintf(stderr, "Error in opening the Camera.\n");
      exit(1);
    }
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
  
  cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("Hue", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("Saturation", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("Value", CV_WINDOW_AUTOSIZE);

  IplImage* frame = cvQueryFrame(capture);
  if(!frame)
    exit(1);
  IplImage* hsv = cvCreateImage(size, IPL_DEPTH_8U, 3);
  IplImage* hue = cvCreateImage(size, IPL_DEPTH_8U, 1);
  IplImage* saturation = cvCreateImage(size, IPL_DEPTH_8U, 1);
  IplImage* value = cvCreateImage(size, IPL_DEPTH_8U, 1);

  while(1)
    {
      frame = cvQueryFrame(capture);
      if(!frame)
	{
	  fprintf(stderr, "Failed to capture an Image.\n");
	  break;
	}
      cvCvtColor(frame, hsv, CV_BGR2HSV);
      cvSplit(hsv, hue, saturation, value, 0);
      cvSmooth(hue, hue, CV_GAUSSIAN,9,9,0,0);
      cvSmooth(saturation, saturation, CV_GAUSSIAN,9,9,0,0);
      cvShowImage("Camera", frame);
      cvShowImage("HSV", hsv);
      cvShowImage("Hue", hue);
      cvShowImage("Saturation", saturation);
      cvShowImage("Value", value);

      char c=cvWaitKey(33);
      if(c == 27)
	break;
    }
  cvDestroyAllWindows();
  cvReleaseCapture(&capture);
  cvReleaseImage(&frame);
  cvReleaseImage(&hsv);
}

