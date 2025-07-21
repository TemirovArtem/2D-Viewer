#include "MainWindow.h"

Window::Window(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(1200, 800);
    setStatusBar(new QStatusBar(this));

    // MenuBar
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *saveAction = fileMenu->addAction("Save");
    QAction *loadAction = fileMenu->addAction("Load");

    QMenu *helpMenu = menuBar()->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");


    // ToolBar
    QToolBar *toolBar = addToolBar("ToolBar");
    QAction *resetAction = toolBar->addAction("Reset Image");
    QAction *zoomInAction = toolBar->addAction("Zoom In");
    QAction *zoomOutAction = toolBar->addAction("Zoom Out");

    //Hierarchy
    hierarchy = new HierarchyWidget(this);
    hierarchy->setFixedWidth(200);


    // Viewport | Inspector
    viewport = new ViewportWidget(this);
    viewport->setMinimumWidth(600);
    inspector = new InspectorWidget(this);
    inspector->setFixedWidth(200);

    // Layouts
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *MainLayout = new QVBoxLayout(central);
    QHBoxLayout *ContentLayout = new QHBoxLayout();
    ContentLayout->addWidget(hierarchy);
    ContentLayout->addWidget(inspector);
    ContentLayout->addWidget(viewport);
    MainLayout->addLayout(ContentLayout);


    // Connects
    connect(inspector, SIGNAL(SignalObjectChanged()), viewport, SLOT(onImageChanged()));
    connect(viewport, SIGNAL(SignalStatusBarChanged(QString,QSize,float)), this, SLOT(onStatusBarChanged(QString,QSize,float)));
    connect(resetAction, SIGNAL(triggered()), this, SLOT(onResetActionPressed()));
    connect(zoomInAction, SIGNAL(triggered()), viewport, SLOT(SlotZoomIn()));
    connect(zoomOutAction, SIGNAL(triggered()), viewport, SLOT(SlotZoomOut()));
    connect(viewport, SIGNAL(SignalImageUpdated()), inspector, SLOT(SlotImageUpdated()));

    connect(saveAction, SIGNAL(triggered()), this, SLOT(onSaveActionPressed()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(onLoadActionPressed()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutActionPressed()));
}

void Window::onLoadActionPressed()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), QCoreApplication::applicationDirPath(), tr("Images (*.png *.jpg *.bmp)"));
    if (path.isEmpty()) return;

    // Удаляем старый объект
    if (image) delete image;

    // Загружаем изображение
    image = new ImageObject(path);
    viewport->SetImage(image);
    inspector->addTarget(image);

    // Добавляем в Hierarchy
    hierarchy->addItemWithName(QFileInfo(path).fileName());

    // Пытаемся загрузить параметры из .params
    QString paramFilePath = path + ".params";
    QFile paramFile(paramFilePath);
    if (paramFile.exists()) {
        if (paramFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&paramFile);
            float x, y, rot, scale;
            in >> x >> y >> rot >> scale;

            image->SetPos(QPointF(x, y));
            image->SetRot(rot);
            image->SetScale(scale);

            viewport->SetImage(image);
            inspector->addTarget(image);
        }
    }
}


void Window::onResetActionPressed()
{
    image->SetPos(QPointF(0,0));
    image->SetRot(0);
    image->SetScale(1);
    viewport->SetImage(image);
    inspector->addTarget(image);
}

void Window::onStatusBarChanged(QString path, QSize resolution, float zoom)
{
    QString text = QString("%1  |  %2 x %3  |  %4%")
                       .arg(path)
                       .arg(resolution.width())
                       .arg(resolution.height())
                       .arg(int(zoom * 100));
    statusBar()->showMessage(text);
}

void Window::onAboutActionPressed()
{
    QMessageBox::aboutQt(this, "About Qt");
}


void Window::onSaveActionPressed()
{
    if (!image) return;

    QString imagePath = image->GetImagePath();
    if (imagePath.isEmpty()) return;

    QString paramFilePath = imagePath + ".params";

    QFile file(paramFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Save Error", "Unable to write parameters.");
        return;
    }

    QTextStream out(&file);
    QPointF pos = image->GetPos();
    out << pos.x() << " " << pos.y() << "\n";
    out << image->GetRot() << "\n";
    out << image->GetScale() << "\n";
    file.close();
}

