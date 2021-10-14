/*
 ==============================================================================

   WaveformDisplay.h
   Created: 26 Feb 2021 5:50:47pm
   Author:  User

 ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, public juce::ChangeListener
{
public:
   WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse);
   ~WaveformDisplay() override;

   void paint (juce::Graphics&) override;
   void resized() override;

   void changeListenerCallback(juce::ChangeBroadcaster* source) override;

   void loadURL(juce::URL audioURL);

   /** Sets the relative position of the playhead */
   void setPositionRelative(double pos);

private:
   juce::AudioThumbnail audioThumb;
   bool fileLoaded;
   double position;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
