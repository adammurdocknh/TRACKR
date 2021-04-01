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
	void processSignal(float *signal, const int numSamples, const int channel);
	void setLowFreq(float newFreq);
	void setHighFreq(float newFreq);
private:
	float lowFreq = 20000.f;
	float highFreq = 20.f;
	float Fs = 48000.f;
	Biquad lowPassFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
	Biquad highPassFilter = Biquad(Biquad::FilterType::HPF,0.7071f);	
};

