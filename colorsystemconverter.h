#ifndef COLORSYSTEMCONVERTER_H
#define COLORSYSTEMCONVERTER_H

#include <QObject>

#include <opencv/cv.h>
#include <opencv/highgui.h>



#include <QMainWindow>

using namespace cv;
using namespace std;

class ColorSystemConverter : public QObject
{
    Q_OBJECT
public:
    explicit ColorSystemConverter(QObject *parent = 0);
    ~ColorSystemConverter();
    static vector<Mat> rgb2cmyk(Mat& img, std::vector<Mat>& cmyk);
    static vector<Mat> rgb2hsv(Mat img, vector<cv::Mat>& hsvVector); //opencv doesn't display it corect
    static vector<Mat> rgb2hls(Mat img, vector<cv::Mat>& hlsVector);
    static vector<Mat> rgb2lab(Mat img, vector<cv::Mat>& labVector);
    static vector<Mat> showChannels(Mat inputImage, Mat channel[], std::string labels[], double scalar[][3], int convertBack, bool CMYK);
    static void cmyk2rgb(const Mat & c,const Mat & m,const Mat & y,const Mat & k, Mat & rgb );
signals:

public slots:
};

#endif // COLORSYSTEMCONVERTER_H
