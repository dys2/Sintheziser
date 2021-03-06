/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SinthesizerAudioProcessor::SinthesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SinthesizerAudioProcessor::~SinthesizerAudioProcessor()
{
}

//==============================================================================
const String SinthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SinthesizerAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SinthesizerAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SinthesizerAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SinthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SinthesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SinthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SinthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const String SinthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void SinthesizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SinthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock); // ignores unused samples from last key pressed
    lastSampleRate = sampleRate; // in case sample rate changes so doesnt crash
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SinthesizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SinthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SinthesizerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    //    ScopedNoDenormals noDenormals;
    //    const int totalNumInputChannels  = getTotalNumInputChannels();
    //    const int totalNumOutputChannels = getTotalNumOutputChannels();
    //
    //    // In case we have more outputs than inputs, this code clears any output
    //    // channels that didn't contain input data, (because these aren't
    //    // guaranteed to be empty - they may contain garbage).
    //    // This is here to avoid people getting screaming feedback
    //    // when they first compile a plugin, but obviously you don't need to keep
    //    // this code if your algorithm always overwrites all the output channels.
    //    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //        buffer.clear (i, 0, buffer.getNumSamples());
    //
    //    // This is the place where you'd normally do the guts of your plugin's
    //    // audio processing...
    //    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //    {
    //        float* channelData = buffer.getWritePointer (channel);
    //
    //        // ..do something to the data...
    //    }
}

//==============================================================================
bool SinthesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SinthesizerAudioProcessor::createEditor()
{
    return new SinthesizerAudioProcessorEditor (*this);
}

//==============================================================================
void SinthesizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SinthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinthesizerAudioProcessor();
}

