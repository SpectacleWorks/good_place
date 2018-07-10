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

	//	Sounds
	sound_player.load("botalo_ambience.mp3");
	sound_player.setLoop(false);

	//	Scene settings
	bInflating = false;
	bSceneRunning = false;

}

//--------------------------------------------------------------
void ofApp::update(){

	ard.update();

	//	Get pin states
	if (bSetupArd)
	{
		p2 = ard.getDigital(2);
		p3 = ard.getDigital(3);
		p4 = ard.getDigital(4);
		p5 = ard.getDigital(5);
		p6 = ard.getDigital(6);
	}

	run_time = ofGetElapsedTimef() - start_time;

	if (bSceneRunning)
	{

		if (run_time >= inflate_delay && !bInflating)
		{
			launchInflatable();
		}
		else if (bInflating)
		{
			inflate_run_time = ofGetElapsedTimef() - inflate_start_time;

			if (inflate_run_time > 40)
			{
				retractInflatable();
			}
		}
	}

	if (run_time >= length)
	{
		bSceneRunning = false;
		sound_player.stop();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	if (bSetupArd)
	{
		ofSetColor(255);
		ofDrawBitmapString("Pin 2: " + ofToString(p2), 20,  20);
		ofDrawBitmapString("Pin 3: " + ofToString(p3), 20,  40);
		ofDrawBitmapString("Pin 4: " + ofToString(p4), 20,  60);
		ofDrawBitmapString("Pin 5: " + ofToString(p5), 20,  80);
		ofDrawBitmapString("Pin 6: " + ofToString(p6), 20, 100);
	}
}

//--------------------------------------------------------------
void ofApp::exit(){

	//	Set all utilized pins to LOW
	ard.sendDigital(2, 0, true);
	ard.sendDigital(3, 0, true);
	ard.sendDigital(4, 0, true);
	ard.sendDigital(5, 0, true);
	ard.sendDigital(6, 0, true);
}

//--------------------------------------------------------------
void ofApp::launchScene(){
	bSceneRunning = true;
	start_time = ofGetElapsedTimef();
	playAudio();
}

//--------------------------------------------------------------
void ofApp::launchInflatable() {

	//	Tell OF we're launching the inflatable
	bInflating = true;

	//	Start timer
	inflate_start_time = ofGetElapsedTimef();

	//	Extend actuator
	ard.sendDigital(3, 1, true);
	ofSleepMillis(250);
	ard.sendDigital(3, 0, true);

	//	Power on blower
	ard.sendDigital(4, 1, true);
}

//--------------------------------------------------------------
void ofApp::retractInflatable(){

	//	Power off blower
	ard.sendDigital(4, 0, true);

	//Retract actuator33
	ard.sendDigital(3, 1, true);
	ofSleepMillis(250);
	ard.sendDigital(3, 0, true);

	bInflating = false;
	bSceneRunning = false;
}

//--------------------------------------------------------------
void ofApp::playAudio(){

	sound_player.play();
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
	ard.sendDigitalPinMode(2, ARD_OUTPUT);
	ard.sendDigitalPinMode(3, ARD_OUTPUT);
	ard.sendDigitalPinMode(4, ARD_OUTPUT);
	ard.sendDigitalPinMode(5, ARD_OUTPUT);
	ard.sendDigitalPinMode(6, ARD_INPUT);

	ard.sendDigital(2, 0, true);
	ard.sendDigital(3, 0, true);
	ard.sendDigital(4, 0, true);
	ard.sendDigital(5, 0, true);

	//	Listen for changes on the pins
	ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pin_num){

	if (pin_num == 6 && ard.getDigital(6) == 1 && !bSceneRunning)
	{
		launchScene();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{
	case '3':
		p3 == 1 ?
			ard.sendDigital(3, 0, true):
			ard.sendDigital(3, 1, true);
		break;
	case '4':
		p4 == 1 ?
			ard.sendDigital(4, 0, true) :
			ard.sendDigital(4, 1, true);
		break;
	case '5':
		p5 == 1 ?
			ard.sendDigital(5, 0, true) :
			ard.sendDigital(5, 1, true);
		break;
	case 'P':
		break;
	default:
		break;
	}
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
