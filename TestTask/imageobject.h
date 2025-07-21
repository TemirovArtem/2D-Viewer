#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H
#include <QPixmap>
#include <QPointF>
#include <QString>

class ImageObject
{
private:
    QString path;
    QPixmap image;
    QPointF pos;
    float rot;
    float scale;

public:
    ImageObject(const QString& path);

    QPixmap GetImage();
    QPointF GetPos();
    float GetRot();
    float GetScale();
    void SetPos(QPointF n);
    void SetRot(float n);
    void SetScale(float n);

    QString GetImagePath();
    void SetImagePath(QString& _path);
};

#endif // IMAGEOBJECT_H
