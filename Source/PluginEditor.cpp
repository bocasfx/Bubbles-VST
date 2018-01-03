
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), steps(10)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (editorWidth, editorHeight);
    
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    
    showBubbles();
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
}

void QAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void QAudioProcessorEditor::resized()
{
}

void QAudioProcessorEditor::showBubbles()
{
    for(auto it = bubbles.begin(); it != bubbles.end(); ++it) {
        addAndMakeVisible(*it);
    }
}

Bubble* QAudioProcessorEditor::createBubble()
{
    Logger::outputDebugString("Creating bubble: " + (String)bubbles.size());
    return new Bubble(processor);
}



