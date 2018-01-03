
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessor::QAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
    startTime (Time::getMillisecondCounterHiRes() * 0.001),
    sampleRate(44100.0),
    previousSampleNumber(0)
#endif
{
    startTimer (1);
}

QAudioProcessor::~QAudioProcessor()
{
}

const String QAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool QAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool QAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool QAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double QAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int QAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int QAudioProcessor::getCurrentProgram()
{
    return 0;
}

void QAudioProcessor::setCurrentProgram (int index)
{
}

const String QAudioProcessor::getProgramName (int index)
{
    return {};
}

void QAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void QAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void QAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool QAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void QAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    if (messageQueue.getNumEvents() == 0) return;
    buffer.clear();
    midiMessages.swapWith(messageQueue);
}

bool QAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* QAudioProcessor::createEditor()
{
    return new QAudioProcessorEditor (*this);
}

void QAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void QAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void QAudioProcessor::addMessageToBuffer (const MidiMessage& message)
{
    const double timestamp = message.getTimeStamp();
    const int sampleNumber =  (int) (timestamp * sampleRate);
    midiMessageBuffer.addEvent (message, sampleNumber);
}

void QAudioProcessor::addMessageToQueue (const MidiMessage& message)
{
    messageQueue.addEvent (message, message.getTimeStamp());
}

void QAudioProcessor::generateMidiMessage() {
    Logger::outputDebugString("Generating midi note...");
    
    MidiMessage messageOn = MidiMessage::noteOn(1, 100, (uint8)100);
    messageOn.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001 - startTime);
    addMessageToBuffer(messageOn);
    
    MidiMessage messageOff = MidiMessage::noteOff(1, 100);
    messageOff.setTimeStamp(messageOn.getTimeStamp() + 0.5);
    addMessageToBuffer(messageOff);
    
    // Send a text message to the Editor.
    const String strMessageOn = extractMidiInfo(messageOn);
    sendActionMessage(strMessageOn);
    
    const String strMessageOff = extractMidiInfo(messageOff);
    sendActionMessage(strMessageOff);
}

const String QAudioProcessor::extractMidiInfo (MidiMessage& message)
{
    if (message.isNoteOn()) {
      return "Note on " + MidiMessage::getMidiNoteName(message.getNoteNumber(), true, true, 3);
    }
    
    return String::toHexString(message.getRawData(), message.getRawDataSize());
}

void QAudioProcessor::timerCallback()
{
    if (midiMessageBuffer.getNumEvents() == 0 ) return;
    const double currentTime = Time::getMillisecondCounterHiRes() * 0.001 - startTime;
    const int currentSampleNumber =  (int) (currentTime * sampleRate);
    MidiBuffer::Iterator iterator (midiMessageBuffer);
    MidiMessage message;
    int sampleNumber;
    while (iterator.getNextEvent (message, sampleNumber))
    {
        if (sampleNumber > currentSampleNumber)
            break;
        
        message.setTimeStamp (sampleNumber / sampleRate);
        addMessageToQueue (message);
    }
    midiMessageBuffer.clear (previousSampleNumber, currentSampleNumber - previousSampleNumber);
    previousSampleNumber = currentSampleNumber;
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new QAudioProcessor();
}
