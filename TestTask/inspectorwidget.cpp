#include "inspectorwidget.h"
#include <QFormLayout>
#include <QGroupBox>

InspectorWidget::InspectorWidget(QWidget* parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // каждый вид настройки по вертикали друг за другом

    QGroupBox *transformBox = new QGroupBox("Transform"); // группировка + заголовок
    QGroupBox *appearanceBox = new QGroupBox("Appearance"); // группировка + заголовок
    QGroupBox *displaysettingsBox = new QGroupBox("Display Settings"); // группировка + заголовок


    // TRANSFORM
    QFormLayout *transformLayout = new QFormLayout();
    // Position
    posX = new QDoubleSpinBox();
    posX->setRange(-10000,10000);
    posY = new QDoubleSpinBox();
    posY->setRange(-10000,10000);
    transformLayout->addRow("Position X", posX);
    transformLayout->addRow("Position Y", posY);

    QObject::connect(posX, SIGNAL(valueChanged(double)), this, SLOT(SlotOnPositionChanged()));
    QObject::connect(posY, SIGNAL(valueChanged(double)), this, SLOT(SlotOnPositionChanged()));

    //Rotation
    rot = new QDoubleSpinBox();
    rot->setRange(-360,360);
    transformLayout->addRow("Rotation", rot);
    QObject::connect(rot, SIGNAL(valueChanged(double)), this, SLOT(SlotOnRotationChanged()));

    //Scale
    scale = new QDoubleSpinBox();
    scale->setSingleStep(0.1);
    scale->setRange(0.01,100);
    transformLayout->addRow("Scale", scale);
    QObject::connect(scale, SIGNAL(valueChanged(double)), this, SLOT(SlotOnScaleChanged()));

    transformBox->setLayout(transformLayout);
    mainLayout->addWidget(transformBox);

    // APPEARANCE
    QFormLayout *appearanceLayout = new QFormLayout();
    //

    appearanceBox->setLayout(appearanceLayout);
    mainLayout->addWidget(appearanceBox);

    // DISPLAY SETTINGS
    QFormLayout *displaysettingsLayout = new QFormLayout();
    //

    displaysettingsBox->setLayout(displaysettingsLayout);
    mainLayout->addWidget(displaysettingsBox);
}


void InspectorWidget::addTarget(ImageObject* _image)
{
    image = nullptr;
    image = _image;


    posX->blockSignals(true);
    posY->blockSignals(true);
    posX->setValue(image->GetPos().x());
    posY->setValue(image->GetPos().y());
    rot->setValue(image->GetRot());
    scale->setValue(image->GetScale());
    posX->blockSignals(false);
    posY->blockSignals(false);

    // posX->setValue(...) — сигнал valueChanged срабатывает,
    // слот onPositionChanged() вызывается до того, как ты вызвал posY->setValue(...),
    // и забирает старое значение Y.
    // То есть это исправление бага когда надо жать 2 раза
}

void InspectorWidget::SlotAddTarget(ImageObject* _image)
{
    addTarget(_image);
}


void InspectorWidget::SlotOnPositionChanged()
{
    if(!image){
        posX->setValue(0);
        posY->setValue(0);
        return;
    }
    image->SetPos({posX->value(), posY->value()});
    emit SignalObjectChanged();
}

void InspectorWidget::SlotOnRotationChanged()
{
    if(!image){
        rot->setValue(0);
        return;
    }
    image->SetRot(rot->value());
    emit SignalObjectChanged();
}

void InspectorWidget::SlotOnScaleChanged()
{
    if(!image){
        scale->setValue(1.0);
        return;
    }
    image->SetScale(scale->value());
    emit SignalObjectChanged();
}


void InspectorWidget::SlotImageUpdated()
{
    posX->blockSignals(true);
    posY->blockSignals(true);
    posX->setValue(image->GetPos().x());
    posY->setValue(image->GetPos().y());
    posX->blockSignals(false);
    posY->blockSignals(false);
}
