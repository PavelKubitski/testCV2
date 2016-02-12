#ifndef IMAGELABELFORM_H
#define IMAGELABELFORM_H

#include <QWidget>
#include <ImageConverter.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>


namespace Ui {
class ImageLabelForm;
}

class ImageLabelForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageLabelForm(QWidget *parent = 0);
    ~ImageLabelForm();
    void setImage(Mat image);

private:
    Ui::ImageLabelForm *ui;
};

#endif // IMAGELABELFORM_H
