//Ball Detection Algorithm 2
//Date - 30/10/2011
/*This is different from the previous code. This has my own addition
Now I am comparing the co-ordinates of the center of the circle with the previous co-ordinates. If the variation is too much, the noise is considerable reduced
But the ball is not being effectively detected many times. Not solved the bug in this code
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <cxcore.h>
#include <math.h>

int main(int argc, char* argv[])
{
  int i;
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

  CvScalar hsv_min = cvScalar(170, 120, 100, 0);
  CvScalar hsv_max = cvScalar(358, 256, 256, 0);

  int xpre = 0, ypre = 0;

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

      CvMemStorage* storage = cvCreateMemStorage(0);
      CvSeq* circles = cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2,thresholded->height/4, 100, 50, 40, 400);
/*The entire code lies in this line, This function detects the actual circles in the image. The parameters are as follows:
      thresholded - input image
      storage - memory storage that stores location of circles
      CV_HOUGH_GRADIENT - method used to detect circles(only one present)
      2(dp) - Resolution for the detection, more the better
      (thresholded->height)/4(minDist) - Minimum Distance between the circles
      100(param1) - For the Canny Edge Detection
      50(param2) - For the Canny Edge Detection
      10(minRadius) - Minimum radius of Circle
      400(maxRadius) - Maximum radius of Circle
      Link Followed for above information - http://www.emgu.com/wiki/files/1.3.0.0/html/0ac8f298-48bc-3eee-88b7-d2deed2a285d.htm
*/
      
      for(i = 0;i<circles->total;i++)
	{
	  float* p = (float*)cvGetSeqElem( circles, i );
	  printf("Ball! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
	  if(xpre == 0 && ypre == 0)
	    {
	      xpre = p[0];
	      ypre = p[1];
	      cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
	      cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
	    }
	  else
	    {
	      if((abs(p[0] - xpre) < 100) && (abs(p[1] - ypre) < 100))
		{
		  cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
		  cvCircle( frame, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
		}
	      else;
	    }
	  xpre = p[0];
	  ypre = p[1];
	}
 /*cvGetSeqElem(circles,i) - This gets each sequence element form the memory storage and puts in the pointer p. Now p has three variables
(p[0],p[1]) - (x,y) coordinates of circle
p[2] - radius of the circle
Link Followed - http://opencv.willowgarage.com/documentation/dynamic_structures.html
 */     
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

