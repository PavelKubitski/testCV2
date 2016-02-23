#ifndef ROCDIALOG_H
#define ROCDIALOG_H

#include <QDialog>
#include <seed.h>
#include <qvector.h>
#include <qstring.h>
#include <qcustomplot.h>
#include <vector>
#include <QVector>
#include <iosfwd>
#include <fstream>
#include <qalgorithms.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Ui {
class ROCDialog;
}

using namespace std;

class ROCDialog : public QDialog
{
    Q_OBJECT
    QVector<double> TP; //roc true positives
    QVector<double> FP; //roc false positive
    QVector<double> TP2; //roc true positives
    QVector<double> FP2; //roc false positive
    QVector<QPair<float, float> > a1;
    QVector<QPair<float, float> > a2;
    QVector<QPair<float,int> > data;
public:
    explicit ROCDialog(QString fileName, QVector<Seed> seedVect, QWidget *parent = 0);
    ~ROCDialog();
    QString fileName;
    QVector<Seed> seedVector;

    void calculateROCparemeters();
    void ROCforCluster(int *labels);
    void drawRocCurve(int posclass);
private:
    Ui::ROCDialog *ui;
    void makePlot();
    void getROCFromData(QVector<QPair<float, int> > data);
    double calcAUC(int *labels, double *scores, int n, int posclass);
    void smoothing(QVector<QPair<float, float> > &a);
    double trapezoidArea(double X1, double X2, double Y1, double Y2);
};

#endif // ROCDIALOG_H
