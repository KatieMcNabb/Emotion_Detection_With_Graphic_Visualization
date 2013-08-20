#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "trackingClass.h"
#include "imageFilter.h"
 
#define  TPL_WIDTH       12      /* template width       */
#define  TPL_HEIGHT      12      /* template height      */
#define  WINDOW_WIDTH    24      /* search window width  */
#define  WINDOW_HEIGHT   24      /* search window height */
#define  THRESHOLD       0.25
 
		
trackingClass faceTrack;		/*tracking class object*/
imageFilter filter;				/*filter class object*/

/* mouse handler */
void mouseHandler( int event, int x, int y, int flags, void *param);


int main( int argc, char** argv )
{

    CvCapture *capture;
    int key = 0;

    capture = cvCaptureFromCAM( 0 );
    if( !capture ) return 1;
 
    faceTrack.frame = cvQueryFrame( capture );
    if ( !faceTrack.frame ) return 1;
   
    /* create template image */
	faceTrack.tmplLeftEye = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),
                         faceTrack.frame->depth, faceTrack.frame->nChannels );

	faceTrack.tmplRightEye = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),
                         faceTrack.frame->depth, faceTrack.frame->nChannels );

    faceTrack.tmplLeftMouth = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),
                         faceTrack.frame->depth, faceTrack.frame->nChannels );

	faceTrack.tmplRightMouth = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),
                         faceTrack.frame->depth, faceTrack.frame->nChannels );
	
	faceTrack.tmplNose = cvCreateImage( cvSize( TPL_WIDTH, TPL_HEIGHT ),
                         faceTrack.frame->depth, faceTrack.frame->nChannels );

   
    /* create image for template matching result */
    faceTrack.tmLeftEye = cvCreateImage( cvSize( WINDOW_WIDTH  - TPL_WIDTH  + 1,  
                                WINDOW_HEIGHT - TPL_HEIGHT + 1 ),
                        IPL_DEPTH_32F, 1 );

	faceTrack.tmRightEye = cvCreateImage( cvSize( WINDOW_WIDTH  - TPL_WIDTH  + 1,
                                WINDOW_HEIGHT - TPL_HEIGHT + 1 ),
                        IPL_DEPTH_32F, 1 );

	faceTrack.tmLeftMouth = cvCreateImage( cvSize( WINDOW_WIDTH  - TPL_WIDTH  + 1,  
                                WINDOW_HEIGHT - TPL_HEIGHT + 1 ),
                        IPL_DEPTH_32F, 1 );

	faceTrack.tmRightMouth = cvCreateImage( cvSize( WINDOW_WIDTH  - TPL_WIDTH  + 1,  
                                WINDOW_HEIGHT - TPL_HEIGHT + 1 ),
                        IPL_DEPTH_32F, 1 );

	faceTrack.tmNose = cvCreateImage( cvSize( WINDOW_WIDTH  - TPL_WIDTH  + 1,  
                                WINDOW_HEIGHT - TPL_HEIGHT + 1 ),
                        IPL_DEPTH_32F, 1 );
   
  
    cvNamedWindow( "video", CV_WINDOW_NORMAL | CV_WINDOW_FREERATIO);
    cvSetMouseCallback( "video", mouseHandler, NULL );


   
    while( key != 'q' ) {
        faceTrack.frame = cvQueryFrame( capture );
        if( !faceTrack.frame ) break;
 
       
        /* perform tracking if template is available */
        if( faceTrack.left_eye_tracking ) faceTrack.trackLeftEye();
		if (faceTrack.right_eye_tracking) faceTrack.trackRightEye();
		if (faceTrack.left_mouth_tracking) faceTrack.trackLeftMouth();
		if (faceTrack.right_mouth_tracking) faceTrack.trackRightMouth();
		if (faceTrack.nose_tracking) faceTrack.trackNose();

		/*if user hits the space bar capture neutral face data*/
		if (key == 32)
		{  faceTrack.captureNeutralFace(); }

		/*if user hits escape key reset data*/
		if (key == 27)
		{	faceTrack.resetData(); }

		/*if we have neutral face data begin to capture facial expressions*/
		if (faceTrack.neutralDataCaptured)
		{	faceTrack.getFaceData(); }

		
		/*if user hits c key display image based on current facial expression*/
		if (key == 'c')
		{
		if (faceTrack.smile == true && faceTrack.eyeRaised == true)
		{
			filter.expressionFilter(3.0,100);

		}
		else if (faceTrack.smile == true && faceTrack.eyeFurrow == true)
		{
			filter.expressionFilter(1.0,100 );

		}
		else if (faceTrack.frown == true && faceTrack.eyeRaised == true)
		{
			filter.expressionFilter(3.0,20);

		}
		else if (faceTrack.frown == true && faceTrack.eyeFurrow == true)
		{
			filter.expressionFilter(1.0,20);

		}
		else if (faceTrack.smile == true)
		{
			filter.expressionFilter(1.5,100);

		}

		else if (faceTrack.frown == true)
		{
			filter.expressionFilter(1.5,20);
		}

		else if (faceTrack.eyeRaised == true)
		{
			filter.expressionFilter(3.0,50);
		}

		else if (faceTrack.eyeFurrow == true)
		{
			filter.expressionFilter(1.0,50);
		}

		else
			filter.expressionFilter(1.5,150);
       
		}

        cvShowImage( "video", faceTrack.frame );
        key = cvWaitKey( 1 );
   
	}

    /* free window */
    cvDestroyWindow( "video" );
   
    return 0;
}


/*mouse event handler*/
void mouseHandler( int event, int x, int y, int flags, void *param)
{
	//Single object tracking code source:  http://nashruddin.com/eyetracking-track-user-eye.htm 

    /*save left eye template */
    if( event == CV_EVENT_LBUTTONDOWN && faceTrack.count == 0) {
        faceTrack.object_x0_left_eye = x - ( TPL_WIDTH  / 2 );
        faceTrack.object_y0_left_eye = y - ( TPL_HEIGHT / 2 );
       
        cvSetImageROI( faceTrack.frame,
                       cvRect( faceTrack.object_x0_left_eye,
                               faceTrack.object_y0_left_eye,
                               TPL_WIDTH,
                               TPL_HEIGHT ) );
        cvCopy( faceTrack.frame, faceTrack.tmplLeftEye, NULL );
        cvResetImageROI( faceTrack.frame );
 
        cout<<"Starting tracking of left eye..."<<endl;
        faceTrack.left_eye_tracking = 1;
		faceTrack.count++;
		}
	   
	/*track right eye*/
	else if( event == CV_EVENT_LBUTTONDOWN && faceTrack.count == 1) {
        faceTrack.object_x0_right_eye = x - ( TPL_WIDTH  / 2 );
        faceTrack.object_y0_right_eye = y - ( TPL_HEIGHT / 2 );
       
        cvSetImageROI( faceTrack.frame,
                       cvRect( faceTrack.object_x0_right_eye,
                               faceTrack.object_y0_right_eye,
                               TPL_WIDTH,
                               TPL_HEIGHT ) );
        cvCopy(faceTrack.frame,faceTrack.tmplRightEye, NULL );
        cvResetImageROI( faceTrack.frame );
 
        cout<<"Starting tracking of right eye..."<<endl;
        faceTrack.right_eye_tracking = 1;
		faceTrack.count++;
    }

	/*track left mouth*/
	else if (event == CV_EVENT_LBUTTONDOWN && faceTrack.count == 2)
	{
		
        faceTrack.object_x0_left_mouth = x - ( TPL_WIDTH  / 2 );
        faceTrack.object_y0_left_mouth = y - ( TPL_HEIGHT / 2 );
       
        cvSetImageROI( faceTrack.frame,
                       cvRect( faceTrack.object_x0_left_mouth,
                               faceTrack.object_y0_left_mouth,
                               TPL_WIDTH,
                               TPL_HEIGHT ) );
        cvCopy( faceTrack.frame, faceTrack.tmplLeftMouth, NULL );
        cvResetImageROI( faceTrack.frame );
 
     
        cout<<"Starting tracking of left mouth..."<<endl;
        faceTrack.left_mouth_tracking = 1;
		faceTrack.count++;

	}
	/*track right mouth*/
	else if (event == CV_EVENT_LBUTTONDOWN && faceTrack.count == 3)
	{
		faceTrack.object_x0_right_mouth = x - ( TPL_WIDTH  / 2 );
        faceTrack.object_y0_right_mouth = y - ( TPL_HEIGHT / 2 );
       
        cvSetImageROI( faceTrack.frame,
                       cvRect( faceTrack.object_x0_right_mouth,
                               faceTrack.object_y0_right_mouth,
                               TPL_WIDTH,
                               TPL_HEIGHT ) );
        cvCopy( faceTrack.frame, faceTrack.tmplRightMouth, NULL );
        cvResetImageROI( faceTrack.frame );
 
      
        cout<<"Starting tracking of right mouth..."<<endl;
        faceTrack.right_mouth_tracking = 1;
		faceTrack.count++;

	}

	/*track nose*/
	else if (event == CV_EVENT_LBUTTONDOWN && faceTrack.count == 4)
	{
		faceTrack.object_x0_nose = x - ( TPL_WIDTH  / 2 );
        faceTrack.object_y0_nose = y - ( TPL_HEIGHT / 2 );
       
        cvSetImageROI( faceTrack.frame,
                       cvRect( faceTrack.object_x0_nose,
                               faceTrack.object_y0_nose,
                               TPL_WIDTH,
                               TPL_HEIGHT ) );
        cvCopy( faceTrack.frame, faceTrack.tmplNose, NULL );
        cvResetImageROI( faceTrack.frame );
 
        
        cout<<"Starting tracking of nose..."<<endl;
		faceTrack.nose_tracking = 1;
		faceTrack.count++;

	}


}




