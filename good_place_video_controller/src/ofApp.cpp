#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//	OF Settings
	//ofSetFrameRate(30);
	//ofSetVerticalSync(true);

	//	App Settings
	bRunning = false;

	//	Hardware
	//setupDMX();
	//connectArduino();

	//	Video
	ofSetHexColor(0xFFFFFF);
	video.loadMovie("goodplace.mp4");
	video.play();
}

//--------------------------------------------------------------
void ofApp::update(){

//	ard.update();
//	updateScene();

	//Video
	
	video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	video.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

	dmx.clear();
	dmx.disconnect();
}

//--------------------------------------------------------------
void ofApp::setupDMX()
{
	//	Clear out the DMX in case we're resetting
	if (dmx.isConnected())
	{
		dmx.clear();
		dmx.update(true);
		dmx.disconnect();
	}

	//	Connect
	bool b_Connect = dmx.connect(dmx_port);

	if (!b_Connect)
		ofLogWarning("DMX") << "Couldn't connect to DMX interface through port " << dmx_port;
	else
		ofLogNotice("DMX") << "Connected to DMX interface through port " << dmx_port << " SUCCESS!";
}

//--------------------------------------------------------------
void ofApp::connectArduino(){

	//	Connect
	ard.connect(ard_port, 57600);
	ard.sendFirmwareVersionRequest();

	//	Add listener
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArd = false;
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version){

	//	Remove listener
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArd = true;

	//	Print firmware version to console
	ofLogNotice() << ard.getFirmwareName();
	ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

	//	Set pin D2 as input
	ard.sendDigitalPinMode(2, ARD_INPUT);

	//	Listen for changes on digital pins
	ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pin_num){

	if (pin_num == 2 && ard.getDigital(2) == 1)
	{
		if (!bRunning)
		{
			startScene();
		}
	}
}

//--------------------------------------------------------------
void ofApp::startScene(){

	bRunning = true;
	start_time = ofGetElapsedTimef();
	ofLogNotice() << "Scene starting";

	video.play();
}

//--------------------------------------------------------------
void ofApp::updateScene(){
	if (bRunning)
	{
		run_time = ofGetElapsedTimef() - start_time;

		int level;

		if (run_time <= 2)
		{
			level = ofMap(run_time, 0, 2, 127, 0);
		}
		else if (run_time > 4 && run_time < length - 2)
		{
			level = 0;
		}
		else if (run_time <= length)
		{
			level = ofMap(run_time, length - 2, length, 0, 127);
		}
		else
		{
			level = 127;
			endScene();
		}

		dmx.setLevel(dmx_channel, level);
	}
	else
	{
		dmx.setLevel(dmx_channel, 127);
	}
}

//--------------------------------------------------------------
void ofApp::endScene(){
	bRunning = false;
	ofLogNotice() << "Scene ending";
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
