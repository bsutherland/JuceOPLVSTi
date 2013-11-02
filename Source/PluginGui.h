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
	This is a GUI for the OPL2 VST plugin, created in Juce.
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
	void updateFromParameters();
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
    ScopedPointer<ToggleButton> tremoloButton;
    ScopedPointer<ToggleButton> vibratoButton;
    ScopedPointer<ToggleButton> sustainButton;
    ScopedPointer<ToggleButton> keyscaleEnvButton;
    ScopedPointer<Slider> keyscaleSlider;
    ScopedPointer<Label> frequencyLabel2;
    ScopedPointer<Label> dbLabel2;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<ComboBox> frequencyComboBox2;
    ScopedPointer<Label> frequencyLabel3;
    ScopedPointer<Slider> aSlider2;
    ScopedPointer<Label> aLabel2;
    ScopedPointer<Slider> dSlider2;
    ScopedPointer<Label> dLabel3;
    ScopedPointer<Slider> sSlider2;
    ScopedPointer<Label> dLabel4;
    ScopedPointer<Slider> rSlider2;
    ScopedPointer<Label> rLabel2;
    ScopedPointer<Slider> attenuationSlider2;
    ScopedPointer<Label> attenuationLabel2;
    ScopedPointer<Label> dbLabel3;
    ScopedPointer<ImageButton> sineImageButton2;
    ScopedPointer<ImageButton> halfsineImageButton2;
    ScopedPointer<ImageButton> abssineImageButton2;
    ScopedPointer<ImageButton> quartersineImageButton2;
    ScopedPointer<Label> waveLabel2;
    ScopedPointer<ToggleButton> tremoloButton2;
    ScopedPointer<ToggleButton> vibratoButton2;
    ScopedPointer<ToggleButton> sustainButton2;
    ScopedPointer<ToggleButton> keyscaleEnvButton2;
    ScopedPointer<Slider> keyscaleSlider2;
    ScopedPointer<Label> frequencyLabel4;
    ScopedPointer<Label> dbLabel4;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<Slider> tremoloSlider;
    ScopedPointer<Label> frequencyLabel5;
    ScopedPointer<Label> dbLabel5;
    ScopedPointer<Slider> vibratoSlider;
    ScopedPointer<Label> frequencyLabel6;
    ScopedPointer<Label> dbLabel6;
    ScopedPointer<Slider> feedbackSlider;
    ScopedPointer<Label> frequencyLabel7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_450C07F5C14097B8__
