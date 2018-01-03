
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./Components/Bubble.h"

class QAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void showBubbles();
    Bubble* createBubble();

private:

    QAudioProcessor& processor;
    Point<int> pos;
    const int steps;
    enum {
        editorWidth = 800,
        editorHeight = 600
    };
    
    Array<Bubble*> bubbles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
