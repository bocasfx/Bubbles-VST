
#include "../../JuceLibraryCode/JuceHeader.h"
#include "ControlPanel.h"

ControlPanel::ControlPanel()
{
    setSize(WIDTH, HEIGHT);
    
    gravity.setSliderStyle (Slider::LinearHorizontal);
    gravity.setRange(-3.0, 3.0, 0.1);
    gravity.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    gravity.setPopupDisplayEnabled (true, false, this);
    gravity.setTextValueSuffix (" Gravity");
    gravity.setValue(0.0);
    
    friction.setSliderStyle (Slider::LinearHorizontal);
    friction.setRange(-1.0, 1.0, 0.1);
    friction.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    friction.setPopupDisplayEnabled (true, false, this);
    friction.setTextValueSuffix (" Friction");
    friction.setValue(0.0);
    
    addAndMakeVisible (&gravity);
    addAndMakeVisible (&friction);
}

ControlPanel::~ControlPanel()
{
}

void ControlPanel::paint (Graphics& g)
{
}

void ControlPanel::resized()
{
    gravity.setBounds(25, 10, 200, 30);
    friction.setBounds(250, 10, 200, 30);
}
