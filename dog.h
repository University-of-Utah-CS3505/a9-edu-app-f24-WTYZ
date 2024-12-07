/**
 * Name:YINHAO CHEN, ZHENGXI ZHANG
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: WYNTER KIM, TERESA PARK
 */
#ifndef DOG_H
#define DOG_H

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QPixmap>
#include <QTimer>
#include "animal.h"
#include <vector>

class Dog : public Animal
{
    Q_OBJECT

public:
    Dog(QPushButton *uiButton, b2World *world, const b2Vec2 &initialPosition);
    ~Dog() override;

    /**
     * @brief performAction
     * Dog animation: barking
     */
    void performAction() override;
    void updatePosition() override;

private slots:
    /**
     * @brief updateAnimationFrame
     */
    void updateAnimationFrame();

private:
    QTimer *animationTimer;               // Timer for animation
    QMediaPlayer *barkSound;              // Media player for MP3 sound
    QAudioOutput *barkOutput;             // Audio output for volume control
    std::vector<QPixmap> animationFrames; // Vector of barking frame image paths
    int frameIndex;
};

#endif // DOG_H
