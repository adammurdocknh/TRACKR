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
	
//	lowShelf.setFreq(60.0);
//	lowShelf.setAmpdB(3.0);
//
//	lowShelf2.setFreq(480);
//	lowShelf2.setAmpdB(-1.0);
	
	lowPeak.setFreq(30.f);
	lowPeak.setAmpdB(2.5f);
	
	highPeak.setFreq(21000.f);
	highPeak.setAmpdB(6.f);
	
	highShelf.setFreq(100.0);
	highShelf.setAmpdB(3.0);

	input *= volume;
	
	
//	float lowBand = lowShelf.processSample(lowShelf2.processSample(input, channel), channel);
//	float highBand = highShelf.processSample(input, channel);
	
	input = hpf.processSample(input, channel);
	input = lowPeak.processSample(input, channel);
	input = highShelf.processSample(input, channel);
	input = highPeak.processSample(input, channel);
	
	
//	float output = lowBand + highBand;
	
	input = distStage->cubicDist(input);
	input *= 4.f;
	return input;

}
