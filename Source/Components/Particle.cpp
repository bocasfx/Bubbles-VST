
#include "../PluginProcessor.h"
#include "Particle.h"

Particle::Particle (QAudioProcessor& p, int n, uint8 v, int x, int y)
: processor(p),
  channel(1),
  active(false),
  diameter(30),
  gravity(0.001),
  friction(-0.75)
{
    int componentSize = diameter + ( 2 * PARTICLE_THICKNESS) + (2 * PADDING);
    setSize (componentSize, componentSize);
    
    radius = diameter / 2;
    
    colours.add(Colours::crimson);
    colours.add(Colours::deeppink);
    colours.add(Colours::orangered);
    colours.add(Colours::yellow);
    colours.add(Colours::magenta);
    colours.add(Colours::darkviolet);
    colours.add(Colours::limegreen);
    colours.add(Colours::yellowgreen);
    colours.add(Colours::mediumturquoise);
    colours.add(Colours::deepskyblue);
    colours.add(Colours::sandybrown);
    colours.add(Colours::mistyrose);
    colours.add(Colours::lightgrey);
    
    int colourIdx = (rand() % colours.size());
    colour = colours[colourIdx];
    
    float deltaX = (rand() % 10) -4;
    float deltaY = (rand() % 10) -4;
    
    delta = Point<float>(deltaX, deltaY);
    
    position = Point<float>(x, y);
    note = n;
    velocity = v;
    updatePosition();
}

Particle::~Particle()
{
}

void Particle::paint (Graphics& g)
{
    
    g.setColour(colour);
    g.drawEllipse (PARTICLE_THICKNESS + PADDING,
                   PARTICLE_THICKNESS + PADDING,
                   diameter, diameter,
                   PARTICLE_THICKNESS);
    
    
    g.beginTransparencyLayer(0.5);
    g.fillEllipse(PARTICLE_THICKNESS + PADDING,
                  PARTICLE_THICKNESS + PADDING,
                  diameter,
                  diameter);

    
    if (active) {
        g.drawEllipse(PARTICLE_THICKNESS,
                      PARTICLE_THICKNESS,
                      diameter + 2 * PADDING,
                      diameter + 2 * PADDING,
                      PARTICLE_THICKNESS);
        
        active = false;
    }
    g.endTransparencyLayer();
}

void Particle::resized()
{
}

void Particle::updatePosition()
{
    int parentWidth = 800;
    int parentHeight = 600;
    
    delta.y += gravity;
    Point<float> nextPos = position + delta;
    
    if (nextPos.x + radius >= parentWidth)
    {
        nextPos.x = parentWidth - radius;
        delta.x *= friction;
        play();
    }
    
    if (nextPos.x - radius <= 0)
    {
        nextPos.x = radius;
        delta.x *= friction;
        play();
    }
    
    if (nextPos.y + radius >= parentHeight)
    {
        nextPos.y = parentHeight - radius;
        delta.y *= friction;
        play();
    }
    
    if (nextPos.y - radius <= 0)
    {
        nextPos.y = radius;
        delta.y *= friction;
        play();
    }

    position = nextPos;
    setCentrePosition(nextPos.x, nextPos.y);
}

void Particle::collided()
{
    play();
}

Point<float>* Particle::getPosition()
{
    return &position;
}

Point<float>* Particle::getDelta()
{
    return &delta;
}

void Particle::setDelta(float dx, float dy)
{
    delta.x = dx;
    delta.y = dy;
}

void Particle::play()
{
    processor.generateMidiMessage(channel, note, velocity);
    active = true;
}

void Particle::setGravity(float g)
{
    gravity = g;
}

void Particle::setFriction(float f)
{
    friction = f;
}

void Particle::setDiameter(int d)
{
    diameter = d;
    radius = diameter / 2;
}
