/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TRACKRAudioProcessorEditor::TRACKRAudioProcessorEditor (TRACKRAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 550);
}

TRACKRAudioProcessorEditor::~TRACKRAudioProcessorEditor()
{
}

//==============================================================================
void TRACKRAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::File backgroundImageFile = juce::File ("./assets/Draft_GUI.png");
    juce::Image background = juce::ImageCache::getFromFile (backgroundImageFile);
    g.drawImageAt (background,0,0);
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
}

void TRACKRAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
