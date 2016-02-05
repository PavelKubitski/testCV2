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
    static cv::Mat rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk);
    static Mat rgb2hsv(Mat img); //opencv doesn't display it corect
    static Mat rgb2hls(Mat img);
    static Mat rgb2lab(Mat img);
    static void showChannels(Mat inputImage, Mat channel[], std::string labels[], double scalar[][3], int convertBack, bool CMYK);
    static void cmyk2rgb(const Mat & c,const Mat & m,const Mat & y,const Mat & k, Mat & rgb );
signals:

public slots:
};

#endif // COLORSYSTEMCONVERTER_H
