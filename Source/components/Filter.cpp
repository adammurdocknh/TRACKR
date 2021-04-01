/*
  ==============================================================================

    Filter.cpp
    Created: 27 Mar 2021 11:05:29pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter(){}

void Filter::processSignal(float *signal, const int numSamples, const int channel) {
	for(int n =0; n < numSamples; n++) {
		float x = signal[n];
		x = lowPassFilter.processSample(x,channel);
		x = highPassFilter.processSample(x, channel);
		signal[n] = x;
	}
}

void Filter::setLowFreq(float newFreq) {
	lowFreq = newFreq;
	lowPassFilter.setFreq(lowFreq);
}
void Filter::setHighFreq(float newFreq) {
	highFreq = newFreq;
	highPassFilter.setFreq(highFreq);
}
