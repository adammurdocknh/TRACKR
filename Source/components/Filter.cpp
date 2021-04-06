/*
  ==============================================================================

    Filter.cpp
    Created: 27 Mar 2021 11:05:29pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter(){}

//void Filter::processSignal(float *signal, const int numSamples, const int channel) {
//	for(int n =0; n < numSamples; n++) {
//		float x = signal[n];
//		x = lowPassFilter.processSample(x, channel);
//		x = highPassFilter.processSample(x, channel);
//		signal[n] = x;
//	}
//}

float Filter::processSample(float input, float channel, double lowGain, double highGain, double midFreq, double midGain) {
//	float x = input;
//	lowShelfFilter.setFreq(100);
//	highShelfFilter.setFreq(10000);
//	lowShelfFilter.setAmpdB(lpFreq);
//	highShelfFilter.setAmpdB(hpFreq);
	
	lowPeak.setFreq(100.0);
	lowPeak.setQ(.41);
	lowPeak.setAmpdB(lowGain);

	highPeak.setFreq(10000.0);
	highPeak.setQ(.41);
	highPeak.setAmpdB(highGain);
	
	midFixedPeakFilter.setFreq(midFreq);
	midFixedPeakFilter.setQ(1.4);
	midFixedPeakFilter.setAmpdB(midGain);
	
//	highPassFilter.setFreq(hpFreq);
//	highPassFilter.setQ(1.4);
//
//	lowPassFilter.setFreq(lpFreq);
//	lowPassFilter.setQ(1.4);
	
//	float output = lowPassFilter.processSample(x, channel);
//	output = highPassFilter.processSample(x, channel);
	
	float x = lowPeak.processSample(input, channel);
	float y = midFixedPeakFilter.processSample(x, channel);
	float output = highPeak.processSample(y, channel);
	
	return output;
	//	return output;
}


//float Filter::processSample(float input, float channel, double lpFreq, double hpFreq, double midFreq, double midGain) {
//	float x = input;
//	lowPassFilter.setFreq(lpFreq);
//	highPassFilter.setFreq(hpFreq);
//	midFixedPeakFilter.setFreq(midFreq);
//	midFixedPeakFilter.setQ(1.4);
//	midFixedPeakFilter.setAmpdB(midGain);
//	float output = lowPassFilter.processSample(x, channel);
//	output = highPassFilter.processSample(x, channel);
//	output = midFixedPeakFilter.processSample(x,channel);
//	return output;
//}

