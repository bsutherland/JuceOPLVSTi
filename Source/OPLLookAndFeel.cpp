/*
  ==============================================================================

    OPLLookAndFeel.cpp
    Created: 10 Oct 2016 9:38:20pm
    Author:  bruce

  ==============================================================================
*/

#include "OPLLookAndFeel.h"
#include "PluginGui.h"

OPLLookAndFeel::OPLLookAndFeel()
{
	toggleOff = ImageCache::getFromMemory(PluginGui::toggle_off_sq_png, PluginGui::toggle_off_sq_pngSize), 1.000f, Colour(0x00000000);
	toggleOn = ImageCache::getFromMemory(PluginGui::toggle_on_sq_png, PluginGui::toggle_on_sq_pngSize), 1.000f, Colour(0x00000000);
	toggleRect = Rectangle<float>((float)toggleOff.getWidth(), (float)toggleOn.getHeight());

	setColour(Label::ColourIds::outlineWhenEditingColourId, Colours::black);
}

void OPLLookAndFeel::drawTickBox(Graphics &g,
	Component &c,
	float 	x,
	float 	y,
	float 	w,
	float 	h,
	bool 	ticked,
	bool 	isEnabled,
	bool 	isMouseOverButton,
	bool 	isButtonDown
) {
	g.drawImage(ticked ? toggleOn : toggleOff, toggleRect.withY(y + 2));
}

