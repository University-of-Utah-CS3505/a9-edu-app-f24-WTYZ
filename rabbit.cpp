#include "rabbit.h"

Rabbit::Rabbit(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : Animal(uiButton, world, initialPosition)
{
    // Define Rabbit shape and fixture
    b2PolygonShape rabbitShape;
    rabbitShape.SetAsBox(1.0f, 1.0f); // Rabbit size
    b2FixtureDef rabbitFixtureDef;
    rabbitFixtureDef.shape = &rabbitShape;
    rabbitFixtureDef.density = 1.0f;
    rabbitFixtureDef.friction = 0.3f;
    body->CreateFixture(&rabbitFixtureDef);
    qDebug() << "Rabbit physics initialized";
}

Rabbit::~Rabbit() {}

void Rabbit::performAction()
{
    if (body->GetLinearVelocity().y == 0) { // Prevent Continuous Jumping
    b2Vec2 jumpImpulse(-7.5f, 30.0f);
    body->ApplyLinearImpulse(jumpImpulse, body->GetWorldCenter(), true);
    }
}
