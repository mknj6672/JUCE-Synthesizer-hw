/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TriagleAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TriagleAudioProcessorEditor (TriagleAudioProcessor&);
    ~TriagleAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TriagleAudioProcessor& audioProcessor;

	juce::Slider levelSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TriagleAudioProcessorEditor)
};
