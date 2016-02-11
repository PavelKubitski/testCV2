#ifndef MORPHOLOGYOPERATION_H
#define MORPHOLOGYOPERATION_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QObject>

using namespace std;
using namespace cv;

class MorphologyOperation : public QObject
{
    Q_OBJECT

    static vector<Vec2b> endPoints;

public:
    explicit MorphologyOperation(QObject *parent = 0);
    ~MorphologyOperation();
    static void findEdgeChains(Mat img);
    static int pixelArea(Mat img, int i, int j);
    static void uniteEndPoinds(Mat img);
    static void grayPixelInArea(Mat img, int i, int j);
signals:

public slots:
};

#endif // MORPHOLOGYOPERATION_H
