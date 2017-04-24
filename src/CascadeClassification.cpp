//============================================================================
// Name        : CascadeClassification.cpp
// Author      : Christian Aguilar
// Version     :
// Copyright   : @2017
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "string_helper.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String face_cascade_name = "/usr/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
String fullbody_cascade_name = "/usr/share/OpenCV/haarcascades/haarcascade_fullbody.xml";
CascadeClassifier face_cascade;
CascadeClassifier fullbody_cascade;
string window_name = "Capture - Face detection";
//RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
CvCapture* capture;
Mat frame;

//-- 1. Load the cascades
if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
if( !fullbody_cascade.load( fullbody_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

//-- 2. Read the video stream
capture = cvCaptureFromCAM( 1 ); //using external usb camera
if( capture )
{
 while( true )
 {
frame = cvQueryFrame( capture );

//-- 3. Apply the classifier to the frame
   if( !frame.empty() )
   { detectAndDisplay( frame ); }
   else
   { printf(" --(!) No captured frame -- Break!"); break; }

   int c = waitKey(10);
   if( (char)c == 'c' ) { break; }
  }
}
return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
Mat frame_gray;
clock_t frame_timer = clock(); //begin time counter for FPS

cvtColor( frame, frame_gray, CV_BGR2GRAY );
equalizeHist( frame_gray, frame_gray );

//-- Detect faces
std::vector<Rect> faces;
face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

for( size_t i = 0; i < faces.size(); i++ ){
	Point face_center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
	ellipse( frame, face_center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 4, 8, 0 );
	Mat faceROI = frame_gray( faces[i] );
}

//-- Full Body Detection
std::vector<Rect> body;
fullbody_cascade.detectMultiScale( frame_gray, body, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

/*int start = 0;
int end = body.size()-1;
Point p1(body[start].x + body[start].height*0.5, body[start].y + body[start].width*0.5 );
Point p2(body[end].x + body[end].height*0.5, body[end].y + body[end].width*0.5);
cv::rectangle( frame, p1, p2, Scalar( 0, 255, 0 ));

for(size_t i = 0; i<body.size(); i++){
	Mat faceROI = frame_gray( body[i] );
}*/

//-- Visual Display w/ FPS
double frame_period = (clock() - frame_timer); //Displaced time period
//cout << frame_period << " divided by " << CLOCKS_PER_SEC << " = " << frame_period/CLOCKS_PER_SEC << endl;
double fps = 1/(frame_period/CLOCKS_PER_SEC); //convert to frequency
putText(frame, stringify(fps), cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,0,0), 1, CV_AA);

imshow( window_name, frame );
}
