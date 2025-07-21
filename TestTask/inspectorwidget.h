#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QDoubleSpinBox>
#include <QLayout>
#include <qwidget.h>
#include "imageobject.h"

class InspectorWidget : public QWidget
{
    Q_OBJECT

private:
    ImageObject *image = nullptr;

    QDoubleSpinBox* posX;
    QDoubleSpinBox* posY;
    QDoubleSpinBox* rot;
    QDoubleSpinBox* scale;


public:
    explicit InspectorWidget(QWidget* parent = nullptr);

    void addTarget(ImageObject* _image);


signals:
    void SignalObjectChanged();

public slots:
    void SlotOnPositionChanged();
    void SlotOnScaleChanged();
    void SlotOnRotationChanged();
    void SlotImageUpdated();
    void SlotAddTarget(ImageObject* _image);

};

#endif // INSPECTORWIDGET_H
