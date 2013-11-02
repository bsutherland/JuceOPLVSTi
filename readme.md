# OPL2 VST plugin #

This VST instrument emulates the OPL2 sound chip.

## What's an OPL2? ##

The OPL2 is a digital sound synthesis chip developed by Yamaha in the mid 1980s. Among other products, it was used in sound cards for PC, including the Adlib card, and later the Sound Blaster Pro, which had two OPL2 chips for stereo output.

At a technical level: the chip can produce 9 channels of sound, each channel having 2 oscillators. Each pair of oscillators is usually combined via phase modulation (basically frequency modulation). Each oscillator can produce one of four variations of a sine wave (sine, half sine, absolute sine and quarter sine), and has an ADSR envelope controlling its amplitude. The unusual waveforms give it a characteristic sound.

The chip is programmed through an 8-bit write-only register interface in a 256 byte address space.

## Caveats and Limitations ##

Before I wrote this, I didn't know much about VST or the OPL at a technical level. This is the first VST plugin I've written.

Some limitations:

- Sample rate is locked at 44.1 kHz
- I'm a bit unsure as to whether the keyscale attenuation values are correct. I had two documents with conflicting information on that.
- There may be some subtle "out by one" type issues lingering around.
- I haven't added support for the built-in percussion. It's very poorly documented in the data sheet and seems like a lot of people never used it anyway.

In hindsight I would have implemented things a bit differently, but it all basically works.

Juce takes care of some of the tedious bits, but I was hoping it would take care of some more of the repetitive details, like converting to and from int/enum/float etc into the normalized floating point values used by VST. If it doesn't exist already, I think that I'd definitely write another layer of abstraction on top of Juce next time.

## How do I use it? ##

Each instance of the plugin emulates an entire OPL2 chip, but polyphony is implemented by using a channel per note, with parameter changes applied to all channels. With this plugin, essentially you are just working with two operators.

Some documentation which may be useful:

- [OPL2 on Wikipedia](http://en.wikipedia.org/wiki/Yamaha_YM3812)
- [Original Yamaha datasheet](http://www.alldatasheet.com/datasheet-pdf/pdf/84281/YAMAHA/YM3812.html)
- [AdLib programming guide](http://www.shipbrook.net/jeff/sb.html) Dates back to 1991!
- [Another programming guide](http://www.ugcs.caltech.edu/~john/computer/opledit/tech/opl3.txt) This one is for the OPL3, but most of the information still applies.

## How did you create the instrument programs? ##

To figure out the parameters used by the original games, I just added a printf to the DOSBox OPL emulator, compiled DOSBox, ran the games, and captured their output as raw register writes with timestamps.

I hacked together a Python script which parses the raw output, identifying unique instruments and outputting the parameter values.

## How did you do this? ##

The emulation (ie, the hard part!) is taken straight from the excellent DOSBox emulator. The current DOSBox OPL emulator was rewritten a couple of years ago to use only integer math. The previous DOSBox OPL emulator, using floating point math, was derived from the MAME OPL emulator, which in turn was derived from ADLIBEMU, a library by Ken Silverman (who wrote the engine used in Duke Nukem 3D). I also used a function from libgamemusic by Adam Nielsen for converting frequencies from Hertz into the "FNUM" values used by the OPL2.

The VST was written using Juce, a cross-platform C++ library inspired by the Java JDK. Among other things, Juce provides a GUI for generating boilerplate for audio plugins.

The code I wrote is basically conversion glue between the DOSBox OPL emulator, the VST interface, and human friendly values.

## Building ##

So far I've only built under Windows. Thanks to Juce, it should be possible to build under OSX and Linux too. **Volunteers to build OSX/Linux releases would be appreciated** (XCode required for OSX).

### Windows Build Instructions ###

1. Download Juce (http://www.juce.com/)
2. Build and run "The Introjucer"
3. Open JuceOPLVSTi.jucer
   - Make any changes to the GUI layout and components here (PluginEditor.cpp).
   - Save PluginEditor.cpp if modified
4. Hit "Save Project and Open in Visual Studio". I used Visual Studio Express 2012.
5. Build!
