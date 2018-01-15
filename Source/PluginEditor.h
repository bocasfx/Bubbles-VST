
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "./Components/Accelerator.h"
#include "./Components/ControlPanel.h"

class QAudioProcessorEditor  : public AudioProcessorEditor,
                               public ActionListener
{
public:
    QAudioProcessorEditor (QAudioProcessor&);
    ~QAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void actionListenerCallback(const String&) override;

private:

    QAudioProcessor& processor;
    Accelerator* accelerator;
    ControlPanel* controlPanel;
    
    const int EDITOR_WIDTH = 800;
    const int EDITOR_HEIGHT = 670;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QAudioProcessorEditor)
};
