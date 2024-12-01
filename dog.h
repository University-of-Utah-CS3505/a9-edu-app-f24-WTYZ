#ifndef DOG_H
#define DOG_H

#include "animal.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <vector>
#include <QPixmap>

class Dog : public Animal {
    Q_OBJECT // Necessary for Qt-specific features

public:
    Dog(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Dog() override;

    void performAction() override; // Trigger barking animation
    void updatePosition() override; // Update position like other animals

private slots:
    void updateAnimationFrame(); // Slot to update barking animation frame

private:
    QTimer *animationTimer;            // Timer for animation
    QMediaPlayer *barkSound;           // Media player for MP3 sound
    QAudioOutput *barkOutput;          // Audio output for volume control
    std::vector<QPixmap> animationFrames; // Vector of barking frame image paths
    int frameIndex;                    // Current frame index for the animation
};

#endif // DOG_H
