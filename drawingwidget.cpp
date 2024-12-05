#include "DrawingWidget.h"
#include <QPainter>
#include <QMouseEvent>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void DrawingWidget::clearCanvas()
{
    strokes.clear();
    currentStroke.clear();
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);


    for (const auto &stroke : strokes) {
        for (int i = 1; i < stroke.size(); ++i) {
            painter.drawLine(stroke[i - 1], stroke[i]);
        }
    }

    for (int i = 1; i < currentStroke.size(); ++i) {
        painter.drawLine(currentStroke[i - 1], currentStroke[i]);
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    currentStroke.clear();
    currentStroke.append(event->pos());
    update();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!currentStroke.isEmpty()) {
        currentStroke.append(event->pos());
        update();
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!currentStroke.isEmpty()) {
        strokes.append(currentStroke);
        currentStroke.clear();
        update();
    }
}
