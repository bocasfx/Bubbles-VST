
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class QAudioProcessorEditor  : public AudioProcessorEditor,
                               public ActionListener,
                               private Timer
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void actionListenerCallback(const String& message) override;
    void writeToMidiConsole (const String& message);
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    QAudioProcessor& processor;
    
    time_t currentTime;
    
    TextEditor midiConsole;
    
    Point<float> pos, delta;
    
    enum
    {
        steps = 10
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
