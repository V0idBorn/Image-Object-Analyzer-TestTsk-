#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QPoint>
#include <QVector>
#include <QColor>

struct SegmentationResult {
    QVector<QPoint> perimeter;
    QVector<QPoint> allPixels;
    double areaPercent = 0.0;
};

class ImageProcessor {
public:
    static SegmentationResult runFloodFill(const QImage &image, QPoint startPoint, int tolerance = 10);

private:
    static bool colorsAreSimilar(QColor c1, QColor c2, int tolerance);
};

#endif // IMAGEPROCESSOR_H
