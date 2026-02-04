#include "imageprocessor.h"
#include <QStack>

bool ImageProcessor::colorsAreSimilar(QColor c1, QColor c2, int tolerance) {
    return qAbs(c1.red() - c2.red()) <= tolerance &&
           qAbs(c1.green() - c2.green()) <= tolerance &&
           qAbs(c1.blue() - c2.blue()) <= tolerance;
}

SegmentationResult ImageProcessor::runFloodFill(const QImage &image, QPoint startPoint, int tolerance) {
    SegmentationResult result;
    if (!image.valid(startPoint)) return result;

    QColor targetColor = image.pixelColor(startPoint);
    QImage visited(image.size(), QImage::Format_Mono);
    visited.fill(0);

    QStack<QPoint> stack;
    stack.push(startPoint);
    long pixelCount = 0;

    while (!stack.isEmpty()) {
        QPoint p = stack.pop();
        if (!image.valid(p) || visited.pixelIndex(p) == 1) continue;

        if (colorsAreSimilar(image.pixelColor(p), targetColor, tolerance)) {
            visited.setPixel(p, 1);
            pixelCount++;
            result.allPixels.append(p);

            bool isBorder = false;
            QPoint dirs[] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            for (const auto& d : dirs) {
                QPoint n = p + d;
                if (!image.valid(n) || !colorsAreSimilar(image.pixelColor(n), targetColor, tolerance)) {
                    isBorder = true;
                } else if (visited.pixelIndex(n) == 0) {
                    stack.push(n);
                }
            }
            if (isBorder) result.perimeter.append(p);
        }
    }

    if (image.width() > 0 && image.height() > 0) {
        result.areaPercent = (static_cast<double>(pixelCount) / (image.width() * image.height())) * 100.0;
    }
    return result;
}
