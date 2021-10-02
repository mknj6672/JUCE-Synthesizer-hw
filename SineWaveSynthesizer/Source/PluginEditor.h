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
class SineWaveSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SineWaveSynthesizerAudioProcessorEditor (SineWaveSynthesizerAudioProcessor&);
    ~SineWaveSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;//介面上畫什麼
    void resized() override;//UI的位置

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SineWaveSynthesizerAudioProcessor& audioProcessor;
    
    juce::Slider levelSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> levelSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineWaveSynthesizerAudioProcessorEditor)
};
