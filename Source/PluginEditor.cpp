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
    
//    knobPreGain.addListener(this);
    // Pre amp section
    knobPreGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobPreGain.setBounds(75, 185, 100, 100);
    knobPreGain.setRange(0.f, 10.f,.01f);
    knobPreGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobPreGain.setValue(5.f);
    addAndMakeVisible(knobPreGain);
    
    knobInputGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobInputGain.setBounds(75, 330, 100, 100);
    knobInputGain.setRange(0.f, 10.f,.01f);
    knobInputGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobInputGain.setValue(5.f);
    addAndMakeVisible(knobInputGain);
    
    
    // EQ section
    knobFilterHP.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterHP.setBounds(257, 190, 75, 75);
    knobFilterHP.setRange(0.f, 10.f,.01f);
    knobFilterHP.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobFilterHP.setValue(5.f);
    addAndMakeVisible(knobFilterHP);
    
    knobFilterLP.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterLP.setBounds(368, 190, 75, 75);
    knobFilterLP.setRange(0.f, 10.f,.01f);
    knobFilterLP.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobFilterLP.setValue(5.f);
    addAndMakeVisible(knobFilterLP);

    knobFilterMidFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidFreq.setBounds(312, 265, 75, 75);
    knobFilterMidFreq.setRange(0.f, 10.f);
    knobFilterMidFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobFilterMidFreq.setValue(5.f);
    addAndMakeVisible(knobFilterMidFreq);
    
    knobFilterMidGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidGain.setBounds(312, 385, 75, 75);
    knobFilterMidGain.setRange(0.f, 10.f,.01f);
    knobFilterMidGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobFilterMidGain.setValue(5.f);
    addAndMakeVisible(knobFilterMidGain);
    
    
    // Tape Section
    knobBias.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobBias.setBounds(482, 190, 75, 75);
    knobBias.setRange(0.f, 10.f);
    knobBias.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobBias.setValue(5.f);
    addAndMakeVisible(knobBias);
    
    knobOutput.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobOutput.setBounds(592, 190, 75, 75);
    knobOutput.setRange(0.f, 10.f);
    knobOutput.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
//    knobOutput.setValue(5.f);
    addAndMakeVisible(knobOutput);
    
    addAndMakeVisible(tapeFormulas);
    tapeFormulas.setBounds(530, 390, 100, 25);
    tapeFormulas.addItem("#1", 1);
    tapeFormulas.addItem("#2", 2);
    
    
    
}

TRACKRAudioProcessorEditor::~TRACKRAudioProcessorEditor()
{
}

//==============================================================================
void TRACKRAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    auto background = juce::ImageCache::getFromMemory(BinaryData::DraftGUIWoKnobs_png, BinaryData::DraftGUIWoKnobs_pngSize);
    g.drawImageAt(background, 0, 0);
//    g.draw
    
//    juce::Slider knobInputGain();
//    juce::Slider knobFilterHP();
//    juce::Slider knobFilterLP();
//    juce::Slider knobFilterMidFreq();
//    juce::Slider knobFilterMidGain();
}

void TRACKRAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
