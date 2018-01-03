
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./Components/Bubble.h"

class QAudioProcessorEditor  : public AudioProcessorEditor,
                               private Timer
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void showBubbles();
    Bubble* createBubble();

private:

    QAudioProcessor& processor;
    time_t currentTime;
    Point<int> pos;
    const int steps;
    enum {
        viewPortWidth = 600,
        viewPortHeight = 600,
        editorWidth = 800,
        editorHeight = 600
    };
    
    Array<Bubble*> bubbles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
