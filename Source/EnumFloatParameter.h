#pragma once
#include "c:\code\game\fm\juceoplvsti\source\floatparameter.h"
class EnumFloatParameter :
	public FloatParameter
{
public:
	EnumFloatParameter(String name, StringArray values);
	~EnumFloatParameter(void);
	String getParameterText(void);
	int getParameterIndex(void);
private:
	StringArray values;
};

