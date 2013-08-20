#ifndef TRACKINGCLASS_H
#define TRACKINGCLASS_H
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include <iostream>
using namespace std;

#define  TPL_WIDTH       12      /* template width       */
#define  TPL_HEIGHT      12     /* template height      */
#define  WINDOW_WIDTH    24      /* search window width  */
#define  WINDOW_HEIGHT   24      /* search window height */
#define  THRESHOLD       0.25

class trackingClass
{
public:

	trackingClass()
	{
		int left_eye_tracking = 0,right_eye_tracking = 0, left_mouth_tracking = 0, right_mouth_tracking = 0, 
			nose_tracking = 0, count = 0, neutralDataCaptured = 0;
			smile = false, frown = false, eyeRaised = false, eyeFurrow = false;
	}

	void trackLeftEye(); //first click
	void trackRightEye(); //second click
	void trackLeftMouth(); // third
	void trackRightMouth(); // fourth
	void trackNose(); // fifth
	void captureNeutralFace(); //space bar
	void resetData(); //escape key
	void getFaceData();

	int count;
	int neutralDataCaptured;
	int left_eye_tracking, right_eye_tracking, left_mouth_tracking, right_mouth_tracking, nose_tracking, center_mouth_tracking;
	int object_x0_left_eye, object_y0_left_eye, object_x0_right_eye, object_y0_right_eye,
		object_x0_left_mouth,object_y0_left_mouth,object_x0_right_mouth,object_y0_right_mouth,
		object_x0_nose,object_y0_nose;
	int neutral_x0_left_eye,neutral_y0_left_eye,neutral_x0_right_eye,neutral_y0_right_eye,
		neutral_x0_left_mouth,neutral_y0_left_mouth,neutral_x0_right_mouth,neutral_y0_right_mouth,
		neutral_x0_nose, neutral_y0_nose;
	float distance_left_eye, distance_right_eye, distance_left_mouth,distance_right_mouth;
	float neutral_distance_left_eye, neutral_distance_right_eye, neutral_distance_left_mouth, neutral_distance_right_mouth;
	float difference_left_eye, difference_right_eye, difference_left_mouth,difference_right_mouth;
	float pleasure, arousal, pleasurePoint, arousalPoint;
	
	bool smile,frown,eyeRaised,eyeFurrow;


	IplImage *frame, *tmplLeftEye, *tmplRightEye, *tmLeftEye, *tmRightEye,
					*tmplLeftMouth, *tmplRightMouth, *tmLeftMouth, *tmRightMouth,
					*tmplNose,*tmNose;

};

#endif


/* track object */
void trackingClass::trackLeftEye()
{
    CvPoint minloc, maxloc;
    double  minval, maxval;
 
    /* setup position of search window */
    int win_x0 = object_x0_left_eye - ( ( WINDOW_WIDTH  - TPL_WIDTH  ) / 2 );
    int win_y0 = object_y0_left_eye - ( ( WINDOW_HEIGHT - TPL_HEIGHT ) / 2 );
   
   
    /* search object in search window */
    cvSetImageROI( frame,
                   cvRect( win_x0,
                           win_y0,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT ) );

    cvMatchTemplate( frame, tmplLeftEye, tmLeftEye, CV_TM_SQDIFF_NORMED );
    cvMinMaxLoc( tmLeftEye, &minval, &maxval, &minloc, &maxloc, 0 );
    cvResetImageROI( frame );
   
    /* if object found... */
    if( minval <= THRESHOLD ) {
        /* save object's current location */
        object_x0_left_eye = win_x0 + minloc.x;
        object_y0_left_eye = win_y0 + minloc.y;
 
        /* and draw a box there */
		        cvRectangle( frame,
                     cvPoint( object_x0_left_eye, object_y0_left_eye ),
                     cvPoint( object_x0_left_eye + TPL_WIDTH,
                              object_y0_left_eye + TPL_HEIGHT ),
                     cvScalar( 0, 0, 0, 0 ), 1, 0, 0 );
    } else {
        /* if not found... */
        fprintf( stdout, "Lost Left Eye.\n" );
        left_eye_tracking = 0;
    }
}

/*track right eye*/
void trackingClass::trackRightEye()
{
    CvPoint minloc, maxloc;
    double  minval, maxval;
 
    /* setup position of search window */
    int win_x0 = object_x0_right_eye - ( ( WINDOW_WIDTH  - TPL_WIDTH  ) / 2 );
    int win_y0 = object_y0_right_eye - ( ( WINDOW_HEIGHT - TPL_HEIGHT ) / 2 );
   
   
    /* search object in search window */
    cvSetImageROI( frame,
                   cvRect( win_x0,
                           win_y0,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT ) );

    cvMatchTemplate( frame, tmplRightEye, tmRightEye, CV_TM_SQDIFF_NORMED );
    cvMinMaxLoc( tmRightEye, &minval, &maxval, &minloc, &maxloc, 0 );
    cvResetImageROI( frame );
   
    /* if object found... */
    if( minval <= THRESHOLD ) {
        /* save object's current location */
        object_x0_right_eye = win_x0 + minloc.x;
        object_y0_right_eye = win_y0 + minloc.y;
 
        /* and draw a box there */
        cvRectangle( frame,
                     cvPoint( object_x0_right_eye, object_y0_right_eye ),
                     cvPoint( object_x0_right_eye + TPL_WIDTH,
                              object_y0_right_eye + TPL_HEIGHT ),
                     cvScalar( 0, 0, 255, 0 ), 1, 0, 0 );
    } else {
        /* if not found... */
        fprintf( stdout, "Lost Right Eye.\n" );
        right_eye_tracking = 0;
    }
}

/* track Left Mouth */
void trackingClass::trackLeftMouth()
{
	
    CvPoint minloc, maxloc;
    double  minval, maxval;
 
    /* setup position of search window */
    int win_x0 = object_x0_left_mouth - ( ( WINDOW_WIDTH  - TPL_WIDTH  ) / 2 );
    int win_y0 = object_y0_left_mouth - ( ( WINDOW_HEIGHT - TPL_HEIGHT ) / 2 );
   
   
    /* search object in search window */
    cvSetImageROI( frame,
                   cvRect( win_x0,
                           win_y0,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT ) );

    cvMatchTemplate( frame, tmplLeftMouth, tmLeftMouth, CV_TM_SQDIFF_NORMED );
    cvMinMaxLoc( tmLeftMouth, &minval, &maxval, &minloc, &maxloc, 0 );
    cvResetImageROI( frame );
   
    /* if object found... */
    if( minval <= THRESHOLD ) {
        /* save object's current location */
        object_x0_left_mouth = win_x0 + minloc.x;
        object_y0_left_mouth = win_y0 + minloc.y;
 
        /* and draw a box there */
		        cvRectangle( frame,
                     cvPoint( object_x0_left_mouth, object_y0_left_mouth ),
                     cvPoint( object_x0_left_mouth + TPL_WIDTH,
                              object_y0_left_mouth + TPL_HEIGHT ),
                     cvScalar( 0, 255, 0, 0 ), 1, 0, 0 );
    } else {
        /* if not found... */
        fprintf( stdout, "Lost Left Mouth.\n" );
        left_mouth_tracking = 0;
    }
}

/*track right mouth*/
void trackingClass::trackRightMouth()
{
	    CvPoint minloc, maxloc;
    double  minval, maxval;
 
    /* setup position of search window */
    int win_x0 = object_x0_right_mouth - ( ( WINDOW_WIDTH  - TPL_WIDTH  ) / 2 );
    int win_y0 = object_y0_right_mouth - ( ( WINDOW_HEIGHT - TPL_HEIGHT ) / 2 );
   
   
    /* search object in search window */
    cvSetImageROI( frame,
                   cvRect( win_x0,
                           win_y0,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT ) );

    cvMatchTemplate( frame, tmplRightMouth, tmRightMouth, CV_TM_SQDIFF_NORMED );
    cvMinMaxLoc( tmRightMouth, &minval, &maxval, &minloc, &maxloc, 0 );
    cvResetImageROI( frame );
   
    /* if object found... */
    if( minval <= THRESHOLD ) {
        /* save object's current location */
        object_x0_right_mouth = win_x0 + minloc.x;
        object_y0_right_mouth = win_y0 + minloc.y;
 
        /* and draw a box there */
        cvRectangle( frame,
                     cvPoint( object_x0_right_mouth, object_y0_right_mouth ),
                     cvPoint( object_x0_right_mouth + TPL_WIDTH,
                              object_y0_right_mouth + TPL_HEIGHT ),
                     cvScalar( 255, 0, 0, 0 ), 1, 0, 0 );
    } else {
        /* if not found... */
        fprintf( stdout, "Lost right mouth.\n" );
        right_mouth_tracking = 0;
    }
}

/*track nose*/
void trackingClass::trackNose()
{
	    CvPoint minloc, maxloc;
    double  minval, maxval;
 
    /* setup position of search window */
    int win_x0 = object_x0_nose - ( ( WINDOW_WIDTH  - TPL_WIDTH  ) / 2 );
    int win_y0 = object_y0_nose - ( ( WINDOW_HEIGHT - TPL_HEIGHT ) / 2 );
   
   
    /* search object in search window */
    cvSetImageROI( frame,
                   cvRect( win_x0,
                           win_y0,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT ) );

    cvMatchTemplate( frame, tmplNose, tmNose, CV_TM_SQDIFF_NORMED );
    cvMinMaxLoc( tmNose, &minval, &maxval, &minloc, &maxloc, 0 );
    cvResetImageROI( frame );
   
    /* if object found... */
    if( minval <= THRESHOLD ) {
        /* save object's current location */
        object_x0_nose = win_x0 + minloc.x;
        object_y0_nose = win_y0 + minloc.y;
 
        /* and draw a box there */
        cvRectangle( frame,
                     cvPoint( object_x0_nose, object_y0_nose ),
                     cvPoint( object_x0_nose + TPL_WIDTH,
                              object_y0_nose + TPL_HEIGHT ),
                     cvScalar( 255, 0, 0, 0 ), 1, 0, 0 );
    } else {
        /* if not found... */
        fprintf( stdout, "Lost nose.\n" );
        nose_tracking = 0;
    }
}

/*store neutral face data*/
void trackingClass::captureNeutralFace()
{	
	
	cout<<"Capturing neutral face data"<<endl;
	/*storing neutral data*/
	neutral_x0_left_eye = object_x0_left_eye;
	neutral_y0_left_eye = object_y0_left_eye; 
	neutral_x0_right_eye = object_x0_right_eye; 
	neutral_y0_right_eye = object_y0_right_eye;
    neutral_x0_left_mouth = object_x0_left_mouth;
	neutral_y0_left_mouth = object_y0_left_mouth;
	neutral_x0_right_mouth = object_x0_right_mouth;
	neutral_y0_right_mouth = object_y0_right_mouth;
	neutral_x0_nose = object_x0_nose;
	neutral_y0_nose = object_y0_nose;

	/*calculate neutral expression distances*/
	
	neutral_distance_left_eye = sqrt((float)((object_x0_left_eye - object_x0_nose)*(object_x0_left_eye - object_x0_nose) + (object_y0_left_eye - object_y0_nose)*(object_y0_left_eye - object_y0_nose)));
	neutral_distance_right_eye = sqrt((float)((object_x0_right_eye - object_x0_nose)*(object_x0_right_eye - object_x0_nose) + (object_y0_right_eye - object_y0_nose)*(object_y0_right_eye - object_y0_nose)));
	neutral_distance_left_mouth = sqrt((float)((object_x0_left_mouth - object_x0_nose)*(object_x0_left_mouth - object_x0_nose) + (object_y0_left_mouth - object_y0_nose)*(object_y0_left_mouth - object_y0_nose)));
	neutral_distance_right_mouth = sqrt((float)((object_x0_right_mouth - object_x0_nose)*(object_x0_right_mouth - object_x0_nose) + (object_y0_right_mouth - object_y0_nose)*(object_y0_right_mouth - object_y0_nose)));

	/*boolean for neutral face data*/
	neutralDataCaptured = 1;

	cout<<"neutral distance left eye"<<neutral_distance_left_eye<<endl;
	cout<<"distance left eye"<<distance_left_eye<<endl;

}

/*capture face data*/
void trackingClass::getFaceData()
{
	distance_left_eye = sqrt((float)((object_x0_left_eye - object_x0_nose)*(object_x0_left_eye - object_x0_nose) + (object_y0_left_eye - object_y0_nose)*(object_y0_left_eye - object_y0_nose)));
	distance_right_eye = sqrt((float)((object_x0_right_eye - object_x0_nose)*(object_x0_right_eye - object_x0_nose) + (object_y0_right_eye - object_y0_nose)*(object_y0_right_eye - object_y0_nose)));
	distance_left_mouth = sqrt((float)((object_x0_left_mouth - object_x0_nose)*(object_x0_left_mouth - object_x0_nose) + (object_y0_left_mouth - object_y0_nose)*(object_y0_left_mouth - object_y0_nose)));
	distance_right_mouth = sqrt((float)((object_x0_right_mouth - object_x0_nose)*(object_x0_right_mouth - object_x0_nose) + (object_y0_right_mouth - object_y0_nose)*(object_y0_right_mouth - object_y0_nose)));
	
	difference_left_eye = distance_left_eye - neutral_distance_left_eye;
	difference_right_eye = distance_right_eye - neutral_distance_right_eye;
	difference_left_mouth = distance_left_mouth - neutral_distance_left_mouth;
	difference_right_mouth = distance_right_mouth - neutral_distance_right_mouth;

	cout<<distance_left_mouth/neutral_distance_left_mouth<<endl;
	/*initialize pleasure and arousal*/
	pleasure = 0;
	arousal = 0;
	
	/*eye raised?*/
	if (distance_left_eye/neutral_distance_left_eye > 1.03  && distance_right_eye/neutral_distance_right_eye > 1.03)
	{
		pleasure = pleasure + .5;
		arousal = arousal + .7;
		cout<<"eye raised"<<endl;
		eyeRaised = true;
		eyeFurrow = false;
	}

	/*brow furrowed?*/
	else if (distance_left_eye/neutral_distance_left_eye < .94 && distance_right_eye/neutral_distance_right_eye < .94)
	{
		pleasure = pleasure - .5;
		arousal = arousal -.7;
		cout<<"eye furrowed"<<endl;
		eyeFurrow = true;
		eyeRaised = false;
	}
	
	else
	{	eyeRaised = false;
		eyeFurrow = false;
	}

	/*smile*/
	if (distance_left_mouth/neutral_distance_left_mouth < .96 && distance_right_mouth/neutral_distance_right_mouth <.97)
	{
		pleasure = pleasure + 1;
		cout<<"smile"<<endl;
		smile = true;
		frown = false;
	}

	/*frown*/
	else if (distance_left_mouth/neutral_distance_left_mouth > 1.05 && distance_right_mouth/neutral_distance_right_mouth > 1.05)
	{
		pleasure = pleasure - 1;
		cout<<"frown detected"<<endl;
		frown = true;
		smile = false;
	}



	else
	{
		smile = false;
		frown = false;
	}

	cvNamedWindow( "Facial Expression",CV_WINDOW_AUTOSIZE);
		
	  /*create Facial Expression Data Window*/
	IplImage *FacialExpression = cvCreateImage(cvSize(300,300),IPL_DEPTH_32F,3);
	cvLine(FacialExpression,cvPoint(150,0),cvPoint(150,300),cvScalar( 255, 0, 0, 0 ),2);
	cvLine(FacialExpression,cvPoint(0,150),cvPoint(300,150),cvScalar( 255, 0, 0, 0 ),2);

	/*set Pleasure Point*/
	if (pleasure == 1)
	{
	pleasurePoint = 250;
	}
	else if (pleasure == -1)
	pleasurePoint = 50;

	else if (pleasure == .5)
	{	pleasurePoint = 200; }

	else if (pleasure == -.5)
	{	pleasurePoint = 100; }

	else if (pleasure == 1.5)
	{	pleasurePoint = 300;  }

	else if (pleasure == -1.5)
	{	pleasurePoint = 0; }

	else
	{	pleasurePoint = 150;	}

	/*set arousal point*/
	if (arousal  > 0)
	{ arousalPoint = 45; }

	else if (arousal < 0)
	{ arousalPoint = 255; }

	else
	{	arousalPoint = 150; }

	cvCircle(FacialExpression,cvPoint(pleasurePoint,arousalPoint),5,cvScalar(0,0,255,0),2);
	cvShowImage("Facial Expression",FacialExpression);
	cvWaitKey(50);

}

/*reset data*/
void trackingClass::resetData()
{
	count =  0;
	left_eye_tracking = 0;
	right_eye_tracking = 0;
	left_mouth_tracking = 0;
	right_mouth_tracking = 0;
	nose_tracking = 0;
	neutralDataCaptured = 0;
	frown = false;
	eyeRaised = false;
	eyeFurrow = false;
	smile = false;


}