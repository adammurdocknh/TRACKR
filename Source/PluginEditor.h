/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TRACKRAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                    public juce::Slider::Listener,
                                    public juce::ComboBox::Listener
{
public:
    TRACKRAudioProcessorEditor (TRACKRAudioProcessor&);
    ~TRACKRAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider * slider) override;
	void comboBoxChanged(juce::ComboBox * box) override;
    

private:
	juce::Image background;
    juce::Slider knobPreGain;
    juce::Slider knobInputGain;
    juce::Slider knobLowGain;
    juce::Slider knobHighGain;
    juce::Slider knobFilterMidFreq;
    juce::Slider knobFilterMidGain;
    juce::Slider knobBias;
    juce::Slider knobOutput;
    juce::ComboBox tapeFormulas;
	
	
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> preGainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lowGainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highGainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterMidFreqAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterMidGainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> biasAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;

	
    
	// This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	TRACKRAudioProcessor& audioProcessor;


	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TRACKRAudioProcessorEditor)
//    BackgroundComponent background;
};
