#pragma once

#include "ofxCv.h"
#include "ofMain.h"
#include "ofxOMXVideoGrabber.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();
    
    void keyPressed(int key);
    
    ofxOMXVideoGrabber videoGrabber;
    ofxOMXCameraSettings settings;
    
    bool ofPixVersion, cvVersion, cvAccumVersion;
    int vW, vH;
    float alpha;
    
    cv::Mat bgMat, frameMat, frameMatAccum, accumMat, accumMatScaled, diffMat, diffMatClr,  greyMat, alpha255;
	
	ofPixels previous;
	ofImage backgroundOutputImage, diff, diff1;

};

