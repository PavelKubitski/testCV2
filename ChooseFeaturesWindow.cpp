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

bool ChooseFeaturesWindow::contrastBoxChecked()
{
    return ui->contrastCheckBox->isChecked();
}

bool ChooseFeaturesWindow::homogeneityBoxChecked()
{
    return ui->homogeneityCheckBox->isChecked();
}

bool ChooseFeaturesWindow::dissimilarityBoxChecked()
{
    return ui->dissimilarityCheckBox->isChecked();
}

bool ChooseFeaturesWindow::energyBoxChecked()
{
    return ui->energyCheckBox->isChecked();
}

bool ChooseFeaturesWindow::entropyBoxChecked()
{
    return ui->entropyCheckBox->isChecked();
}

bool ChooseFeaturesWindow::correlationBoxChecked()
{
    return ui->correlationCheckBox->isChecked();
}

bool ChooseFeaturesWindow::matExpectBoxChecked()
{
    return ui->matExtectCheckBox->isChecked();
}

bool ChooseFeaturesWindow::dispertionBoxChecked()
{
    return ui->dispertionCheckBox->isChecked();
}

bool ChooseFeaturesWindow::elongationBoxChecked()
{
    return ui->elongationCheckBox->isChecked();
}


void ChooseFeaturesWindow::on_okButton_clicked()
{
    if (ui->areaCheckBox->isChecked())
        features.push_back(AREA);
    if (ui->perimetrCheckBox->isChecked())
        features.push_back(PERIMETR);
    if (ui->compactnessCheckBox->isChecked())
        features.push_back(COMPACTNESS);
    if (ui->elongationCheckBox->isChecked())
        features.push_back(ELONGATION);
    if (ui->lumaCheckBox->isChecked())
        features.push_back(LUMA);
    if (ui->contrastCheckBox->isChecked())
        features.push_back(CONTRAST);
    if (ui->homogeneityCheckBox->isChecked())
        features.push_back(HOMOGENEITY);
    if (ui->dissimilarityCheckBox->isChecked())
        features.push_back(DISSIMILARITY);
    if (ui->energyCheckBox->isChecked())
        features.push_back(ENERGY);
    if (ui->entropyCheckBox->isChecked())
        features.push_back(ENTROPY);
    if (ui->correlationCheckBox->isChecked())
        features.push_back(CORRELATION);
    if (ui->matExtectCheckBox->isChecked())
        features.push_back(MATEXPECT);
    if (ui->dispertionCheckBox->isChecked())
        features.push_back(DISPERTION);

    if(features.empty())
    {
        QMessageBox::information(this, tr("Classification"), tr("There is no features were chosen"));
    } else
    {
        this->hide();
    }
}
