/**
 * Name:YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: ZHENGXI ZHANG, YINHAO CHEN
 */
#include "rabbit.h"

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
    boxShape.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
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
        b2Vec2 impulse(-2.5f, 20.0f);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true); // Apply impulse for jump
    }
}

void Rabbit::updatePosition()
{
    if (body) {
        b2Vec2 position = body->GetPosition();

        // Clamp position to prevent rabbit from going out of bounds
        float clampedX = std::max(0.0f,
                                  std::min(position.x * 50.0f, 800.0f));
        float clampedY = std::max(0.0f,
                                  std::min(300.0f - position.y * 50.0f,
                                           600.0f));

        button->move(clampedX, clampedY);
    }
}

void Rabbit::updatePhysics()
{
    //rabbits no need addition physics
}
