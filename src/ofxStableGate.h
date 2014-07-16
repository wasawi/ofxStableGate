/*
 * ofxStableGate.h
 *
 *  Created on: July 10, 2014
 *      Author: wasawi
 *		Based on ofxSatate by Tadokoro Atsushi
 */

#pragma once

#include "ofMain.h"
#include "ofxStableGate.h"

class ofxStableGate {

public:

	ofxStableGate();
	~ofxStableGate();

	void	setup(float& input);
	void	update();
	void	draw();
	void	force(bool input);
	void	reset();

	
	void	setVisible(bool enabled);
	void	setMaxMin(float& _maxValue, float& _minValue);
	void	setMaxValue(float& maxValue);
	void	setMinValue(float& minValue);
	void	setPosition(float left, float top);
	void	setSize(float width, float height);
	bool	getState();
	
	// time based stableizer
	void	useDelay( int openDelayMilis=1000, int closeDelayMilis=1000);

	// average based stableizer
	// be careful this method won't be too stable in certain cases.
	void	useMean( int size );

	//Events
	ofEvent <float>	gateEvent;
	
private:
	void	onChange();
	void	processDelay();
	void	processMean();
	
	int		top;
    int		left;
    int		width;
    int		height;
	int		lapTime;
	int		padding;
	int		textH;
    float*	maxValue;
    float*	minValue;
	int		sampleSize;
	float	dMax;
	float	dMin;
	
	// Delay params
	float	lastTimeClosed;
	float	lastTimeOpen;
	float	openDelay;
	float	closeDelay;
	
	// Average params
	int		qLength;
	

	bool	bUseDelay;
	bool	bUseMean;
	bool	isVisible;
	
	float*	input;
	float	gateState;
	
	deque<float> inputQ;
	deque<float> outputQ;
	
};