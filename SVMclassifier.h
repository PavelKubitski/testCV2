#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include <QObject>
#include <seed.h>
#include <QVector>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ml/ml.hpp>
#include <ChooseFeaturesWindow.h>
#include <seed.h>
#include <QMessageBox>

using namespace cv;
using namespace std;

//enum FEATURES { AREA = 0, PERIMETR, COMPACTNESS, LUMA };


class SVMclassifier : public QObject
{
    Q_OBJECT

    QVector<Seed> seedVect;
    cv::Mat training_mat;
    QVector<int> featVect;
    QVector<QVector<int> > trainigDataObjs;


public:
    explicit SVMclassifier(QObject *parent = 0);
    ~SVMclassifier();
    SVMclassifier(QVector<Seed> seedVector, QVector<int> featVector, int clusters, QVector<QVector<int> > trainDataObj);
    void FillTrainingMat();
    float** CalculateTrainingData();
    void fillObject(float *arr, int numberOfSeed);
    QVector<Seed> GetSeedVector();

signals:



public slots:


protected:
//    void createTrainingDataArray(float trainArray[][featVect.length()]);
};

#endif // SVMCLASSIFIER_H
