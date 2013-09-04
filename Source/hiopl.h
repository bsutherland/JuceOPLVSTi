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
		void Hiopl::KeyOn(int ch, int frq);
		void _WriteReg(Bit32u reg, Bit8u value);
		~Hiopl();
	private:
		Adlib::Handler *adlib;
		Bit8u regCache[256];
		Bit32s *Buf32;
		bool _CheckParams(int ch, int osc);
};
