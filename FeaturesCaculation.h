#ifndef FEATURESCACULATION_H
#define FEATURESCACULATION_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <qvector.h>
#include <seed.h>

using namespace cv;
using namespace std;


class FeaturesCalculation
{
    Mat srcImg;
    QVector<Seed> seedVect;
public:
    FeaturesCalculation(Mat img, QVector<Seed> seedVector);
    ~FeaturesCalculation();

    void calculateArea();
    void calculatePerimetr();
    void calculateCompactness();
    bool HaveBlackNeighbors(int x, int y);
    QVector<Seed> GetSeedVector();
    void calculateLumaParametre(Mat srcImage);
};

#endif // FEATURESCACULATION_H
