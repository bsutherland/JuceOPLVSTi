#include "DROMultiplexer.h"

#include "JuceHeader.h"

// Used by the first recording instance to claim master status
// TODO: develop the logic for recording data from other (non-master) plugins
DROMultiplexer* DROMultiplexer::master = NULL;

static Bit8u dro_header[] = {
	'D', 'B', 'R', 'A',		/* 0x00, Bit32u ID */
	'W', 'O', 'P', 'L',		/* 0x04, Bit32u ID */
	0x0, 0x00,				/* 0x08, Bit16u version low */
	0x1, 0x00,				/* 0x09, Bit16u version high */
	0x0, 0x0, 0x0, 0x0,		/* 0x0c, Bit32u total milliseconds */
	0x0, 0x0, 0x0, 0x0,		/* 0x10, Bit32u total data */
	0x0, 0x0, 0x0, 0x0			/* 0x14, Bit32u Type 0=opl2,1=opl3,2=dual-opl2 */
};

static Bit8u dro_opl3_enable[] = {
	0x03,	// switch to extended register bank
	0x05,	// register 0x105
	0x01,	// value 0x1
	0x02	// switch back to regular OPL2 registers
};

INLINE void host_writed(Bit8u *off, Bit32u val) {
	off[0] = (Bit8u)(val);
	off[1] = (Bit8u)(val >> 8);
	off[2] = (Bit8u)(val >> 16);
	off[3] = (Bit8u)(val >> 24);
};

DROMultiplexer::DROMultiplexer()
{
}


DROMultiplexer::~DROMultiplexer()
{
}

void DROMultiplexer::TwoOpMelodicNoteOn(Hiopl* opl, int ch) {

}

void DROMultiplexer::TwoOpMelodicNoteOff(Hiopl* opl, int ch) {

}

void DROMultiplexer::PercussionHit(Hiopl* opl) {

}


void DROMultiplexer::InitCaptureVariables() {
	captureHandle = NULL;
	captureLengthBytes = 0;
	lastWrite = -1;
	captureStart = -1;
}

void DROMultiplexer::StartCapture(const char* filepath, Hiopl *opl) {
	DROMultiplexer::master = this;
	lastWrite = -1;
	captureLengthBytes = 0;
	captureStart = Time::currentTimeMillis();
	captureHandle = fopen(filepath, "wb");
	fwrite(dro_header, 1, sizeof(dro_header), captureHandle);
	for (int i = 0; i <= 0xff; i++) {
		_CaptureRegWrite(i, 0);
	}
	_CaptureOpl3Enable();
	for (Bit8u i = 0x20; i <= 0x35; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i));
	}
	for (Bit8u i = 0x40; i <= 0x55; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i));
	}
	for (Bit8u i = 0x60; i <= 0x75; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i));
	}
	for (Bit8u i = 0x80; i <= 0x95; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i));
	}
	_CaptureRegWrite(0xbd, opl->_ReadReg(0xbd));
	for (Bit8u i = 0xc0; i <= 0xc8; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i) | 0x30);	// enable L + R channels
	}
	for (Bit8u i = 0xe0; i <= 0xf5; i++) {
		_CaptureRegWrite(i, opl->_ReadReg(i));
	}
}

void DROMultiplexer::StopCapture() {
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

void DROMultiplexer::_CaptureDelay(Bit16u delayMs) {
	Bit8u delay[3];
	delay[0] = 0x01;
	delay[1] = delayMs & 0xff;
	delay[2] = (delayMs >> 8) & 0xff;
	fwrite(delay, 1, 3, captureHandle);
	captureLengthBytes += 3;
}

void DROMultiplexer::_CaptureRegWrite(Bit32u reg, Bit8u value) {
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

void DROMultiplexer::_CaptureRegWriteWithDelay(Bit32u reg, Bit8u value) {
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

void DROMultiplexer::_CaptureOpl3Enable() {
	fwrite(dro_opl3_enable, 1, 4, captureHandle);
	captureLengthBytes += 4;
}

bool DROMultiplexer::IsAnInstanceRecording() {
	return NULL != DROMultiplexer::master;
}

bool DROMultiplexer::IsAnotherInstanceRecording() {
	return this->IsAnInstanceRecording() && this != DROMultiplexer::master;
}
