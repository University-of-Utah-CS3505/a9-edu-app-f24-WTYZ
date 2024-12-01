#include "animal.h"

Animal::Animal(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : button(uiButton), world(world)
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
    if (body && world) {
        world->DestroyBody(body); // Clean up the Box2D body
    }
}

void Animal::updatePosition()
{
    if (body) {
        b2Vec2 position = body->GetPosition();
        button->move(position.x * 50, 300 - position.y * 50); // Adjust scaling and Y-axis inversion
    }
}

QPushButton* Animal::getButton() const
{
    return button;
}

void Animal::updatePhysics() {
    // Default physics update; overridden by specific animals
}
