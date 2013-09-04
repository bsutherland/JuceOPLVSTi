#include "adlib.h"
#include "dbopl.h"

enum Waveform
{
	SIN = 0, HALF_SIN = 1, ABS_SIN = 2, QUART_SIN = 3
};

enum Oscillator
{
	CAR = 0, MOD = 1
};

const int CHANNELS = 9;
const int OSCILLATORS = 2;

class Hiopl {
	public:
		Hiopl(int buflen);
		void Generate(int length, short* buffer);
		void Generate(int length, float* buffer);
		void SetSampleRate(int hz);
		void SetWaveform(int ch, int osc, Waveform wave);
		Waveform GetWaveform(int ch, int osc);
		void KeyOn(int ch, float frqHz);
		void KeyOff(int ch);
		void _WriteReg(Bit32u reg, Bit8u value);
		void _ClearRegBits(Bit32u reg, Bit8u mask);
		~Hiopl();
	private:
		Adlib::Handler *adlib;
		Bit8u regCache[256];
		Bit32s *Buf32;
		bool _CheckParams(int ch, int osc);
		void _milliHertzToFnum(unsigned int milliHertz, unsigned int *fnum, unsigned int *block, unsigned int conversionFactor=49716);
};
