#include "ChooseFeaturesWindow.h"
#include "ui_ChooseFeaturesWindow.h"

ChooseFeaturesWindow::ChooseFeaturesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseFeaturesWindow)
{
    ui->setupUi(this);
    features = QVector<int>();
}

ChooseFeaturesWindow::~ChooseFeaturesWindow()
{
    delete ui;
}


bool ChooseFeaturesWindow::areaBoxChecked()
{
    return ui->areaCheckBox->isChecked();
}


bool ChooseFeaturesWindow::perimetrBoxChecked()
{
    return ui->perimetrCheckBox->isChecked();
}

bool ChooseFeaturesWindow::compactnessBoxChecked()
{
    return ui->compactnessCheckBox->isChecked();
}

bool ChooseFeaturesWindow::lumaBoxChecked()
{
    return ui->lumaCheckBox->isChecked();
}


void ChooseFeaturesWindow::on_okButton_clicked()
{
    if (ui->areaCheckBox->isChecked())
        features.push_back(AREA);
    if (ui->compactnessCheckBox->isChecked())
        features.push_back(COMPACTNESS);
    if (ui->perimetrCheckBox->isChecked())
        features.push_back(PERIMETR);
    if (ui->lumaCheckBox->isChecked())
        features.push_back(LUMA);
    this->hide();
}
