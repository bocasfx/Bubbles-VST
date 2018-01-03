
#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class Bubble  : public Component
{
public:
    Bubble (QAudioProcessor& p);
    ~Bubble();

    void paint (Graphics& g) override;
    void resized() override;
    Point<int> getDelta();
    void setDeltaX(int);
    void setDeltaY(int);
    void updatePosition();

private:
    
    QAudioProcessor& processor;
    Point<int> delta;
    Point<int> position;
    int channel;
    int note;
    uint8 velocity;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Bubble)
};

