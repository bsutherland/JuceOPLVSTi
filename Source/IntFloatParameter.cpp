#include "IntFloatParameter.h"


IntFloatParameter::IntFloatParameter(String name, int min, int max)
:FloatParameter(name)
{
	this->min = min;
	this->max = max;
}

IntFloatParameter::~IntFloatParameter(void)
{
}

int IntFloatParameter::getParameterValue(void)
{
	int range = max - min;
	int i = (int)(this->value * range);
	if (i > range)
		i = range;
	return i;
}

String IntFloatParameter::getParameterText(void)
{
	return String(this->getParameterValue());
}
