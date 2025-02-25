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
    /**
     * @brief performAction
     * Rabbit jumps
     */
    void performAction() override;
    void updatePosition() override;
    void updatePhysics() override;

private:
    /**
     * @brief jump
     * Helper method to handle jumping logic
     */
    void jump();
};

#endif // RABBIT_H
