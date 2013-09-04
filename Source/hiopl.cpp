#include "Hiopl.h"

#include <assert.h>

// A higher level wrapper around the DOSBox OPL emulator.

Hiopl::Hiopl(int buflen) {
	adlib = new DBOPL::Handler();
	Buf32 = new Bit32s[buflen];
}

void Hiopl::Generate(int length, short* buffer) {
	//printf("Generating %d samples\n", length);
	adlib->Generate(length, Buf32);
	for (int i = 0; i < length; i++) {
		buffer[i] = (short)(Buf32[i]);
	}
}

void Hiopl::SetSampleRate(int hz) {
	adlib->Init(hz);
}

void Hiopl::_WriteReg(Bit32u reg, Bit8u value) {
	adlib->WriteReg(reg, value);
	regCache[reg] = value;
}

void Hiopl::SetWaveform(int ch, int osc, Waveform wave) {
	assert(_CheckParams(ch, osc));
	_WriteReg(0xe0+2*ch+osc, wave);
}

Waveform Hiopl::GetWaveform(int ch, int osc) {
	assert(_CheckParams(ch, osc));
	return static_cast<Waveform>(regCache[0xe0+2*ch+osc]);
}

void Hiopl::KeyOn(int ch, int frq) {

}

Hiopl::~Hiopl() {
	delete Buf32;
};

bool Hiopl::_CheckParams(int ch, int osc) {
	return ch >= 0 && ch < CHANNELS && osc >= 0 && osc < OSCILLATORS;
}