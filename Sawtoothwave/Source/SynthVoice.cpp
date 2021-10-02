/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/
#include <math.h>
#include "SynthVoice.h"
#include<iostream>
#define PI acos(-1)

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    noteMidiNumber = midiNoteNumber;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentAngle = 0.f;
    angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi;
    tailOff = 0.0;
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        level = 0;
        currentAngle = 0.f;
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // handle midi control change
}

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	if (tailOff > 0.0)
	{
		for (int i = startSample; i < (startSample + numSamples); i++)
		{
			float value = std::atan(tan(currentAngle)) * level * tailOff;
			outputBuffer.addSample(0, i, value);
			outputBuffer.addSample(1, i, value);


			currentAngle += angleIncrement;
			tailOff *= 0.99;

			if (tailOff <= 0.05)
			{
				clearCurrentNote();
				angleIncrement = 0.0;
				level = 0.0;
				break;
			}
		}

	}
	else
	{
		for (int i = startSample; i < (startSample + numSamples); i++)
		{
			float value = std::atan(tan(currentAngle)) * level;
			outputBuffer.addSample(0, i, value);
			outputBuffer.addSample(1, i, value);

			currentAngle += angleIncrement;
		}

	}
}

void SynthVoice::setLevel(float newLevel)
{
    level = newLevel;
}
