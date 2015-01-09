#pragma once
#include <map>
#include "hiopl.h"
#include "../JuceLibraryCode/JuceHeader.h"

class DROMultiplexer
{
public:
	static const int MELODIC_CHANNELS = 15;

	DROMultiplexer();
	~DROMultiplexer();

	void TwoOpMelodicNoteOn(Hiopl* opl, int ch);
	void TwoOpMelodicNoteOff(Hiopl* opl, int ch);
	void PercussionHit(Hiopl* opl);

	void InitCaptureVariables();
	bool IsAnInstanceRecording();
	bool IsAnotherInstanceRecording();
	bool StartCapture(const char* filepath, Hiopl* opl);
	void StopCapture();
	static DROMultiplexer* GetMaster();

private:
	void _CaptureDelay(Bit16u delayMs);
	void _CaptureRegWriteWithDelay(Bit32u reg, Bit8u value);
	void _CaptureRegWrite(Bit32u reg, Bit8u value);
	void _CaptureOpl3Enable();
	int _FindFreeChannel(Hiopl* opl, int inCh);
	void _DebugOut(const char* str);
	static DROMultiplexer* master;

	FILE* captureHandle;
	Bit64s captureStart;
	Bit64s lastWrite;
	Bit32u captureLengthBytes;
	static CriticalSection lock;

	typedef struct oplch {
		Hiopl* opl;
		int ch;
		bool operator<(const oplch &o) const {
			return opl < o.opl ||
				(opl == o.opl && ch < o.ch);
		};
		bool operator==(const oplch &o) const {
			return opl == o.opl && ch == o.ch;
		};
	} OplCh_t;

	OplCh_t channels[MELODIC_CHANNELS];
	std::map<OplCh_t, int> channelMap;
};

