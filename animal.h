/**
 * Name: WYNTER KIM, TERESA PARK, YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK
 */
#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QPushButton>
#include <Box2D/Box2D.h>

class Animal : public QObject
{
    Q_OBJECT

public:
    explicit Animal(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    virtual ~Animal();

    /**
     * @brief performAction
     * All animals have their action(jumping, barking, swinging)
     */
    virtual void performAction() = 0;
    /**
     * @brief updatePosition
     * Update the position for the animal
     */
    virtual void updatePosition();
    /**
     * @brief updatePhysics
     * Update the Box2D object physics
     */
    virtual void updatePhysics();
    QPushButton *getButton() const;

protected:
    QPushButton *button; // The animal
    b2Body *body;        // Box2D physics body
    b2World *world;
};

#endif // ANIMAL_H
