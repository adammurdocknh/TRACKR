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
    knobPreGain.addListener(this);
    knobPreGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobPreGain.setBounds(75, 185, 100, 100);
    knobPreGain.setRange(-12.f, 12.f,.01f);
    knobPreGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	knobPreGain.setValue(0.0);
    addAndMakeVisible(knobPreGain);
    
    knobInputGain.addListener(this);
	knobInputGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobInputGain.setBounds(75, 330, 100, 100);
    knobInputGain.setRange(-12.f, 12.f,.01f);
    knobInputGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobInputGain.setValue(0.f);
    addAndMakeVisible(knobInputGain);
    
    
    // EQ section
    knobFilterHP.addListener(this);
    knobFilterHP.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterHP.setBounds(257, 190, 75, 75);
    knobFilterHP.setRange(10.f, 1000.f,.01f);
    knobFilterHP.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterHP.setValue(10.f);
    addAndMakeVisible(knobFilterHP);
    
   
    knobFilterLP.addListener(this);
	knobFilterLP.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterLP.setBounds(368, 190, 75, 75);
    knobFilterLP.setRange(1000.f, 21000.f,.01f);
    knobFilterLP.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterLP.setValue(21000.f);
    addAndMakeVisible(knobFilterLP);

    knobFilterMidFreq.addListener(this);
	knobFilterMidFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidFreq.setBounds(312, 265, 75, 75);
    knobFilterMidFreq.setRange(500.f, 2000.f);
    knobFilterMidFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterMidFreq.setValue(1000.f);
    addAndMakeVisible(knobFilterMidFreq);
    
    knobFilterMidGain.addListener(this);
	knobFilterMidGain.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobFilterMidGain.setBounds(312, 385, 75, 75);
    knobFilterMidGain.setRange(-12.f, 12.f,.01f);
    knobFilterMidGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobFilterMidGain.setValue(0.f);
    addAndMakeVisible(knobFilterMidGain);
    
    
    // Tape Section
    knobBias.addListener(this);
    knobBias.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobBias.setBounds(482, 190, 75, 75);
    knobBias.setRange(-10.f, 10.f);
    knobBias.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobBias.setValue(0.f);
    addAndMakeVisible(knobBias);
    
    knobOutput.addListener(this); knobOutput.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobOutput.setBounds(592, 190, 75, 75);
    knobOutput.setRange(-12.f, 12.f);
    knobOutput.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobOutput.setValue(0.f);
    addAndMakeVisible(knobOutput);
    
    // @TODO Flesh out the logic case for each component.
//    tapeFormulas.addListener(this);
//    tapeFormulas.setBounds(530, 390, 100, 25);
//    tapeFormulas.addItem("#1", 1);
//    tapeFormulas.addItem("#2", 2);
//    addAndMakeVisible(tapeFormulas);
    
    
    
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


void TRACKRAudioProcessorEditor::sliderValueChanged(juce::Slider * slider) {
    if (slider == &knobPreGain) {
        audioProcessor.preGain = knobPreGain.getValue();
    }
    if (slider == &knobInputGain) {
        audioProcessor.inputGain = knobInputGain.getValue();
    }
    if (slider == &knobFilterHP) {
        audioProcessor.filterHP = knobFilterHP.getValue();
    }
    if (slider == &knobFilterLP) {
        audioProcessor.filterLP = knobFilterLP.getValue();
    }
    if (slider == &knobFilterMidFreq) {
        audioProcessor.filterMidFreq = knobFilterMidFreq.getValue();
    }
    if (slider == &knobFilterMidGain) {
        audioProcessor.filterMidGain = knobFilterMidGain.getValue();
    }
    if (slider == &knobBias) {
        audioProcessor.bias = knobBias.getValue();
    }
}

// @TODO will come back to once tape formulas are worked out.
void TRACKRAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox) {
    if (comboBox == &tapeFormulas) {

    }
}
