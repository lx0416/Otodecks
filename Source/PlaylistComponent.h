/*
 ==============================================================================

   PlaylistComponent.h
   Created: 26 Feb 2021 11:05:41pm
   Author:  User

 ==============================================================================
*/

#pragma once
#include <vector>
#include <string>
#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "Track.h"
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                          public juce::TableListBoxModel,
                          public juce::Button::Listener,
                          public juce::TextEditor::Listener
{
public:
   PlaylistComponent(DeckGUI* _deckGUI1,
                     DeckGUI* _deckGUI2,
                     DJAudioPlayer* _metaPlayer);
   ~PlaylistComponent() override;
   void paint (juce::Graphics&) override;
   void resized() override;
   int getNumRows() override;
   void paintRowBackground(juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
   void paintCell(juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
   juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component *existingComponentToUpdate) override;
   void buttonClicked(juce::Button* button) override;

private:
   juce::TextButton loadButton{ "LOAD" };
   juce::TextButton deck1Button{ "LOAD TO DECK 1" };
   juce::TextButton deck2Button{ "LOAD TO DECK 2" };
   juce::TextEditor searchbox;
   juce::TableListBox tableComponent;
   std::vector<Track> songs;
   DeckGUI* deckGUI1;
   DeckGUI* deckGUI2;
   DJAudioPlayer* metaPlayer;
   juce::String timeToDisplay(juce::URL audioURL);
   juce::String getTime(double seconds);
   void loadSongs();
   bool isAdded(juce::String trackName);
   void deleteSongs(int trackId);
   void search(juce::String searchText);
   void savePlaylist();
   void loadPlaylist();
   void loadToDeck(DeckGUI* deckGUI);
   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
