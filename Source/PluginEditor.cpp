
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
    
    addAndMakeVisible(&triggerMidi);
    triggerMidi.setButtonText("Trigger Midi");
    triggerMidi.addListener(this);
    
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
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
    triggerMidi.removeListener(this);
    processor.removeActionListener(this);
}

void QAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText (std::ctime(&currentTime), getLocalBounds(), Justification::bottomRight, 1);
}

void QAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    triggerMidi.setBounds(10, 10, 100, 32);
    midiConsole.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}


void QAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &triggerMidi) processor.generateMidiMessage();
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



