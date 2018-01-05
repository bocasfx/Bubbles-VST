
#pragma once

const int EDITOR_WIDTH = 800;
const int EDITOR_HEIGHT = 600;
const int SPRING = 1;

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
    Bubble* createBubble(int x, int y);
    void detectCollissions();
    void mouseDown(const MouseEvent &event) override;

private:

    QAudioProcessor& processor;
    Point<int> pos;
    const int steps;
    Array<Bubble*> bubbles;
    Image background;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
