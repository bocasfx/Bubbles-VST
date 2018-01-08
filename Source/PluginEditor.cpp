
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (EDITOR_WIDTH, EDITOR_HEIGHT);
    srand((int)time(NULL));
    
    accelerator = new Accelerator(processor);
    addAndMakeVisible(accelerator);
    accelerator->setTopLeftPosition(0, 70);
    
    controlPanel = new ControlPanel(accelerator);
    addAndMakeVisible(controlPanel);
    controlPanel->setTopLeftPosition(0, 0);
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
}

void QAudioProcessorEditor::paint (Graphics& g)
{
}

void QAudioProcessorEditor::resized()
{
}



