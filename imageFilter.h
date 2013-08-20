#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H
#include <cv.h>
#include <highgui.h>
#include <iostream>

class imageFilter
{
public:
	
	void expressionFilter(int alpha, int beta);

};
#endif

/*filters image contrast and brightness based on expression */
 void imageFilter::expressionFilter(int alpha, int beta)
 {

	 cv::Mat myImage;
	 char buffer [50];
	
	 sprintf(buffer,"mainePic.jpg");
	 myImage = cv::imread(buffer);

	 cv::Mat new_image = cv::Mat::zeros( myImage.size(), myImage.type() );
	 myImage.convertTo(new_image, -1, alpha, beta);

	 cv::imshow("New Image", new_image);
 
 
 }

