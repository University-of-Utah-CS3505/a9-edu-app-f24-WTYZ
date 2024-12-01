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
    virtual void updatePosition();

    virtual void updatePhysics(); // New function

    QPushButton* getButton() const; // Getter for button (used for dog and monkey)

protected:
    QPushButton *button;// UI representation of the animal
    b2Body *body;        // Box2D physics body
    b2World *world;
};

#endif // ANIMAL_H
