#include "dog.h"
#include <QDebug>

Dog::Dog(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : Animal(uiButton, world, initialPosition)
    , animationTimer(nullptr)
    , frameIndex(0)
{
    // Define Dog's physics body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initialPosition;
    bodyDef.allowSleep = true; // Allow body to sleep when inactive
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.1f; // Minimal bounce
    body->CreateFixture(&fixtureDef);

    // Zero out any initial velocity
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    body->SetAngularVelocity(0.0f);

    qDebug() << "Dog initialized at position:" << initialPosition.x << initialPosition.y;

    // Initialize animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Dog::updateAnimationFrame);

    // Initialize sound playback
    barkSound = new QMediaPlayer(this);
    barkOutput = new QAudioOutput(this);
    barkSound->setAudioOutput(barkOutput);
    barkOutput->setVolume(0.5);                             // Volume percentage (0.0 to 1.0)
    barkSound->setSource(QUrl("qrc:/sounds/dog_bark.wav")); // Ensure this path is correct

    // Load animation frames
    animationFrames = {
        QPixmap(":/images/frame_002.png"),
        QPixmap(":/images/frame_003.png"),
        QPixmap(":/images/frame_004.png"),
        QPixmap(":/images/frame_005.png"),
    };

    if (animationFrames.empty()) {
        qDebug() << "Dog animation frames failed to load!";
    }

    qDebug() << "Dog initialized at position:" << initialPosition.x << initialPosition.y;
}

Dog::~Dog()
{
    if (body && world) {
        world->DestroyBody(body);
    }

    if (animationTimer) {
        animationTimer->stop();
        delete animationTimer;
    }

    delete barkSound;
    delete barkOutput;
}

void Dog::performAction()
{
    if (animationFrames.empty()) {
        qDebug() << "No animation frames available for dog barking.";
        return;
    }

    frameIndex = 0;             // Reset the frame index
    animationTimer->start(100); // Start animation timer (100 ms per frame)
    barkSound->play();          // Play bark sound
    qDebug() << "Dog barking animation started.";
}

void Dog::updateAnimationFrame()
{
    if (frameIndex < animationFrames.size() && button) {
        button->setIcon(QIcon(animationFrames[frameIndex]));
        button->setIconSize(button->size());
        frameIndex++;
    } else {
        animationTimer->stop();
    }
}

void Dog::updatePosition()
{
    if (body) {
        b2Vec2 position = body->GetPosition();

        // Convert Box2D position to UI coordinates
        float xPos = position.x * 50.0f;          // Scale up for UI
        float yPos = 300.0f - position.y * 50.0f; // Adjust for Y-axis inversion

        // Clamp to UI dimensions (consider button size)
        const float maxWidth = 800.0f - button->width();
        const float maxHeight = 600.0f - button->height();
        float clampedX = std::max(0.0f, std::min(xPos, maxWidth));
        float clampedY = std::max(0.0f, std::min(yPos, maxHeight));

        // Set the button position
        button->move(static_cast<int>(clampedX), static_cast<int>(clampedY));
        qDebug() << "Dog updated to clamped position:" << clampedX << clampedY;
    }
}
