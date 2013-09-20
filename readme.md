# OPL2 VST plugin #

This VST instrument emulates the OPL2 sound chip.

## What's an OPL2 when it's at home? ##

The OPL2 is a digital sound synthesis chip developed by Yamaha in the mid 1980s. Among other products, it was used in sound cards for PC, including the Adlib card, and later the Sound Blaster Pro, which had two OPL2 chips for stereo output.

At a technical level: the chip can produce 9 channels of sound, each channel having 2 oscillators. Each pair of oscillators is usually combined via phase modulation, which in this case is mathematically equivalent to frequency modulation. Each oscillator can produce one of four variations of a sine wave (sine, half sine, absolute sine and quarter sine), and has an ADSR envelope controlling its amplitude. The unusual waveforms give it a characteristic sound.

The chip is programmed through an 8-bit write-only register interface in a 256 byte address space.

## How do I use it? ##

Each instance of the plugin emulates an entire OPL2 chip, but polyphony is implemented by using a channel per note, with parameter changes applied to all channels. Essentially you are just working with two operators like this:



## How did you create the instrument programs? ##

To figure out the parameters used by the original games, I just added a printf to the DOSBox OPL emulator, compiled DOSBox, ran the games, and captured their output.

I hacked together a Python script which parses the raw output, identifying unique instruments and outputting the parameter values as normalized floating point values for the VST.

## Why did you do this? ##

I grew up in the early 90s. For a long time, I had no sound card in my PC at the time (a 486). Eventually I bought a secondhand Sound Blaster Pro, and it transformed games completely. Music from games like Syndicate, Dune 2 and Doom have stuck with me since then.

Although there are many FM synthesis VST instruments, I couldn't find any which emulated the OPL2 precisely.

While working on this plugin I learned about the VST interface, how much C++ has improved in recent standards, and FM synthesis.

## How did you do this? ##

The emulation (ie, the hard part!) is taken straight from the excellent DOSBox emulator. The current DOSBox OPL emulator was rewritten a couple of years ago to use only integer math. The previous DOSBox OPL emulator, using floating point math, was derived from the MAME OPL emulator, which in turn was derived from ADLIBEMU, a library by Ken Silverman (who wrote the engine used in Duke Nukem 3D). I also used a function from libgamemusic by Adam Nielsen for converting frequencies from Hertz into the "FNUM" values used by the OPL2.

The VST was written using Juce, a cross-platform C++ library inspired by the Java JDK. Among other things, Juce provides a GUI for generating empty classes for audio plugins.

The code I wrote is basically conversion glue between the DOSBox OPL emulator (original OPL 8-bit register interface), the VST interface (all parameters and samples are normalized floating-point values), and human friendly values.

