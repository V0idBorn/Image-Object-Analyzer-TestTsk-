#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPixmap>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadButton = new QPushButton("Завантажити зображення", this);
    highlightButton = new QPushButton("Підсвітка вимкнена", this);
    highlightButton->setCheckable(true);

    imageLabel = new QLabel("Тут буде зображення", this);
    coordsLabel = new QLabel("Координати: [X: 0, Y: 0]", this);
    resultLog = new QTextEdit(this);

    resultLog->setReadOnly(true);
    resultLog->setMaximumHeight(200);

    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(400, 300);
    imageLabel->setStyleSheet("border: 2px dashed gray; background: #f0f0f0;");
    imageLabel->setScaledContents(true);
    imageLabel->setMouseTracking(true);
    imageLabel->installEventFilter(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(loadButton);
    layout->addWidget(highlightButton);
    layout->addWidget(imageLabel);
    layout->addWidget(coordsLabel);
    layout->addWidget(resultLog);

    if (ui->centralwidget) ui->centralwidget->setLayout(layout);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(highlightButton, &QPushButton::clicked, this, &MainWindow::highlightSegment);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Відкрити", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty() && currentImage.load(fileName)) {
        imageLabel->setPixmap(QPixmap::fromImage(currentImage));
        lastSegmentPixels.clear();
        isHighlighted = false;
        highlightButton->setChecked(false);
        highlightButton->setText("Підсвітка вимкнена");
        resultLog->clear();
        resultLog->append("<b>Зображення завантажено.</b>");
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == imageLabel && !currentImage.isNull()) {
        if (event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            int x = qBound(0, mouseEvent->pos().x() * currentImage.width() / imageLabel->width(), currentImage.width() - 1);
            int y = qBound(0, mouseEvent->pos().y() * currentImage.height() / imageLabel->height(), currentImage.height() - 1);

            coordsLabel->setText(QString("Координати: [X: %1, Y: %2]").arg(x).arg(y));

            if (event->type() == QEvent::MouseButtonPress) {
                processSegmentation(QPoint(x, y));
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::processSegmentation(QPoint pos) {

    SegmentationResult res = ImageProcessor::runFloodFill(currentImage, pos);
    this->lastSegmentPixels = res.allPixels;

    resultLog->clear();
    if (res.allPixels.isEmpty()) return;

    resultLog->append(QString("<b>Точка старту:</b> [%1, %2]").arg(pos.x()).arg(pos.y()));
    resultLog->append(QString("<b>Площа:</b> %1%").arg(res.areaPercent, 0, 'f', 2));
    resultLog->append(QString("<b>Всього пікселів:</b> %1").arg(res.allPixels.size()));

    resultLog->append("<br><b>Координати межі (перші 10):</b>");
    for(int i = 0; i < qMin(10, (int)res.perimeter.size()); ++i) {
        resultLog->append(QString("• [%1, %2]").arg(res.perimeter[i].x()).arg(res.perimeter[i].y()));
    }

    updateDisplay(isHighlighted);
}

void MainWindow::updateDisplay(bool showRed) {
    if (showRed && !lastSegmentPixels.isEmpty()) {
        QImage highlightImage = currentImage;
        for (const QPoint &p : lastSegmentPixels) {
            if (highlightImage.valid(p)) highlightImage.setPixelColor(p, Qt::red);
        }
        imageLabel->setPixmap(QPixmap::fromImage(highlightImage));
    } else {
        imageLabel->setPixmap(QPixmap::fromImage(currentImage));
    }
}

void MainWindow::highlightSegment() {
    isHighlighted = highlightButton->isChecked();
    highlightButton->setText(isHighlighted ? "Підсвітка УВІМКНЕНА" : "Підсвітка вимкнена");
    updateDisplay(isHighlighted);
}
