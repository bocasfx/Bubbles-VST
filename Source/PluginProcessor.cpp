
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
    startTime (Time::getMillisecondCounterHiRes() * 0.001)
#endif
{
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
    buffer.clear();
    midiMessages.swapWith(midiMessageBuffer);
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

void QAudioProcessor::generateMidiMessage() {
    Logger::outputDebugString("Generating midi note...");
    
    MidiMessage message = MidiMessage::noteOn(1, 100, (uint8)100);
    double timeStamp = Time::getMillisecondCounterHiRes() * 0.001 - startTime;
    message.setTimeStamp(timeStamp);
    midiMessageBuffer.addEvent(message, timeStamp);
    
    const String strMessage = extractMidiInfo(message);
    sendActionMessage(strMessage);
}

const String QAudioProcessor::extractMidiInfo (MidiMessage& message)
{
    if (message.isNoteOn())         return "Note on " + MidiMessage::getMidiNoteName(message.getNoteNumber(), true, true, 3);
    
    return String::toHexString(message.getRawData(), message.getRawDataSize());
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new QAudioProcessor();
}
