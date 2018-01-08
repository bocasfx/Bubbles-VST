
#include "../../JuceLibraryCode/JuceHeader.h"
#include "ControlPanel.h"

ControlPanel::ControlPanel(Accelerator* a) : accelerator(a)
{
    setSize(WIDTH, HEIGHT);
    
    gravity.setSliderStyle (Slider::Rotary);
    gravity.setRange(-1.0, 1.0, 0.01);
    gravity.setValue(0.0);
    gravity.setTextBoxStyle(Slider::NoTextBox, false, 50, 18);
    gravity.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
    gravity.setPopupDisplayEnabled(true, true, this);
    gravity.setTextValueSuffix(" Gravity");
    gravity.addListener(this);
    
    friction.setSliderStyle (Slider::Rotary);
    friction.setRange(-1.0, 0.0, 0.01);
    friction.setValue(-1.0);
    friction.setTextBoxStyle(Slider::NoTextBox, false, 50, 18);
    friction.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
    friction.setPopupDisplayEnabled(true, true, this);
    friction.setTextValueSuffix(" Friction");
    friction.addListener(this);
    
    spring.setSliderStyle (Slider::Rotary);
    spring.setRange(0.5, 1.0, 0.01);
    spring.setValue(1.0);
    spring.setTextBoxStyle(Slider::NoTextBox, false, 50, 18);
    spring.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
    spring.setPopupDisplayEnabled(true, true, this);
    spring.setTextValueSuffix(" Spring");
    spring.addListener(this);
    
    diameter.setSliderStyle (Slider::Rotary);
    diameter.setRange(5, 30, 1);
    diameter.setValue(30);
    diameter.setTextBoxStyle(Slider::NoTextBox, false, 50, 18);
    diameter.setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
    diameter.setPopupDisplayEnabled(true, true, this);
    diameter.setTextValueSuffix(" Diameter");
    diameter.addListener(this);
    
    addAndMakeVisible (&gravity);
    addAndMakeVisible (&friction);
    addAndMakeVisible (&spring);
    addAndMakeVisible (&diameter);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::paint (Graphics& g)
{
    g.setColour(Colours::black);
    g.fillAll();
}

void ControlPanel::resized()
{
    const int controlHeight = 60;
    const int controlWidth = 100;
    const int controlTop = 5;

    gravity.setBounds (50, controlTop, controlWidth, controlHeight);
    friction.setBounds (250, controlTop, controlWidth, controlHeight);
    spring.setBounds (450, controlTop, controlWidth, controlHeight);
    diameter.setBounds (650, controlTop, controlWidth, controlHeight);
}

void ControlPanel::sliderValueChanged (Slider* slider)
{
    if (slider == &gravity)
    {
        accelerator->setGravity(slider->getValue());
    }
    else if (slider == &friction)
    {
        accelerator->setFriction(slider->getValue());
    }
    else if (slider == &spring)
    {
        accelerator->setSpring(slider->getValue());
    }
    else if (slider == &diameter)
    {
        accelerator->setDiameter(slider->getValue());
    }
}
