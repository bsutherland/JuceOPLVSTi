#pragma once
#include "c:\code\juceoplvsti\source\instrumentloader.h"
class SbiLoader :
	public InstrumentLoader
{
public:
	SbiLoader(void);
	virtual ~SbiLoader(void);

	void loadInstrumentData(int n, const unsigned char* data, JuceOplvstiAudioProcessor *proc);
	String getExtension();
};

