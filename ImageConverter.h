#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <QMainWindow>

using namespace cv;
using namespace std;

class ImageConverter : public QObject
{
    Q_OBJECT
public:
    explicit ImageConverter(QObject *parent = 0);
    ~ImageConverter();

    static QImage* IplImage2QImage(IplImage *iplImg);
    static IplImage * Image2IplImage(const QImage * qImage);
    static QImage MatToQImage( const Mat &inMat );
signals:

public slots:
};

#endif // CONVERTER_H
