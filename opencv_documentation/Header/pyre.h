//This header file is used to resize an image

IplImage* pyre(IplImage* image, int i, int j)
{
	assert(image->width%i == 0 && image->height%2 == 0);
	
	IplImage* out = cvCreateImage(cvSize(image->width/2, image->height/2), image->depth, image->nChannels);

	cvPyrDown(image, out, IPL_GAUSSIAN_5x5);
	return(out);
}

	
