/*
  ==============================================================================

    preamp.cpp
    Created: 6 Feb 2021 9:48:44pm
    Author:  Adam Murdock

  ==============================================================================
*/

#include "Preamp.h"

Preamp::Preamp(){}

void Preamp::processSignal(float *signal, const int numSamples, const int channel) {
	for (int n = 0; n < numSamples; n++) {
		float x = signal[n];
		signal[n] = x;
	}
}

float Preamp::processSample(float input, float volume, float drive) {
//	drive = juce::Decibels::decibelsToGain(drive);
	volume = juce::Decibels::decibelsToGain(volume);
	float x = atandist(input, drive);
	return x * volume;
}

float Preamp::atandist(float sample, float drive) {
    return (2.f/M_PI) * drive * sample;
}
