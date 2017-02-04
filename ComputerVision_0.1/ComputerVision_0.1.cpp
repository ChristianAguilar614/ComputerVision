// ComputerVision_0.1.cpp : Defines the entry point for the console application. To test stereoscopic vision using open source software (openCV)
//							This program should define a basic principle of the functionality of two cameras to find distance of any object. To
//							perform this task, a stictched up map displaying distances of every pixle will be generated that can then be scanned
//							for particular patterns.
//
// Version 0.1
// Christian Aguilar

#include <iostream>
	//#include "stdafx.h"
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"


using namespace cv;
using namespace std;

int main(int, char**)
{

	VideoCapture cam(0); // open Camera #1
	//VideoCapture cam2(1);// open Camera #2

	// set video capture properties for MacBook' iSight camera
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 500);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 600);

	if( !cam.isOpened() )
	{
		cerr << "***Could not initialize capturing...***\n";
		cerr << "Current parameter's value: \n";
		return -1;
	}


	Mat edges;
	Mat3b frame0;
	for (;;)
	{
		cam >> frame0;

		if(frame0.empty()){
			cerr << "frame is empty" << endl;
			break;
		}


		cvtColor(frame0, edges, CV_BGR2GRAY); //to Gray image
		GaussianBlur(edges, edges, Size(3, 3), 1.5, 1.5); //Reduce noise
		Canny(edges, edges, 10, 70, 3); //Find edges and ommit everything else

		//show both raw and edges
		imshow("Edges", edges);
		imshow("Raw", frame0);

		if (waitKey(30) >= 'q') break; //quit when 'q' is pressed
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
