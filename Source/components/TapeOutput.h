/*
  ==============================================================================

    TapeOutput.h
    Created: 5 Apr 2021 7:18:21pm
    Author:  Adam Murdock

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Preamp.h"
#include "Biquad.h"

class TapeOutput {
public:
	TapeOutput();
	float processSample(float input, float volume, float bias, int channel);
private:
	Preamp *distStage = new Preamp();
	Biquad highShelf = Biquad{Biquad::FilterType::HSHELF,0.7071f};
	Biquad lowShelf = Biquad{Biquad::FilterType::LSHELF,1.4f};
	Biquad lowShelf2 = Biquad{Biquad::FilterType::LSHELF,1.4f};
	Biquad lowPeak = Biquad{Biquad::FilterType::PEAK,1.4f};
	Biquad highPeak = Biquad{Biquad::FilterType::PEAK,2.1f};
	Biquad hpf = Biquad{Biquad::FilterType::HPF,1.4f};
};
