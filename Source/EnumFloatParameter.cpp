#include "EnumFloatParameter.h"


EnumFloatParameter::EnumFloatParameter(String name, StringArray values)
:FloatParameter(name)
{
	this->values = values;
}


EnumFloatParameter::~EnumFloatParameter(void)
{
}

int EnumFloatParameter::getParameterIndex(void)
{
	int i = (int)(this->value * values.size());
	if (i >= values.size())
		i = values.size() - 1;
	return i;
}

String EnumFloatParameter::getParameterText(void)
{
	return values[this->getParameterIndex()];
}
