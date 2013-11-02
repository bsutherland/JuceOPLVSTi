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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void PluginGui::updateFromParameters()
{
	sineImageButton->setToggleState(false, false);
	halfsineImageButton->setToggleState(false, false);
	abssineImageButton->setToggleState(false, false);
	quartersineImageButton->setToggleState(false, false);
	switch(processor->getEnumParameter("Modulator Wave")) {
		case 0: sineImageButton->setToggleState(true, false); break;
		case 1: halfsineImageButton->setToggleState(true, false); break;
		case 2: abssineImageButton->setToggleState(true, false); break;
		case 3: quartersineImageButton->setToggleState(true, false); break;
	}
	sineImageButton2->setToggleState(false, false);
	halfsineImageButton2->setToggleState(false, false);
	abssineImageButton2->setToggleState(false, false);
	quartersineImageButton2->setToggleState(false, false);
	switch(processor->getEnumParameter("Carrier Wave")) {
		case 0: sineImageButton2->setToggleState(true, false); break;
		case 1: halfsineImageButton2->setToggleState(true, false); break;
		case 2: abssineImageButton2->setToggleState(true, false); break;
		case 3: quartersineImageButton2->setToggleState(true, false); break;
	}

	frequencyComboBox->setSelectedItemIndex(processor->getEnumParameter("Modulator Frequency Multiplier"), true);
	frequencyComboBox2->setSelectedItemIndex(processor->getEnumParameter("Carrier Frequency Multiplier"), true);

	attenuationSlider->setValue(processor->getEnumParameter("Modulator Attenuation") * -0.75, NotificationType::dontSendNotification);
	attenuationSlider2->setValue(processor->getEnumParameter("Carrier Attenuation") * -0.75, NotificationType::dontSendNotification);

	aSlider->setValue(processor->getIntParameter("Modulator Attack"), NotificationType::dontSendNotification);
	dSlider->setValue(processor->getIntParameter("Modulator Decay"), NotificationType::dontSendNotification);
	sSlider->setValue(processor->getIntParameter("Modulator Sustain Level"), NotificationType::dontSendNotification);
	rSlider->setValue(processor->getIntParameter("Modulator Release"), NotificationType::dontSendNotification);
	aSlider2->setValue(processor->getIntParameter("Carrier Attack"), NotificationType::dontSendNotification);
	dSlider2->setValue(processor->getIntParameter("Carrier Decay"), NotificationType::dontSendNotification);
	sSlider2->setValue(processor->getIntParameter("Carrier Sustain Level"), NotificationType::dontSendNotification);
	rSlider2->setValue(processor->getIntParameter("Carrier Release"), NotificationType::dontSendNotification);

	keyscaleSlider->setValue(processor->getIntParameter("Modulator Keyscale Level"), NotificationType::dontSendNotification);
	keyscaleSlider2->setValue(processor->getIntParameter("Carrier Keyscale Level"), NotificationType::dontSendNotification);


	if (processor->getEnumParameter("Modulator Tremolo")) tremoloButton->setToggleState(true, false);
	if (processor->getEnumParameter("Modulator Vibrato")) vibratoButton->setToggleState(true, false);
	if (processor->getEnumParameter("Modulator Sustain")) sustainButton->setToggleState(true, false);
	if (processor->getEnumParameter("Modulator Keyscale Rate")) keyscaleEnvButton->setToggleState(true, false);

	if (processor->getEnumParameter("Carrier Tremolo")) tremoloButton2->setToggleState(true, false);
	if (processor->getEnumParameter("Carrier Vibrato")) vibratoButton2->setToggleState(true, false);
	if (processor->getEnumParameter("Carrier Sustain")) sustainButton2->setToggleState(true, false);
	if (processor->getEnumParameter("Carrier Keyscale Rate")) keyscaleEnvButton2->setToggleState(true, false);

	vibratoSlider->setValue(processor->getEnumParameter("Vibrato Depth") * 7.0 + 7.0, NotificationType::dontSendNotification);
	tremoloSlider->setValue(processor->getEnumParameter("Tremolo Depth") * 3.8 + 1.0, NotificationType::dontSendNotification);
	feedbackSlider->setValue(processor->getIntParameter("Modulator Feedback"), NotificationType::dontSendNotification);

}
//[/MiscUserDefs]

//==============================================================================
PluginGui::PluginGui (JuceOplvstiAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            "Modulator"));
    groupComponent->setTextLabelPosition (Justification::centredLeft);
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0xff007f00));
    groupComponent->setColour (GroupComponent::textColourId, Colour (0xff007f00));

    addAndMakeVisible (frequencyComboBox = new ComboBox ("frequency combo box"));
    frequencyComboBox->setEditableText (false);
    frequencyComboBox->setJustificationType (Justification::centredLeft);
    frequencyComboBox->setTextWhenNothingSelected (String::empty);
    frequencyComboBox->setTextWhenNoChoicesAvailable ("(no choices)");
    frequencyComboBox->addListener (this);

    addAndMakeVisible (frequencyLabel = new Label ("frequency label",
                                                   "Frequency"));
    frequencyLabel->setFont (Font (15.00f, Font::plain));
    frequencyLabel->setJustificationType (Justification::centredLeft);
    frequencyLabel->setEditable (false, false, false);
    frequencyLabel->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (aSlider = new Slider ("a slider"));
    aSlider->setRange (0, 15, 1);
    aSlider->setSliderStyle (Slider::LinearVertical);
    aSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    aSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    aSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    aSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    aSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    aSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    aSlider->addListener (this);

    addAndMakeVisible (aLabel = new Label ("a label",
                                           "A"));
    aLabel->setFont (Font (15.00f, Font::plain));
    aLabel->setJustificationType (Justification::centred);
    aLabel->setEditable (false, false, false);
    aLabel->setColour (Label::textColourId, Colour (0xff007f00));
    aLabel->setColour (TextEditor::textColourId, Colours::black);
    aLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dSlider = new Slider ("d slider"));
    dSlider->setRange (0, 15, 1);
    dSlider->setSliderStyle (Slider::LinearVertical);
    dSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    dSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    dSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    dSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    dSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    dSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    dSlider->addListener (this);

    addAndMakeVisible (dLabel = new Label ("d label",
                                           "D"));
    dLabel->setFont (Font (15.00f, Font::plain));
    dLabel->setJustificationType (Justification::centred);
    dLabel->setEditable (false, false, false);
    dLabel->setColour (Label::textColourId, Colour (0xff007f00));
    dLabel->setColour (TextEditor::textColourId, Colours::black);
    dLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sSlider = new Slider ("s slider"));
    sSlider->setRange (0, 15, 1);
    sSlider->setSliderStyle (Slider::LinearVertical);
    sSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    sSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    sSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    sSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    sSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    sSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    sSlider->addListener (this);

    addAndMakeVisible (dLabel2 = new Label ("d label",
                                            "S"));
    dLabel2->setFont (Font (15.00f, Font::plain));
    dLabel2->setJustificationType (Justification::centred);
    dLabel2->setEditable (false, false, false);
    dLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    dLabel2->setColour (TextEditor::textColourId, Colours::black);
    dLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rSlider = new Slider ("r slider"));
    rSlider->setRange (0, 15, 1);
    rSlider->setSliderStyle (Slider::LinearVertical);
    rSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    rSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    rSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    rSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    rSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    rSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    rSlider->addListener (this);

    addAndMakeVisible (rLabel = new Label ("r label",
                                           "R"));
    rLabel->setFont (Font (15.00f, Font::plain));
    rLabel->setJustificationType (Justification::centred);
    rLabel->setEditable (false, false, false);
    rLabel->setColour (Label::textColourId, Colour (0xff007f00));
    rLabel->setColour (TextEditor::textColourId, Colours::black);
    rLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attenuationSlider = new Slider ("attenuation slider"));
    attenuationSlider->setRange (-47.25, 0, 0.75);
    attenuationSlider->setSliderStyle (Slider::LinearVertical);
    attenuationSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    attenuationSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    attenuationSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    attenuationSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    attenuationSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    attenuationSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    attenuationSlider->addListener (this);

    addAndMakeVisible (attenuationLabel = new Label ("attenuation label",
                                                     "Attenuation"));
    attenuationLabel->setFont (Font (15.00f, Font::plain));
    attenuationLabel->setJustificationType (Justification::centred);
    attenuationLabel->setEditable (false, false, false);
    attenuationLabel->setColour (Label::textColourId, Colour (0xff007f00));
    attenuationLabel->setColour (TextEditor::textColourId, Colours::black);
    attenuationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel = new Label ("db label",
                                            "dB"));
    dbLabel->setFont (Font (15.00f, Font::plain));
    dbLabel->setJustificationType (Justification::centred);
    dbLabel->setEditable (false, false, false);
    dbLabel->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel->setColour (TextEditor::textColourId, Colours::black);
    dbLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sineImageButton = new ImageButton ("sine image button"));
    sineImageButton->setTooltip ("sine");
    sineImageButton->setButtonText ("Sine");
    sineImageButton->setRadioGroupId (1);
    sineImageButton->addListener (this);

    sineImageButton->setImages (false, true, true,
                                ImageCache::getFromMemory (full_sine_png, full_sine_pngSize), 0.500f, Colour (0x00000000),
                                Image(), 0.500f, Colour (0x00000000),
                                Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (halfsineImageButton = new ImageButton ("half sine image button"));
    halfsineImageButton->setTooltip ("half sine");
    halfsineImageButton->setButtonText ("Half Sine");
    halfsineImageButton->setRadioGroupId (1);
    halfsineImageButton->addListener (this);

    halfsineImageButton->setImages (false, true, true,
                                    ImageCache::getFromMemory (half_sine_png, half_sine_pngSize), 0.500f, Colour (0x00000000),
                                    Image(), 0.500f, Colour (0x00000000),
                                    Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (abssineImageButton = new ImageButton ("abs sine image button"));
    abssineImageButton->setTooltip ("abs sine");
    abssineImageButton->setButtonText ("Abs Sine");
    abssineImageButton->setRadioGroupId (1);
    abssineImageButton->addListener (this);

    abssineImageButton->setImages (false, true, true,
                                   ImageCache::getFromMemory (abs_sine_png, abs_sine_pngSize), 0.500f, Colour (0x00000000),
                                   Image(), 0.500f, Colour (0x00000000),
                                   Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (quartersineImageButton = new ImageButton ("quarter sine image button"));
    quartersineImageButton->setTooltip ("quarter sine");
    quartersineImageButton->setButtonText ("Quarter Sine");
    quartersineImageButton->setRadioGroupId (1);
    quartersineImageButton->addListener (this);

    quartersineImageButton->setImages (false, true, true,
                                       ImageCache::getFromMemory (quarter_sine_png, quarter_sine_pngSize), 0.500f, Colour (0x00000000),
                                       Image(), 0.500f, Colour (0x00000000),
                                       Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (waveLabel = new Label ("wave label",
                                              "Wave"));
    waveLabel->setFont (Font (15.00f, Font::plain));
    waveLabel->setJustificationType (Justification::centredLeft);
    waveLabel->setEditable (false, false, false);
    waveLabel->setColour (Label::textColourId, Colour (0xff007f00));
    waveLabel->setColour (TextEditor::textColourId, Colours::black);
    waveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (tremoloButton = new ToggleButton ("tremolo button"));
    tremoloButton->setButtonText ("Tremolo");
    tremoloButton->addListener (this);
    tremoloButton->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (vibratoButton = new ToggleButton ("vibrato button"));
    vibratoButton->setButtonText ("Vibrato");
    vibratoButton->addListener (this);
    vibratoButton->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (sustainButton = new ToggleButton ("sustain button"));
    sustainButton->setButtonText ("Sustain");
    sustainButton->addListener (this);
    sustainButton->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (keyscaleEnvButton = new ToggleButton ("keyscale env button"));
    keyscaleEnvButton->setButtonText ("Keyscale Envelope Rate");
    keyscaleEnvButton->addListener (this);
    keyscaleEnvButton->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (keyscaleSlider = new Slider ("keyscale slider"));
    keyscaleSlider->setRange (-6, 0, 1.5);
    keyscaleSlider->setSliderStyle (Slider::LinearHorizontal);
    keyscaleSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 44, 20);
    keyscaleSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    keyscaleSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    keyscaleSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    keyscaleSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    keyscaleSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    keyscaleSlider->addListener (this);

    addAndMakeVisible (frequencyLabel2 = new Label ("frequency label",
                                                    "Keyscale Attenuation"));
    frequencyLabel2->setFont (Font (15.00f, Font::plain));
    frequencyLabel2->setJustificationType (Justification::centred);
    frequencyLabel2->setEditable (false, false, false);
    frequencyLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel2->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel2 = new Label ("db label",
                                             "dB/\n8ve\n"));
    dbLabel2->setFont (Font (15.00f, Font::plain));
    dbLabel2->setJustificationType (Justification::centred);
    dbLabel2->setEditable (false, false, false);
    dbLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel2->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel2->setColour (TextEditor::textColourId, Colours::black);
    dbLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             "Carrier"));
    groupComponent2->setTextLabelPosition (Justification::centredLeft);
    groupComponent2->setColour (GroupComponent::outlineColourId, Colour (0xff007f00));
    groupComponent2->setColour (GroupComponent::textColourId, Colour (0xff007f00));

    addAndMakeVisible (frequencyComboBox2 = new ComboBox ("frequency combo box"));
    frequencyComboBox2->setEditableText (false);
    frequencyComboBox2->setJustificationType (Justification::centredLeft);
    frequencyComboBox2->setTextWhenNothingSelected (String::empty);
    frequencyComboBox2->setTextWhenNoChoicesAvailable ("(no choices)");
    frequencyComboBox2->addListener (this);

    addAndMakeVisible (frequencyLabel3 = new Label ("frequency label",
                                                    "Frequency"));
    frequencyLabel3->setFont (Font (15.00f, Font::plain));
    frequencyLabel3->setJustificationType (Justification::centredLeft);
    frequencyLabel3->setEditable (false, false, false);
    frequencyLabel3->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel3->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (aSlider2 = new Slider ("a slider"));
    aSlider2->setRange (0, 15, 1);
    aSlider2->setSliderStyle (Slider::LinearVertical);
    aSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    aSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    aSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    aSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    aSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    aSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    aSlider2->addListener (this);

    addAndMakeVisible (aLabel2 = new Label ("a label",
                                            "A"));
    aLabel2->setFont (Font (15.00f, Font::plain));
    aLabel2->setJustificationType (Justification::centred);
    aLabel2->setEditable (false, false, false);
    aLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    aLabel2->setColour (TextEditor::textColourId, Colours::black);
    aLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dSlider2 = new Slider ("d slider"));
    dSlider2->setRange (0, 15, 1);
    dSlider2->setSliderStyle (Slider::LinearVertical);
    dSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    dSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    dSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    dSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    dSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    dSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    dSlider2->addListener (this);

    addAndMakeVisible (dLabel3 = new Label ("d label",
                                            "D"));
    dLabel3->setFont (Font (15.00f, Font::plain));
    dLabel3->setJustificationType (Justification::centred);
    dLabel3->setEditable (false, false, false);
    dLabel3->setColour (Label::textColourId, Colour (0xff007f00));
    dLabel3->setColour (TextEditor::textColourId, Colours::black);
    dLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sSlider2 = new Slider ("s slider"));
    sSlider2->setRange (0, 15, 1);
    sSlider2->setSliderStyle (Slider::LinearVertical);
    sSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    sSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    sSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    sSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    sSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    sSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    sSlider2->addListener (this);

    addAndMakeVisible (dLabel4 = new Label ("d label",
                                            "S"));
    dLabel4->setFont (Font (15.00f, Font::plain));
    dLabel4->setJustificationType (Justification::centred);
    dLabel4->setEditable (false, false, false);
    dLabel4->setColour (Label::textColourId, Colour (0xff007f00));
    dLabel4->setColour (TextEditor::textColourId, Colours::black);
    dLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rSlider2 = new Slider ("r slider"));
    rSlider2->setRange (0, 15, 1);
    rSlider2->setSliderStyle (Slider::LinearVertical);
    rSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    rSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    rSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    rSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    rSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    rSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    rSlider2->addListener (this);

    addAndMakeVisible (rLabel2 = new Label ("r label",
                                            "R"));
    rLabel2->setFont (Font (15.00f, Font::plain));
    rLabel2->setJustificationType (Justification::centred);
    rLabel2->setEditable (false, false, false);
    rLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    rLabel2->setColour (TextEditor::textColourId, Colours::black);
    rLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attenuationSlider2 = new Slider ("attenuation slider"));
    attenuationSlider2->setRange (-47.25, 0, 0.75);
    attenuationSlider2->setSliderStyle (Slider::LinearVertical);
    attenuationSlider2->setTextBoxStyle (Slider::TextBoxBelow, false, 64, 20);
    attenuationSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    attenuationSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    attenuationSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    attenuationSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    attenuationSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    attenuationSlider2->addListener (this);

    addAndMakeVisible (attenuationLabel2 = new Label ("attenuation label",
                                                      "Attenuation"));
    attenuationLabel2->setFont (Font (15.00f, Font::plain));
    attenuationLabel2->setJustificationType (Justification::centred);
    attenuationLabel2->setEditable (false, false, false);
    attenuationLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    attenuationLabel2->setColour (TextEditor::textColourId, Colours::black);
    attenuationLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel3 = new Label ("db label",
                                             "dB"));
    dbLabel3->setFont (Font (15.00f, Font::plain));
    dbLabel3->setJustificationType (Justification::centred);
    dbLabel3->setEditable (false, false, false);
    dbLabel3->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel3->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel3->setColour (TextEditor::textColourId, Colours::black);
    dbLabel3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sineImageButton2 = new ImageButton ("sine image button"));
    sineImageButton2->setTooltip ("sine");
    sineImageButton2->setButtonText ("Sine");
    sineImageButton2->setRadioGroupId (2);
    sineImageButton2->addListener (this);

    sineImageButton2->setImages (false, true, true,
                                 ImageCache::getFromMemory (full_sine_png, full_sine_pngSize), 0.500f, Colour (0x00000000),
                                 Image(), 0.500f, Colour (0x00000000),
                                 Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (halfsineImageButton2 = new ImageButton ("half sine image button"));
    halfsineImageButton2->setTooltip ("half sine");
    halfsineImageButton2->setButtonText ("Half Sine");
    halfsineImageButton2->setRadioGroupId (2);
    halfsineImageButton2->addListener (this);

    halfsineImageButton2->setImages (false, true, true,
                                     ImageCache::getFromMemory (half_sine_png, half_sine_pngSize), 0.500f, Colour (0x00000000),
                                     Image(), 0.500f, Colour (0x00000000),
                                     Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (abssineImageButton2 = new ImageButton ("abs sine image button"));
    abssineImageButton2->setTooltip ("abs sine");
    abssineImageButton2->setButtonText ("Abs Sine");
    abssineImageButton2->setRadioGroupId (2);
    abssineImageButton2->addListener (this);

    abssineImageButton2->setImages (false, true, true,
                                    ImageCache::getFromMemory (abs_sine_png, abs_sine_pngSize), 0.500f, Colour (0x00000000),
                                    Image(), 0.500f, Colour (0x00000000),
                                    Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (quartersineImageButton2 = new ImageButton ("quarter sine image button"));
    quartersineImageButton2->setTooltip ("quarter sine");
    quartersineImageButton2->setButtonText ("Quarter Sine");
    quartersineImageButton2->setRadioGroupId (2);
    quartersineImageButton2->addListener (this);

    quartersineImageButton2->setImages (false, true, true,
                                        ImageCache::getFromMemory (quarter_sine_png, quarter_sine_pngSize), 0.500f, Colour (0x00000000),
                                        Image(), 0.500f, Colour (0x00000000),
                                        Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (waveLabel2 = new Label ("wave label",
                                               "Wave"));
    waveLabel2->setFont (Font (15.00f, Font::plain));
    waveLabel2->setJustificationType (Justification::centredLeft);
    waveLabel2->setEditable (false, false, false);
    waveLabel2->setColour (Label::textColourId, Colour (0xff007f00));
    waveLabel2->setColour (TextEditor::textColourId, Colours::black);
    waveLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (tremoloButton2 = new ToggleButton ("tremolo button"));
    tremoloButton2->setButtonText ("Tremolo");
    tremoloButton2->addListener (this);
    tremoloButton2->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (vibratoButton2 = new ToggleButton ("vibrato button"));
    vibratoButton2->setButtonText ("Vibrato");
    vibratoButton2->addListener (this);
    vibratoButton2->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (sustainButton2 = new ToggleButton ("sustain button"));
    sustainButton2->setButtonText ("Sustain");
    sustainButton2->addListener (this);
    sustainButton2->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (keyscaleEnvButton2 = new ToggleButton ("keyscale env button"));
    keyscaleEnvButton2->setButtonText ("Keyscale Envelope Rate");
    keyscaleEnvButton2->addListener (this);
    keyscaleEnvButton2->setColour (ToggleButton::textColourId, Colour (0xff007f00));

    addAndMakeVisible (keyscaleSlider2 = new Slider ("keyscale slider"));
    keyscaleSlider2->setRange (-6, 0, 1.5);
    keyscaleSlider2->setSliderStyle (Slider::LinearHorizontal);
    keyscaleSlider2->setTextBoxStyle (Slider::TextBoxLeft, false, 44, 20);
    keyscaleSlider2->setColour (Slider::thumbColourId, Colour (0xff00af00));
    keyscaleSlider2->setColour (Slider::trackColourId, Colour (0x7f007f00));
    keyscaleSlider2->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    keyscaleSlider2->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    keyscaleSlider2->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    keyscaleSlider2->addListener (this);

    addAndMakeVisible (frequencyLabel4 = new Label ("frequency label",
                                                    "Keyscale Attenuation"));
    frequencyLabel4->setFont (Font (15.00f, Font::plain));
    frequencyLabel4->setJustificationType (Justification::centred);
    frequencyLabel4->setEditable (false, false, false);
    frequencyLabel4->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel4->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel4 = new Label ("db label",
                                             "dB/\n8ve\n"));
    dbLabel4->setFont (Font (15.00f, Font::plain));
    dbLabel4->setJustificationType (Justification::centred);
    dbLabel4->setEditable (false, false, false);
    dbLabel4->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel4->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel4->setColour (TextEditor::textColourId, Colours::black);
    dbLabel4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             "Common"));
    groupComponent3->setTextLabelPosition (Justification::centredLeft);
    groupComponent3->setColour (GroupComponent::outlineColourId, Colour (0xff007f00));
    groupComponent3->setColour (GroupComponent::textColourId, Colour (0xff007f00));

    addAndMakeVisible (tremoloSlider = new Slider ("tremolo slider"));
    tremoloSlider->setRange (1, 4.8, 3.8);
    tremoloSlider->setSliderStyle (Slider::LinearHorizontal);
    tremoloSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 44, 20);
    tremoloSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    tremoloSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    tremoloSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    tremoloSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    tremoloSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    tremoloSlider->addListener (this);

    addAndMakeVisible (frequencyLabel5 = new Label ("frequency label",
                                                    "Tremolo Depth\n"));
    frequencyLabel5->setFont (Font (15.00f, Font::plain));
    frequencyLabel5->setJustificationType (Justification::centred);
    frequencyLabel5->setEditable (false, false, false);
    frequencyLabel5->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel5->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel5 = new Label ("db label",
                                             "dB"));
    dbLabel5->setFont (Font (15.00f, Font::plain));
    dbLabel5->setJustificationType (Justification::centred);
    dbLabel5->setEditable (false, false, false);
    dbLabel5->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel5->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel5->setColour (TextEditor::textColourId, Colours::black);
    dbLabel5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vibratoSlider = new Slider ("vibrato slider"));
    vibratoSlider->setRange (7, 14, 7);
    vibratoSlider->setSliderStyle (Slider::LinearHorizontal);
    vibratoSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 44, 20);
    vibratoSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    vibratoSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    vibratoSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    vibratoSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    vibratoSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    vibratoSlider->addListener (this);

    addAndMakeVisible (frequencyLabel6 = new Label ("frequency label",
                                                    "Vibrato Depth"));
    frequencyLabel6->setFont (Font (15.00f, Font::plain));
    frequencyLabel6->setJustificationType (Justification::centred);
    frequencyLabel6->setEditable (false, false, false);
    frequencyLabel6->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel6->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (dbLabel6 = new Label ("db label",
                                             "cents\n"));
    dbLabel6->setFont (Font (15.00f, Font::plain));
    dbLabel6->setJustificationType (Justification::centred);
    dbLabel6->setEditable (false, false, false);
    dbLabel6->setColour (Label::textColourId, Colour (0xff007f00));
    dbLabel6->setColour (Label::outlineColourId, Colour (0x00000000));
    dbLabel6->setColour (TextEditor::textColourId, Colours::black);
    dbLabel6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feedbackSlider = new Slider ("feedback slider"));
    feedbackSlider->setRange (0, 7, 1);
    feedbackSlider->setSliderStyle (Slider::LinearHorizontal);
    feedbackSlider->setTextBoxStyle (Slider::TextBoxRight, false, 44, 20);
    feedbackSlider->setColour (Slider::thumbColourId, Colour (0xff00af00));
    feedbackSlider->setColour (Slider::trackColourId, Colour (0x7f007f00));
    feedbackSlider->setColour (Slider::textBoxTextColourId, Colour (0xff007f00));
    feedbackSlider->setColour (Slider::textBoxBackgroundColourId, Colours::black);
    feedbackSlider->setColour (Slider::textBoxHighlightColourId, Colour (0xff00af00));
    feedbackSlider->addListener (this);

    addAndMakeVisible (frequencyLabel7 = new Label ("frequency label",
                                                    "Feedback"));
    frequencyLabel7->setFont (Font (15.00f, Font::plain));
    frequencyLabel7->setJustificationType (Justification::centredLeft);
    frequencyLabel7->setEditable (false, false, false);
    frequencyLabel7->setColour (Label::textColourId, Colour (0xff007f00));
    frequencyLabel7->setColour (TextEditor::textColourId, Colours::black);
    frequencyLabel7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
	frequencyComboBox->setColour (ComboBox::textColourId, Colour (COLOUR_MID));
	frequencyComboBox->setColour (ComboBox::outlineColourId, Colour (COLOUR_MID));
	frequencyComboBox->setColour (ComboBox::arrowColourId, Colour (COLOUR_MID));
	frequencyComboBox->setColour (ComboBox::buttonColourId, Colours::black);
	frequencyComboBox->setColour (ComboBox::backgroundColourId, Colours::black);

	frequencyComboBox->addItem ("x1/2", 16);		// can't use 0 :(
    frequencyComboBox->addItem ("x1", 1);
    frequencyComboBox->addItem ("x2", 2);
    frequencyComboBox->addItem ("x3", 3);
    frequencyComboBox->addItem ("x4", 4);
    frequencyComboBox->addItem ("x5", 5);
    frequencyComboBox->addItem ("x6", 6);
    frequencyComboBox->addItem ("x7", 7);
    frequencyComboBox->addItem ("x8", 8);
    frequencyComboBox->addItem ("x9", 9);
    frequencyComboBox->addItem ("x10", 10);
    frequencyComboBox->addItem ("x12", 12);
    frequencyComboBox->addItem ("x15", 15);

	frequencyComboBox2->setColour (ComboBox::textColourId, Colour (COLOUR_MID));
	frequencyComboBox2->setColour (ComboBox::outlineColourId, Colour (COLOUR_MID));
	frequencyComboBox2->setColour (ComboBox::arrowColourId, Colour (COLOUR_MID));
	frequencyComboBox2->setColour (ComboBox::buttonColourId, Colours::black);
	frequencyComboBox2->setColour (ComboBox::backgroundColourId, Colours::black);
	frequencyComboBox2->addItem ("x1/2", 16);		// can't use 0 :(
    frequencyComboBox2->addItem ("x1", 1);
    frequencyComboBox2->addItem ("x2", 2);
    frequencyComboBox2->addItem ("x3", 3);
    frequencyComboBox2->addItem ("x4", 4);
    frequencyComboBox2->addItem ("x5", 5);
    frequencyComboBox2->addItem ("x6", 6);
    frequencyComboBox2->addItem ("x7", 7);
    frequencyComboBox2->addItem ("x8", 8);
    frequencyComboBox2->addItem ("x9", 9);
    frequencyComboBox2->addItem ("x10", 10);
    frequencyComboBox2->addItem ("x12", 12);
    frequencyComboBox2->addItem ("x15", 15);

	sineImageButton->setClickingTogglesState(true);
	sineImageButton->setRepaintsOnMouseActivity(false);
	abssineImageButton->setClickingTogglesState(true);
	abssineImageButton->setRepaintsOnMouseActivity(false);
	halfsineImageButton->setClickingTogglesState(true);
	halfsineImageButton->setRepaintsOnMouseActivity(false);
	quartersineImageButton->setClickingTogglesState(true);
	quartersineImageButton->setRepaintsOnMouseActivity(false);
	sineImageButton2->setClickingTogglesState(true);
	sineImageButton2->setRepaintsOnMouseActivity(false);
	abssineImageButton2->setClickingTogglesState(true);
	abssineImageButton2->setRepaintsOnMouseActivity(false);
	halfsineImageButton2->setClickingTogglesState(true);
	halfsineImageButton2->setRepaintsOnMouseActivity(false);
	quartersineImageButton2->setClickingTogglesState(true);
	quartersineImageButton2->setRepaintsOnMouseActivity(false);

	tremoloButton->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	vibratoButton->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	keyscaleEnvButton->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	sustainButton->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	tremoloButton2->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	vibratoButton2->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	keyscaleEnvButton2->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
	sustainButton2->setColour(TextButton::buttonColourId, Colour(COLOUR_MID));
    //[/UserPreSize]

    setSize (430, 800);


    //[Constructor] You can add your own custom stuff here..
	processor = ownerFilter;
    //[/Constructor]
}

PluginGui::~PluginGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    frequencyComboBox = nullptr;
    frequencyLabel = nullptr;
    aSlider = nullptr;
    aLabel = nullptr;
    dSlider = nullptr;
    dLabel = nullptr;
    sSlider = nullptr;
    dLabel2 = nullptr;
    rSlider = nullptr;
    rLabel = nullptr;
    attenuationSlider = nullptr;
    attenuationLabel = nullptr;
    dbLabel = nullptr;
    sineImageButton = nullptr;
    halfsineImageButton = nullptr;
    abssineImageButton = nullptr;
    quartersineImageButton = nullptr;
    waveLabel = nullptr;
    tremoloButton = nullptr;
    vibratoButton = nullptr;
    sustainButton = nullptr;
    keyscaleEnvButton = nullptr;
    keyscaleSlider = nullptr;
    frequencyLabel2 = nullptr;
    dbLabel2 = nullptr;
    groupComponent2 = nullptr;
    frequencyComboBox2 = nullptr;
    frequencyLabel3 = nullptr;
    aSlider2 = nullptr;
    aLabel2 = nullptr;
    dSlider2 = nullptr;
    dLabel3 = nullptr;
    sSlider2 = nullptr;
    dLabel4 = nullptr;
    rSlider2 = nullptr;
    rLabel2 = nullptr;
    attenuationSlider2 = nullptr;
    attenuationLabel2 = nullptr;
    dbLabel3 = nullptr;
    sineImageButton2 = nullptr;
    halfsineImageButton2 = nullptr;
    abssineImageButton2 = nullptr;
    quartersineImageButton2 = nullptr;
    waveLabel2 = nullptr;
    tremoloButton2 = nullptr;
    vibratoButton2 = nullptr;
    sustainButton2 = nullptr;
    keyscaleEnvButton2 = nullptr;
    keyscaleSlider2 = nullptr;
    frequencyLabel4 = nullptr;
    dbLabel4 = nullptr;
    groupComponent3 = nullptr;
    tremoloSlider = nullptr;
    frequencyLabel5 = nullptr;
    dbLabel5 = nullptr;
    vibratoSlider = nullptr;
    frequencyLabel6 = nullptr;
    dbLabel6 = nullptr;
    feedbackSlider = nullptr;
    frequencyLabel7 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginGui::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginGui::resized()
{
    groupComponent->setBounds (16, 8, 400, 336);
    frequencyComboBox->setBounds (128, 80, 72, 24);
    frequencyLabel->setBounds (32, 80, 80, 24);
    aSlider->setBounds (40, 208, 48, 72);
    aLabel->setBounds (40, 280, 48, 24);
    dSlider->setBounds (104, 208, 48, 72);
    dLabel->setBounds (104, 280, 48, 24);
    sSlider->setBounds (168, 208, 48, 72);
    dLabel2->setBounds (168, 280, 48, 24);
    rSlider->setBounds (232, 208, 48, 72);
    rLabel->setBounds (232, 280, 48, 24);
    attenuationSlider->setBounds (304, 168, 72, 112);
    attenuationLabel->setBounds (304, 280, 96, 24);
    dbLabel->setBounds (368, 256, 40, 24);
    sineImageButton->setBounds (120, 40, 34, 30);
    halfsineImageButton->setBounds (176, 40, 34, 30);
    abssineImageButton->setBounds (232, 40, 34, 30);
    quartersineImageButton->setBounds (288, 40, 34, 30);
    waveLabel->setBounds (32, 40, 80, 24);
    tremoloButton->setBounds (144, 120, 96, 24);
    vibratoButton->setBounds (40, 120, 96, 24);
    sustainButton->setBounds (40, 304, 96, 24);
    keyscaleEnvButton->setBounds (136, 304, 184, 24);
    keyscaleSlider->setBounds (256, 104, 112, 24);
    frequencyLabel2->setBounds (248, 80, 152, 24);
    dbLabel2->setBounds (368, 96, 40, 40);
    groupComponent2->setBounds (16, 352, 400, 320);
    frequencyComboBox2->setBounds (128, 424, 72, 24);
    frequencyLabel3->setBounds (32, 424, 80, 24);
    aSlider2->setBounds (40, 536, 48, 72);
    aLabel2->setBounds (40, 608, 48, 24);
    dSlider2->setBounds (104, 536, 48, 72);
    dLabel3->setBounds (104, 608, 48, 24);
    sSlider2->setBounds (168, 536, 48, 72);
    dLabel4->setBounds (168, 608, 48, 24);
    rSlider2->setBounds (232, 536, 48, 72);
    rLabel2->setBounds (232, 608, 48, 24);
    attenuationSlider2->setBounds (304, 496, 72, 112);
    attenuationLabel2->setBounds (304, 608, 96, 24);
    dbLabel3->setBounds (368, 584, 40, 24);
    sineImageButton2->setBounds (120, 384, 34, 30);
    halfsineImageButton2->setBounds (176, 384, 34, 30);
    abssineImageButton2->setBounds (232, 384, 34, 30);
    quartersineImageButton2->setBounds (288, 384, 34, 30);
    waveLabel2->setBounds (32, 384, 80, 24);
    tremoloButton2->setBounds (152, 464, 96, 24);
    vibratoButton2->setBounds (40, 464, 96, 24);
    sustainButton2->setBounds (40, 632, 96, 24);
    keyscaleEnvButton2->setBounds (136, 632, 184, 24);
    keyscaleSlider2->setBounds (256, 448, 112, 24);
    frequencyLabel4->setBounds (248, 424, 152, 24);
    dbLabel4->setBounds (368, 440, 40, 40);
    groupComponent3->setBounds (16, 680, 400, 96);
    tremoloSlider->setBounds (48, 712, 112, 24);
    frequencyLabel5->setBounds (40, 736, 152, 24);
    dbLabel5->setBounds (160, 704, 40, 40);
    vibratoSlider->setBounds (233, 713, 112, 24);
    frequencyLabel6->setBounds (225, 737, 152, 24);
    dbLabel6->setBounds (345, 705, 47, 40);
    feedbackSlider->setBounds (120, 168, 136, 24);
    frequencyLabel7->setBounds (32, 168, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginGui::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == frequencyComboBox)
    {
        //[UserComboBoxCode_frequencyComboBox] -- add your combo box handling code here..
		int id = comboBoxThatHasChanged->getSelectedId();
		if (id > 15) id = 0;
		processor->setEnumParameter("Modulator Frequency Multiplier", id);
        //[/UserComboBoxCode_frequencyComboBox]
    }
    else if (comboBoxThatHasChanged == frequencyComboBox2)
    {
        //[UserComboBoxCode_frequencyComboBox2] -- add your combo box handling code here..
		int id = comboBoxThatHasChanged->getSelectedId();
		if (id > 15) id = 0;
		processor->setEnumParameter("Carrier Frequency Multiplier", id);
        //[/UserComboBoxCode_frequencyComboBox2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void PluginGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == aSlider)
    {
        //[UserSliderCode_aSlider] -- add your slider handling code here..
		processor->setIntParameter("Modulator Attack", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_aSlider]
    }
    else if (sliderThatWasMoved == dSlider)
    {
        //[UserSliderCode_dSlider] -- add your slider handling code here..
		processor->setIntParameter("Modulator Decay", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_dSlider]
    }
    else if (sliderThatWasMoved == sSlider)
    {
        //[UserSliderCode_sSlider] -- add your slider handling code here..
		processor->setIntParameter("Modulator Sustain Level", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_sSlider]
    }
    else if (sliderThatWasMoved == rSlider)
    {
        //[UserSliderCode_rSlider] -- add your slider handling code here..
		processor->setIntParameter("Modulator Release", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_rSlider]
    }
    else if (sliderThatWasMoved == attenuationSlider)
    {
        //[UserSliderCode_attenuationSlider] -- add your slider handling code here..
		processor->setEnumParameter("Modulator Attenuation", -(int)(sliderThatWasMoved->getValue()/0.75));
        //[/UserSliderCode_attenuationSlider]
    }
    else if (sliderThatWasMoved == keyscaleSlider)
    {
        //[UserSliderCode_keyscaleSlider] -- add your slider handling code here..
		processor->setEnumParameter("Modulator Keyscale Level", -(int)(sliderThatWasMoved->getValue()/1.5));
        //[/UserSliderCode_keyscaleSlider]
    }
    else if (sliderThatWasMoved == aSlider2)
    {
        //[UserSliderCode_aSlider2] -- add your slider handling code here..
		processor->setIntParameter("Carrier Attack", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_aSlider2]
    }
    else if (sliderThatWasMoved == dSlider2)
    {
        //[UserSliderCode_dSlider2] -- add your slider handling code here..
		processor->setIntParameter("Carrier Decay", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_dSlider2]
    }
    else if (sliderThatWasMoved == sSlider2)
    {
        //[UserSliderCode_sSlider2] -- add your slider handling code here..
		processor->setIntParameter("Carrier Sustain Level", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_sSlider2]
    }
    else if (sliderThatWasMoved == rSlider2)
    {
        //[UserSliderCode_rSlider2] -- add your slider handling code here..
		processor->setIntParameter("Carrier Release", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_rSlider2]
    }
    else if (sliderThatWasMoved == attenuationSlider2)
    {
        //[UserSliderCode_attenuationSlider2] -- add your slider handling code here..
		processor->setEnumParameter("Carrier Attenuation", -(int)(sliderThatWasMoved->getValue()/0.75));
        //[/UserSliderCode_attenuationSlider2]
    }
    else if (sliderThatWasMoved == keyscaleSlider2)
    {
        //[UserSliderCode_keyscaleSlider2] -- add your slider handling code here..
		processor->setEnumParameter("Carrier Keyscale Level", -(int)(sliderThatWasMoved->getValue()/1.5));
        //[/UserSliderCode_keyscaleSlider2]
    }
    else if (sliderThatWasMoved == tremoloSlider)
    {
        //[UserSliderCode_tremoloSlider] -- add your slider handling code here..
		processor->setEnumParameter("Tremolo Depth", sliderThatWasMoved->getValue() < 2.0 ? 0 : 1);
        //[/UserSliderCode_tremoloSlider]
    }
    else if (sliderThatWasMoved == vibratoSlider)
    {
        //[UserSliderCode_vibratoSlider] -- add your slider handling code here..
		processor->setEnumParameter("Vibrato Depth", sliderThatWasMoved->getValue() < 8.0 ? 0 : 1);
        //[/UserSliderCode_vibratoSlider]
    }
    else if (sliderThatWasMoved == feedbackSlider)
    {
        //[UserSliderCode_feedbackSlider] -- add your slider handling code here..
		processor->setIntParameter("Modulator Feedback", (int)sliderThatWasMoved->getValue());
        //[/UserSliderCode_feedbackSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PluginGui::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == sineImageButton)
    {
        //[UserButtonCode_sineImageButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Wave", 0);
        //[/UserButtonCode_sineImageButton]
    }
    else if (buttonThatWasClicked == halfsineImageButton)
    {
        //[UserButtonCode_halfsineImageButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Wave", 1);
        //[/UserButtonCode_halfsineImageButton]
    }
    else if (buttonThatWasClicked == abssineImageButton)
    {
        //[UserButtonCode_abssineImageButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Wave", 2);
        //[/UserButtonCode_abssineImageButton]
    }
    else if (buttonThatWasClicked == quartersineImageButton)
    {
        //[UserButtonCode_quartersineImageButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Wave", 3);
        //[/UserButtonCode_quartersineImageButton]
    }
    else if (buttonThatWasClicked == tremoloButton)
    {
        //[UserButtonCode_tremoloButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Tremolo", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_tremoloButton]
    }
    else if (buttonThatWasClicked == vibratoButton)
    {
        //[UserButtonCode_vibratoButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Vibrato", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_vibratoButton]
    }
    else if (buttonThatWasClicked == sustainButton)
    {
        //[UserButtonCode_sustainButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Sustain", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_sustainButton]
    }
    else if (buttonThatWasClicked == keyscaleEnvButton)
    {
        //[UserButtonCode_keyscaleEnvButton] -- add your button handler code here..
		processor->setEnumParameter("Modulator Keyscale Rate", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_keyscaleEnvButton]
    }
    else if (buttonThatWasClicked == sineImageButton2)
    {
        //[UserButtonCode_sineImageButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Wave", 0);
        //[/UserButtonCode_sineImageButton2]
    }
    else if (buttonThatWasClicked == halfsineImageButton2)
    {
        //[UserButtonCode_halfsineImageButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Wave", 1);
        //[/UserButtonCode_halfsineImageButton2]
    }
    else if (buttonThatWasClicked == abssineImageButton2)
    {
        //[UserButtonCode_abssineImageButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Wave", 2);
        //[/UserButtonCode_abssineImageButton2]
    }
    else if (buttonThatWasClicked == quartersineImageButton2)
    {
        //[UserButtonCode_quartersineImageButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Wave", 3);
        //[/UserButtonCode_quartersineImageButton2]
    }
    else if (buttonThatWasClicked == tremoloButton2)
    {
        //[UserButtonCode_tremoloButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Tremolo", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_tremoloButton2]
    }
    else if (buttonThatWasClicked == vibratoButton2)
    {
        //[UserButtonCode_vibratoButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Vibrato", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_vibratoButton2]
    }
    else if (buttonThatWasClicked == sustainButton2)
    {
        //[UserButtonCode_sustainButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Sustain", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_sustainButton2]
    }
    else if (buttonThatWasClicked == keyscaleEnvButton2)
    {
        //[UserButtonCode_keyscaleEnvButton2] -- add your button handler code here..
		processor->setEnumParameter("Carrier Keyscale Rate", buttonThatWasClicked->getToggleState() ? 1 : 0);
        //[/UserButtonCode_keyscaleEnvButton2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginGui" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="JuceOplvstiAudioProcessor* ownerFilter"
                 variableInitialisers=" AudioProcessorEditor (ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.33" fixedSize="0"
                 initialWidth="430" initialHeight="800">
  <BACKGROUND backgroundColour="ff000000"/>
  <GROUPCOMPONENT name="new group" id="d2c7c07bf2d78c30" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="16 8 400 336" outlinecol="ff007f00"
                  textcol="ff007f00" title="Modulator" textpos="33"/>
  <COMBOBOX name="frequency combo box" id="4e65faf3d9442460" memberName="frequencyComboBox"
            virtualName="" explicitFocusOrder="0" pos="128 80 72 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="frequency label" id="7414532477c7f744" memberName="frequencyLabel"
         virtualName="" explicitFocusOrder="0" pos="32 80 80 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Frequency" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="a slider" id="1b9be27726a5b3ae" memberName="aSlider" virtualName=""
          explicitFocusOrder="0" pos="40 208 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="a label" id="9dd0b13f00b4de42" memberName="aLabel" virtualName=""
         explicitFocusOrder="0" pos="40 280 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="d slider" id="d4cc8ddf2fc9cf2b" memberName="dSlider" virtualName=""
          explicitFocusOrder="0" pos="104 208 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="d label" id="a7f17b098b85f10b" memberName="dLabel" virtualName=""
         explicitFocusOrder="0" pos="104 280 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="s slider" id="9bcadfc61e498bce" memberName="sSlider" virtualName=""
          explicitFocusOrder="0" pos="168 208 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="d label" id="6467455c7573fefa" memberName="dLabel2" virtualName=""
         explicitFocusOrder="0" pos="168 280 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="r slider" id="5616976a8c5a3f5f" memberName="rSlider" virtualName=""
          explicitFocusOrder="0" pos="232 208 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="r label" id="ef30d2907e867666" memberName="rLabel" virtualName=""
         explicitFocusOrder="0" pos="232 280 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="attenuation slider" id="dfb943cd83b3977f" memberName="attenuationSlider"
          virtualName="" explicitFocusOrder="0" pos="304 168 72 112" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="-47.25" max="0" int="0.75" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="attenuation label" id="643f88854c82ca3e" memberName="attenuationLabel"
         virtualName="" explicitFocusOrder="0" pos="304 280 96 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Attenuation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="666be8c96c85c9f1" memberName="dbLabel" virtualName=""
         explicitFocusOrder="0" pos="368 256 40 24" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dB"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="sine image button" id="5e72e0ec4fc09c1a" memberName="sineImageButton"
               virtualName="" explicitFocusOrder="0" pos="120 40 34 30" tooltip="sine"
               buttonText="Sine" connectedEdges="0" needsCallback="1" radioGroupId="1"
               keepProportions="1" resourceNormal="full_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="half sine image button" id="bf9e0504c5e9e5d5" memberName="halfsineImageButton"
               virtualName="" explicitFocusOrder="0" pos="176 40 34 30" tooltip="half sine"
               buttonText="Half Sine" connectedEdges="0" needsCallback="1" radioGroupId="1"
               keepProportions="1" resourceNormal="half_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="abs sine image button" id="1b0b532ac934edae" memberName="abssineImageButton"
               virtualName="" explicitFocusOrder="0" pos="232 40 34 30" tooltip="abs sine"
               buttonText="Abs Sine" connectedEdges="0" needsCallback="1" radioGroupId="1"
               keepProportions="1" resourceNormal="abs_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="quarter sine image button" id="47d1bd1fd4ae011d" memberName="quartersineImageButton"
               virtualName="" explicitFocusOrder="0" pos="288 40 34 30" tooltip="quarter sine"
               buttonText="Quarter Sine" connectedEdges="0" needsCallback="1"
               radioGroupId="1" keepProportions="1" resourceNormal="quarter_sine_png"
               opacityNormal="0.5" colourNormal="0" resourceOver="" opacityOver="0.5"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <LABEL name="wave label" id="d35c942584ea52a6" memberName="waveLabel"
         virtualName="" explicitFocusOrder="0" pos="32 40 80 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Wave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="tremolo button" id="1e6ab9b2f1fee312" memberName="tremoloButton"
                virtualName="" explicitFocusOrder="0" pos="144 120 96 24" txtcol="ff007f00"
                buttonText="Tremolo" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="vibrato button" id="a989eb6692e3dbd8" memberName="vibratoButton"
                virtualName="" explicitFocusOrder="0" pos="40 120 96 24" txtcol="ff007f00"
                buttonText="Vibrato" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="sustain button" id="e0ae2bc46ec1861c" memberName="sustainButton"
                virtualName="" explicitFocusOrder="0" pos="40 304 96 24" txtcol="ff007f00"
                buttonText="Sustain" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="keyscale env button" id="a3f62a22526b4b49" memberName="keyscaleEnvButton"
                virtualName="" explicitFocusOrder="0" pos="136 304 184 24" txtcol="ff007f00"
                buttonText="Keyscale Envelope Rate" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="keyscale slider" id="8bde8e6e39d8ae89" memberName="keyscaleSlider"
          virtualName="" explicitFocusOrder="0" pos="256 104 112 24" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="-6" max="0" int="1.5" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="44"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="frequency label" id="7898903168ad06c2" memberName="frequencyLabel2"
         virtualName="" explicitFocusOrder="0" pos="248 80 152 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Keyscale Attenuation"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="b9b3cedf2b541262" memberName="dbLabel2" virtualName=""
         explicitFocusOrder="0" pos="368 96 40 40" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dB/&#10;8ve&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="93b9aaeb75040aed" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="16 352 400 320" outlinecol="ff007f00"
                  textcol="ff007f00" title="Carrier" textpos="33"/>
  <COMBOBOX name="frequency combo box" id="30b8c81b6bd2a17" memberName="frequencyComboBox2"
            virtualName="" explicitFocusOrder="0" pos="128 424 72 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="frequency label" id="65d58d2259c13bf1" memberName="frequencyLabel3"
         virtualName="" explicitFocusOrder="0" pos="32 424 80 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Frequency" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="a slider" id="d6d2f4556ea9394" memberName="aSlider2" virtualName=""
          explicitFocusOrder="0" pos="40 536 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="a label" id="9ec6412cc79720bc" memberName="aLabel2" virtualName=""
         explicitFocusOrder="0" pos="40 608 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="d slider" id="4a1f1b6038500f67" memberName="dSlider2" virtualName=""
          explicitFocusOrder="0" pos="104 536 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="d label" id="10231adaf9e23e14" memberName="dLabel3" virtualName=""
         explicitFocusOrder="0" pos="104 608 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="s slider" id="2fc057248a815958" memberName="sSlider2" virtualName=""
          explicitFocusOrder="0" pos="168 536 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="d label" id="5b881f2381defac" memberName="dLabel4" virtualName=""
         explicitFocusOrder="0" pos="168 608 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="r slider" id="5474ad005fb58e97" memberName="rSlider2" virtualName=""
          explicitFocusOrder="0" pos="232 536 48 72" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="15" int="1" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="r label" id="ca2834438bee82a9" memberName="rLabel2" virtualName=""
         explicitFocusOrder="0" pos="232 608 48 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="attenuation slider" id="edb48da87d7535dd" memberName="attenuationSlider2"
          virtualName="" explicitFocusOrder="0" pos="304 496 72 112" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="-47.25" max="0" int="0.75" style="LinearVertical"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="64"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="attenuation label" id="958314f88253f461" memberName="attenuationLabel2"
         virtualName="" explicitFocusOrder="0" pos="304 608 96 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Attenuation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="7efc6195ef5e25d1" memberName="dbLabel3" virtualName=""
         explicitFocusOrder="0" pos="368 584 40 24" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dB"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="sine image button" id="27e01d31ba835965" memberName="sineImageButton2"
               virtualName="" explicitFocusOrder="0" pos="120 384 34 30" tooltip="sine"
               buttonText="Sine" connectedEdges="0" needsCallback="1" radioGroupId="2"
               keepProportions="1" resourceNormal="full_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="half sine image button" id="6e9afdb08dd4edac" memberName="halfsineImageButton2"
               virtualName="" explicitFocusOrder="0" pos="176 384 34 30" tooltip="half sine"
               buttonText="Half Sine" connectedEdges="0" needsCallback="1" radioGroupId="2"
               keepProportions="1" resourceNormal="half_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="abs sine image button" id="361941cfa04130c1" memberName="abssineImageButton2"
               virtualName="" explicitFocusOrder="0" pos="232 384 34 30" tooltip="abs sine"
               buttonText="Abs Sine" connectedEdges="0" needsCallback="1" radioGroupId="2"
               keepProportions="1" resourceNormal="abs_sine_png" opacityNormal="0.5"
               colourNormal="0" resourceOver="" opacityOver="0.5" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="quarter sine image button" id="3fa62f49fdd1a41f" memberName="quartersineImageButton2"
               virtualName="" explicitFocusOrder="0" pos="288 384 34 30" tooltip="quarter sine"
               buttonText="Quarter Sine" connectedEdges="0" needsCallback="1"
               radioGroupId="2" keepProportions="1" resourceNormal="quarter_sine_png"
               opacityNormal="0.5" colourNormal="0" resourceOver="" opacityOver="0.5"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <LABEL name="wave label" id="c810628f3c772781" memberName="waveLabel2"
         virtualName="" explicitFocusOrder="0" pos="32 384 80 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Wave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="tremolo button" id="a517934e39704073" memberName="tremoloButton2"
                virtualName="" explicitFocusOrder="0" pos="152 464 96 24" txtcol="ff007f00"
                buttonText="Tremolo" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="vibrato button" id="736b965a99641077" memberName="vibratoButton2"
                virtualName="" explicitFocusOrder="0" pos="40 464 96 24" txtcol="ff007f00"
                buttonText="Vibrato" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="sustain button" id="a3832cb840cae1f2" memberName="sustainButton2"
                virtualName="" explicitFocusOrder="0" pos="40 632 96 24" txtcol="ff007f00"
                buttonText="Sustain" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="keyscale env button" id="4cd968dae86d143c" memberName="keyscaleEnvButton2"
                virtualName="" explicitFocusOrder="0" pos="136 632 184 24" txtcol="ff007f00"
                buttonText="Keyscale Envelope Rate" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <SLIDER name="keyscale slider" id="57fc6e489a26a985" memberName="keyscaleSlider2"
          virtualName="" explicitFocusOrder="0" pos="256 448 112 24" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="-6" max="0" int="1.5" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="44"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="frequency label" id="a1e2dd50c2835d73" memberName="frequencyLabel4"
         virtualName="" explicitFocusOrder="0" pos="248 424 152 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Keyscale Attenuation"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="82d5ab731de2099e" memberName="dbLabel4" virtualName=""
         explicitFocusOrder="0" pos="368 440 40 40" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dB/&#10;8ve&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="7392f7d1c8cf6e74" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="16 680 400 96" outlinecol="ff007f00"
                  textcol="ff007f00" title="Common" textpos="33"/>
  <SLIDER name="tremolo slider" id="ab64abee7ac8874b" memberName="tremoloSlider"
          virtualName="" explicitFocusOrder="0" pos="48 712 112 24" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="1" max="4.8" int="3.8" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="44"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="frequency label" id="134ce8f87da62b88" memberName="frequencyLabel5"
         virtualName="" explicitFocusOrder="0" pos="40 736 152 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Tremolo Depth&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="720df8e7c502dd91" memberName="dbLabel5" virtualName=""
         explicitFocusOrder="0" pos="160 704 40 40" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="dB"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="vibrato slider" id="b45a1f20f22cf5ca" memberName="vibratoSlider"
          virtualName="" explicitFocusOrder="0" pos="233 713 112 24" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="7" max="14" int="7" style="LinearHorizontal"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="44"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="frequency label" id="1412b9d14e37bcbe" memberName="frequencyLabel6"
         virtualName="" explicitFocusOrder="0" pos="225 737 152 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Vibrato Depth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="db label" id="e13e0aff8b974a36" memberName="dbLabel6" virtualName=""
         explicitFocusOrder="0" pos="345 705 47 40" textCol="ff007f00"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="cents&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="feedback slider" id="f9d22e12f5e417e4" memberName="feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="120 168 136 24" thumbcol="ff00af00"
          trackcol="7f007f00" textboxtext="ff007f00" textboxbkgd="ff000000"
          textboxhighlight="ff00af00" min="0" max="7" int="1" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="44"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="frequency label" id="880eaf14af62578a" memberName="frequencyLabel7"
         virtualName="" explicitFocusOrder="0" pos="32 168 80 24" textCol="ff007f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: full_sine_png, 154, "../img/full_sine.png"
static const unsigned char resource_PluginGui_full_sine_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,17,0,0,0,15,8,6,0,0,0,2,177,36,17,0,0,0,97,73,68,65,84,56,141,99,100,96,96,248,207,
64,33,96,194,16,89,5,197,36,130,255,112,188,10,7,155,48,198,163,137,72,131,48,189,67,38,192,111,35,17,174,161,138,75,88,224,44,123,60,170,112,201,101,51,48,48,132,65,152,248,157,75,132,87,169,24,176,228,
184,102,21,149,3,150,56,151,16,72,205,140,12,164,100,64,88,158,10,67,21,38,205,16,28,0,0,120,172,116,52,166,46,206,86,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* PluginGui::full_sine_png = (const char*) resource_PluginGui_full_sine_png;
const int PluginGui::full_sine_pngSize = 154;

// JUCER_RESOURCE: half_sine_png, 126, "../img/half_sine.png"
static const unsigned char resource_PluginGui_half_sine_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,17,0,0,0,15,8,6,0,0,0,2,177,36,17,0,0,0,69,73,68,65,84,56,141,99,100,96,96,248,207,
64,33,96,194,16,89,5,197,36,130,255,112,188,10,7,155,48,198,163,137,72,131,48,189,67,38,192,111,35,17,174,161,138,75,88,224,44,123,60,170,240,201,29,100,96,96,100,160,73,58,25,53,100,240,24,2,0,70,254,
59,115,155,0,139,238,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* PluginGui::half_sine_png = (const char*) resource_PluginGui_half_sine_png;
const int PluginGui::half_sine_pngSize = 126;

// JUCER_RESOURCE: abs_sine_png, 134, "../img/abs_sine.png"
static const unsigned char resource_PluginGui_abs_sine_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,17,0,0,0,15,8,6,0,0,0,2,177,36,17,0,0,0,77,73,68,65,84,56,141,99,100,96,96,248,207,
64,33,96,194,16,89,5,197,216,0,30,185,255,112,188,10,7,155,144,28,30,9,132,24,62,57,6,134,255,152,222,33,19,96,183,9,159,11,209,228,168,226,18,22,56,203,30,143,42,124,114,12,12,12,140,12,52,73,39,163,
134,12,30,67,0,177,31,63,88,3,168,147,82,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* PluginGui::abs_sine_png = (const char*) resource_PluginGui_abs_sine_png;
const int PluginGui::abs_sine_pngSize = 134;

// JUCER_RESOURCE: quarter_sine_png, 130, "../img/quarter_sine.png"
static const unsigned char resource_PluginGui_quarter_sine_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,17,0,0,0,15,8,6,0,0,0,2,177,36,17,0,0,0,73,73,68,65,84,56,141,99,100,96,96,248,
207,64,33,96,194,16,89,133,71,53,14,57,38,98,20,17,146,99,66,81,20,134,199,0,92,114,24,46,33,19,48,81,234,10,170,185,132,5,206,178,71,18,181,71,83,133,79,238,32,3,3,35,3,77,210,201,168,33,131,199,16,0,
110,115,10,130,242,45,164,156,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* PluginGui::quarter_sine_png = (const char*) resource_PluginGui_quarter_sine_png;
const int PluginGui::quarter_sine_pngSize = 130;


//[EndFile] You can add extra defines here...
//[/EndFile]
