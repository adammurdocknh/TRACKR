/*
  ==============================================================================

    preamp.h
    Created: 6 Feb 2021 9:48:44pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once
//#include "ATanDistortion.h"
//#include "expoDistortion.h"
#include <JuceHeader.h>
//#include "expoDistortion.h"
//#include "ATanDistortion.h"

class Preamp {
public:
	Preamp();
	
	void processSignal(float *signal, const int numSamples, const int channel);
	float processSample(float input);
	float processSample(float input, float gain, float drive);
	float atandist(float sample, float drive);

private:

	float Fs = 48000.f;
};
