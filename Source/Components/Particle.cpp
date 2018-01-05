
#include "../PluginProcessor.h"
#include "Particle.h"

Particle::Particle (QAudioProcessor& p, int n, uint8 v, int x, int y)
: processor(p),
  channel(1),
  active(false)
{
    int componentSize = PARTICLE_SIZE + ( 2 * PARTICLE_THICKNESS) + (2 * PADDING);
    setSize (componentSize, componentSize);
    
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
                   PARTICLE_SIZE, PARTICLE_SIZE,
                   PARTICLE_THICKNESS);
    
    g.beginTransparencyLayer(0.5);
    g.fillEllipse(PARTICLE_THICKNESS + PADDING,
                  PARTICLE_THICKNESS + PADDING,
                  PARTICLE_SIZE,
                  PARTICLE_SIZE);

    g.endTransparencyLayer();
    
    if (active) {
        g.drawEllipse(PARTICLE_THICKNESS,
                      PARTICLE_THICKNESS,
                      PARTICLE_SIZE + 2 * PADDING,
                      PARTICLE_SIZE + 2 * PADDING,
                      PARTICLE_THICKNESS);
        
        active = false;
    }


    updatePosition();
}

void Particle::resized()
{
}

void Particle::updatePosition()
{
    int parentWidth = getParentWidth();
    int parentHeight = getParentHeight();
    
    delta.y += GRAVITY;
    Point<float> nextPos = position + delta;
    
    if (nextPos.x + RADIUS >= parentWidth)
    {
        nextPos.x = parentWidth - RADIUS;
        delta.x *= FRICTION;
        play();
    }
    else if (nextPos.x - RADIUS <= 0)
    {
        nextPos.x = RADIUS;
        delta.x *= FRICTION;
        play();
    }
    else if (nextPos.y + RADIUS >= parentHeight)
    {
        nextPos.y = parentHeight - RADIUS;
        delta.y *= FRICTION;
        play();
    }
    else if (nextPos.y - RADIUS <= 0)
    {
        nextPos.y = RADIUS;
        delta.y *= FRICTION;
        play();
    }
    
    position = nextPos;
    setCentrePosition(nextPos.x, nextPos.y);
}

void Particle::collided()
{
    Logger::outputDebugString("Collided");
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
