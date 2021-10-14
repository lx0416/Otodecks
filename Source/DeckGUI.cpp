/*
  ==============================================================================

    DeckGUI.cpp
    Created: 24 Feb 2021 10:49:14pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"
#include "WaveformDisplay.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse)
    : player(_player), waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Constructor: add any child components and initialise any special settings that your component needs.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(replayButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(volumeLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(positionLabel);

    playButton.addListener(this);
    stopButton.addListener(this);
    replayButton.addListener(this);

    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    speedSlider.addListener(this);
    speedSlider.setRange(0.0, 100);
    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0);

    volSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setNumDecimalPlacesToDisplay(2);
    startTimer(500); //start the timer every 500 milliseconds
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    volumeLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::lightcoral);
    volumeLabel.setJustificationType(juce::Justification::left);
    //volume.attachToComponent(&volSlider, true);

    speedLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.setColour(juce::Label::textColourId, juce::Colours::lightcoral);
    speedLabel.setJustificationType(juce::Justification::left);

    positionLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    positionLabel.setText("Position", juce::dontSendNotification);
    positionLabel.setColour(juce::Label::textColourId, juce::Colours::lightcoral);
    positionLabel.setJustificationType(juce::Justification::left);
}

void DeckGUI::resized()
{
    // Set the bounds of any child components that your component contains
    double rowH = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    replayButton.setBounds(0, rowH * 2, getWidth(), rowH);
    volSlider.setBounds(60, rowH * 3, getWidth()-60, rowH);
    speedSlider.setBounds(60, rowH * 4, getWidth()-60, rowH);
    posSlider.setBounds(60, rowH * 5, getWidth()-60, rowH);
    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH*2);
    volumeLabel.setBounds(0, rowH * 3, 60, 40);
    speedLabel.setBounds(0, rowH * 4, 60, 40);
    positionLabel.setBounds(0, rowH * 5, 60, 40);
}

void DeckGUI::buttonClicked(juce::Button* button) {
    if (button == &playButton) {
        std::cout << "Play button was clicked" << std::endl;
        player->start();
    }
    if (button == &stopButton) {
        std::cout << "Stop button was clicked" << std::endl;
        player->stop();
    }
    if (button == &replayButton) {
        /**
        juce::FileChooser chooser{ "Select a file" };
        if (chooser.browseForFileToOpen()) {
            player->loadURL(juce::URL{ chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
            //loadURL(juce::URL{ chooser.getResult() });
        }
        */
        restartButton(&replayButton, &posSlider);
        player->start();
    }
}

void DeckGUI::restartButton(juce::Button* button, juce::Slider* slider) {
    slider->setValue(0);
    //waveformDisplay.setPositionRelative(0);
}

void DeckGUI::sliderValueChanged(juce::Slider *slider) {
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider) {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) {
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y) {
    if (files.size() == 1) {
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}

void DeckGUI::loadFile(juce::URL audioURL) {
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

void DeckGUI::timerCallback() {
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
