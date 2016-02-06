#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ImageConverter.h>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStack>
#include <QVector>
#include <seed.h>
#include "QStandardItemModel"
#include <ColorSystemConverter.h>

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
    void CircuitFilter();
    void DilatingFilter();
    void AllocateObjects();
    void OpeningFilter();
    void Kmeans();
    void ShowKmeansStatistics();
    void ChangeColorSystemRGBtoCMYK();
    void ChangeColorSystemRGBtoHSV();
    void ChangeColorSystemRGBtoHLS();
    void ChangeColorSystemRGBtoLab();
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

    int main1();
    void rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk);


    void calculateArea(Mat srcImg);
    void calculatePerimetr(Mat srcImg);
    void calculateCompactness();
    bool HaveBlackNeighbors(Mat srcImg, int x, int y);
    Scalar getColor(int cluster);
    void showClusters(Mat srcImg);
};

#endif // MAINWINDOW_H
