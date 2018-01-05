/*
  ==============================================================================

    Accelerator.h
    Created: 5 Jan 2018 11:03:38am
    Author:  Rodolfo Palacios

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Accelerator    : public Component
{
public:
    Accelerator();
    ~Accelerator();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Accelerator)
};
