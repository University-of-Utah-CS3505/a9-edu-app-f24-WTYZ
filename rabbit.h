#ifndef RABBIT_H
#define RABBIT_H

#include "animal.h"

class Rabbit : public Animal
{
public:
    Rabbit(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Rabbit();

    void performAction() override; // Rabbit-specific action (jump)
};

#endif // RABBIT_H
