#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <iostream>
#include <math.h>

#include <QFile>
#include <QImage>
#include <QString>
#include <QVector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MyImage
{
private:
    QString qTitle;

public:
    // --- Consructor / Destructor ---
    MyImage(QString input);
    ~MyImage();

    // --- OpenCV members ---
    static const int intensityColorMap = cv::IMREAD_COLOR;
    cv::Mat image;

    // --- Accessors ---
    QImage getQImage();
    void saveImageToPNG(QString outputPath);

    // --- Mutators ---
    void setImage(QString filePath);
    void setImage(QString filePath, int intensityValue);

    void adjustRGB(const cv::Mat& inputImage,
                   int colorCode,
                   double colorScale);
    void adjustRGB(const cv::Mat& inputImage,
                   double redScale,
                   double greenScale,
                   double blueScale);
};

#endif // MYIMAGE_H
