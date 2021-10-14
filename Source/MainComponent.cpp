#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(playlist);

    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function is called when the audio device is started, or when its settings (eg. sample rate, block size, etc) are changed.
    // You can use this function to initialise any resources you might need, but it will be called on the audio thread, not the GUI thread.
    
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false); //bool for whether we want to delete the source when it's done
    mixerSource.addInputSource(&player2, false);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
    //resampleSource.getNextAudioBlock(bufferToFill);
    //player1.getNextAudioBlock(bufferToFill);
    mixerSource.getNextAudioBlock(bufferToFill);
}
/**
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!
    auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    for (auto i = 0; i < bufferToFill.numSamples; ++i) { //use ++i to skip the copying, as compared to i++ that makes a copy, increments and assigns it
        //double sample = rand.nextDouble() * 0.25;
        //double sample = fmod(phase, 0.2); //when phase hits 0.2 we bring it down
        double sample = sin(phase) * 0.1;
        leftChan[i] = sample;
        rightChan[i] = sample;
        phase += dphase;
    }
    // Clears buffer to prevent the output of random noise
    // bufferToFill.clearActiveBufferRegion();
}
*/
void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is restarting due to a setting change.
    //transportSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // Called when the MainContentComponent is resized.
    // If you add any child components, this is where you should update their positions.
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    deckGUI2.setBounds(getWidth()/2, 0, getWidth() / 2, getHeight() / 2);
    playlist.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
}
