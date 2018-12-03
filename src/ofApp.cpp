#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {
	
	vW = 640;
	vH = 360;
	
	ofPixVersion = false; 
	cvVersion = true; 
	cvAccumVersion = false;
   
    alpha = 0.001;
    
    settings.sensorWidth = vW;
    settings.sensorHeight = vH;
    settings.framerate = 24;
    settings.enableTexture = true;
    settings.enablePixels = true;
    //settings.brightness = 50;
    
    videoGrabber.setup(settings);
    
    // for forcing 255 alpha
	allocate(alpha255, vW, vH, CV_8UC4);
	alpha255 = Scalar(0, 0, 0, 255);
  
}	

//--------------------------------------------------------------
void ofApp::update() {
	
	if(videoGrabber.isFrameNew()) {
	
		if(ofPixVersion) {

				absdiff(videoGrabber.getPixels(), previous, diff);				
				diff.update();

				copy(videoGrabber.getPixels(), previous);
				
		}
		else if (cvVersion) {
						
				frameMat = toCv(videoGrabber.getPixels());
				
				//uncomment for greyscale version
				//cvtColor(frameMat, greyMat, CV_BGR2GRAY);
				
				absdiff(frameMat, bgMat, diffMat);
				
				//uncomment to force alpha 255
				//add(diffMat, outputImage, diffMatClr);

				copy(frameMat, bgMat);

		}
		else if (cvAccumVersion) {
					
			if(frameMatAccum.empty()) {
				
					frameMatAccum = ofxCv::toCv(videoGrabber.getPixels());

					frameMatAccum.convertTo(accumMat, CV_32F);
					
			}
			else {
				
					frameMat = toCv(videoGrabber.getPixels());
					
					//uncomment for greyscale version
					//cvtColor(frameMat, greyMat, CV_BGR2GRAY);
					
					accumulateWeighted(frameMatAccum, accumMat, alpha);
					convertScaleAbs(accumMat, accumMatScaled); 
					
					absdiff(accumMatScaled, bgMat, diffMat);
					
					//uncomment to force alpha 255
					//add(diffMat, outputImage, diffMatClr);

					copy(frameMat, bgMat);
					
			}
		}
	}
	
}


//--------------------------------------------------------------
void ofApp::draw(){
	
	//as alpha channel may be zero
	ofDisableAlphaBlending();
	
	if(ofPixVersion) {
		diff.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	else if (cvVersion || cvAccumVersion) {
		if(!diffMat.empty()) {
			
			toOf(diffMat, backgroundOutputImage);
			backgroundOutputImage.update();
			backgroundOutputImage.draw(0, 0, ofGetWidth(), ofGetHeight());
			
		}
	}
    
	stringstream info;
	info << "APP FPS: " << ofGetFrameRate() << endl;
	info << endl;

    ofDrawBitmapStringHighlight(info.str(), 100, 100, ofColor(ofColor::black, 90), ofColor::yellow);

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
	//ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    switch (key) 
    {
        case '1':
        {
            ofPixVersion = true;
            cvVersion = false;
            cvAccumVersion = false;
            break;
        }
        case '2':
        {
			cvVersion = true;
			cvAccumVersion = false;
			ofPixVersion = false;
            break;
        }  
        case '3':
        {
			cvAccumVersion = true;
			cvVersion = false;
            ofPixVersion = false;
            break;
        } 
        
    }
}

