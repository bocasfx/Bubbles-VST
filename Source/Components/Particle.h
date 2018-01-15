
#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

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
    void setGravity(float);
    void setFriction(float);
    void setDiameter(int);
    void update();

private:
    
    const int PARTICLE_THICKNESS = 3;
    const int PADDING = 10;
    
    QAudioProcessor& processor;
    Point<float> delta;
    Point<float> position;
    int channel;
    int note;
    uint8 velocity;
    Array<Colour> colours;
    Colour colour;
    Boolean active;
    
    int diameter;
    int radius;
    float gravity;
    float friction;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Particle)
};

