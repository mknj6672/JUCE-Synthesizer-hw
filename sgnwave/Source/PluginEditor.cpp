/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SgnwaveAudioProcessorEditor::SgnwaveAudioProcessorEditor (SgnwaveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(400, 300);
	levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	levelSlider.setValue(0.5);
	levelSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
		true,
		levelSlider.getTextBoxWidth(),
		levelSlider.getTextBoxHeight());
	levelSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "level", levelSlider));

	addAndMakeVisible(levelSlider);
}

SgnwaveAudioProcessorEditor::~SgnwaveAudioProcessorEditor()
{
}

//==============================================================================
void SgnwaveAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::white);
	int x = 50;
	int y = 100;
	int width = 50;
	int height = levelSlider.getHeight();

	g.drawFittedText("Leveltest", x, y, width, height, juce::Justification::centred, 1);
}

void SgnwaveAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();
	int sliderWidth = area.getWidth() / 2;
	int sliderHeight = area.getHeight() / 4;
	int x = 100;
	int y = 100;

	levelSlider.setBounds(x, y, sliderWidth, sliderHeight);
}
