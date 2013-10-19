var DBOPL = new function() {	// DBOPL namespace

// dbopl.h

this.WAVE_HANDLER = 10;
this.WAVE_TABLELOG = 11;
this.WAVE_TABLEMUL = 12;
this.DBOPL_WAVE = this.WAVE_TABLEMUL;

this.SynthMode = {
	sm2AM:0,
	sm2FM:1,
	sm3AM:2,
	sm3FM:3,
	sm4Start:4,
	sm3FMFM:5,
	sm3AMFM:6,
	sm3FMAM:7,
	sm3AMAM:8,
	sm6Start:9,
	sm2Percussion:10,
	sm3Percussion:11,
};

this.SHIFT_KSLBASE = 16;
this.SHIFT_KEYCODE = 24;

this.Operator = function() {
	// public:

	// enum
	this.MASK_KSR = 0x10;
	this.MASK_SUSTAIN = 0x20;
	this.MASK_VIBRATO = 0x40;
	this.MASK_TREMOLO = 0x80;
	this.State = {	// typedef enum
		OFF:0,
		RELEASE:1,
		SUSTAIN:2,
		DECAY:3,
		ATTACK:4,
	};
	this.volHandler=0;
	this.waveBase=0;
	this.waveMask=0;
	this.waveStart=0;

	this.waveIndex=0;			//WAVE_BITS shifted counter of the frequency index
	this.waveAdd=0;				//The base frequency without vibrato
	this.waveCurrent=0;			//waveAdd + vibratao

	this.chanData=0;			//Frequency/octave and derived data coming from whatever channel controls this
	this.freqMul=0;				//Scale channel frequency with this, TODO maybe remove?
	this.vibrato=0;				//Scaled up vibrato strength
	this.sustainLevel=0;		//When stopping at sustain level stop here
	this.totalLevel=0;			//totalLevel is added to every generated volume
	this.currentLevel=0;		//totalLevel + tremolo
	this.volume=0;				//The currently active volume
	
	this.attackAdd=0;			//Timers for the different states of the envelope
	this.decayAdd=0;
	this.releaseAdd=0;
	this.rateIndex=0;			//Current position of the evenlope

	this.rateZero=0;				//Bits for the different states of the envelope having no changes
	this.keyOn=0;				//Bitmask of different values that can generate keyon
	//Registers, also used to check for changes
	this.reg20=0;
	this.reg40=0;
	this.reg60=0;
	this.reg80=0;
	this.regE0=0;
	//Active part of the envelope we're in
	this.state=0;
	//0xff when tremolo is enabled
	this.tremoloMask=0;
	//Strength of the vibrato
	this.vibStrength=0;
	//Keep track of the calculated KSR so we can check for changes
	this.ksr=0;

	return this;
};

// dbopl.cpp (private stuff)
var ZeroArray = function(size) {
	// http://stackoverflow.com/questions/1295584/most-efficient-way-to-create-a-zero-filled-javascript-array
	return Array.apply(null, new Array(size)).map(Number.prototype.valueOf,0);
};

var PI = 3.14159265358979323846;
var OPLRATE = 14318180.0 / 288.0;
var TREMOLO_TABLE = 52;
var WAVE_BITS = 10;
var WAVE_SH = 32 - WAVE_BITS;
var WAVE_MASK = (1 << WAVE_SH) - 1;
var LFO_SH = WAVE_SH - 10;
var LFO_MAX = 256 << LFO_SH;
var ENV_BITS = 9;
var ENV_MIN	= 0;
var ENV_EXTRA = ENV_BITS - 9;
var ENV_MAX = 511 << ENV_EXTRA;
var ENV_LIMIT = (12 * 256) >> (3 - ENV_EXTRA);
var ENV_SILENT = function(_X_) { return _X_ >= ENV_LIMIT; }
var RATE_SH = 24;
var RATE_MASK = (1 << RATE_SH ) - 1;
var MUL_SH = 16;

var KslCreateTable = [
	64, 32, 24, 19, 
	16, 12, 11, 10, 
	 8,  6,  5,  4,
	 3,  2,  1,  0,
];
var M = function(_X_) {return _X_ * 2};
var FreqCreateTable = [
	M(0.5), M(1), M(2), M(3), M(4), M(5), M(6), M(7),
	M(8), M(9), M(10), M(10), M(12), M(12), M(15), M(15),
];

var AttackSamplesTable = [
	69, 55, 46, 40,
	35, 29, 23, 20,
	19, 15, 11, 10,
	9
];
var EnvelopeIncreaseTable = [
	4,  5,  6,  7,
	8, 10, 12, 14,
	16, 20, 24, 28,
	32, 
];

var WaveTable = ZeroArray(8 * 512);

var WaveBaseTable = [
	0x000, 0x200, 0x200, 0x800,
	0xa00, 0xc00, 0x100, 0x400,
];

var WaveMaskTable = [
	1023, 1023, 511, 511,
	1023, 1023, 512, 1023,
];

var WaveStartTable = [
	512, 0, 0, 0,
	0, 512, 512, 256,
];

var MulTable = ZeroArray(384);
var KslTable = ZeroArray(8 * 16);
var TremoloTable = ZeroArray(TREMOLO_TABLE);
var ChanOffsetTable = ZeroArray(32);
var OpOffsetTable = ZeroArray(64);
var VibratoTable = [
	1 - 0x00, 0 - 0x00, 1 - 0x00, 30 - 0x00, 
	1 - 0x80, 0 - 0x80, 1 - 0x80, 30 - 0x80 
];

// Note: the original used reference parameters to return index and shift..
function EnvelopeSelect(val) {
	var shift, index;
	if ( val < 13 * 4 ) {				//Rate 0 - 12
		shift = 12 - ( val >> 2 );
		index = val & 3;
	} else if ( val < 15 * 4 ) {		//rate 13 - 14
		shift = 0;
		index = val - 12 * 4;
	} else {							//rate 15 and up
		shift = 0;
		index = 12;
	}
	return [index, shift];
}

}; // end of DBOPL namespace
