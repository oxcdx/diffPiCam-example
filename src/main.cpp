#include "ofMain.h"
#include "ofApp.h"

int main()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetupOpenGL(1920, 1080, OF_WINDOW);
	ofRunApp( new ofApp());
}
