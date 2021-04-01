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

float Preamp::processSample(float input) {
	float x = atandist(input);
	return x * inputVolume;
}

float Preamp::atandist(float sample) {
    return (2.f/M_PI) * drive * sample;
}

void Preamp::setInput(float newGain){
	newGain =
	inputVolume = juce::Decibels::gainToDecibels(newGain);
}

void Preamp::setDrive(float newDrive) {
    drive = juce::Decibels::gainToDecibels(newDrive);
}
