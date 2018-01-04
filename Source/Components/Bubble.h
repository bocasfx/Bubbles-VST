
#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

const int BUBBLE_SIZE = 30;
const int RADIUS = BUBBLE_SIZE / 2;
const int BUBBLE_THICKNESS = 2;
const float GRAVITY = 0.001;
const float SPRING = 2;
const float FRICTION = -1;

class Bubble  : public Component
{
public:
    Bubble (QAudioProcessor& p);
    ~Bubble();

    void paint (Graphics& g) override;
    void resized() override;
    Point<float>* getPosition();
    Point<float>* getDelta();
    void setDelta(float dx, float dy);
    void updatePosition();
    void collided();
    void play();

private:
    
    QAudioProcessor& processor;
    Point<float> delta;
    Point<float> position;
    int channel;
    int note;
    uint8 velocity;
    Array<Colour> colours;
    Colour colour;
    Boolean active;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Bubble)
};

