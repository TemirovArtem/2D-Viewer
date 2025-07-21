#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QPushButton>
#include "MainWindow.h"
#include <QSlider>
#include <QProgressBar>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGridLayout>
#include <QLayout>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
