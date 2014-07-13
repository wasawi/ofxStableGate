#include "ofxStableGate.h"

ofxStableGate:: ofxStableGate()
:top(0), left(0), width(160), height(120), maxValue(1), minValue(-1), sampleSize(160){
	isVisible	= true;
	bUseDelay	= false;
	bUseMean	= false;
	padding		= 5;

	
	// gate closed by default
	gateState	= 0;
	lastTimeClosed	= ofGetElapsedTimef();
}

ofxStableGate:: ~ofxStableGate(){
	
}

//--------------------------------------------------------------
void ofxStableGate::setup(float& _input){
	input = &_input;
}


//--------------------------------------------------------------
void ofxStableGate::useDelay( int openDelayMilis, int closeDelayMilis){
	openDelay = openDelayMilis/1000.0;
	closeDelay = closeDelayMilis/1000.0;
	bUseDelay = true;
}

//--------------------------------------------------------------
void ofxStableGate::useMean( int size){
	qLength=size;
	bUseMean = true;
}

//--------------------------------------------------------------
void ofxStableGate::force(bool _input){
	
}

//--------------------------------------------------------------
void ofxStableGate::update(){
	// fill input
	inputQ.push_front(*input);
	if (inputQ.size() > sampleSize) {
		inputQ.pop_back();
	}

	// process
	if (bUseDelay) processDelay();
	if (bUseMean)  processMean();
	
	ofLogVerbose("gateState") << gateState;
	
	// fill output
	outputQ.push_front(gateState);
	if (outputQ.size() > sampleSize) {
		outputQ.pop_back();
	}
	
	ofLogVerbose("outputQ[sample]") << outputQ[0];
}
//--------------------------------------------------------------
void ofxStableGate::processMean(){
	
	float sum = inputQ[0];
	for (int i=1; i < qLength; i++){
		sum += inputQ[i];
	}
	float mean = sum/qLength;
	
	ofLogVerbose("mean") << mean;
	gateState = mean;
}

//--------------------------------------------------------------
void ofxStableGate::processDelay(){
	/*		
	 ofLogNotice("*********************");
	 ofLogNotice("openDelay") << openDelay;
	 ofLogNotice("closeDelay") << closeDelay;
	 
	 ofLogNotice("lastTimeClosed") << lastTimeClosed;
	 ofLogNotice("lastTimeOpen") << lastTimeOpen;
	 
	 ofLogNotice("ofGetElapsedTimef") << ofGetElapsedTimef();
	 ofLogNotice("*input") << *input;
	 */
	
	// if positive input
	if (*input>0){
		
		// if prev state is closed try to open, else nothing
		if (!gateState) {
			
			// if timer has finished, open
			if( lastTimeClosed + openDelay < ofGetElapsedTimef()){
				// open gate
				gateState=true;
				ofLogVerbose("gate") << "open";
			}
		}
		
		lastTimeOpen=ofGetElapsedTimef();
		
		// if negative input
	}else{
		
		// if prev state is open try to close, else nothing
		if (gateState) {
			
			// if timer has finished, open
			if( lastTimeOpen + closeDelay < ofGetElapsedTimef()){
				// close gate
				gateState=false;
				ofLogVerbose("gate") << "closed";
			}
		}
		lastTimeClosed=ofGetElapsedTimef();
	}
}

//--------------------------------------------------------------
void ofxStableGate::reset(){
	
}

//--------------------------------------------------------------
bool ofxStableGate::getState(){

}

//--------------------------------------------------------------
void ofxStableGate::draw(){
	
	if (isVisible){
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(left, top);
		
		// draw text
		ofPushMatrix();
		ofTranslate(0, -15);
		ofSetColor(20);
		ofRect(0, 0, width, 15);
		ofSetHexColor(0x00ffff);
		ofDrawBitmapString("Gate " + ofToString(gateState), 2, 12);
		ofPopMatrix();
		
		// draw input
		ofSetColor(0, 0, 0, 204);
		ofRect(0, 0, width , height);
		ofSetColor(ofColor::cyan);
		ofSetLineWidth(1);
		for (int i = 0; i < width; i++) {
			int sample = (int) ofMap(i, 0, width, 0, inputQ.size(), true);
			float length = ofMap(inputQ[sample], minValue, maxValue, -height/2, height/2,true);
			(length>0) ? ofSetColor(ofColor::green): ofSetColor(ofColor::red);
			
			int startX = width;
			int startY = height/2;
			ofLine(startX - i, startY, startX - i, startY - length);
		
			if (bUseMean){
				ofSetColor(ofColor::cyan);
				ofLine(startX - i, startY - (outputQ[sample] * startY), startX - i, startY - (outputQ[sample] * startY)+1);
			}
		}

		// middle line at 0
		ofSetColor(ofColor::yellow);
		ofLine(0, height/2, width, height/2);

		// draw output
		int h = 20;
		ofTranslate(0, height);
		
		for (int i = 0; i < width; i++) {
			int sample = (int) ofMap(i, 0, width, 0, outputQ.size(), true);
			float length = outputQ[sample];
			(length>0) ? ofSetColor(ofColor::green): ofSetColor(ofColor::red);
			int startX = width;
			ofLine(startX - i, 0, startX - i, h);
		}

		ofPopMatrix();
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofxStableGate::setVisible(bool enabled){
	isVisible = enabled;
}

//--------------------------------------------------------------
void ofxStableGate::setMaxValue(float _maxValue){
    maxValue = _maxValue;
}
//--------------------------------------------------------------
void ofxStableGate::setMinValue(float _minValue){
    minValue = _minValue;
}

//--------------------------------------------------------------
void ofxStableGate::setPosition(float _left, float _top){
    left = _left;
    top = _top;
}

//--------------------------------------------------------------
void ofxStableGate::setSize(float _width, float _height){
    width = _width;
    height = _height;
}
