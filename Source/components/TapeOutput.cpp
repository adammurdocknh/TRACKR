/*
  ==============================================================================

    TapeOutput.cpp
    Created: 5 Apr 2021 7:18:21pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "TapeOutput.h"

TapeOutput::TapeOutput(){}

float TapeOutput::processSample(float input, float volume, float bias, int channel) {

	volume = Decibels::Decibels::decibelsToGain(volume);
	
	hpf.setFreq(20);
	lowPeak.setFreq(30.f);
	lowPeak.setAmpdB(4.f);
	
	highPeak.setFreq(21000.f);
	highPeak.setAmpdB(6.f);
	
	highShelf.setFreq(100.0);
	highShelf.setAmpdB(3.0);
	
	input = hpf.processSample(input, channel);
	input = lowPeak.processSample(input, channel);
	input = highShelf.processSample(input, channel);
	input = highPeak.processSample(input, channel);
	
	input = distStage->atandist(input, bias);

	input *= volume;
	input *= 4.f;
	return input;

}
