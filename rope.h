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

    void attachMonkey(b2Body *monkeyBody); // Attach monkey to the rope
    void enableSwingingMotor();            // Enable motor for swinging rope
    void setAngle(float angle);            // Set the angle of the rope
    void updatePosition();                 // Update the visual position of the rope
    b2Body *getBody() const;               // Return the Box2D body of the rope
    b2Body *getBottomSegment() const;      // Return the bottom segment of the rope
    bool isAttached() const;               // Check if a monkey is attached
    void resizeRope(int segmentCount, float segmentWidth, float segmentHeight); // Resize the rope
    void updateBottomPosition(float deltaY); // Move bottom rope segment
    b2RevoluteJoint *getJoint();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    b2World *world;                            // Box2D world
    b2Body *anchorBody;                        // The anchor point of the rope
    b2Body *monkeyBody;                        // The monkey attached to the rope
    b2Joint *joint;                            // Joint connecting the monkey and the rope
    std::vector<b2Body *> ropeSegments;        // Rope segments (dynamic bodies)
    std::vector<QPushButton *> buttonSegments; // QPushButton rope segments

    QPushButton *button;      // UI representation of the rope
    bool isDragging;          // Track if the rope is being dragged
    QPoint dragStartPosition; // Store the drag start position
};

#endif // ROPE_H
