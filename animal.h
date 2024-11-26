#ifndef ANIMAL_H
#define ANIMAL_H

#include <QPushButton>
#include <Box2D/Box2D.h>
#include <QObject>

class Animal : public QObject
{
    Q_OBJECT

public:
    explicit Animal(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    virtual ~Animal();

    virtual void performAction() = 0; // Each animal will define its action
    void updatePosition();

protected:
    QPushButton *button; // UI representation of the animal
    b2Body *body;        // Box2D physics body
};

#endif // ANIMAL_H
