#include "viewportwidget.h"
#include <qapplication.h>

ViewportWidget::ViewportWidget(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
}

void ViewportWidget::SetImage(ImageObject *_image)
{
    scene->clear();
    image = nullptr;
    image = _image;

    QPixmap *img = new QPixmap(image->GetImage());
    item = new QGraphicsPixmapItem();
    item->setPixmap(*img);
    item->setTransformOriginPoint(item->boundingRect().center());
    item->setPos(image->GetPos());
    item->setRotation(image->GetRot());
    item->setScale(image->GetScale());
    scene->addItem(item);

    UpdateStatusBar();
}

void ViewportWidget::UpdateStatusBar()
{
    emit SignalStatusBarChanged(image->GetImagePath(), image->GetImage().size(), currentZoom);
}


void ViewportWidget::onImageChanged()
{
    item->setPos(image->GetPos());
    item->setRotation(image->GetRot());
    item->setScale(image->GetScale());
}

// Mouse controls

void ViewportWidget::ZoomIn()
{
    if(!item) return;
    float delta = 1.2;
    if (currentZoom < 10.0f)
    {
        scale(delta,delta);
        currentZoom*=delta;
        UpdateStatusBar();
    }
}

void ViewportWidget::ZoomOut()
{
    if(!item) return;
    float delta = 1.2;
    if (currentZoom > 0.1f)
    {
        scale(1/delta,1/delta);
        currentZoom/=delta;
        UpdateStatusBar();
    }
}

void ViewportWidget::SlotZoomIn() {ZoomIn(); };
void ViewportWidget::SlotZoomOut() {ZoomOut(); };

void ViewportWidget::wheelEvent(QWheelEvent *event)
{
    if (item)
    {
        if(event->angleDelta().y() > 0)
        {
            ZoomIn();

        }
        else if(event->angleDelta().y() < 0)
        {
            ZoomOut();
        }
    }
}


void ViewportWidget::mousePressEvent(QMouseEvent* event) {
    if (item)
    {
        if(item->contains(item->mapFromScene(mapToScene(event->pos()))))
        {
            dragStart = mapToScene(event->pos());
            dragOffset = mapToScene(event->pos()) - item->pos(); // смещение курсора относительно центра картинки В МОМЕНТ НАЖАТИЯ
        }
    }
}

void ViewportWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(
        ( event->buttons() & Qt::LeftButton ) && // ЛКМ
        item && // есть ли объект
        item->contains(item->mapFromScene(mapToScene(event->pos()))) && // мышка внутри объекта (коорды мыши -> коорды сцены -> коорды итема)
        QApplication::startDragDistance() <= ( event->pos() - dragStart ).manhattanLength() // смещение достаточно велика(защита от срабатывания на клике)
        )
        // manhattanLength возвращает сумму абсолютных значений координат X и Y
    {

        QPointF newItemPos = mapToScene(event->pos()) - dragOffset; // текущая позиция мыши - смещение курсора относительно центра картинки В МОМЕНТ НАЖАТИЯ
        item->setPos(newItemPos);
        image->SetPos(newItemPos);
        emit SignalImageUpdated();
    }
}

