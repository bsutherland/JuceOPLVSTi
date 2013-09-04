/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


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
    return 0;
}

float JuceOplvstiAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void JuceOplvstiAudioProcessor::setParameter (int index, float newValue)
{
}

const String JuceOplvstiAudioProcessor::getParameterName (int index)
{
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
	Opl->SetSampleRate(sampleRate);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	Opl->_WriteReg(0x20,0x32);
	Opl->_WriteReg(0x23,0x21);
	Opl->_WriteReg(0x40,0x1a);
	Opl->_WriteReg(0x43,0x09);
	Opl->_WriteReg(0x60,0x84);
	Opl->_WriteReg(0x63,0x84);
	Opl->_WriteReg(0x80,0x29);
	Opl->_WriteReg(0x83,0x44);
	Opl->_WriteReg(0xe3,0x00);
	Opl->_WriteReg(0xe0,0x02);
	Opl->_WriteReg(0xc0,0x06);
	Opl->_WriteReg(0xa0,0x8b);
	Opl->_WriteReg(0xb0,0x26);
	Opl->_WriteReg(0x21,0x32);
	Opl->_WriteReg(0x24,0x21);
	Opl->_WriteReg(0x41,0x1a);
	Opl->_WriteReg(0x44,0x09);
	Opl->_WriteReg(0x61,0x84);
	Opl->_WriteReg(0x64,0x84);
	Opl->_WriteReg(0x81,0x29);
	Opl->_WriteReg(0x84,0x44);
	Opl->_WriteReg(0xe4,0x00);
	Opl->_WriteReg(0xe1,0x02);
	Opl->_WriteReg(0xc1,0x06);
	Opl->_WriteReg(0xa1,0x8b);
	Opl->_WriteReg(0xb1,0x2a);
}

void JuceOplvstiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceOplvstiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.clear(0, 0, buffer.getNumSamples());
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
