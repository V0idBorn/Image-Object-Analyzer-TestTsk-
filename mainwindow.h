#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>
#include <QPoint>
#include "imageprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void loadImage();
    void processSegmentation(QPoint pos);
    void highlightSegment();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QLabel *coordsLabel;
    QPushButton *loadButton;
    QPushButton *highlightButton;
    QTextEdit *resultLog;

    QImage currentImage;
    QVector<QPoint> lastSegmentPixels;
    bool isHighlighted = false;

    void updateDisplay(bool showRed);
};

#endif // MAINWINDOW_H
