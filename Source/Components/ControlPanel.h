
#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "./Accelerator.h"

class ControlPanel    : public Component,
                        private Slider::Listener
{
public:
    ControlPanel(Accelerator*);
    ~ControlPanel();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    void sliderValueChanged (Slider* slider) override;
    
    const int WIDTH = 800;
    const int HEIGHT = 70;
    
    Slider gravity;
    Slider friction;
    Slider spring;
    Slider diameter;
    
    Accelerator* accelerator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};
