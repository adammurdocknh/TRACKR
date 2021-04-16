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

float Preamp::processSample(float input, float volume, float drive, int channel) {

		drive = juce::Decibels::decibelsToGain(drive);
		volume = juce::Decibels::decibelsToGain(volume);
		drive *= .5;
		float output = input * volume;
		output = cubicDist(output);
		output = atandist(output, drive);
		output = tandist(output, drive);
		output = cubicDist(output);
		output = cubicDist(output);
		output *= juce::Decibels::decibelsToGain(12);
		return output;
}

float Preamp::atandist(float sample, float drive) {
	return (2.f/M_PI) * atan( drive * sample);
}

float Preamp::tandist(float sample, float drive) {
	return tanh(sample * drive);
}
float Preamp::cubicDist(float sample) {
	return (sample - .2 * std::pow(sample, 3));
}
