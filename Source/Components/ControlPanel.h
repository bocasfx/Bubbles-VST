
#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class ControlPanel    : public Component
{
public:
    ControlPanel();
    ~ControlPanel();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    const int WIDTH = 800;
    const int HEIGHT = 50;
    
    Slider gravity;
    Slider friction;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};
