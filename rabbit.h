#ifndef RABBIT_H
#define RABBIT_H

#include "animal.h"

class Rabbit : public Animal
{
    Q_OBJECT

public:
    Rabbit(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Rabbit() override;

    void performAction() override;  // Rabbit-specific action (e.g., jump)
    void updatePosition() override; // Update position like other animals
    void updatePhysics() override;  // New override for physics updates

private:
    void jump(); // Helper method to handle jumping logic
};

#endif // RABBIT_H
