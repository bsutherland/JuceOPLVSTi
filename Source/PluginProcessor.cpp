#include "PluginProcessor.h"
#include "PluginGui.h"
#include "EnumFloatParameter.h"
#include "IntFloatParameter.h"
#include "SbiLoader.h"

//==============================================================================
JuceOplvstiAudioProcessor::JuceOplvstiAudioProcessor()
{
	// Initalize OPL
	velocity = false;
	Opl = new Hiopl(44100);	// 1 second at 44100
	Opl->SetSampleRate(44100);
	Opl->EnableWaveformControl();

	// Initialize parameters

	const String waveforms[] = {"Sine", "Half Sine", "Abs Sine", "Quarter Sine", "Alternating Sine", "Camel Sine", "Square", "Logarithmic Sawtooth"};
	params.push_back(new EnumFloatParameter("Carrier Wave",
		StringArray(waveforms, sizeof(waveforms)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Wave",
		StringArray(waveforms, sizeof(waveforms)/sizeof(String)))
	);

	const String frq_multipliers[] = {
		"x0.5", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x10", "x12", "x12", "x15", "x15"
	};
	params.push_back(new EnumFloatParameter("Carrier Frequency Multiplier",
		StringArray(frq_multipliers, sizeof(frq_multipliers)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Frequency Multiplier",
		StringArray(frq_multipliers, sizeof(frq_multipliers)/sizeof(String)))
	);

	const String levels[] = {"0.00 dB", "0.75 dB", "1.50 dB", "2.25 dB", "3.00 dB", "3.75 dB", "4.50 dB", "5.25 dB", "6.00 dB", "6.75 dB", "7.50 dB", "8.25 dB", "9.00 dB", "9.75 dB", "10.50 dB", "11.25 dB", "12.00 dB", "12.75 dB", "13.50 dB", "14.25 dB", "15.00 dB", "15.75 dB", "16.50 dB", "17.25 dB", "18.00 dB", "18.75 dB", "19.50 dB", "20.25 dB", "21.00 dB", "21.75 dB", "22.50 dB", "23.25 dB", "24.00 dB", "24.75 dB", "25.50 dB", "26.25 dB", "27.00 dB", "27.75 dB", "28.50 dB", "29.25 dB", "30.00 dB", "30.75 dB", "31.50 dB", "32.25 dB", "33.00 dB", "33.75 dB", "34.50 dB", "35.25 dB", "36.00 dB", "36.75 dB", "37.50 dB", "38.25 dB", "39.00 dB", "39.75 dB", "40.50 dB", "41.25 dB", "42.00 dB", "42.75 dB", "43.50 dB", "44.25 dB", "45.00 dB", "45.75 dB", "46.50 dB", "47.25 dB"};
	params.push_back(new EnumFloatParameter("Carrier Attenuation",
		StringArray(levels, sizeof(levels)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Attenuation",
		StringArray(levels, sizeof(levels)/sizeof(String)))
	);

	const String depth[] = {"Light", "Heavy"};
	params.push_back(new EnumFloatParameter("Tremolo Depth",
		StringArray(depth, sizeof(depth)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Vibrato Depth",
		StringArray(depth, sizeof(depth)/sizeof(String)))
	);

	const String onoff[] = {"Disable", "Enable"};
	params.push_back(new EnumFloatParameter("Carrier Tremolo",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Carrier Vibrato",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Carrier Sustain",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Carrier Keyscale Rate",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Tremolo",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Vibrato",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Sustain",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Keyscale Rate",
		StringArray(onoff, sizeof(onoff)/sizeof(String)))
	);

	const String ksrs[] = {"None","1.5 dB/8ve","3 dB/8ve","6 dB/8ve"};
	params.push_back(new EnumFloatParameter("Carrier Keyscale Level",
		StringArray(ksrs, sizeof(ksrs)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Keyscale Level",
		StringArray(ksrs, sizeof(ksrs)/sizeof(String)))
	);

	const String algos[] = {"Frequency Modulation", "Additive"};
	params.push_back(new EnumFloatParameter("Algorithm",
		StringArray(algos, sizeof(algos)/sizeof(String)))
	);

	params.push_back(new IntFloatParameter("Modulator Feedback", 0, 7));
	params.push_back(new IntFloatParameter("Carrier Attack", 0, 15));
	params.push_back(new IntFloatParameter("Carrier Decay", 0, 15));
	params.push_back(new IntFloatParameter("Carrier Sustain Level", 0, 15));
	params.push_back(new IntFloatParameter("Carrier Release", 0, 15));
	params.push_back(new IntFloatParameter("Modulator Attack", 0, 15));
	params.push_back(new IntFloatParameter("Modulator Decay", 0, 15));
	params.push_back(new IntFloatParameter("Modulator Sustain Level", 0, 15));
	params.push_back(new IntFloatParameter("Modulator Release", 0, 15));

	const String sensitivitySettings[] = {"None", "Low", "High"};
	params.push_back(new EnumFloatParameter("Carrier Velocity Sensitivity",
		StringArray(sensitivitySettings, sizeof(sensitivitySettings)/sizeof(String)))
	);
	params.push_back(new EnumFloatParameter("Modulator Velocity Sensitivity",
		StringArray(sensitivitySettings, sizeof(sensitivitySettings)/sizeof(String)))
	);

	for(unsigned int i = 0; i < params.size(); i++) {
		paramIdxByName[params[i]->getName()] = i;
	}

	initPrograms();

	for(std::map<String,std::vector<float>>::iterator it = programs.begin(); it != programs.end(); ++it) {
		program_order.push_back(it->first);
	}
	
	setCurrentProgram(0);
	for (int i = 0; i < Hiopl::CHANNELS+1; i++) {
		active_notes[i] = NO_NOTE;
	}
}

void JuceOplvstiAudioProcessor::initPrograms()
{
	// these ones from the Syndicate in-game music
    const float i_params_0[] = {
        0.000000f, 0.330000f,  // waveforms
        0.066667f, 0.133333f,  // frq multipliers
        0.142857f, 0.412698f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        0.5f, 0.3f, 0.3f, 0.3f,  // adsr
        0.5f, 0.3f, 0.1f, 0.6f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_0 (i_params_0, i_params_0 + sizeof(i_params_0) / sizeof(float));
    programs["Mercenary Bass"] = std::vector<float>(v_i_params_0);

    const float i_params_19189[] = {
        0.000000f, 0.000000f,  // waveforms
        0.066667f, 0.200000f,  // frq multipliers
        0.000000f, 0.285714f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 0.0f, 1.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.571429f,            // feedback
        1.0f, 1.0f, 0.0f, 0.3f,  // adsr
        1.0f, 0.5f, 0.2f, 0.3f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_19189 (i_params_19189, i_params_19189 + sizeof(i_params_19189) / sizeof(float));
    programs["Patrol Bass"] = std::vector<float>(v_i_params_19189);

    const float i_params_38377[] = {
        0.000000f, 0.160000f,  // waveforms
        0.066667f, 0.066667f,  // frq multipliers
        0.000000f, 0.460317f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        1.0f, 0.3f, 0.5f, 0.5f,  // adsr
        1.0f, 0.1f, 0.9f, 1.0f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_38377 (i_params_38377, i_params_38377 + sizeof(i_params_38377) / sizeof(float));
    programs["Subdue Bass"] = std::vector<float>(v_i_params_38377);

    const float i_params_38392[] = {
        0.000000f, 0.000000f,  // waveforms
        0.000000f, 0.000000f,  // frq multipliers
        0.000000f, 0.000000f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        0.1f, 0.1f, 0.7f, 0.1f,  // adsr
        0.1f, 0.9f, 0.1f, 0.1f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_38392 (i_params_38392, i_params_38392 + sizeof(i_params_38392) / sizeof(float));
    programs["Dark Future Sweep"] = std::vector<float>(v_i_params_38392);

    const float i_params_39687[] = {
        0.000000f, 0.000000f,  // waveforms
        0.066667f, 0.333333f,  // frq multipliers
        0.000000f, 0.301587f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 1.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.571429f,            // feedback
        1.0f, 0.3f, 0.1f, 0.3f,  // adsr
        1.0f, 0.7f, 0.0f, 0.4f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_39687 (i_params_39687, i_params_39687 + sizeof(i_params_39687) / sizeof(float));
    programs["Sinister Bass"] = std::vector<float>(v_i_params_39687);

    const float i_params_76784[] = {
        0.000000f, 0.330000f,  // waveforms
        0.066667f, 0.133333f,  // frq multipliers
        0.000000f, 0.428571f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        1.0f, 0.3f, 0.4f, 0.4f,  // adsr
        1.0f, 0.4f, 0.5f, 0.3f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_76784 (i_params_76784, i_params_76784 + sizeof(i_params_76784) / sizeof(float));
    programs["Buzcut Bass"] = std::vector<float>(v_i_params_76784);

    const float i_params_97283[] = {
        0.000000f, 0.330000f,  // waveforms
        0.133333f, 0.400000f,  // frq multipliers
        0.000000f, 0.365079f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 0.0f, 1.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.660000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        0.6f, 0.7f, 0.0f, 0.2f,  // adsr
        0.6f, 0.7f, 0.1f, 0.1f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_97283 (i_params_97283, i_params_97283 + sizeof(i_params_97283) / sizeof(float));
    programs["Death Toll Bell"] = std::vector<float>(v_i_params_97283);

	// The start of the Dune 2 introduction
    const float i_params_3136[] = {
        0.000000f, 0.330000f,  // waveforms
        0.133333f, 0.133333f,  // frq multipliers
        0.000000f, 0.333333f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.330000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.571429f,            // feedback
        1.0f, 0.1f, 0.1f, 0.3f,  // adsr
        1.0f, 0.4f, 0.2f, 0.3f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_3136 (i_params_3136, i_params_3136 + sizeof(i_params_3136) / sizeof(float));
    programs["Westwood Chime"] = std::vector<float>(v_i_params_3136);

    const float i_params_7254[] = {
        0.000000f, 0.160000f,  // waveforms
        0.066667f, 0.066667f,  // frq multipliers
        0.253968f, 0.476190f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        1.0f, 1.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        1.0f, 1.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.330000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.571429f,            // feedback
        0.1f, 0.1f, 0.1f, 0.1f,  // adsr
        0.2f, 0.1f, 0.1f, 0.0f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_7254 (i_params_7254, i_params_7254 + sizeof(i_params_7254) / sizeof(float));
    programs["Desert Pipe"] = std::vector<float>(v_i_params_7254);

    const float i_params_20108[] = {
        0.000000f, 0.000000f,  // waveforms
        0.400000f, 0.066667f,  // frq multipliers
        0.238095f, 0.000000f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        1.0f, 1.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 1.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.000000f, 0.330000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        0.1f, 0.1f, 0.1f, 0.1f,  // adsr
        0.1f, 0.1f, 0.1f, 0.1f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_20108 (i_params_20108, i_params_20108 + sizeof(i_params_20108) / sizeof(float));
    programs["Y2180 Strings"] = std::vector<float>(v_i_params_20108);

    const float i_params_27550[] = {
        0.500000f, 0.000000f,  // waveforms
        0.000000f, 0.066667f,  // frq multipliers
        0.238095f, 0.793651f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 1.0f, 0.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 0.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.571429f,            // feedback
        1.0f, 0.0f, 1.0f, 1.0f,  // adsr
        0.9f, 0.1f, 0.0f, 1.0f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_27550 (i_params_27550, i_params_27550 + sizeof(i_params_27550) / sizeof(float));
    programs["Emperor Chord"] = std::vector<float>(v_i_params_27550);

    const float i_params_harpsi[] = {
        0.330000f, 0.160000f,  // waveforms
        0.066667f, 0.200000f,  // frq multipliers
        0.142857f, 0.260000f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        0.0f, 1.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.000000f,            // feedback
        0.85f, 0.3f, 0.3f, 0.3f,  // adsr
        0.85f, 0.3f, 0.1f, 0.6f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_harpsi (i_params_harpsi, i_params_harpsi + sizeof(i_params_harpsi) / sizeof(float));
    programs["Harpsi"] = std::vector<float>(v_i_params_harpsi);

    const float i_params_tromba[] = {
        0.000000f, 0.160000f,  // waveforms
        0.066667f, 0.000000f,  // frq multipliers
        0.142857f, 0.220000f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        0.0f, 0.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        1.0f, 0.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.500000f,            // feedback
        0.45f, 0.3f, 0.3f, 0.3f,  // adsr
        0.45f, 0.45f, 0.1f, 0.6f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_tromba (i_params_tromba, i_params_tromba + sizeof(i_params_tromba) / sizeof(float));
    programs["Tromba"] = std::vector<float>(v_i_params_tromba);

    const float i_params_bassdrum[] = {
        0.000000f, 0.500000f,  // waveforms
        0.000000f, 0.000000f,  // frq multipliers
        0.000000f, 0.090000f,  // attenuation
		0.000000f, 0.000000f,  // tremolo / vibrato depth
        1.0f, 1.0f, 1.0f, 0.0f,  // tre / vib / sus / ks
        1.0f, 1.0f, 1.0f, 1.0f,  // tre / vib / sus / ks
        0.000000f, 0.000000f,  // KSR/8ve
        0.000000f,            // algorithm
        0.500000f,            // feedback
        1.00f, 0.5f, 0.3f, 0.4f,  // adsr
        1.00f, 0.75f, 0.5f, 0.5f,  // adsr
		0.0f, 0.0f,				 // velocity sensitivity
    };
    std::vector<float> v_i_params_bassdrum (i_params_bassdrum, i_params_bassdrum + sizeof(i_params_bassdrum) / sizeof(float));
    programs["bassdrum"] = std::vector<float>(v_i_params_bassdrum);

}

JuceOplvstiAudioProcessor::~JuceOplvstiAudioProcessor()
{
}

//==============================================================================
const String JuceOplvstiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JuceOplvstiAudioProcessor::getNumParameters()
{
	return params.size();
}

float JuceOplvstiAudioProcessor::getParameter (int index)
{
    return params[index]->getParameter();
}

void JuceOplvstiAudioProcessor::setIntParameter (String name, int value)
{
	int i = paramIdxByName[name];
	IntFloatParameter* p = (IntFloatParameter*)params[i];
	p->setParameterValue(value);
	setParameter(i, p->getParameter());
}

void JuceOplvstiAudioProcessor::setEnumParameter (String name, int index)
{
	int i = paramIdxByName[name];
	EnumFloatParameter* p = (EnumFloatParameter*)params[i];
	p->setParameterIndex(index);
	setParameter(i, p->getParameter());
}

int JuceOplvstiAudioProcessor::getIntParameter (String name)
{
	int i = paramIdxByName[name];
	IntFloatParameter* p = (IntFloatParameter*)params[i];
	return p->getParameterValue();
}

int JuceOplvstiAudioProcessor::getEnumParameter (String name)
{
	int i = paramIdxByName[name];
	EnumFloatParameter* p = (EnumFloatParameter*)params[i];
	return p->getParameterIndex();
}

void JuceOplvstiAudioProcessor::setParameter (int index, float newValue)
{
	FloatParameter* p = params[index];
	p->setParameter(newValue);
	String name = p->getName();
	int osc = 2;	// Carrier
	if (name.startsWith("Modulator")) {
		osc = 1;
	}
	if (name.endsWith("Wave")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetWaveform(c, osc, (Waveform)((EnumFloatParameter*)p)->getParameterIndex());
	} else if (name.endsWith("Attenuation")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetAttenuation(c, osc, ((EnumFloatParameter*)p)->getParameterIndex());
	} else if (name.endsWith("Frequency Multiplier")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetFrequencyMultiple(c, osc, (FreqMultiple)((EnumFloatParameter*)p)->getParameterIndex());
	} else if (name.endsWith("Attack")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetEnvelopeAttack(c, osc, ((IntFloatParameter*)p)->getParameterValue());
	} else if (name.endsWith("Decay")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetEnvelopeDecay(c, osc, ((IntFloatParameter*)p)->getParameterValue());
	} else if (name.endsWith("Sustain Level")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetEnvelopeSustain(c, osc, ((IntFloatParameter*)p)->getParameterValue());
	} else if (name.endsWith("Release")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetEnvelopeRelease(c, osc, ((IntFloatParameter*)p)->getParameterValue());
	} else if (name.endsWith("Feedback")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetModulatorFeedback(c, ((IntFloatParameter*)p)->getParameterValue());
	} else if (name.endsWith("Keyscale Level")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->SetKsl(c, osc, ((EnumFloatParameter*)p)->getParameterIndex());
	} else if (name.endsWith("Keyscale Rate")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->EnableKsr(c, osc, ((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.endsWith("Sustain")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->EnableSustain(c, osc, ((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.endsWith("Tremolo")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->EnableTremolo(c, osc, ((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.endsWith("Vibrato")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->EnableVibrato(c, osc, ((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.endsWith("Algorithm")) {
		for(int c=1;c<=Hiopl::CHANNELS;c++) Opl->EnableAdditiveSynthesis(c, ((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.startsWith("Tremolo Depth")) {
		Opl->TremoloDepth(((EnumFloatParameter*)p)->getParameterIndex() > 0);
	} else if (name.startsWith("Vibrato Depth")) {
		Opl->VibratoDepth(((EnumFloatParameter*)p)->getParameterIndex() > 0);
	}
}

void JuceOplvstiAudioProcessor::loadInstrumentFromFile(String filename)
{
	FILE* f = fopen(filename.toUTF8(), "rb");
	unsigned char buf[MAX_INSTRUMENT_FILE_SIZE_BYTES];
	int n = fread(buf, 1, MAX_INSTRUMENT_FILE_SIZE_BYTES, f);
	fclose(f);
	SbiLoader* loader = new SbiLoader();
	loader->loadInstrumentData(n, buf, this);
	updateGuiIfPresent();
}

void JuceOplvstiAudioProcessor::setParametersByRegister(int register_base, int op, uint8 value)
{
	const String operators[] = {"Modulator", "Carrier"};
	register_base &= 0xF0;
	switch (register_base) {
	case 0x20:
		setEnumParameter(operators[op] + " Tremolo", (value & 0x80) ? 1 : 0);
		setEnumParameter(operators[op] + " Vibrato", (value & 0x40) ? 1 : 0);
		setEnumParameter(operators[op] + " Sustain", (value & 0x20) ? 1 : 0);
		setEnumParameter(operators[op] + " Keyscale Rate", (value & 0x10) ? 1 : 0);
		setEnumParameter(operators[op] + " Frequency Multiplier", value & 0x0f);
		break;
	case 0x40:
		setEnumParameter(operators[op] + " Keyscale Level", (value & 0xc0) >> 6);
		setEnumParameter(operators[op] + " Attenuation", value & 0x3f);
		break;
	case 0x60:
		setIntParameter(operators[op] + " Attack", (value & 0xf0) >> 4);
		setIntParameter(operators[op] + " Decay", value & 0x0f);
		break;
	case 0x80:
		setIntParameter(operators[op] + " Sustain Level", (value & 0xf0) >> 4);
		setIntParameter(operators[op] + " Release", value & 0x0f);
		break;
	case 0xC0:
		setIntParameter("Modulator Feedback", (value & 0xe) >> 1);
		setEnumParameter("Algorithm", value & 0x1);
		break;
	case 0xE0:
		printf("Setting wave to %d", value & 0x7);
		setEnumParameter(operators[op] + " Wave", value & 0x7);
		break;
	default:
		break;
	}
}

const String JuceOplvstiAudioProcessor::getParameterName (int index)
{
	return params[index]->getName();
}

const String JuceOplvstiAudioProcessor::getParameterText (int index)
{
    return params[index]->getParameterText();
}

const String JuceOplvstiAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JuceOplvstiAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JuceOplvstiAudioProcessor::isInputChannelStereoPair (int index) const
{
    return false;
}

bool JuceOplvstiAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return false;
}

bool JuceOplvstiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceOplvstiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceOplvstiAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JuceOplvstiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceOplvstiAudioProcessor::getNumPrograms()
{
    return programs.size();
}

int JuceOplvstiAudioProcessor::getCurrentProgram()
{
    return i_program;
}

void JuceOplvstiAudioProcessor::updateGuiIfPresent()
{
	PluginGui* gui = (PluginGui*)getActiveEditor();
	if (gui) {
		gui->updateFromParameters();
	}
}

void JuceOplvstiAudioProcessor::setCurrentProgram (int index)
{
	i_program = index;
	std::vector<float> &v_params = programs[getProgramName(index)];
	for (unsigned int i = 0; i < params.size() && i < v_params.size(); i++) {
		setParameter(i, v_params[i]);
	}
	updateGuiIfPresent();
}

const String JuceOplvstiAudioProcessor::getProgramName (int index)
{
    return program_order[index];
}

void JuceOplvstiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceOplvstiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	//Opl->SetSampleRate((int)sampleRate);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceOplvstiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JuceOplvstiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.clear(0, 0, buffer.getNumSamples());
	MidiBuffer::Iterator midi_buffer_iterator(midiMessages);

	MidiMessage midi_message(0);
	int sample_number;
	while (midi_buffer_iterator.getNextEvent(midi_message,sample_number)) {
		if (midi_message.isNoteOn()) {
			//note on at sample_number samples after 
			//the beginning of the current buffer
			int n = midi_message.getNoteNumber();
			float noteHz = (float)MidiMessage::getMidiNoteInHertz(n);
			int ch = 1;
			while (ch <= Hiopl::CHANNELS && NO_NOTE != active_notes[ch]) {
				ch += 1;
			}
			switch (getEnumParameter("Carrier Velocity Sensitivity")) {
				case 0:
					Opl->SetAttenuation(ch, 2, getEnumParameter("Carrier Attenuation"));
					break;
				case 1:
					Opl->SetAttenuation(ch, 2, 16 - (midi_message.getVelocity() / 8));
					break;
				case 2:
					Opl->SetAttenuation(ch, 2, 32 - (midi_message.getVelocity() / 4));
					break;
			}
			switch (getEnumParameter("Modulator Velocity Sensitivity")) {
				case 0:
					Opl->SetAttenuation(ch, 1, getEnumParameter("Modulator Attenuation"));
					break;
				case 1:
					Opl->SetAttenuation(ch, 1, 32 - (midi_message.getVelocity() / 4));
					break;
				case 2:
					Opl->SetAttenuation(ch, 1, 63 - (midi_message.getVelocity() / 2));
					break;
			}
			Opl->KeyOn(ch, noteHz);
			active_notes[ch] = n;
		}
		else if (midi_message.isNoteOff()) {
			int n = midi_message.getNoteNumber();
			int ch = 1;
			while (ch <= Hiopl::CHANNELS && n != active_notes[ch]) {
				ch += 1;
			}
			Opl->KeyOff(ch);
			active_notes[ch] = NO_NOTE;
		}
	}
	Opl->Generate(buffer.getNumSamples(), buffer.getSampleData(0));
}

//==============================================================================
bool JuceOplvstiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceOplvstiAudioProcessor::createEditor()
{
	PluginGui* gui = new PluginGui(this);
	gui->updateFromParameters();
	return gui;
}

//==============================================================================
void JuceOplvstiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	destData.ensureSize(sizeof(float) * getNumParameters());
	for (int i = 0; i < getNumParameters(); i++) {
		float p = getParameter(i);
		destData.copyFrom((void*)&p, i*sizeof(float), sizeof(float));
	}
}

void JuceOplvstiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	float* fdata = (float*)data;
	for (unsigned int i = 0; i < sizeInBytes / sizeof(float); i++) {
		setParameter(i, fdata[i]);
	}	
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceOplvstiAudioProcessor();
}
