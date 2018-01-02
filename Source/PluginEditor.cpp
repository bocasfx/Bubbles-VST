
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    auto now = std::chrono::system_clock::now();
    currentTime = std::chrono::system_clock::to_time_t(now);
    
    addAndMakeVisible(&midiConsole);
    midiConsole.setReadOnly(true);
    midiConsole.setMultiLine (true);
    midiConsole.setReturnKeyStartsNewLine (true);
    midiConsole.setScrollbarsShown (true);
    midiConsole.setCaretVisible (false);
    midiConsole.setPopupMenuEnabled (true);
    midiConsole.setColour (TextEditor::backgroundColourId, Colour (0x32ffffff));
    midiConsole.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    midiConsole.setColour (TextEditor::shadowColourId, Colour (0x16000000));
    
    processor.addActionListener(this);
    delta = (Point<float>(10.0, 10.0));
    startTimerHz (60);
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
    processor.removeActionListener(this);
}

void QAudioProcessorEditor::paint (Graphics& g)
{
    Point<float> nextPos = pos + delta;
    
    if (nextPos.x < 0 || nextPos.x + 10 > getWidth())
    {
        delta.x = -delta.x;
        nextPos.x = pos.x + delta.x;
        processor.generateMidiMessage();
    }
    
    if (nextPos.y < 0 || nextPos.y + 10 > getHeight())
    {
        delta.y = -delta.y;
        nextPos.y = pos.y + delta.y;
        processor.generateMidiMessage();
    }
    
    pos = nextPos;
    
    // draw a circle
    g.setColour (getLookAndFeel().findColour (Slider::thumbColourId));
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillEllipse (pos.x, pos.y, 20, 20);
}

void QAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    midiConsole.setBounds(0, 0, getWidth(), getHeight());
}

void QAudioProcessorEditor::actionListenerCallback(const String& message)
{
    writeToMidiConsole(message);
}

void QAudioProcessorEditor::writeToMidiConsole (const String& message)
{
    midiConsole.moveCaretToEnd();
    midiConsole.insertTextAtCaret(message + newLine);
}

void QAudioProcessorEditor::timerCallback()
{
    repaint();
}



