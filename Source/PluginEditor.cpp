/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <JuceHeader.h>

//==============================================================================
TRACKRAudioProcessorEditor::TRACKRAudioProcessorEditor (TRACKRAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 550);
    
    // Pre amp section
    knobPreGain.addListener(this);
    knobPreGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobPreGain.setBounds(75, 185, 100, 100);
    knobPreGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	knobPreGain.setValue(0.0);
    addAndMakeVisible(knobPreGain);
	preGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"PREGAIN",knobPreGain);
    
    knobInputGain.addListener(this);
	knobInputGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobInputGain.setBounds(75, 330, 100, 100);
    knobInputGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobInputGain.setValue(0.f);
    addAndMakeVisible(knobInputGain);
	inputGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"INPUTGAIN",knobInputGain);
    
    // EQ section
    knobLowGain.addListener(this);
    knobLowGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobLowGain.setBounds(257, 190, 75, 75);
    knobLowGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobFilterHP.setValue(10.f);
	knobLowGain.setValue(0.0);
    addAndMakeVisible(knobLowGain);
	lowGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"LOWGAIN",knobLowGain);
    
   
    knobHighGain.addListener(this);
	knobHighGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobHighGain.setBounds(368, 190, 75, 75);
    knobHighGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	knobHighGain.setValue(0.0);
    addAndMakeVisible(knobHighGain);
	highGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "HIGHGAIN",knobHighGain);

    knobFilterMidFreq.addListener(this);
	knobFilterMidFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidFreq.setBounds(312, 265, 75, 75);
    knobFilterMidFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterMidFreq.setValue(1000.f);
    addAndMakeVisible(knobFilterMidFreq);
	filterMidFreqAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FILTERMIDFREQ",knobFilterMidFreq);
    
    knobFilterMidGain.addListener(this);
	knobFilterMidGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidGain.setBounds(312, 385, 75, 75);
    knobFilterMidGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterMidGain.setValue(0.f);
    addAndMakeVisible(knobFilterMidGain);
	filterMidGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FILTERMIDGAIN",knobFilterMidGain);

	knobBias.addListener(this);
	knobBias.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	knobBias.setBounds(482, 190, 75, 75);
	knobBias.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	knobBias.setValue(1.f);
	addAndMakeVisible(knobBias);
	biasAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"BIAS", knobBias);
    
    knobOutput.addListener(this);
	knobOutput.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobOutput.setBounds(592, 190, 75, 75);
    knobOutput.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobOutput.setValue(0.f);
    addAndMakeVisible(knobOutput);
	outputGainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"OUTPUTGAIN",knobOutput);
}

TRACKRAudioProcessorEditor::~TRACKRAudioProcessorEditor()
{
}

//==============================================================================
void TRACKRAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto background = juce::ImageCache::getFromMemory(BinaryData::gui_png, BinaryData::gui_pngSize);
    g.drawImageAt(background, 0, 0);
}

void TRACKRAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void TRACKRAudioProcessorEditor::sliderValueChanged(juce::Slider * slider) {

}

// @TODO will come back to once tape formulas are worked out.
void TRACKRAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox) {
    if (comboBox == &tapeFormulas) {

    }
}
