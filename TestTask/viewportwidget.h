#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include "imageobject.h"

class ViewportWidget : public QGraphicsView
{
    Q_OBJECT

private:
    QGraphicsScene *scene;
    ImageObject *image;
    QGraphicsPixmapItem *item = nullptr;
    QPointF dragStart;
    QPointF dragOffset;

    float currentZoom = 1.0;

public:
    explicit ViewportWidget(QWidget *parent = nullptr);

    void ZoomIn();
    void ZoomOut();
    void SetImage(ImageObject *image);
    void UpdateStatusBar();

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);


signals:
    void SignalStatusBarChanged(QString path, QSize size, float zoom);
    void SignalImageUpdated();

public slots:
    void onImageChanged();
    void SlotZoomIn();
    void SlotZoomOut();

};

#endif // VIEWPORTWIDGET_H
