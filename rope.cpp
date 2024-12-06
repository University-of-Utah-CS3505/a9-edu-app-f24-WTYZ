#include "rope.h"

Rope::Rope(b2World *world, const b2Vec2 &anchorPosition, const std::vector<QPushButton *> &buttonSegments)
    : world(world), buttonSegments(buttonSegments)
{
    if (buttonSegments.empty()) {
        qDebug() << "Error: No buttons provided for the rope.";
        return;
    }

    // Create Box2D anchor body
    b2BodyDef anchorDef;
    anchorDef.type = b2_staticBody;
    anchorDef.position = anchorPosition;
    anchorBody = world->CreateBody(&anchorDef);

    // Create rope segments
    float segmentWidth = 0.2f;
    float segmentHeight = 0.5f;

    for (size_t i = 0; i < buttonSegments.size(); ++i) {
        b2BodyDef segmentDef;
        segmentDef.type = b2_dynamicBody;

        // Calculate the Box2D position based on button index and spacing
        segmentDef.position.Set(anchorPosition.x, anchorPosition.y - i * segmentHeight);

        b2Body *segment = world->CreateBody(&segmentDef);

        // Define the shape and fixture for the Box2D body
        b2PolygonShape segmentShape;
        segmentShape.SetAsBox(segmentWidth, segmentHeight);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &segmentShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;
        segment->CreateFixture(&fixtureDef);

        ropeSegments.push_back(segment);

        // Connect joints between consecutive segments
        if (i > 0) {
            b2RevoluteJointDef jointDef;
            jointDef.bodyA = ropeSegments[i - 1];
            jointDef.bodyB = segment;
            jointDef.localAnchorA.Set(0.0f, -segmentHeight);
            jointDef.localAnchorB.Set(0.0f, segmentHeight);
            world->CreateJoint(&jointDef);
        }
    }

    // Attach the first segment to the anchor body
    b2RevoluteJointDef anchorJointDef;
    anchorJointDef.bodyA = anchorBody;
    anchorJointDef.bodyB = ropeSegments[0];
    anchorJointDef.localAnchorA.Set(0.0f, 0.0f);
    anchorJointDef.localAnchorB.Set(0.0f, segmentHeight);
    world->CreateJoint(&anchorJointDef);

    qDebug() << "Rope initialized with" << ropeSegments.size() << "segments.";

}

Rope::~Rope()
{
    if (joint) {
        world->DestroyJoint(joint);
    }
    for (auto* segment : ropeSegments) {
        if (segment) {
            world->DestroyBody(segment);
        }
    }
    qDebug() << "Rope destroyed.";
}

bool Rope::eventFilter(QObject* obj, QEvent* event) {
    if (obj == button) {
        qDebug() << "Event received for Rope button:" << event->type();

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                isDragging = true;
                dragStartPosition = mouseEvent->globalPos() - button->pos();
                qDebug() << "Drag start position:" << dragStartPosition;
                return true;
            }
        } else if (event->type() == QEvent::MouseMove && isDragging) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint newPos = mouseEvent->globalPos() - dragStartPosition;

            int newX = button->x();  // Horizontal position stays constant

            // Dynamically adjust maxY based on parent height
            int parentHeight = button->parentWidget()->height();
            int maxY = std::max(0, parentHeight - button->height());
            maxY = std::max(0, maxY); // Ensure non-negative value for maxY
            int newY = std::clamp(newPos.y(), 0, maxY); // Clamp Y position

            qDebug() << "Attempting to move Rope button to:" << newX << newY
                     << "Parent widget height:" << parentHeight
                     << "Button height:" << button->height()
                     << "Max Y:" << maxY;

            button->move(newX, newY);

            qDebug() << "Button geometry after move:" << button->geometry();
            return true;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            isDragging = false;
            qDebug() << "Mouse dragging ended.";
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void Rope::attachMonkey(b2Body* monkeyBody) {
    if (!monkeyBody) {
        qDebug() << "Error: Monkey body is null.";
        return;
    }

    // Destroy any existing joint
    if (joint) {
        world->DestroyJoint(joint);
        joint = nullptr;
    }

    // Attach the monkey to the bottom segment of the rope
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = getBottomSegment();
    jointDef.bodyB = monkeyBody;
    jointDef.localAnchorA.Set(0.0f, -0.3f); // Adjust attachment point
    jointDef.localAnchorB.Set(0.0f, 0.5f);  // Adjust monkey's anchor point

    joint = world->CreateJoint(&jointDef);
    if (joint) {
        qDebug() << "Monkey successfully attached to the rope.";
    } else {
        qDebug() << "Error: Failed to create joint for Monkey and Rope.";
    }
}

void Rope::enableSwingingMotor() {
    if (ropeSegments.size() > 1) {
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = ropeSegments[ropeSegments.size() - 2];
        jointDef.bodyB = ropeSegments.back();
        jointDef.localAnchorA.Set(0.0f, -0.25f);
        jointDef.localAnchorB.Set(0.0f, 0.25f);
        jointDef.enableMotor = true;
        jointDef.motorSpeed = -5.0f; // Adjust speed
        jointDef.maxMotorTorque = 10.0f;
        world->CreateJoint(&jointDef);
    }
}

b2RevoluteJoint* Rope::getJoint()  {
    return static_cast<b2RevoluteJoint*>(joint);
}

b2Body* Rope::getBottomSegment() const {
    return ropeSegments.empty() ? nullptr : ropeSegments.back();
}

b2Body* Rope::getBody() const {
    return anchorBody;
}

void Rope::updatePosition() {
    if (ropeSegments.size() != buttonSegments.size()) {
        qDebug() << "Mismatch between rope segments and button segments.";
        return;
    }

    for (size_t i = 0; i < ropeSegments.size(); ++i) {
        b2Vec2 position = ropeSegments[i]->GetPosition();
        float angle = ropeSegments[i]->GetAngle();

        // Map Box2D coordinates to screen coordinates
        int x = static_cast<int>(position.x * 50 - buttonSegments[i]->width() / 2);
        int y = static_cast<int>(300 - position.y * 50 - buttonSegments[i]->height() / 2);

        buttonSegments[i]->move(x, y);

        // Apply rotation to the QPushButton
        buttonSegments[i]->setStyleSheet("background: transparent; ");
    }
}

bool Rope::isAttached() const {
    return monkeyBody != nullptr;
}
