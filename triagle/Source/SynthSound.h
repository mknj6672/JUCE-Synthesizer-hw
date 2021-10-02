/*
  ==============================================================================

    SynthSound.h
    Created: 24 Jul 2021 12:43:06pm
    Author:  tuiji da

  ==============================================================================
*/

#pragma once

class SynthSound : public juce::SynthesiserSound
{

public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiNoteNumber) override
    {
        return true;
    }
};
