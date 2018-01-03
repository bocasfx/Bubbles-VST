
#include "../PluginProcessor.h"
#include "Bubble.h"

Bubble::Bubble (QAudioProcessor& p)
: processor(p),
  channel(1)
{
    setSize (20, 20);

    int xDelta = (rand() % 10) + 1;
    int yDelta = (rand() % 10) + 1;
    delta = Point<int>(xDelta, yDelta);
    
    int xPosition = rand() % 800;
    int yPosition = rand() % 600;
    position = Point<int>(xPosition, yPosition);
    
    Logger::outputDebugString("Bubble position: (" + (String)position.x + ", " + (String)position.y + ")");
    
    note = rand() % 127;
    velocity = (uint8)(rand() % 127);

    updatePosition();
}

Bubble::~Bubble()
{
}

void Bubble::paint (Graphics& g)
{
    g.setColour(Colours::mistyrose);
    g.fillEllipse (0, 0, 20, 20);
    updatePosition();
}

void Bubble::resized()
{
}

void Bubble::updatePosition()
{
    Point<int> nextPos = position + delta;
    
    if (nextPos.x < 0 || nextPos.x + 10 > getParentWidth())
    {
        delta.x = -delta.x;
        nextPos.x = position.x + delta.x;
        processor.generateMidiMessage(channel, note, velocity);
    }
    
    if (nextPos.y < 0 || nextPos.y + 10 > getParentHeight())
    {
        delta.y = -delta.y;
        nextPos.y = position.y + delta.y;
        processor.generateMidiMessage(channel, note, velocity);
    }
    
    position = nextPos;
    setTopLeftPosition(position);
}
