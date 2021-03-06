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
#include <MorphologyOperation.h>
#include <SVMclassifier.h>
#include <FeaturesCaculation.h>
#include <ChooseFeaturesWindow.h>
#include <TrainingDataDialog.h>
#include <ROCDialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum ColorSystem { CMYK, HSV, HLS, LAB, NONE };
    vector<Mat> CSvector;     //CS - color system
    vector<Mat> CSvectorColored;

    ColorSystem lastColorSystem;
    int currentIndex;
    Mat matsrc;
    Mat duplicateMatSrc;
    Mat firstImage;
    Ui::MainWindow *ui;
    QStack<Mat> imgStack;
    QStack<Mat> imgBinaryStack;
    QVector<Seed> seedVect;
    QVector<Seed> seedVectorOldVertion;
    bool binarizated;
    QString fileName;

    ChooseFeaturesWindow *featuresWindow;
    TrainingDataDialog *trainingDataWindow;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CalculateFeatures(Mat drawing);

    void setEnabledAfterCSButtonClicked(bool state);
public slots:
    void OpenPicture();
    void ToGrayScale();
    void ChangeBrightness();
    void ChangeContrast();
    void AdaptiveThreshold();
    void AdaptiveThresholdOtsu();
    void MedianFilter();
    void DenyFilter();
    void ErodeFilter();
    void ClosingFilter();
    void DilatingFilter();
    void AllocateObjects();
    void OpeningFilter();

    void ShowClassificationStatistics();
    void ChangeColorSystemRGBtoCMYK();
    void ChangeColorSystemRGBtoHSV();
    void ChangeColorSystemRGBtoHLS();
    void ChangeColorSystemRGBtoLab();
    void MorphologySkeleton();
    void ClassificationSVM();
    void StartClassification();

private slots:
    void on_grayScaleCheckBox_clicked();
    void on_featuresButton_clicked();

    void on_tryAgainClassifButton_clicked();

    void on_denyButton_clicked();

    void on_denyBinarizationButton_clicked();

private:


    void ClearForm();
    void BrightnessAdjust(Mat &srcImg, Mat &dstImg, float brightness);
    void ContrastAdjust(Mat &srcImg, Mat &dstImg, float contrast);
    float GetValidContrast(float );
    void showOnSrcLabel(Mat);
    void showOnGrayLabel(Mat, QString title);
    void ChangeColorSystemRGBtoAnother(ColorSystem cs, QString systemName);
    void DeleteAllTabs();

    int main1();
    void rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk);



    bool HaveBlackNeighbors(Mat srcImg, int x, int y);
    Scalar getColor(int cluster);
    void showClusters(Mat srcImg);

    void setEnabledButtonsAfterChoosingFeatures(bool state);
    void setEnabledAfterFilterButtonClicked(bool state);
    void setEnabledAfterGrayScaleButtonClicked(bool state);
};

#endif // MAINWINDOW_H
