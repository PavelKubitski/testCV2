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
    int countOfObjsInGrBox;
    Mat srcImg;
    Mat allocObjMat;
    QVector<QVector<int> > trainDataObjsVectrs;

public:
    QVector<Seed> seedVect;
//    QVector<QVector<int> > trainDataObjsVectrs;
    explicit TrainingDataDialog(QVector<Seed> seedVector, int countOfClusters, Mat allocObjMat, Mat srcImg, QWidget *parent = 0);
    ~TrainingDataDialog();
    void colorOfСircuit(QPoint& pos);

    void fillLabels(int numberOfObject);
    QVector<QVector<int> > getTrainDataObjsVectrs() const;


public slots:
    void showMousePosition(QPoint& pos);

protected:
    void showOnSrcLabel(Mat matImage);
    Scalar getColor(int cluster);
    bool HaveBlackNeighbors( int x, int y);
private slots:
    void on_okButton_clicked();

    void on_denyButton_clicked();

private:
    Ui::TrainingDataDialog *ui;

    void contourDetection(Scalar sc);

    void showActiveGroupBox();
signals:
    void trainingDataReady();
};

#endif // TRAININGDATADIALOG_H
