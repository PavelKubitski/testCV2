#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <converter.h>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStack>
#include <QVector>
#include <seed.h>
#include "QStandardItemModel"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void OpenPicture();
    void ToGrayScale();
    void ChangeBrightness();
    void ChangeContrast();
    void AdaptiveThreshold();
    void MedianFilter();
    void DenyFilter();
    void ErodeFilter();
    void DilatingFilter();
    void AllocateObjects();
    void Kmeans();
    void ShowKmeansStatistics();
private:

    Mat matsrc;
    Mat duplicateMatSrc;
    Ui::MainWindow *ui;
    QStack<Mat> imgStack;
    QVector<Seed> seedVect;

    bool binarizated;
    void ClearForm();
    void BrightnessAdjust(Mat &srcImg, Mat &dstImg, float brightness);
    void ContrastAdjust(Mat &srcImg, Mat &dstImg, float contrast);
    float GetValidContrast(float );
    void showOnSrcLabel(Mat);
    void showOnGrayLabel(Mat);



    void calculateArea(Mat srcImg);
    void calculatePerimetr(Mat srcImg);
    void calculateCompactness();
    bool HaveBlackNeighbors(Mat srcImg, int x, int y);
    Scalar getColor(int cluster);
    void showClusters(Mat srcImg);
};

#endif // MAINWINDOW_H
