#ifndef TRAININGDATADIALOG_H
#define TRAININGDATADIALOG_H

#include <QDialog>
#include <stdio.h>
#include <QVector>
#include <seed.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ml/ml.hpp>
#include <ImageConverter.h>
namespace Ui {
class TrainingDataDialog;
}

class TrainingDataDialog : public QDialog
{
    Q_OBJECT
    int countOfClusters;
    int countOfObjs;
    Mat srcImg;
    Mat allocObjMat;

public:
    QVector<Seed> seedVect;
    QVector<QPoint> trainDataDots;
    explicit TrainingDataDialog(QVector<Seed> seedVector, int countOfClusters, Mat allocObjMat, Mat srcImg, QWidget *parent = 0);
    ~TrainingDataDialog();
    void colorOfСircuit(QPoint& pos);

    void fillLabels(int numberOfObject);
public slots:
    void showMousePosition(QPoint& pos);

protected:
    void showOnSrcLabel(Mat matImage);
    Scalar getColor(int cluster);
    bool HaveBlackNeighbors( int x, int y);
private slots:
    void on_okButton_clicked();

private:
    Ui::TrainingDataDialog *ui;
//    Scalar getColor(int cluster);
    void contourDetection(Scalar sc);
};

#endif // TRAININGDATADIALOG_H
