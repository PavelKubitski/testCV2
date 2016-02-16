#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include <QObject>
#include <seed.h>
#include <QVector>
//#include <svm.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ml/ml.hpp>
#include <ChooseFeaturesWindow.h>

using namespace cv;

//enum FEATURES { AREA = 0, PERIMETR, COMPACTNESS, LUMA };


class SVMclassifier : public QObject
{
    Q_OBJECT

    QVector<Seed> seedVect;
    cv::Mat training_mat;
    QVector<int> featVect;

public:
    explicit SVMclassifier(QObject *parent = 0);
    ~SVMclassifier();
    SVMclassifier(QVector<Seed> seedVector, QVector<int> featVector);
    void FillTrainingMat();
    float** CalculateTrainingData();
    void fillObject(float *arr, int numberOfSeed);
signals:



public slots:


};

#endif // SVMCLASSIFIER_H
