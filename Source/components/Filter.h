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
	float processSample(float input, float channel, double lowGain, double highGain, double midFreq, double midGain);
	void setLowFreq(float newFreq);
	void setHighFreq(float newFreq);
private:
//	float lowFreq = 20000.f;
//	float highFreq = 20.f;
	
	
	
	float midFreq = 1000.f;
	float Fs = 48000.f;
//	Biquad lowPassFilter = Biquad(Biquad::FilterType::LPF,0.7071f);
//	Biquad highPassFilter = Biquad(Biquad::FilterType::HPF,0.7071f);
//	Biquad midFixedPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4f);
	Biquad lowPassFilter = Biquad(Biquad::FilterType::LPF,1.4);
	Biquad highPassFilter = Biquad(Biquad::FilterType::HPF,1.4);
	
	Biquad lowShelfFilter = Biquad(Biquad::FilterType::LSHELF,1.4);
	Biquad highShelfFilter = Biquad(Biquad::FilterType::HSHELF,1.4);
	
	Biquad lowPeak = Biquad(Biquad::FilterType::PEAK,0.7071f);
	Biquad highPeak = Biquad(Biquad::FilterType::PEAK,0.7071f);
	
	Biquad midFixedPeakFilter = Biquad(Biquad::FilterType::PEAK,1.4);
};
