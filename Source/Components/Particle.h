
#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

const int PARTICLE_SIZE = 30;
const int RADIUS = PARTICLE_SIZE / 2;
const int PARTICLE_THICKNESS = 3;
const int PADDING = 10;
const float GRAVITY = 0.0;
const float FRICTION = -1;

class Particle  : public Component
{
public:
    Particle (QAudioProcessor& p, int note, uint8 velocity, int x, int y);
    ~Particle();

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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Particle)
};

