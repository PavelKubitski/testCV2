#ifndef FEATURESCACULATION_H
#define FEATURESCACULATION_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <qvector.h>
#include <seed.h>
#include <opencv2/legacy/legacy.hpp>
#include <qstring.h>
#include <QtCore/qmath.h>
using namespace cv;
using namespace std;


class FeaturesCalculation
{
    Mat srcImg;
    Mat firstImg;
    QVector<Seed> seedVect;
    enum PARAMETR { CONTRAST, HOMOGENEITY, DISSIMILARITY, ENERGY, ENTROPY, CORRELATION };

public:
    FeaturesCalculation(Mat img, QVector<Seed> seedVector, Mat first);
    ~FeaturesCalculation();

    void calculateArea();
    void calculatePerimetr();
    void calculateCompactness();
    bool HaveBlackNeighbors(int x, int y);
    QVector<Seed> GetSeedVector();
    void calculateLumaParameter(Mat srcImage);
    void calculateTextureGLCM();
    void createGLCM(int indexOfSeed);
    void calculateContrast();
    void calculateHomogeneity();
    void calculateDissimilarity();
    void calculateEnergy();
    void calculateParameter(PARAMETR param);
    void calculateEntropy();
    void calculateCorrelation();
    void calculateUandThigma(int index, float &U, float &thigmaSqr);
    void calculateMatExpectation();
    void calculateDispertion();
    void calculateMassCenter();
    void calculateElongation();
};

#endif // FEATURESCACULATION_H
