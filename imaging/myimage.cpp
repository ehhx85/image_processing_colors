#include "myimage.h"

// ----- Constructor / Destructor ---------------------------------------------
MyImage::MyImage(QString input)
{
    qTitle = input;
}

MyImage::~MyImage()
{
    // destructor call goes here
}

// ----- Accessors ------------------------------------------------------------
// --- Get QImage conversion from OpenCV image to use in the GUI
QImage MyImage::getQImage()
{
    cv::Mat tmp;
    cv::cvtColor(image, tmp, CV_BGR2RGB);

    QImage dest((const uchar *)
                tmp.data,
                tmp.cols,
                tmp.rows,
                tmp.step,
                QImage::Format_RGB888);
    dest.bits();
    return dest;
}

// --- Save the OpenCV image to a PNG file
void MyImage::saveImageToPNG(QString outputPath)
{
    std::vector<int> compression_parameters;
    compression_parameters.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_parameters.push_back(3);

    cv::imwrite(outputPath.toStdString(), image, compression_parameters);
}

// ----- Mutators -------------------------------------------------------------
// --- Set image to data read from file ---
void MyImage::setImage(QString filePath)
{
    cv::destroyAllWindows();
    image.release();
    image = cv::imread(filePath.toStdString(), intensityColorMap);
}

// --- Set image to data read from default file or to default flat intensity ---
void MyImage::setImage(QString filePath, int intensityValue)
{
    if(intensityValue<0) {
        QFile file(filePath);
        cv::destroyAllWindows();
        image.release();

        if(file.open(QIODevice::ReadOnly)) {
            qint64 imageFileSize = file.size();
            std::vector<uchar> buf(imageFileSize);

            file.read((char*)buf.data(), imageFileSize);

            image = cv::imdecode(buf,intensityColorMap);
        }
    }
    else {
        image.release();
        image = cv::Mat::ones(256, 512, CV_32FC3) * intensityValue;
    }
}

// --- ---
void MyImage::adjustRGB(const cv::Mat& inputImage, int colorCode, double colorScale)
{
    for (int row=0; row < inputImage.rows; row++)
    {
        for (int col=0; col < inputImage.cols; col++)
        {
            cv::Vec3b color = inputImage.at<cv::Vec3b>(row,col);

            color[colorCode] *= colorScale;

            image.at<cv::Vec3b>(row,col) = color;
        }
    }
}

void MyImage::adjustRGB(const cv::Mat& inputImage,
                        double redScale,
                        double greenScale,
                        double blueScale)
{
    for (int row=0; row < inputImage.rows; row++)
    {
        for (int col=0; col < inputImage.cols; col++)
        {
            cv::Vec3b color = inputImage.at<cv::Vec3b>(row,col);
            color[2] *= redScale;
            color[1] *= greenScale;
            color[0] *= blueScale;

            image.at<cv::Vec3b>(row,col) = color;
        }
    }
}









