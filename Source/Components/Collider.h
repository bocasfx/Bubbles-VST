/*
  ==============================================================================

    Collider.h
    Created: 5 Jan 2018 10:01:24am
    Author:  Rodolfo Palacios

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Collider    : public Component
{
public:
    Collider();
    ~Collider();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Collider)
};
