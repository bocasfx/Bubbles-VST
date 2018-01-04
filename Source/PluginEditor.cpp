
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), steps(10)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (EDITOR_WIDTH, EDITOR_HEIGHT);
    
    background = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    bubbles.add(createBubble());
    
    showBubbles();
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
}

void QAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colour(30, 30, 30));
    g.drawImageAt(background, 0, 0);
    detectCollissions();
}

void QAudioProcessorEditor::resized()
{
}

void QAudioProcessorEditor::showBubbles()
{
    for(auto it = bubbles.begin(); it != bubbles.end(); ++it) {
        addAndMakeVisible(*it);
    }
}

Bubble* QAudioProcessorEditor::createBubble()
{
    Logger::outputDebugString("Creating bubble: " + (String)bubbles.size());
    return new Bubble(processor);
}

void QAudioProcessorEditor::detectCollissions()
{
    for(int i = 0; i < bubbles.size() - 1; ++i) {
        for (int j = i + 1; j < bubbles.size(); ++j) {
            
            Bubble* bubbleI = bubbles[i];
            Bubble* bubbleJ = bubbles[j];

            auto posI = bubbleI->getPosition();
            auto posJ = bubbleJ->getPosition();

            auto deltaI = bubbleI->getDelta();
            auto deltaJ = bubbleJ->getDelta();
            
            float dx = posJ->x - posI->x;
            float dy = posJ->y - posI->y;
            
            float distance = sqrt(pow(dx, 2) + pow(dy, 2));

            const int minDist = 30;
            const int spring = 1;

            if (distance < minDist)
            {
                float angle = atan2(dy, dx);

                float targetX = posI->x + cos(angle) * minDist;
                float targetY = posI->y + sin(angle) * minDist;

                float ax = (targetX - posJ->x) * spring;
                float ay = (targetY - posJ->y) * spring;
                
                float deltaIx = deltaI->x - ax;
                float deltaIy = deltaI->y - ay;
                
                float deltaJx = deltaJ->x + ax;
                float deltaJy = deltaJ->y + ay;

                bubbleI->setDelta(deltaIx, deltaIy);
                bubbleJ->setDelta(deltaJx, deltaJy);

                bubbles[i]->collided();
                bubbles[j]->collided();
            }
        }
    }
}



