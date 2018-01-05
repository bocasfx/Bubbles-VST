
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), steps(10)
{
    setSize (EDITOR_WIDTH, EDITOR_HEIGHT);
    background = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    srand((int)time(NULL));
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
    for(auto it = bubbles.begin(); it != bubbles.end(); ++it) {
        delete *it;
    }
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

void QAudioProcessorEditor::mouseDown(const MouseEvent &event)
{
    Bubble* bub = createBubble(event.x, event.y);
    bubbles.add(bub);
    addAndMakeVisible(bub);
}

Bubble* QAudioProcessorEditor::createBubble(int x, int y)
{
    Logger::outputDebugString("Creating bubble: " + (String)bubbles.size());
    int note = rand() % 127;
    uint8 velocity = (uint8)(rand() % 127);
    return new Bubble(processor, note, velocity, x, y);
}

void QAudioProcessorEditor::detectCollissions()
{
    for(int i = 0; i < bubbles.size(); ++i) {

        Bubble* bubbleI = bubbles[i];
        Point<float>* posI = bubbleI->getPosition();
        Point<float>* deltaI = bubbleI->getDelta();

        for (int j = i + 1; j < bubbles.size(); ++j) {

            Bubble* bubbleJ = bubbles[j];

            Point<float>* posJ = bubbleJ->getPosition();
            Point<float>* deltaJ = bubbleJ->getDelta();

            float dx = posJ->x - posI->x;
            float dy = posJ->y - posI->y;
            
            float distance = sqrt(pow(dx, 2) + pow(dy, 2));

            if (distance <= BUBBLE_SIZE)
            {
                float angle = atan2(dy, dx);

                float targetX = posI->x + cos(angle) * BUBBLE_SIZE;
                float targetY = posI->y + sin(angle) * BUBBLE_SIZE;

                float ax = (targetX - posJ->x) * SPRING;
                float ay = (targetY - posJ->y) * SPRING;
                
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



