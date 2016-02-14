#ifndef SVMCLASSIFIER_H
#define SVMCLASSIFIER_H

#include <QObject>
#include <seed.h>
#include <QVector>
//#include <svm.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ml/ml.hpp>

using namespace cv;





class SVMclassifier : public QObject
{
    Q_OBJECT

    QVector<Seed> seedVect;
    cv::Mat training_mat;

public:
    explicit SVMclassifier(QObject *parent = 0);
    ~SVMclassifier();
    SVMclassifier(QVector<Seed> seedVector);
    void FillTrainingMat();
    float** CalculateTrainingData();
signals:



public slots:


};

#endif // SVMCLASSIFIER_H
