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
                  )
#endif
{
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
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //        auto* channelData = buffer.getWritePointer (channel);
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            float x = buffer.getReadPointer(channel)[n];
            expoDistortion(n, 5);
            
            buffer.getWritePointer(channel)[n] =  x; // -12 dB
            
            // ..do something to the data...
            
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

/*
 Checks the sign and changes it to an int value
 instead of boolean. signbit return true if
 is negative. Function returns -1 or 1
 */



int getSign (float signal) {
    if (signal < 0) {
        return -1;
    }
    else {
        return 1;
    }
}

float TRACKRAudioProcessor::expoDistortion (float signal, float distValue) {
    float output;
    float x;
    float y;

    /* MATLAB code:
    sign(in(n,1)) * (1 - exp(-abs(G*in(n,1))));
     */
    output = getSign (signal);
    x = exp(-abs (distValue*signal));
    y = 1-x;
    output += y;
    return output;
    }

float TRACKRAudioProcessor::arcTanDistortion (float signal, float alpha) {
    float output;
    /* MATLAB code
     out(n,1) = (2/pi)*atan(in(n,1)*alpha)
     */
    output = (2/M_PI) * atan (signal*alpha);
    return output;
    
}
