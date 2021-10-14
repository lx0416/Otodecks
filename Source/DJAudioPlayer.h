/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 24 Feb 2021 5:56:51pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//#include "PlaylistComponent.h"

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    void start();
    void stop();

    /** Gets the relative position of the playhead */
    double getPositionRelative();
    double getLengthInSeconds();

private:
    juce::AudioFormatManager& formatManager;
    // juce::AudioFormatReaderSource readerSource; -> we don't use this instead as it is not a smart pointer
    std::unique_ptr < juce::AudioFormatReaderSource> readerSource; //smart pointer
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
    //std::vector<std::string> trackTitles;
};
