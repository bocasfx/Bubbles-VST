
#include "../PluginProcessor.h"
#include "Bubble.h"

Bubble::Bubble (QAudioProcessor& p, int n, uint8 v, int x, int y)
: processor(p),
  channel(1),
  active(false)
{
    int componentSize = BUBBLE_SIZE + ( 2 * BUBBLE_THICKNESS) + (2 * PADDING);
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

Bubble::~Bubble()
{
}

void Bubble::paint (Graphics& g)
{
    g.setColour(colour);
    g.drawEllipse (BUBBLE_THICKNESS + PADDING,
                   BUBBLE_THICKNESS + PADDING,
                   BUBBLE_SIZE, BUBBLE_SIZE,
                   BUBBLE_THICKNESS);
    
    g.beginTransparencyLayer(0.5);
    g.fillEllipse(BUBBLE_THICKNESS + PADDING,
                  BUBBLE_THICKNESS + PADDING,
                  BUBBLE_SIZE,
                  BUBBLE_SIZE);

    g.endTransparencyLayer();
    
    if (active) {
        g.drawEllipse(BUBBLE_THICKNESS,
                      BUBBLE_THICKNESS,
                      BUBBLE_SIZE + 2 * PADDING,
                      BUBBLE_SIZE + 2 * PADDING,
                      BUBBLE_THICKNESS);
        
        active = false;
    }


    updatePosition();
}

void Bubble::resized()
{
}

void Bubble::updatePosition()
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

void Bubble::collided()
{
    Logger::outputDebugString("Collided");
    play();
}

Point<float>* Bubble::getPosition()
{
    return &position;
}

Point<float>* Bubble::getDelta()
{
    return &delta;
}

void Bubble::setDelta(float dx, float dy)
{
    delta.x = dx;
    delta.y = dy;
}

void Bubble::play()
{
    processor.generateMidiMessage(channel, note, velocity);
    active = true;
}
