#ifndef MONKEY_H
#define MONKEY_H

#include "animal.h"

class Monkey : public Animal
{
public:
    Monkey(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Monkey() override;

    void performAction() override; // Monkey swings

    void updatePosition() override; // Update the position of the monkey based on physics

    bool eventFilter(QObject *watched, QEvent *event) override;

    void updatePhysics() override; // Overrides the new method in Animal


private:
    bool isDragging;               // Whether the monkey is being dragged
    QPoint dragStartPosition;      // Start position of the drag
};

#endif // MONKEY_H
