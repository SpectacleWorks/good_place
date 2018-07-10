#pragma once

#include "ofMain.h"

//	Core OF
#include "ofEvents.h"

//	Addons
#include "ofxDmx.h"

//	Constants
const string ard_port = "COM 6";
const string dmx_port = "COM 5";
const int dmx_channel = 1;
const float length = 120;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void setupDMX();
	void connectArduino();
	void setupArduino(const int& version);

	void digitalPinChanged(const int& pin_num);

	void startScene();
	void updateScene();
	void endScene();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	//***********************************************

	//	Arduino
	ofArduino ard;
	bool bSetupArd;

	//	DMX
	ofxDmx dmx;

	//	Scene
	float run_time, start_time;
	bool bRunning;

	//	Video
	ofVideoPlayer video;
};