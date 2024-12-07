/**
 * Name:YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK
 */
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
