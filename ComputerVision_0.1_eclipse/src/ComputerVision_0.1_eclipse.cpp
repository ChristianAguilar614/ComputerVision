// ComputerVision_0.1.cpp : Defines the entry point for the console application. To test stereoscopic vision using open source software (openCV)
//							This program should define a basic principle of the functionality of two cameras to find distance of any object. To
//							perform this task, a stictched up map displaying distances of every pixle will be generated that can then be scanned
//							for particular patterns.
//
// Version 0.1
// Christian Aguilar

#include <iostream>

#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"


using namespace cv;
using namespace std;

int main(int, char**)
{
	const int cameraCount = 2;

	VideoCapture cam[cameraCount];
	for (int i = 0; i < cameraCount; i++) { //initializes two non internal cameras
		cam[i] = VideoCapture(i+1);

		// set video capture properties for camera, forcing lower res
		cam[i].set(CV_CAP_PROP_FRAME_WIDTH, 640);
		cam[i].set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	}


	VideoCapture camL = cam[0]; // open Camera #1
	VideoCapture camR = cam[1];// open Camera #2


	Ptr<StereoBM> createStereoBM(int numDisparities=0, int blockSize=21);

	Ptr<StereoBM> sbm = StereoBM::create(16, 7);


	if( !camL.isOpened() )
	{
		cerr << "***Could not initialize capturing...***\n";
		cerr << "Current parameter's value: \n";
		return -1;
	}


	Mat edges,disparity, ImageL, ImageR;
	for (;;)
	{
		camL >> ImageL;
		camR >> ImageR;

		if(ImageL.empty() || ImageR.empty()){
			cerr << "a frame is empty" << endl;
			break;
		}

		cvtColor(ImageL, ImageL, CV_BGR2GRAY); //to Gray image
		cvtColor(ImageR, ImageR, CV_BGR2GRAY); //to Gray image

		sbm->compute(ImageL, ImageR, disparity);


		GaussianBlur(ImageL, edges, Size(3, 3), 1.5, 1.5); //Reduce noise
		Canny(edges, edges, 10, 70, 3); //Find edges and ommit everything else

		//show both raw and edges
		imshow("Edges", edges);
		imshow("Raw", ImageL);
		imshow("Disparity",disparity);

		if (waitKey(30) >= 'q') break; //quit when 'q' is pressed
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
