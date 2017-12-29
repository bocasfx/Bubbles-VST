/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class QAudioProcessorEditor  : public AudioProcessorEditor,
                               public ButtonListener,
                               public ActionListener
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;
    void actionListenerCallback(const String& message) override;
    void writeToMidiConsole (const String& message);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    QAudioProcessor& processor;
    
    time_t currentTime;
    
    TextButton triggerMidi;
    TextEditor midiConsole;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
