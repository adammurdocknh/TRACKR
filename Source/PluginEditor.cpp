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
    
    knobPreGain().addListener(this);
    knobPreGain().setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knobPreGain().setBounds,87.5f,197.5f,75,75);
    knobPreGain().setTextBoxStyle(juce::Slider::TextBoxAbove,false,75,25);
    addAndMakeVisible(knobPreGain())
    
//    gainSlider.addListener(this); // listen to user interaction with this GUI window
//    gainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag); // Circular knob
//    gainSlider.setBounds(40,90,120,120); // position on GUI
//    gainSlider.setRange(0.f,4.f,.01f);
//    gainSlider.setSkewFactorFromMidPoint(1.f);
//    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
//    gainSlider.setValue(audioProcessor.gain);
//    addAndMakeVisible(gainSlider);
//    auto background = juce::ImageCache::getFromMemory(BinaryData::DraftGUI_png, BinaryData::DraftGUI_pngSize);
//
//    if (! background.isNull() ) {
//        imageComponent.setImage(background,juce::RectanglePlacement::stretchToFit);
//    }
//    else {
//        jassert (! background.isNull());
//    }
//    addAndMakeVisible(imageComponent);
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
    auto background = juce::ImageCache::getFromMemory(BinaryData::DraftGUIWithKnobs_png, BinaryData::DraftGUIWithKnobs_pngSize);
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
