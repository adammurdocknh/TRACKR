/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "components/Biquad.h"
#include "components/Filter.h"
#include "components/Preamp.h"
#include "components/TapeOutput.h"

//==============================================================================
/**
*/
class TRACKRAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TRACKRAudioProcessor();
    ~TRACKRAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float expoDistortion (float signal, float distValue);
    float arcTanDistortion (float signal, float alpha);
    float getSign (float signal);
	
	Preamp preampSection;
	Filter filterSection;
	TapeOutput tapeSection;
	
	AudioProcessorValueTreeState apvts;

    
private:
    //==============================================================================
	
	std::atomic<float>* preGainParameter = nullptr;
	std::atomic<float>* inputGainParameter = nullptr;
	std::atomic<float>* lowGainParameter = nullptr;
	std::atomic<float>* highGainParameter = nullptr;
	std::atomic<float>* filterMidFreqParameter = nullptr;
	std::atomic<float>* filterMidGainParameter = nullptr;
	std::atomic<float>* outputGainParameter = nullptr;
	
	AudioProcessorValueTreeState::ParameterLayout createParams();
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TRACKRAudioProcessor)
 };
