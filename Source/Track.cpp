/*
  ==============================================================================

    Track.cpp
    Created: 1 Mar 2021 9:00:05pm
    Author:  User

  ==============================================================================
*/

#include "Track.h"

Track::Track(juce::File _file) : file(_file),
                                 trackName(_file.getFileNameWithoutExtension()),
                                 fileType(_file.getFileExtension()),
                                 trackURL(juce::URL{ _file })
{

}

bool Track::operator==(const juce::String& other) const {
    return trackName == other;
}
