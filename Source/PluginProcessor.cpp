/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TRACKRAudioProcessor::TRACKRAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor (BusesProperties()
		#if ! JucePlugin_IsMidiEffect
		#if ! JucePlugin_IsSynth
		  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
		#endif
		  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
		#endif
		  ),
			apvts(*this, nullptr, "Params", createParams())
#endif

{
	preGainParameter = apvts.getRawParameterValue("PREGAIN");
	inputGainParameter = apvts.getRawParameterValue("INPUTGAIN");
	lowGainParameter = apvts.getRawParameterValue("LOWGAIN");
	highGainParameter = apvts.getRawParameterValue("HIGHGAIN");
	filterMidFreqParameter = apvts.getRawParameterValue("FILTERMIDFREQ");
	filterMidGainParameter = apvts.getRawParameterValue("FILTERMIDGAIN");
	outputGainParameter = apvts.getRawParameterValue("OUTPUTGAIN");
}

TRACKRAudioProcessor::~TRACKRAudioProcessor()
{
}

//==============================================================================
const juce::String TRACKRAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TRACKRAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TRACKRAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TRACKRAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double TRACKRAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TRACKRAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TRACKRAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TRACKRAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TRACKRAudioProcessor::getProgramName (int index)
{
    return {};
}

void TRACKRAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TRACKRAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TRACKRAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TRACKRAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void TRACKRAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
	auto preGain = apvts.getRawParameterValue("PREGAIN")->load();
	auto inputGain = apvts.getRawParameterValue("INPUTGAIN")->load();
	auto lowGain = apvts.getRawParameterValue("LOWGAIN")->load();
	auto highGain = apvts.getRawParameterValue("HIGHGAIN")->load();
	auto filterMidFreq = apvts.getRawParameterValue("FILTERMIDFREQ")->load();
	auto filterMidGain = apvts.getRawParameterValue("FILTERMIDGAIN")->load();
	auto outputGain = apvts.getRawParameterValue("OUTPUTGAIN")->load();
	
	
	
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            float input = buffer.getReadPointer(channel)[n];
			// Preamp Module
			input = preampSection.processSample(input, inputGain, preGain,channel);
			input = filterSection.processSample(input, channel, lowGain, highGain, filterMidFreq, filterMidGain);

			float output = tapeSection.processSample(input, outputGain, channel);
            buffer.getWritePointer(channel)[n] =  output; // -12 dB
        }
        
    }
}

//==============================================================================
bool TRACKRAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TRACKRAudioProcessor::createEditor()
{
    return new TRACKRAudioProcessorEditor (*this);
}

//==============================================================================
void TRACKRAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
//	ScopedPointer <XmlElement> xml (

}

void TRACKRAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TRACKRAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout TRACKRAudioProcessor::createParams() {
	std::vector<std::unique_ptr<RangedAudioParameter>> params;
	params.push_back(std::make_unique<AudioParameterFloat>("PREGAIN",
														  "Pre Gain",
														  0.0f,
														  3.0f,
														  0.f));
	params.push_back(std::make_unique<AudioParameterFloat>("INPUTGAIN",
														  "Input Gain",
														  -12.f,
														  12.f,
														   0.f));
	params.push_back(std::make_unique<AudioParameterFloat>("LOWGAIN",
														   "Low Gain",
														   -12.f,
														   12.f,
														   0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("HIGHGAIN",
														   "High Gain",
														   -12.f,
														   12.f,
														   0.f));
	params.push_back(std::make_unique<AudioParameterFloat>("FILTERMIDFREQ",
														   "Filter Mid Frequency",
														   500.f,
														   4000.f,
														   1000.f));
	params.push_back(std::make_unique<AudioParameterFloat>("FILTERMIDGAIN",
														   "Filter Mid Gain",
														   -12.f,
														   12.f,
														   0.f));
	
	params.push_back(std::make_unique<AudioParameterFloat>("OUTPUTGAIN",
														   "Output Gain",
														   -12.f,
														   12.f,
														   0.f));
	
	return { params.begin(), params.end() };
	
//
//			 : apvts (*this, nullptr, Identifier ("TestTree"), {
//				 std::make_unique<AudioParameterFloat("preGain",
//													  "PreGain",
//													  0.0f,
//													  3.0f,
//													  0.f),
//				 std::make_unique<AudioParameterFloat("inputGain",
//													  "InputGain",
//													  -12.f,
//													  12.f,
//													  0.f),
//				 std::make_unique<AudioParameterFloat("lowGain",
//													  "LowGain",
//													  -12.f,
//													  12.f,
//													  0.f),
//				 std::make_unique<AudioParameterFloat("highGain",
//													  "HighGain",
//													  -12.f,
//													  12.f,
//													  0.f),
//				 std::make_unique<AudioParameterFloat("filterMidFreq",
//													  "FilterMidFreq",
//													  500.f,
//													  4000.f,
//													  1000.f),
//				 std::make_unique<AudioParameterFloat("filterMidGain",
//													  "FilterMidGain",
//													  -12.f,
//													  12.f,
//													  0.f),
//				 std::make_unique<AudioParameterFloat("outputGain",
//													  "OutputGain",
//													  -12.f,
//													  12.f,
//													  0.f),
//
//			 }
}
