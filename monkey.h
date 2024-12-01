#ifndef MONKEY_H
#define MONKEY_H

#include "animal.h"
#include "rope.h"

class Monkey : public Animal
{
public:
    Monkey(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Monkey() override;

    void performAction() override; // Monkey swings

    void updatePosition() override; // Update the position of the monkey based on physics

    bool eventFilter(QObject *watched, QEvent *event) override;

    void updatePhysics() override; // Overrides the new method in Animal

    void attachToRope(Rope *rope); // Attach the monkey to the rope
    bool isNearRope(Rope *rope) const; // Check if the monkey is close enough to the rope
    bool overlapsWithRope(Rope *rope) const;

    b2Body* getBody() const;


private:
    bool isDragging;               // Whether the monkey is being dragged
    QPoint dragStartPosition;      // Start position of the drag
    b2Joint *ropeJoint; // Joint connecting the monkey to the rope
};

#endif // MONKEY_H
