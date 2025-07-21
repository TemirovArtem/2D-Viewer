#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QStatusBar>
#include <Qstring>
#include <QMenuBar>
#include <QToolBar>
#include "viewportwidget.h"
#include "inspectorwidget.h"
#include "hierarchywidget.h"

class Window : public QMainWindow
{
    Q_OBJECT

private:
    QPushButton *loadButton;
    QPushButton *resetButton;
    HierarchyWidget *hierarchy;
    ViewportWidget *viewport;
    InspectorWidget *inspector;
    ImageObject *image = nullptr;

public:
    explicit Window(QWidget *parent = nullptr);



signals:


public slots:
    void onStatusBarChanged(QString path, QSize resolution, float zoom);
    void onLoadActionPressed();
    void onResetActionPressed();
    void onSaveActionPressed();
    void onAboutActionPressed();

};

#endif // MAINWINDOW_H
