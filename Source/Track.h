/*
  ==============================================================================

    Track.h
    Created: 1 Mar 2021 9:00:05pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track {
public:
    Track(juce::File _file);
    juce::File file;
    juce::String trackName;
    juce::String time;
    juce::String fileType;
    juce::URL trackURL;
    bool operator==(const juce::String& other) const;
};
