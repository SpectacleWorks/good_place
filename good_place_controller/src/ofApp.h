#pragma once

#include "ofMain.h"
#include "ofEvents.h"

//	Addons
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	//	Arduino
	void setupArduino(const int& version);
	void digitalPinChanged(const int& pin_num);

	//	Scene
	void launchScene();
	void launchInflatable();
	void retractInflatable();
	void playAudio();

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

	bool bSetupArd;
	bool bInflating;
	bool bSceneRunning;
	
	const float length = 60;
	const float inflate_delay = 10;
	float inflate_start_time, inflate_run_time;
	float start_time, run_time;

	ofArduino ard;
	ofSoundPlayer sound_player;
	ofxXmlSettings xml_settings;

	int p2, p3, p4, p5, p6;
};
