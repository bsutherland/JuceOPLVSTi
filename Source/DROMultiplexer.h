#pragma once
#include "hiopl.h"

class DROMultiplexer
{
public:
	DROMultiplexer();
	~DROMultiplexer();

	void TwoOpMelodicNoteOn(Hiopl* opl, int ch);
	void TwoOpMelodicNoteOff(Hiopl* opl, int ch);
	void PercussionHit(Hiopl* opl);

	void InitCaptureVariables();
	bool IsAnInstanceRecording();
	bool IsAnotherInstanceRecording();
	void StartCapture(const char* filepath, Hiopl* opl);
	void StopCapture();

//private:
	void _CaptureDelay(Bit16u delayMs);
	void _CaptureRegWriteWithDelay(Bit32u reg, Bit8u value);
	void _CaptureRegWrite(Bit32u reg, Bit8u value);
	void _CaptureOpl3Enable();

	static DROMultiplexer* master;
	FILE* captureHandle;
	Bit64s captureStart;
	Bit64s lastWrite;
	Bit32u captureLengthBytes;

};

