
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class QAudioProcessor  : public AudioProcessor,
                         public ActionBroadcaster,
                         private Timer
{
public:

    QAudioProcessor();
    ~QAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void generateMidiMessage ();
    const String extractMidiInfo (MidiMessage& message);
    void addMessageToBuffer (const MidiMessage& message);
    void addMessageToQueue (const MidiMessage& message);
    void timerCallback() override;
    
    double startTime;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessor)
    
    MidiBuffer midiMessageBuffer;
    MidiBuffer messageQueue;
    double sampleRate;
    int previousSampleNumber;
};
