
#pragma once

#include "../PluginProcessor.h"
#include "../../JuceLibraryCode/JuceHeader.h"
#include "./Particle.h"

class Accelerator    : public Component,
                       private Timer
{
public:
    Accelerator(QAudioProcessor&);
    ~Accelerator();

    void paint (Graphics&) override;
    void resized() override;
    void createParticle(int, int);
    void detectCollissions();
    void mouseDown(const MouseEvent &) override;
    
    void setGravity(float);
    void setFriction(float);
    void setSpring(float);
    void setDiameter(int);
    void timerCallback() override;

private:

    QAudioProcessor& processor;
    Array<Particle*> particles;
    Image background;
    
    float spring;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int PARTICLE_SIZE = 30;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Accelerator)
};
