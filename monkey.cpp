#include "monkey.h"
#include <QMouseEvent>
#include <QDebug>

Monkey::Monkey(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition)
    : Animal(uiButton, world, initialPosition), isDragging(false)
{
    if (!world) {
        qDebug() << "Error: world is null in Monkey constructor!";
        return;
    }

    // Define the monkey's body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = initialPosition;
    bodyDef.allowSleep = false; // Prevent monkey from sleeping
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f); // Adjust monkey's size
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f; // Adjust density for better stability
    fixtureDef.friction = 0.5f; // Add some friction to prevent sliding
    fixtureDef.restitution = 0.1f; // Minimal bounce
    body->CreateFixture(&fixtureDef);

    uiButton->installEventFilter(this); // Install event filter for dragging
    qDebug() << "Monkey physics initialized at position:" << initialPosition.x << initialPosition.y;
}

Monkey::~Monkey()
{
    if (body && world) {
        world->DestroyBody(body);
    }
}

void Monkey::performAction()
{
    qDebug() << "Monkey is performing an action!";
}

bool Monkey::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == button) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
            if (mouseEvent && mouseEvent->button() == Qt::LeftButton) {
                isDragging = true;
                dragStartPosition = mouseEvent->globalPos() - button->pos();
                qDebug() << "Monkey dragging started at:" << dragStartPosition;
                return true;
            }
        } else if (event->type() == QEvent::MouseMove) {
            if (isDragging) {
                QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
                if (mouseEvent) {
                    QPoint globalPos = mouseEvent->globalPos();
                    QPoint newPos = globalPos - dragStartPosition;

                    // Update the button position
                    button->move(newPos);

                    // Update the Box2D body position
                    float newX = newPos.x() / 50.0f;
                    float newY = (300 - newPos.y()) / 50.0f; // Adjust Y coordinate for UI to Box2D mapping
                    body->SetTransform(b2Vec2(newX, newY), body->GetAngle());

                    qDebug() << "Monkey dragged to UI position:" << newPos << " | Physics position:" << newX << "," << newY;
                    return true;
                }
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
            if (mouseEvent && mouseEvent->button() == Qt::LeftButton && isDragging) {
                isDragging = false;
                qDebug() << "Monkey dragging ended.";
                return true;
            }
        }
    }
    return Animal::eventFilter(watched, event); // Pass to base class if unhandled
}

void Monkey::updatePosition()
{
    if (!isDragging && body) {
        b2Vec2 position = body->GetPosition();

        // Clamp position to the visible screen area
        float clampedX = std::max(0.0f, std::min(position.x * 50.0f, 800.0f)); // Assuming width = 800
        float clampedY = std::max(0.0f, std::min(300.0f - position.y * 50.0f, 600.0f)); // Assuming height = 600

        button->move(clampedX, clampedY);
    }
}

void Monkey::updatePhysics() {
    if (ropeJoint) {
        // Monkey is swinging; let physics handle the movement
        qDebug() << "Monkey is swinging on the rope.";
    } else {
        // Default physics update
        if (body) {
            // Example: Dampen horizontal velocity
            b2Vec2 velocity = body->GetLinearVelocity();
            if (std::abs(velocity.x) > 10.0f) { // Limit horizontal speed
                velocity.x *= 0.9f;
            }
            body->SetLinearVelocity(velocity);

            // Ensure the monkey doesn't leave bounds
            b2Vec2 position = body->GetPosition();
            if (position.x < 0 || position.x > 16 || position.y < -2 || position.y > 6) {
                body->SetTransform(b2Vec2(8, 4), body->GetAngle()); // Reset position
            }
        }
    }
}

void Monkey::attachToRope(Rope* rope) {
    if (rope) {
        rope->attachMonkey(body);
        qDebug() << "Monkey attached to the rope!";
    }
}

bool Monkey::isNearRope(Rope *rope) const {
    if (!rope) return false;

    b2Vec2 monkeyPos = body->GetPosition();
    b2Vec2 ropePos = rope->getBody()->GetPosition();

    return (monkeyPos - ropePos).Length() < 1.5f; // Adjust proximity threshold as needed
}

bool Monkey::overlapsWithRope(Rope* rope) const {
    b2Body* ropeBody = rope->getBottomSegment();
    if (!ropeBody) return false;



    b2Vec2 monkeyPosition = body->GetPosition();
    b2Vec2 ropePosition = ropeBody->GetPosition();

    return std::abs(monkeyPosition.x - ropePosition.x) < 1.0f &&
           std::abs(monkeyPosition.y - ropePosition.y) < 1.0f;
}
b2Body* Monkey::getBody() const {
    return body;
}
