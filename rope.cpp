#include "rope.h"

Rope::Rope(b2World* world, const b2Vec2& anchorPosition, QPushButton* uiButton)
    : world(world), monkeyBody(nullptr), joint(nullptr), button(uiButton), isDragging(false)
{
    if (!button) {
        qDebug() << "Error: ropeButton is null.";
        return;
    }

    // Install event filter and verify success
    button->installEventFilter(this);
    qDebug() << "Event filter installed on Rope button:";

    // Set button properties
    button->setParent(this); // Ensure button belongs to the Rope
    button->setEnabled(true);
    button->setFocusPolicy(Qt::StrongFocus);
    button->setGeometry(anchorPosition.x * 50 - 15, 0, 50, 600);
    button->setGeometry(anchorPosition.x * 50 - 15, 0, 300, 600); // Match button geometry
    button->setIcon(QIcon(":/images/rope_icon.png"));
    button->setIconSize(QSize(300, 300)); // Use fixed icon size
    button->setStyleSheet("background: transparent; border: none;");
    button->show();

    // Debug button state
    qDebug() << "Button properties:"
             << "\nEnabled:" << button->isEnabled()
             << "\nFocusPolicy:" << button->focusPolicy()
             << "\nGeometry:" << button->geometry()
             << "\nVisible:" << button->isVisible();

    // Create Box2D anchor body
    b2BodyDef anchorDef;
    anchorDef.type = b2_staticBody;
    anchorDef.position = anchorPosition;
    anchorBody = world->CreateBody(&anchorDef);

    // Create rope segments
    float segmentWidth = 0.2f;
    float segmentHeight = 0.5f;
    int segmentCount = 20;

    for (int i = 0; i < segmentCount; ++i) {
        b2BodyDef segmentDef;
        segmentDef.type = b2_dynamicBody;
        segmentDef.position.Set(anchorPosition.x, anchorPosition.y - i * segmentHeight);

        b2Body* segment = world->CreateBody(&segmentDef);
        b2PolygonShape segmentShape;
        segmentShape.SetAsBox(segmentWidth, segmentHeight);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &segmentShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;

        segment->CreateFixture(&fixtureDef);
        ropeSegments.push_back(segment);

        if (i > 0) {
            b2RevoluteJointDef jointDef;
            jointDef.bodyA = ropeSegments[i - 1];
            jointDef.bodyB = segment;
            jointDef.localAnchorA.Set(0.0f, -segmentHeight);
            jointDef.localAnchorB.Set(0.0f, segmentHeight);
            world->CreateJoint(&jointDef);
        }
    }

    // Attach first segment to anchor
    b2RevoluteJointDef anchorJointDef;
    anchorJointDef.bodyA = anchorBody;
    anchorJointDef.bodyB = ropeSegments[0];
    anchorJointDef.localAnchorA.Set(0.0f, 0.0f);
    anchorJointDef.localAnchorB.Set(0.0f, segmentHeight);
    world->CreateJoint(&anchorJointDef);

    qDebug() << "Rope initialized with" << ropeSegments.size() << "segments at anchor position:"
             << anchorPosition.x << anchorPosition.y;
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
    if (joint) {
        world->DestroyJoint(joint); // Destroy existing joint
    }

    this->monkeyBody = monkeyBody;
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = getBottomSegment();
    jointDef.bodyB = monkeyBody;
    jointDef.localAnchorA.Set(0.0f, -0.3f);
    jointDef.localAnchorB.Set(0.0f, 0.5f);
    joint = world->CreateJoint(&jointDef);

    qDebug() << "Monkey successfully attached to the rope.";
}

void Rope::enableSwingingMotor() {
    if (ropeSegments.size() > 1) {
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = ropeSegments[ropeSegments.size() - 2];
        jointDef.bodyB = ropeSegments.back();
        jointDef.localAnchorA.Set(0.0f, -0.25f);
        jointDef.localAnchorB.Set(0.0f, 0.25f);
        jointDef.enableMotor = true;
        jointDef.motorSpeed = -5.0f;
        jointDef.maxMotorTorque = 10.0f;
        world->CreateJoint(&jointDef);
        qDebug() << "Swinging motor enabled.";
    }
}

b2Body* Rope::getBottomSegment() const {
    if (ropeSegments.empty()) {
        qDebug() << "Error: Rope segments are empty. Returning nullptr.";
        return nullptr;
    }
    return ropeSegments.back();
}

b2Body* Rope::getBody() const {
    return anchorBody;
}

void Rope::updatePosition() {
    if (!ropeSegments.empty()) {
        b2Vec2 position = ropeSegments.front()->GetPosition();
        int x = static_cast<int>(position.x * 50);
        int y = static_cast<int>(position.y * 50);
        button->move(x, y);
        qDebug() << "Rope updated to UI position:" << button->pos() << "Physics position:" << position.x << position.y;
    }
}

bool Rope::isAttached() const {
    return monkeyBody != nullptr;
}
