# OPL VST plugin #

This VST instrument provides an emulated OPL sound chip. It provides all features of the OPL2, and some features of the OPL3.

See here for binaries, screenshots etc: http://bsutherland.github.io/JuceOPLVSTi/

## What's an OPL? ##

The OPL is a digital sound synthesis chip developed by Yamaha in the mid 1980s. Among other products, it was used in sound cards for PC, including the Ad Lib card and early Sound Blaster series.

At a technical level: the emulator has channels comprised of 2 oscillators each. Each pair of oscillators is usually combined via phase modulation (basically frequency modulation). Each oscillator can produce one of eight waveforms (sine, half sine, absolute sine, quarter sine, alternating sine, camel sine, square, logarithmic sawtooth), and has an ADSR envelope controlling its amplitude. The unusual waveforms give it a characteristic sound.

## Caveats and Limitations ##

Before I wrote this, I didn't know much about VST or the OPL at a technical level. This is the first VST plugin I've written. The sample rate is locked at 44.1 kHz. In hindsight I would have implemented things a bit differently, but it all basically works, and is now reasonably well tested.

## How do I use it? ##

Each instance of the plugin emulates an entire OPL chip, but polyphony is implemented by using a channel per note. Parameter changes applied to all channels. With this plugin, essentially you are just working with two operators.

Some documentation which may be useful:

- [Introduction to FM Synthesis](https://www.youtube.com/watch?v=ziFv00PegJg) (not specific to the OPL, but a great primer)
- [OPL2 on Wikipedia](http://en.wikipedia.org/wiki/Yamaha_YM3812)
- [Original Yamaha datasheet](http://www.alldatasheet.com/datasheet-pdf/pdf/84281/YAMAHA/YM3812.html)
- [AdLib programming guide](http://www.shipbrook.net/jeff/sb.html) Dates back to 1991!
- [Another programming guide](http://www.ugcs.caltech.edu/~john/computer/opledit/tech/opl3.txt) This one is for the OPL3, but most of the information still applies.

### Percussion

Percussion mode is now supported! This mode is not very well documented, even in the original Yamaha documentation. It works with the DOSBox emulator, but doesn't seem to work too well in the ZDoom emulator. Here are some tips on using it based on experimentation and looking at the DOSBox source code.

- Bass drum: Uses both operators. Essentially just doubles output amplitude?
- Snare: Uses carrier settings. Abs-sine waveform recommended.
- Tom: Uses modulator settings. Sine waveform recommended.
- Cymbal: Uses carrier settings. Half-sine recommended.
- Hi-hat: Uses modulator settings. Half-sine recommended.

Also, some [much more detailed notes](http://midibox.org/forums/topic/18625-opl3-percussion-mode-map/) on percussion mode based on experimentation with real hardware!



## How did you create the instrument programs? ##

To figure out the parameters used by the original games, I just added a printf to the DOSBox OPL emulator, compiled DOSBox, ran the games, and captured their output as raw register writes with timestamps.

I hacked together a Python script which parses the raw output, identifying unique instruments and outputting the parameter values.

## How did you do this? ##

The emulation (ie, the hard part!) is taken straight from the excellent DOSBox and ZDoom projects. I also used a function from libgamemusic by Adam Nielsen for converting frequencies from Hertz into the "FNUM" values used by the OPL.

The VST was written using Juce, a cross-platform C++ library inspired by the Java JDK. Among other things, Juce provides a GUI for generating boilerplate for audio plugins.

The code I wrote is essentially a device driver for the emulated OPL, implementing the VST interface, and providing a UI.

## Building ##

So far I've only built under Windows. Thanks to the hard work of others, OSX and Linux builds should be coming very soon!

### Windows Build Instructions ###

1. Download Juce (http://www.juce.com/)
2. Download the VST SDK (http://www.steinberg.net/en/company/developer.html)
3. Run "The Introjucer" executable included in Juce.
4. Open JuceOPLVSTi.jucer
   - Make any changes to the GUI layout and components here (PluginEditor.cpp).
   - Save PluginEditor.cpp if modified
5. Hit "Save Project and Open in Visual Studio". I use Visual Studio Express 2013.
6. (For Windows XP compatibility) In the project's properties, set platform toolset to Windows XP (Configuration Properties > General).
7. Build!
