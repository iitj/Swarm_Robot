//This code detects the color red in the iamge
//This uses the function InRangeS()
//The thresholds given in this code are very sensitive
//They have been arrived at purely by luck and this program is now only capable of tracking very specifically colored red objects
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
  cvNamedWindow("Thresholded", CV_WINDOW_AUTOSIZE);

  IplImage* frame = cvQueryFrame(capture);
  if(!frame)
    exit(1);
  IplImage* hsv = cvCreateImage(size, IPL_DEPTH_8U, 3);
  IplImage* thresholded = cvCreateImage(size, IPL_DEPTH_8U, 1);

  CvScalar hsv_min = cvScalar(170, 84, 100, 0);
  CvScalar hsv_max = cvScalar(358, 256, 256, 0);

  while(1)
    {
      frame = cvQueryFrame(capture);
      if(!frame)
	{
	  fprintf(stderr, "Failed to capture an Image.\n");
	  break;
	}
      cvCvtColor(frame, hsv, CV_BGR2HSV);
      cvInRangeS(hsv, hsv_min, hsv_max, thresholded);
      cvSmooth(thresholded, thresholded, CV_GAUSSIAN, 9,9,0,0);
      cvShowImage("Camera", frame);
      cvShowImage("HSV", hsv);
      cvShowImage("Thresholded", thresholded);

      char c=cvWaitKey(33);
      if(c == 27)
	break;
    }
  cvDestroyAllWindows();
  cvReleaseCapture(&capture);
  cvReleaseImage(&frame);
  cvReleaseImage(&hsv);
}

