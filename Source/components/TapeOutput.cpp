/*
  ==============================================================================

    TapeOutput.cpp
    Created: 5 Apr 2021 7:18:21pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "TapeOutput.h"

TapeOutput::TapeOutput(){}

float TapeOutput::processSample(float input, float volume, int channel) {

	volume = Decibels::Decibels::decibelsToGain(volume);
	
	hpf.setFreq(20);
	
	lowShelf.setFreq(60.0);
	lowShelf.setAmpdB(3.0);
	
	lowShelf2.setFreq(480);
	lowShelf2.setAmpdB(-1.0);
	
	highShelf.setFreq(6000.0);
	highShelf.setAmpdB(1.0);

	input = hpf.processSample(input, channel);
	float lowBand = lowShelf.processSample(lowShelf2.processSample(input, channel), channel);
	float highBand = highShelf.processSample(input, channel);
	
	float output = lowBand + highBand;
//		output *= .5;
	
	output = distStage->cubicDist(output);
//		output *= 4.f;
	return output * volume;

}
