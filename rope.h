#ifndef ROPE_H
#define ROPE_H

#include <Box2D/Box2D.h>
#include <QPushButton>
#include <QObject>
#include <vector>
#include <QMouseEvent>
#include <QDebug>

class Rope : public QPushButton
{
    Q_OBJECT

public:
    Rope(b2World* world, const b2Vec2& anchorPosition, QPushButton* uiButton);
    ~Rope();

    void attachMonkey(b2Body* monkeyBody); // Attach monkey to the rope
    void enableSwingingMotor();           // Enable motor for swinging rope
    void setAngle(float angle);           // Set the angle of the rope
    void updatePosition();                // Update the visual position of the rope
    b2Body* getBody() const;              // Return the Box2D body of the rope
    b2Body* getBottomSegment() const;     // Return the bottom segment of the rope
    bool isAttached() const;              // Check if a monkey is attached
    void resizeRope(int segmentCount, float segmentWidth, float segmentHeight); // Resize the rope
    void updateBottomPosition(float deltaY); // Move bottom rope segment

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    b2World* world;                  // Box2D world
    b2Body* anchorBody;              // The anchor point of the rope
    b2Body* monkeyBody;              // The monkey attached to the rope
    b2Joint* joint;                  // Joint connecting the monkey and the rope
    std::vector<b2Body*> ropeSegments; // Rope segments (dynamic bodies)

    QPushButton* button; // UI representation of the rope
    bool isDragging;               // Track if the rope is being dragged
    QPoint dragStartPosition;      // Store the drag start position
};

#endif // ROPE_H
