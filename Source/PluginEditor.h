
#pragma once

const int EDITOR_WIDTH = 800;
const int EDITOR_HEIGHT = 600;
const int SPRING = 1;

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./Components/Particle.h"

class QAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    Particle* createParticle(int x, int y);
    void detectCollissions();
    void mouseDown(const MouseEvent &event) override;

private:

    QAudioProcessor& processor;
    Point<int> pos;
    const int steps;
    Array<Particle*> particles;
    Image background;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
