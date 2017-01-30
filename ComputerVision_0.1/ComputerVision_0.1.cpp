// ComputerVision_0.1.cpp : Defines the entry point for the console application. To test stereoscopic vision using open source software (openCV)
//							This program should define a basic principle of the functionality of two cameras to find distance of any object. To
//							perform this task, a stictched up map displaying distances of every pixle will be generated that can then be scanned
//							for particular patterns.
//
// Version 0.1
// Christian Aguilar

#include <iostream>
#include "stdafx.h"
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;

int main(int, char**)
{
	VideoCapture cam(1); // open Camera #1
						 //VideoCapture cam2(1);// open Camera #2
	if (!cam.isOpened()) return 1;
	//if(!cam2.isOpened()) return 1;

	Mat edges;
	//namedWindow("Video",1);
	//Mat3b frame1;
	Mat3b frame0;
	for (;;)
	{
		cam >> frame0;
		cvtColor(frame0, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(3, 3), 1.5, 1.5);
		Canny(edges, edges, 10, 70, 3);
		imshow("Edges", edges);
		imshow("Raw", frame0);
		if (waitKey(30) >= 'q') break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}