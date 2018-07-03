#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	OF Settings
	ofBackground(0);
	ofSetFrameRate(30);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(true);

	//	Connect Arduino
	bool b_connect = ard.connect("COM3", 57600);

	if (!b_connect)
		ofLogWarning("Arduino connection") << "FAILED!";
	else
		ofLogNotice("Arduino connection") << "SUCCESS!";

	ard.sendFirmwareVersionRequest();

	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArd = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version){

	//	Remove listener
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);

	//	It is now safe to send commands to the Arduino
	bSetupArd = true;

	//	Print firmware version
	ofLogNotice() << ard.getFirmwareName();
	ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

	//	Set inputs and outputs
	ard.sendDigitalPinMode(2, ARD_INPUT);
	ard.sendDigitalPinMode(3, ARD_OUTPUT);

	//	Listen for changes on the pins
	ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pin_num){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
