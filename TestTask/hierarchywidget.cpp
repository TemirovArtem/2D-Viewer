#include "hierarchywidget.h"

HierarchyWidget::HierarchyWidget(QWidget *parent) : QListWidget(parent) {}

void HierarchyWidget::addItemWithName(const QString &filename)
{
    addItem(filename);
}

