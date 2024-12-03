#ifndef HANZICANVAS_H
#define HANZICANVAS_H

#include <QWidget>
#include <QImage>
#include <QPoint>

class HanziCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit HanziCanvas(QWidget* parent = nullptr);

    void clearCanvas();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage canvasImage;
    QPoint lastPoint;
    bool isDrawing;
};

#endif // HANZICANVAS_H
