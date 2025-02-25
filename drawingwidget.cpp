/**
 * Name: WYNTER KIM, TERESA PARK
 * Course: CS 3505 Fall2024
 * Assignment Name: A9: An Educational project
 * Project name: Hanzi Party
 * Descrption: Our game is an interactive learning experience designed to teach players Mandarin Chinese through engaging visuals and gameplay.
 *
 * Reviewer: ZHENGXI ZHANG, YINHAO CHEN
 */
#include "DrawingWidget.h"

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
    , canvas(size())
{
    canvas.fill(Qt::transparent);
}

void DrawingWidget::clearDrawing()
{
    canvas.fill(Qt::transparent);
    update();
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPainter painter(&canvas);
        painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, canvas);
}

void DrawingWidget::resizeEvent(QResizeEvent *event)
{
    QPixmap newCanvas(size());
    newCanvas.fill(Qt::transparent);

    QPainter painter(&newCanvas);
    painter.drawPixmap(0, 0, canvas);
    canvas = newCanvas;

    QWidget::resizeEvent(event);
}
