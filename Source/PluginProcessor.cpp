/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

enum
{
	// Parameters Tags
	pOsc1Wave = 0,
	pOsc2Wave,
	
	pNumParams
};

//==============================================================================
JuceOplvstiAudioProcessor::JuceOplvstiAudioProcessor()
{
	Opl = new Hiopl(44100);	// 1 second at 44100
}

JuceOplvstiAudioProcessor::~JuceOplvstiAudioProcessor()
{
}

//==============================================================================
const String JuceOplvstiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JuceOplvstiAudioProcessor::getNumParameters()
{
    return pNumParams;
}

float JuceOplvstiAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void JuceOplvstiAudioProcessor::setParameter (int index, float newValue)
{
	switch (index) {
	case pOsc1Wave:
		break;
	case pOsc2Wave:
		break;
	}
}

const String JuceOplvstiAudioProcessor::getParameterName (int index)
{
	switch (index) {
	case pOsc1Wave:
		return "Carrier waveform";
	case pOsc2Wave:
		return "Modulator waveform";
	}
    return String::empty;
}

const String JuceOplvstiAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String JuceOplvstiAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JuceOplvstiAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JuceOplvstiAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool JuceOplvstiAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool JuceOplvstiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceOplvstiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceOplvstiAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JuceOplvstiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceOplvstiAudioProcessor::getNumPrograms()
{
    return 0;
}

int JuceOplvstiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceOplvstiAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceOplvstiAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void JuceOplvstiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceOplvstiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	Opl->SetSampleRate((int)sampleRate);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceOplvstiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceOplvstiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.clear(0, 0, buffer.getNumSamples());
	MidiBuffer::Iterator midi_buffer_iterator(midiMessages);

	MidiMessage midi_message(0);
	int sample_number;
	while (midi_buffer_iterator.getNextEvent(midi_message,sample_number)) {
		if (midi_message.isNoteOn()) {
			//note on at sample_number samples after 
			//the begining of the current buffer
			float noteHz = MidiMessage::getMidiNoteInHertz(midi_message.getNoteNumber());
			Opl->KeyOn(0, noteHz);
		}
		else if (midi_message.isNoteOff()) {
			Opl->KeyOff(0);
		}
	}
	Opl->Generate(buffer.getNumSamples(), buffer.getSampleData(0));
}

//==============================================================================
bool JuceOplvstiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceOplvstiAudioProcessor::createEditor()
{
    return new JuceOplvstiAudioProcessorEditor (this);
}

//==============================================================================
void JuceOplvstiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceOplvstiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceOplvstiAudioProcessor();
}
