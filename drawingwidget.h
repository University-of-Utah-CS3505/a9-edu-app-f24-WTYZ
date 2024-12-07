/**
 * Name: WYNTER KIM, TERESA PARK
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: ZHENGXI ZHANG, YINHAO CHEN
 */
#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    void clearDrawing();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QPixmap canvas;
    QPoint lastPoint;
};

#endif // DRAWINGWIDGET_H
