#include "Hiopl.h"

#include <assert.h>
#include "JuceHeader.h"

// A wrapper around the DOSBox and ZDoom OPL emulators.

// Used by the first recording instance to claim master status
// TODO: develop the logic for recording data from other (non-master) plugins
Hiopl* Hiopl::master = NULL;

bool Hiopl::IsAnInstanceRecording() {
	return NULL != Hiopl::master;
}

bool Hiopl::IsAnotherInstanceRecording() {
	return this->IsAnInstanceRecording() && this != Hiopl::master;
}

Hiopl::Hiopl(int buflen, Emulator emulator) {
	InitCaptureVariables();

	adlib = new DBOPL::Handler();
	zdoom = JavaOPLCreate(false);

	_op1offset[1] = 0x0;
	_op1offset[2] = 0x1;
	_op1offset[3] = 0x2;
	_op1offset[4] = 0x8;
	_op1offset[5] = 0x9;
	_op1offset[6] = 0xa;
	_op1offset[7] = 0x10;
	_op1offset[8] = 0x11;
	_op1offset[9] = 0x12;
	
	_op2offset[1] = 0x3;
	_op2offset[2] = 0x4;
	_op2offset[3] = 0x5;
	_op2offset[4] = 0xb;
	_op2offset[5] = 0xc;
	_op2offset[6] = 0xd;
	_op2offset[7] = 0x13;
	_op2offset[8] = 0x14;
	_op2offset[9] = 0x15;

	SetEmulator(emulator);
	_ClearRegisters();
}

void Hiopl::_ClearRegisters() {
	for (int i = 0; i < 256; i++) {
		_WriteReg(i, 0);
	}
}

void Hiopl::SetEmulator(Emulator emulator) {
	this->emulator = emulator;
}

void Hiopl::Generate(int length, float* buffer) {
	// This would be better done using Juce's built in audio format conversion.
	if (DOSBOX == emulator) {
		Bit32s* buf32 = new Bit32s[length];
		adlib->Generate(length, buf32);
		for (int i = 0; i < length; i++) {
			// The magic divisor is tuned to match to ZDoom output amplitude.
			buffer[i] = (float)(buf32[i])/8200.0f;
		}
		delete buf32;
	} else if (ZDOOM == emulator) {
		// ZDoom hacked to write mono samples
		zdoom->Update(buffer, length);
	}
}

void Hiopl::SetSampleRate(int hz) {
	adlib->Init(hz);
}

void Hiopl::_WriteReg(Bit32u reg, Bit8u value, Bit8u mask) {
	if (mask > 0) {
		value = (regCache[reg] & (~mask)) | (value & mask);
	}
	// Write to the registers of both emulators.
	//if (DOSBOX == emulator) {
		adlib->WriteReg(reg, value);
	//} else if (ZDOOM == emulator) {
		zdoom->WriteReg(reg, value);
	//}
	regCache[reg] = value;
	_CaptureRegWriteWithDelay(reg, value);
}

void Hiopl::_ClearRegBits(Bit32u reg, Bit8u mask) {
	_WriteReg(reg, regCache[reg] & ~mask);
}

void Hiopl::EnableWaveformControl() {
	_WriteReg(0x01, 0x20);
}

void Hiopl::SetWaveform(int ch, int osc, Waveform wave) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0xe0+offset, (Bit8u)wave, 0x7);
}

void Hiopl::SetAttenuation(int ch, int osc, int level) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x40+offset, (Bit8u)level, 0x3f);
}

void Hiopl::SetKsl(int ch, int osc, int level) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x40+offset, (Bit8u)(level<<6), 0xc0);
}

void Hiopl::SetFrequencyMultiple(int ch, int osc, FreqMultiple mult) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x20+offset, (Bit8u)mult, 0xf);
}

void Hiopl::SetEnvelopeAttack(int ch, int osc, int t) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x60+offset, (Bit8u)t<<4, 0xf0);
}

void Hiopl::SetEnvelopeDecay(int ch, int osc, int t) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x60+offset, (Bit8u)t, 0x0f);
}

void Hiopl::SetEnvelopeSustain(int ch, int osc, int level) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x80+offset, (Bit8u)level<<4, 0xf0);
}

void Hiopl::SetEnvelopeRelease(int ch, int osc, int t) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x80+offset, (Bit8u)t, 0x0f);
}

void Hiopl::EnableTremolo(int ch, int osc, bool enable) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x20+offset, enable ? 0x80 : 0x0, 0x80);
}

void Hiopl::EnableVibrato(int ch, int osc, bool enable) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x20+offset, enable ? 0x40 : 0x0, 0x40);
}

void Hiopl::TremoloDepth(bool high) {
	_WriteReg(0xbd, high ? 0x80 : 0x0, 0x80);
}

void Hiopl::VibratoDepth(bool high) {
	_WriteReg(0xbd, high ? 0x40 : 0x0, 0x40);
}

void Hiopl::EnableSustain(int ch, int osc, bool enable) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x20+offset, enable ? 0x20 : 0x0, 0x20);
}

void Hiopl::EnableKsr(int ch, int osc, bool enable) {
	int offset = this->_GetOffset(ch, osc);
	_WriteReg(0x20+offset, enable ? 0x10 : 0x0, 0x10);
}

void Hiopl::EnableAdditiveSynthesis(int ch, bool enable) {
	int offset = this->_GetOffset(ch);
	_WriteReg(0xc0+offset, enable ? 0x1 : 0x0, 0x1);
}

void Hiopl::SetModulatorFeedback(int ch, int level) {
	int offset = this->_GetOffset(ch);
	_WriteReg(0xc0+offset, (Bit8u)level, 0x0e);
}

void Hiopl::SetPercussionMode(bool enable) {
	_WriteReg(0xbd, enable ? 0x20 : 0x0, 0x20);
}

void Hiopl::HitPercussion(Drum drum) {
	Bit8u mask = (Bit8u)drum;
	_WriteReg(0xbd, mask, mask);
}

void Hiopl::ReleasePercussion() {
	_WriteReg(0xbd, 0x0, 0x1f);
}

void Hiopl::KeyOn(int ch, float frqHz) {
	Hiopl::SetFrequency(ch, frqHz, true);
}

void Hiopl::KeyOff(int ch) {
	int offset = this->_GetOffset(ch);
	_ClearRegBits(0xb0+offset, 0x20);
}

void Hiopl::SetFrequency(int ch, float frqHz, bool keyOn) {
	unsigned int fnum, block;
	int offset = this->_GetOffset(ch);
	// ZDoom emulator seems to be tuned down by two semitones for some reason.
	if (ZDOOM == emulator) {
		frqHz *= 1.122461363636364f;
	}
	_milliHertzToFnum((unsigned int)(frqHz * 1000.0), &fnum, &block);
	_WriteReg(0xa0+offset, fnum % 0x100);
	uint8 trig = (regCache[0xb0+offset] & 0x20) | (keyOn ? 0x20 : 0x00);
	_WriteReg(0xb0+offset, trig|((block&0x7)<<2)|(0x3&(fnum/0x100)));
}

// from libgamemusic, opl-util.cpp
void Hiopl::_milliHertzToFnum(unsigned int milliHertz,
	unsigned int *fnum, unsigned int *block, unsigned int conversionFactor)
{
	// Special case to avoid divide by zero
	if (milliHertz == 0) {
		*block = 0; // actually any block will work
		*fnum = 0;
		return;
	}
	// Special case for frequencies too high to produce
	if (milliHertz > 6208431) {
		*block = 7;
		*fnum = 1023;
		return;
	}

	// This is a bit more efficient and doesn't need log2() from math.h
	if (milliHertz > 3104215) *block = 7;
	else if (milliHertz > 1552107) *block = 6;
	else if (milliHertz > 776053) *block = 5;
	else if (milliHertz > 388026) *block = 4;
	else if (milliHertz > 194013) *block = 3;
	else if (milliHertz > 97006) *block = 2;
	else if (milliHertz > 48503) *block = 1;
	else *block = 0;

	// Slightly more efficient version
	*fnum = (unsigned int)(((unsigned long long)milliHertz << (20 - *block)) / (conversionFactor * 1000.0) + 0.5);
	if ((*block == 7) && (*fnum > 1023)) {
		// frequency out of range, clipping to maximum value.
		*fnum = 1023;
	}
	assert(*block <= 7);
	assert(*fnum < 1024);
	return;
}

static Bit8u dro_header[]={
	'D','B','R','A',		/* 0x00, Bit32u ID */
	'W','O','P','L',		/* 0x04, Bit32u ID */
	0x0,0x00,				/* 0x08, Bit16u version low */
	0x1,0x00,				/* 0x09, Bit16u version high */
	0x0,0x0,0x0,0x0,		/* 0x0c, Bit32u total milliseconds */
	0x0,0x0,0x0,0x0,		/* 0x10, Bit32u total data */
	0x0,0x0,0x0,0x0			/* 0x14, Bit32u Type 0=opl2,1=opl3,2=dual-opl2 */
};

static Bit8u dro_opl3_enable[]={
	0x03,	// switch to extended register bank
	0x05,	// register 0x105
	0x01,	// value 0x1
	0x02	// switch back to regular OPL2 registers
};

void Hiopl::StartCapture(const char* filepath) {
	Hiopl::master = this;
	lastWrite = -1;
	captureLengthBytes = 0;
	captureStart = Time::currentTimeMillis();
	captureHandle = fopen(filepath, "wb");
	fwrite(dro_header, 1, sizeof(dro_header), captureHandle);
	for (int i = 0; i <= 0xff; i++) {
		_CaptureRegWrite(i, 0);
	}
	//_CaptureRegWrite(0x1, 0x20);
	/*
	for (int ch = 1; ch <= CHANNELS; ch++) {
		int offset1 = this->_GetOffset(ch, 1);
		int offset2 = this->_GetOffset(ch, 2);
		int offset0 = this->_GetOffset(ch);
		_CaptureRegWrite(0x20 + offset1, regCache[0x20 + offset1]);
		_CaptureRegWrite(0x20 + offset2, regCache[0x20 + offset2]);
		_CaptureRegWrite(0x40 + offset1, regCache[0x40 + offset1]);
		_CaptureRegWrite(0x40 + offset2, regCache[0x40 + offset2]);
		_CaptureRegWrite(0x60 + offset1, regCache[0x60 + offset1]);
		_CaptureRegWrite(0x60 + offset2, regCache[0x60 + offset2]);
		_CaptureRegWrite(0x80 + offset1, regCache[0x80 + offset1]);
		_CaptureRegWrite(0x80 + offset2, regCache[0x80 + offset2]);
		_CaptureRegWrite(0xe0 + offset1, regCache[0xe0 + offset1]);
		_CaptureRegWrite(0xe0 + offset2, regCache[0xe0 + offset2]);
		_CaptureRegWrite(0xc0 + offset0, regCache[0xc0 + offset0]);
	}
	*/
	_CaptureOpl3Enable();
	for (Bit8u i = 0x20; i <= 0x35; i++) {
		_CaptureRegWrite(i, regCache[i]);
	}
	for (Bit8u i = 0x40; i <= 0x55; i++) {
		_CaptureRegWrite(i, regCache[i]);
	}
	for (Bit8u i = 0x60; i <= 0x75; i++) {
		_CaptureRegWrite(i, regCache[i]);
	}
	for (Bit8u i = 0x80; i <= 0x95; i++) {
		_CaptureRegWrite(i, regCache[i]);
	}
	_CaptureRegWrite(0xbd, regCache[0xbd]);
	for (Bit8u i = 0xc0; i <= 0xc8; i++) {
		_CaptureRegWrite(i, regCache[i] | 0x30);	// enable L + R channels
	}
	for (Bit8u i = 0xe0; i <= 0xf5; i++) {
		_CaptureRegWrite(i, regCache[i]);
	}
}

INLINE void host_writed(Bit8u *off, Bit32u val) {
	off[0]=(Bit8u)(val);
	off[1]=(Bit8u)(val >> 8);
	off[2]=(Bit8u)(val >> 16);
	off[3]=(Bit8u)(val >> 24);
};

void Hiopl::InitCaptureVariables() {
	captureHandle = NULL;
	captureLengthBytes = 0;
	lastWrite = -1;
	captureStart = -1;
}

void Hiopl::StopCapture() {
	if (NULL != captureHandle) {
		Bit16u finalDelay = (Bit16u)(Time::currentTimeMillis() - lastWrite);
		_CaptureDelay(finalDelay);
		Bit32u lengthMilliseconds = (Bit32u)(finalDelay + Time::currentTimeMillis() - captureStart);
		host_writed(&dro_header[0x0c], lengthMilliseconds);
		host_writed(&dro_header[0x10], captureLengthBytes);
		//if (opl.raw.opl3 && opl.raw.dualopl2) host_writed(&dro_header[0x14],0x1);
		//else if (opl.raw.dualopl2) host_writed(&dro_header[0x14],0x2);
		//else host_writed(&dro_header[0x14],0x0);
		host_writed(&dro_header[0x14], 0x1);	// OPL3
		fseek(captureHandle, 0, 0);
		fwrite(dro_header, 1, sizeof(dro_header), captureHandle);
		fclose(captureHandle);
	}
	InitCaptureVariables();
}

void Hiopl::_CaptureDelay(Bit16u delayMs) {
	Bit8u delay[3];
	delay[0] = 0x01;
	delay[1] = delayMs & 0xff;
	delay[2] = (delayMs >> 8) & 0xff;
	fwrite(delay, 1, 3, captureHandle);
	captureLengthBytes += 3;
}

void Hiopl::_CaptureRegWrite(Bit32u reg, Bit8u value) {
	if (reg <= 0x4) {
		Bit8u escape = 0x4;
		fwrite(&escape, 1, 1, captureHandle);
		captureLengthBytes += 1;
	}
	Bit8u regAndVal[2];
	regAndVal[0] = (Bit8u)reg;
	regAndVal[1] = value;
	fwrite(regAndVal, 1, 2, captureHandle);
	captureLengthBytes += 2;
}

void Hiopl::_CaptureRegWriteWithDelay(Bit32u reg, Bit8u value) {
	if (NULL != captureHandle) {
		Bit64s t = Time::currentTimeMillis();
		if (lastWrite >= 0) {
			// Delays of over 65 seconds will be truncated, but that kind of delay is a bit silly anyway..
			_CaptureDelay((Bit16u)(t - lastWrite));
		}
		_CaptureRegWrite(reg, value);
		lastWrite = t;
	}
}

void Hiopl::_CaptureOpl3Enable() {
	fwrite(dro_opl3_enable, 1, 4, captureHandle);
	captureLengthBytes += 4;
}

Hiopl::~Hiopl() {

};

bool Hiopl::_CheckParams(int ch, int osc=OSCILLATORS) {
	return ch > 0 && ch <= CHANNELS && osc > 0 && osc <= OSCILLATORS;
}

int Hiopl::_GetOffset(int ch, int osc) {
	assert(_CheckParams(ch, osc));
	return (1 == osc) ? _op1offset[ch] : _op2offset[ch];
}

int Hiopl::_GetOffset(int ch) {
	assert(_CheckParams(ch));
	return ch - 1;
}
