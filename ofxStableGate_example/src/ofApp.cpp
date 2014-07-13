#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	gate.setup( watchedVar);
	gate.setPosition(50, 50);

	gate.useDelay(500, 500);
//	gate.useMean(100);
	
	
	counter = 1;
	direction = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	int limit = 100;
	
	// fake a noisy input range -1.5 to 1.5
	watchedVar = (ofRandom(-0.5, 0.5) + counter/limit);

	// dont use Mean in cases like this:
//	watchedVar = ofRandom(-0.5, 0.5);
	
	// fake ramp
	(counter>limit || counter<-limit) ? direction*= -1 : direction;
	counter = counter+direction;
	gate.update();
//	ofLogVerbose()<< watchedVar;
}

//--------------------------------------------------------------
void ofApp::draw(){
	gate.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}