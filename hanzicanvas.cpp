#include "HanziCanvas.h"
#include <QMouseEvent>
#include <QPainter>

HanziCanvas::HanziCanvas(QWidget *parent)
    : QWidget(parent), isDrawing(false) {
    canvasImage = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    canvasImage.fill(Qt::transparent);
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_TranslucentBackground);
}

void HanziCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = true;
        lastPoint = event->pos();
    }
}

void HanziCanvas::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing && (event->buttons() & Qt::LeftButton)) {
        QPainter painter(&canvasImage);
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void HanziCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing) {
        isDrawing = false;
    }
}

void HanziCanvas::clearCanvas() {
    canvasImage.fill(Qt::transparent);
    update();
}


