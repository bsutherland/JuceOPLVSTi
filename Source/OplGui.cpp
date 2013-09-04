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

#include "OplGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NewComponent::NewComponent ()
{
    addAndMakeVisible (label = new Label ("new label",
                                          "Carrier waveform"));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wav_car_sin = new ToggleButton ("new toggle button"));
    wav_car_sin->setButtonText ("Sine");
    wav_car_sin->addListener (this);

    addAndMakeVisible (toggleButton2 = new ToggleButton ("new toggle button"));
    toggleButton2->setButtonText ("Half Sine");
    toggleButton2->addListener (this);

    addAndMakeVisible (toggleButton3 = new ToggleButton ("new toggle button"));
    toggleButton3->setButtonText ("Abs Sine");
    toggleButton3->addListener (this);

    addAndMakeVisible (toggleButton4 = new ToggleButton ("new toggle button"));
    toggleButton4->setButtonText ("Quarter Sine");
    toggleButton4->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

NewComponent::~NewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    wav_car_sin = nullptr;
    toggleButton2 = nullptr;
    toggleButton3 = nullptr;
    toggleButton4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NewComponent::resized()
{
    label->setBounds (8, 8, 150, 24);
    wav_car_sin->setBounds (152, 8, 150, 24);
    toggleButton2->setBounds (152, 32, 150, 24);
    toggleButton3->setBounds (152, 56, 150, 24);
    toggleButton4->setBounds (152, 80, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NewComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == wav_car_sin)
    {
        //[UserButtonCode_wav_car_sin] -- add your button handler code here..
        //[/UserButtonCode_wav_car_sin]
    }
    else if (buttonThatWasClicked == toggleButton2)
    {
        //[UserButtonCode_toggleButton2] -- add your button handler code here..
        //[/UserButtonCode_toggleButton2]
    }
    else if (buttonThatWasClicked == toggleButton3)
    {
        //[UserButtonCode_toggleButton3] -- add your button handler code here..
        //[/UserButtonCode_toggleButton3]
    }
    else if (buttonThatWasClicked == toggleButton4)
    {
        //[UserButtonCode_toggleButton4] -- add your button handler code here..
        //[/UserButtonCode_toggleButton4]
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

<JUCER_COMPONENT documentType="Component" className="NewComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.33"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="40d227ec2225494a" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Carrier waveform" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="bfb505f78994ec5d" memberName="wav_car_sin"
                virtualName="" explicitFocusOrder="0" pos="152 8 150 24" buttonText="Sine"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="f565d4caaf1be1c8" memberName="toggleButton2"
                virtualName="" explicitFocusOrder="0" pos="152 32 150 24" buttonText="Half Sine"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="c8242ddebab8a74f" memberName="toggleButton3"
                virtualName="" explicitFocusOrder="0" pos="152 56 150 24" buttonText="Abs Sine"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="86bf0db3d1bd0f34" memberName="toggleButton4"
                virtualName="" explicitFocusOrder="0" pos="152 80 150 24" buttonText="Quarter Sine"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
