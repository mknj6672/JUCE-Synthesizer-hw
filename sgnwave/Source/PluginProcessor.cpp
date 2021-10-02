/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SgnwaveAudioProcessor::SgnwaveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
					#endif
	 ),
	tree(*this, nullptr, "PARAM",
		std::make_unique<juce::AudioParameterFloat>("level",
			"Level",
			juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f), 0.5f,
			juce::String(),
			juce::AudioProcessorParameter::genericParameter,
			[](float value, int) {return juce::String(value); },
			[](juce::String text) { return text.getFloatValue(); }))
#endif
{
	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());

	mySynth.clearVoices();
	for (int i = 0; i < 5; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}
}

SgnwaveAudioProcessor::~SgnwaveAudioProcessor()
{
}

//==============================================================================
const juce::String SgnwaveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SgnwaveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SgnwaveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SgnwaveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SgnwaveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SgnwaveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SgnwaveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SgnwaveAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SgnwaveAudioProcessor::getProgramName (int index)
{
    return {};
}

void SgnwaveAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SgnwaveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(sampleRate);
}

void SgnwaveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SgnwaveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SgnwaveAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		auto* myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i));
		myVoice->setLevel(tree.getRawParameterValue("level")->load());
	}
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());


}

//==============================================================================
bool SgnwaveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SgnwaveAudioProcessor::createEditor()
{
    return new SgnwaveAudioProcessorEditor (*this);
}

//==============================================================================
void SgnwaveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SgnwaveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SgnwaveAudioProcessor();
}
