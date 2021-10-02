/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
   
    void renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;
    
    void setLevel(float newLevel);
    
private:
    float level;//amp
    float frequency;//key
    int noteMidiNumber;
    float currentAngle;//sinewave delta
    float angleIncrement;//sinewave delta+¤@ÂI«á¼W¥[¦h¤Ö¬Û¦ì
    float tailOff;
};
