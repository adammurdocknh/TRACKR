/*
  ==============================================================================

    Filter.h
    Created: 27 Mar 2021 11:05:29pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once

#include "Biquad.h"

class Filter {
public:
	Filter();
	float processSample(float input, float channel, double lowGain, double highGain, double midFreq, double midGain);
	void setLowFreq(float newFreq);
	void setHighFreq(float newFreq);
private:
	
	float midFreq = 1000.f;
	float Fs = 48000.f;
	
	Biquad lowPeak = Biquad(Biquad::FilterType::PEAK,0.7071f);
	Biquad highPeak = Biquad(Biquad::FilterType::PEAK,0.7071f);
	
	Biquad midFixedPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4);
};

