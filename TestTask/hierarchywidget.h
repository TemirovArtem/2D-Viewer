#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QListWidget>

class HierarchyWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit HierarchyWidget(QWidget* parent = nullptr);

    void addItemWithName(const QString &filename);

signals:


public slots:

};

#endif // HIERARCHYWIDGET_H
