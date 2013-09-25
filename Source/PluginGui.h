/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_450C07F5C14097B8__
#define __JUCE_HEADER_450C07F5C14097B8__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginGui  : public AudioProcessorEditor,
                   public ComboBoxListener,
                   public SliderListener,
                   public ButtonListener
{
public:
    //==============================================================================
    PluginGui (JuceOplvstiAudioProcessor* ownerFilter);
    ~PluginGui();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* full_sine_png;
    static const int full_sine_pngSize;
    static const char* half_sine_png;
    static const int half_sine_pngSize;
    static const char* abs_sine_png;
    static const int abs_sine_pngSize;
    static const char* quarter_sine_png;
    static const int quarter_sine_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	static const uint32 COLOUR_MID = 0xff007f00;
	JuceOplvstiAudioProcessor* processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ComboBox> frequencyComboBox;
    ScopedPointer<Label> frequencyLabel;
    ScopedPointer<Slider> aSlider;
    ScopedPointer<Label> aLabel;
    ScopedPointer<Slider> dSlider;
    ScopedPointer<Label> dLabel;
    ScopedPointer<Slider> sSlider;
    ScopedPointer<Label> dLabel2;
    ScopedPointer<Slider> rSlider;
    ScopedPointer<Label> rLabel;
    ScopedPointer<Slider> attenuationSlider;
    ScopedPointer<Label> attenuationLabel;
    ScopedPointer<Label> dbLabel;
    ScopedPointer<ImageButton> sineImageButton;
    ScopedPointer<ImageButton> halfsineImageButton;
    ScopedPointer<ImageButton> abssineImageButton;
    ScopedPointer<ImageButton> quartersineImageButton;
    ScopedPointer<Label> waveLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_450C07F5C14097B8__
