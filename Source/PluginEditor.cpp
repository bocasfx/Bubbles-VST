
#include "PluginProcessor.h"
#include "PluginEditor.h"

QAudioProcessorEditor::QAudioProcessorEditor (QAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), steps(10)
{
    setSize (EDITOR_WIDTH, EDITOR_HEIGHT);
    background = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    srand((int)time(NULL));
    
    accelerator = new Accelerator();
    addAndMakeVisible(accelerator);
}

QAudioProcessorEditor::~QAudioProcessorEditor()
{
    for(auto it = particles.begin(); it != particles.end(); ++it) {
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
    Particle* bub = createParticle(event.x, event.y);
    particles.add(bub);
    addAndMakeVisible(bub);
}

Particle* QAudioProcessorEditor::createParticle(int x, int y)
{
    Logger::outputDebugString("Creating Particle: " + (String)particles.size());
    int note = rand() % 127;
    uint8 velocity = (uint8)(rand() % 127);
    return new Particle(processor, note, velocity, x, y);
}

void QAudioProcessorEditor::detectCollissions()
{
    for(int i = 0; i < particles.size(); ++i) {

        Particle* particleI = particles[i];
        Point<float>* posI = particleI->getPosition();
        Point<float>* deltaI = particleI->getDelta();

        for (int j = i + 1; j < particles.size(); ++j) {

            Particle* particleJ = particles[j];

            Point<float>* posJ = particleJ->getPosition();
            Point<float>* deltaJ = particleJ->getDelta();

            float dx = posJ->x - posI->x;
            float dy = posJ->y - posI->y;
            
            float distance = sqrt(pow(dx, 2) + pow(dy, 2));

            if (distance <= PARTICLE_SIZE)
            {
                float angle = atan2(dy, dx);

                float targetX = posI->x + cos(angle) * PARTICLE_SIZE;
                float targetY = posI->y + sin(angle) * PARTICLE_SIZE;

                float ax = (targetX - posJ->x) * SPRING;
                float ay = (targetY - posJ->y) * SPRING;
                
                float deltaIx = deltaI->x - ax;
                float deltaIy = deltaI->y - ay;
                
                float deltaJx = deltaJ->x + ax;
                float deltaJy = deltaJ->y + ay;

                particleI->setDelta(deltaIx, deltaIy);
                particleJ->setDelta(deltaJx, deltaJy);

                particles[i]->collided();
                particles[j]->collided();
            }
        }
    }
}



