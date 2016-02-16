#ifndef CHOOSEFEATURESWINDOW_H
#define CHOOSEFEATURESWINDOW_H

#include <QDialog>

enum FEATURES { AREA = 0, PERIMETR, COMPACTNESS, LUMA, CONTRAST, HOMOGENEITY, DISSIMILARITY, ENERGY, ENTROPY, CORRELATION };

namespace Ui {
class ChooseFeaturesWindow;
}

class ChooseFeaturesWindow : public QDialog
{
    Q_OBJECT

public:

    QVector<int> features;




    explicit ChooseFeaturesWindow(QWidget *parent = 0);
    ~ChooseFeaturesWindow();
    bool areaBoxChecked();
    bool perimetrBoxChecked();
    bool compactnessBoxChecked();
    bool lumaBoxChecked();
    bool contrastBoxChecked();
    bool homogeneityBoxChecked();
    bool dissimilarityBoxChecked();
    bool energyBoxChecked();
    bool entropyBoxChecked();
    bool correlationBoxChecked();
private slots:
    void on_okButton_clicked();

private:
    Ui::ChooseFeaturesWindow *ui;
};

#endif // CHOOSEFEATURESWINDOW_H
