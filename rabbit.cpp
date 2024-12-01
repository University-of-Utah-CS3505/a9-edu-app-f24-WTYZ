#include "rabbit.h"
#include <QDebug>

Rabbit::Rabbit(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : Animal(uiButton, world, initialPosition)
{
    // Define the rabbit's body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initialPosition;
    bodyDef.allowSleep = false;
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f); // Rabbit's physical size
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f; // Set density for proper physics
    fixtureDef.friction = 0.3f; // Add friction to avoid sliding
    body->CreateFixture(&fixtureDef);

    qDebug() << "Rabbit initialized at position:" << initialPosition.x << initialPosition.y;
}

Rabbit::~Rabbit()
{
    if (body && world) {
        world->DestroyBody(body);
    }
}

void Rabbit::performAction()
{
    qDebug() << "Rabbit is jumping!";
    jump(); // Call the private jump helper
}

void Rabbit::jump()
{
    if (body) {
        b2Vec2 impulse(-2.5f, 20.0f); // Upward force
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true); // Apply impulse for jump
    }
}

void Rabbit::updatePosition()
{
    if (body) {
        b2Vec2 position = body->GetPosition();

        // Clamp position to prevent rabbit from going out of bounds
        float clampedX = std::max(0.0f, std::min(position.x * 50.0f, 800.0f)); // Assuming width = 800
        float clampedY = std::max(0.0f, std::min(300.0f - position.y * 50.0f, 600.0f)); // Assuming height = 600

        button->move(clampedX, clampedY);
    }
}

void Rabbit::updatePhysics()
{
    // Add any additional physics-specific logic for rabbit here if needed
}
