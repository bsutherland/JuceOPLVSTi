# OPL VST plugin #

This VST instrument provides an emulated OPL sound chip. It provides all features of the OPL2, and some features of the OPL3. It is distributed under the GPLv2 or later.

See here for binaries, screenshots etc: http://bsutherland.github.io/JuceOPLVSTi/

## Maintenance status ##

I'm sorry to say, this project is now essentially unmaintained.

If you're looking for an alternative, I'd like to recommend ADLplug (https://github.com/jpcima/ADLplug). I'm not affiliated with the project, but it looks like an excellent plugin:

- maintained
- 32/64 bit builds for Windows and OSX
- OPL3 support
- multiple emulator cores
- etc!!!

## What's an OPL? ##

The OPL is a digital sound synthesis chip developed by Yamaha in the mid 1980s. Among other products, it was used in sound cards for PC, including the Ad Lib card and early Sound Blaster series.

At a technical level: the emulator has channels comprised of 2 oscillators each. Each pair of oscillators is usually combined via phase modulation (basically frequency modulation). Each oscillator can produce one of eight waveforms (sine, half sine, absolute sine, quarter sine, alternating sine, camel sine, square, logarithmic sawtooth), and has an ADSR envelope controlling its amplitude. The unusual waveforms give it a characteristic sound.

## Caveats and Limitations ##

Before I wrote this, I didn't know much about VST or the OPL at a technical level. This is the first VST plugin I've written, and my knowledge of C++ was extremely limited. In hindsight I would have implemented things a bit differently, but it all basically works, and is now reasonably well tested.

One thing I have learned is that all VST hosts are not created equal. I only really work with Renoise. Your mileage may vary. I also don't have a Mac at home, so unfortunately I have no way to build / test on OSX. Working binaries for OSX would be gladly accepted.

Note that I started and work on this project for fun. I'm not accepting donations, but any contributions in the form of code, SBI files, links to music you've created etc are very welcome.

While I'm very happy that a lot of people are enjoying the plugin, please also understand that I also write software full time for a living and have a life outside of software development.

## How do I use it? ##

Each instance of the plugin emulates an entire OPL chip, but with this plugin, essentially you are just working with two operators: the carrier and modulator.

Some documentation which may be useful:

- [Introduction to FM Synthesis](https://www.youtube.com/watch?v=ziFv00PegJg) (not specific to the OPL, but a great primer)
- [OPL2 on Wikipedia](http://en.wikipedia.org/wiki/Yamaha_YM3812)
- [Original Yamaha datasheet](http://www.alldatasheet.com/datasheet-pdf/pdf/84281/YAMAHA/YM3812.html)
- [AdLib programming guide](http://www.shipbrook.net/jeff/sb.html) Dates back to 1991!
- [Another programming guide](http://www.ugcs.caltech.edu/~john/computer/opledit/tech/opl3.txt) This one is for the OPL3, but most of the information still applies.

## What can it do? ##

Here are some examples:

- [Demo showing how parameters affect sound](https://www.youtube.com/watch?v=yU0CWQ66Z28)Thanks estonoesunusuario!
- [Dune 2 music reproduced using the plugin](https://www.youtube.com/watch?v=w6Lu0C_vZwQ)Great work by Ion Claudiu Van Damme
- [Tyrian remix](https://www.youtube.com/watch?v=ZGwhKVFMCqM) by Block35 Music
- [Syndicate theme](https://www.youtube.com/watch?v=HI7U5XxTSW0) demo I created for the first release
- (your link here...)

### SBI Files ###

SBI files are an instrument file format developed by Creative Labs back in the day for the Sound Blaster. Essentially they work as presets for this plugin. Just drag and drop them into the plugin window!

I've collected a bunch of presets in this repository. I've also added support for saving SBI files. Please contribute!

It's possible to extract SBI instruments from games using [DOSBox 0.7.2](https://sourceforge.net/projects/dosbox/files/dosbox/0.72/) and [DRO2MIDI](https://github.com/Malvineous/dro2midi) by Malvineous.

1. Run the game in DOSBox.
2. Start capturing OPL output with ctrl+alt+F7. Output will be recorded to a .dro file.
3. Run DRO2MIDI:
  `dro2midi -s input_capture.dro output_midi.mid`

Note data will be extracted to .mid, instruments will be extracted to .sbi files.

### Percussion ###

Percussion mode is now supported! This mode is not very well documented, even in the original Yamaha documentation. Here are some tips on using it based on experimentation and looking at the DOSBox source code.

- Bass drum: Uses both operators. Essentially just doubles output amplitude?
- Snare: Uses carrier settings. Abs-sine waveform recommended.
- Tom: Uses modulator settings. Sine waveform recommended.
- Cymbal: Uses carrier settings. Half-sine recommended.
- Hi-hat: Uses modulator settings. Half-sine recommended.

Also, some [much more detailed notes](http://midibox.org/forums/topic/18625-opl3-percussion-mode-map/) on percussion mode based on experimentation with real hardware!

## How did you create the instrument programs? ##

To figure out the parameters used by the original games, I just added a printf to the DOSBox OPL emulator, compiled DOSBox, ran the games, and captured their output as raw register writes with timestamps.

I hacked together a Python script which parses the raw output, identifying unique instruments and outputting the parameter values.

## How did you create this? ##

The emulation (ie, the hard part!) is taken straight from the excellent DOSBox project. I also used a function from libgamemusic by Adam Nielsen for converting frequencies from Hertz into the "FNUM" values used by the OPL.

The VST was written using Juce, a cross-platform C++ library inspired by the Java JDK. Among other things, Juce provides a GUI for generating boilerplate for audio plugins.

The code I wrote is essentially a device driver for the emulated OPL, implementing the VST interface, and providing a UI.

## Building ##

So far I've only built under Windows. Thanks to the hard work of Jeff Russ, there is also an OSX build, but I currently have no way to build it myself on OSX..

### Windows Build Instructions ###

1. Download Juce (http://www.juce.com/)
2. Download the VST SDK (http://www.steinberg.net/en/company/developers.html)
3. Run "The Projucer" executable included in Juce.
4. Open JuceOPLVSTi.jucer
   - Make any changes to the GUI layout and components here (PluginEditor.cpp).
   - Save PluginEditor.cpp if modified
5. Hit "Save Project and Open in Visual Studio". I use Visual Studio Express 2015.
6. Select the build: "Release - 64-bit" and set platform to x64.
7. (Optional, for Windows XP compatibility) In the project's properties, set platform toolset to Windows XP (Configuration Properties > General).
8. Build!


### Linux Build Instructions ###

Thanks to Dave Phillips. See original instructions here: https://www.linuxmusicians.com/viewtopic.php?f=19&t=15485

1. Download Juce (http://www.juce.com)
2. Download the VST SDK (http://www.steinberg.net/en/company/developers.html)
3. Open JuceOPLVSTi.jucer in the Introjucer application.
   - Right click on the JuceOPLVSTi label in the file tree.
   - Select "Create Linux Makefile Target".
   - Open the juce_audio_basics module. Set paths and/or update all other Juce modules as required.
   - Click on the Linux Makefile label and set the location of the VST SDK.
4. Make. Output at Builds/LinuxMakefile/build/JuceOPLVSTi.so

