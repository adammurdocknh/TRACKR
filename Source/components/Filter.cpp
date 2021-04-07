/*
  ==============================================================================

    Filter.cpp
    Created: 27 Mar 2021 11:05:29pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Filter.h"

Filter::Filter(){}


//}

float Filter::processSample(float input, float channel, double lowGain, double highGain, double midFreq, double midGain) {
	
	lowPeak.setFreq(100.0);
	lowPeak.setQ(.41);
	lowPeak.setAmpdB(lowGain);

	highPeak.setFreq(10000.0);
	highPeak.setQ(.41);
	highPeak.setAmpdB(highGain);
	
	midFixedPeakFilter.setFreq(midFreq);
	midFixedPeakFilter.setQ(1.4);
	midFixedPeakFilter.setAmpdB(midGain);
	
	
	float x = lowPeak.processSample(input, channel);
	float y = midFixedPeakFilter.processSample(x, channel);
	float output = highPeak.processSample(y, channel);
	
	return output;
	//	return output;
}
