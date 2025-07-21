#include "imageobject.h"
#include <qdebug.h>

ImageObject::ImageObject(const QString& _path)
{
    path = _path;
    image.load(path);
    pos = QPointF(0, 0);
    rot = 0;
    scale = 1.0;
}


QPixmap ImageObject::GetImage() { return image; }
QPointF ImageObject::GetPos() { return pos; }
float ImageObject::GetRot() { return rot; }
float ImageObject::GetScale() { return scale; }

void ImageObject::SetPos(QPointF n) { pos = n; };
void ImageObject::SetRot(float n) { rot = n; };
void ImageObject::SetScale(float n) { scale = n; };

QString ImageObject::GetImagePath() { return path; };
void ImageObject::SetImagePath(QString& _path) { image.load(_path); };
