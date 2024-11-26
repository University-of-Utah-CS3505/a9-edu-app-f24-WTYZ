#include "animal.h"

Animal::Animal(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : button(uiButton)
{
    // Define the Box2D body for the animal
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initialPosition;
    body = world->CreateBody(&bodyDef);

    // Define the shape and fixture for the animal's body
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}

Animal::~Animal()
{
}

void Animal::updatePosition()
{
    // Get the body's position from Box2D
    b2Vec2 position = body->GetPosition();
    float32 angle = body->GetAngle();

    button->move(position.x * 50, 300 - position.y * 50);
}
