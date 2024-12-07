/**
 * Name:YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: ZHENGXI ZHANG, YINHAO CHEN
 */
#ifndef ROPE_H
#define ROPE_H

#include <QDebug>
#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <Box2D/Box2D.h>
#include <vector>

class Rope : public QPushButton
{
    Q_OBJECT

public:
    Rope(b2World *world,
         const b2Vec2 &anchorPosition,
         const std::vector<QPushButton *> &buttonSegments);
    ~Rope();

    void attachMonkey(b2Body *monkeyBody);
    void enableSwingingMotor();
    void setAngle(float angle);
    void updatePosition();
    b2Body *getBody() const;
    b2Body *getBottomSegment() const;
    bool isAttached() const;
    void resizeRope(int segmentCount, float segmentWidth, float segmentHeight);
    /**
     * @brief updateBottomPosition
     * Move bottom rope segment
     * The bottom segement will be the monkey when attached
     * @param deltaY
     */
    void updateBottomPosition(float deltaY);
    b2RevoluteJoint *getJoint();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    b2World *world;
    b2Body *anchorBody;
    b2Body *monkeyBody;
    b2Joint *joint;
    std::vector<b2Body *> ropeSegments;        // Rope segments
    std::vector<QPushButton *> buttonSegments; // QPushButton rope segments

    QPushButton *button;
    bool isDragging;
    QPoint dragStartPosition;
};

#endif // ROPE_H
