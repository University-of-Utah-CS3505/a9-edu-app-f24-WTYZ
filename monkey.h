/**
 * Name:YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK
 */
#ifndef MONKEY_H
#define MONKEY_H
#include "animal.h"
#include "rope.h"
#include <QDebug>
#include <QMouseEvent>

class Monkey : public Animal
{
public:
    Monkey(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition, Rope *rope);
    ~Monkey() override;
    /**
     * @brief performAction
     * Monkey swings
     */
    void performAction() override;
    void updatePosition() override;
    /**
     * @brief eventFilter
     * Control the monkey with mouse
     * @param watched
     * @param event
     * @return
     */
    bool eventFilter(QObject *watched, QEvent *event) override;
    void updatePhysics() override;
    /**
     * @brief attachToRope
     * Attach the monkey to the rope
     * @param rope
     */
    void attachToRope(Rope *rope);
    /**
     * @brief isNearRope
     * Check if the monkey is close enough to the rope
     * @param rope
     * @return
     */
    bool isNearRope(Rope *rope) const;
    bool overlapsWithRope(Rope *rope) const;
    b2Body *getBody() const;

private:
    bool isDragging;
    QPoint dragStartPosition;
    b2Joint *ropeJoint;       // Joint connecting the monkey to the rope
    Rope *rope;
    bool isAttachedToRope = false;
};

#endif // MONKEY_H
