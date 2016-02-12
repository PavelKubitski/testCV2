#include "ImageLabelForm.h"
#include "ui_ImageLabelForm.h"

ImageLabelForm::ImageLabelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageLabelForm)
{
    ui->setupUi(this);

}

ImageLabelForm::~ImageLabelForm()
{
    delete ui;
}



void ImageLabelForm::setImage(Mat image)
{
//    imshow("debug", image);
    QImage imageView = ImageConverter::MatToQImage(image);
    QPixmap qp = QPixmap::fromImage(imageView);
    if(!ui->ImageLabel)
    {
        printf("sd");
    }
    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageView));
    ui->ImageLabel->setScaledContents(true);

}
