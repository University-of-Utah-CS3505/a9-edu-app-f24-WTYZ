#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPoint>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);

    void clearCanvas(); // 캔버스 지우기

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<QPoint> currentStroke;       // 현재 획 저장
    QVector<QVector<QPoint>> strokes;    // 모든 획 저장
};

#endif // DRAWINGWIDGET_H
