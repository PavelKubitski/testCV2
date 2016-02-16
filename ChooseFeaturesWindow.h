#ifndef CHOOSEFEATURESWINDOW_H
#define CHOOSEFEATURESWINDOW_H

#include <QDialog>

enum FEATURES { AREA = 0, PERIMETR, COMPACTNESS, LUMA };

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
private slots:
    void on_okButton_clicked();

private:
    Ui::ChooseFeaturesWindow *ui;
};

#endif // CHOOSEFEATURESWINDOW_H
