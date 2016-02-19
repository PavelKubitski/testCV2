#include "TrainingDataDialog.h"
#include "ui_TrainingDataDialog.h"

TrainingDataDialog::TrainingDataDialog(QVector<Seed> seedVector, int countOfClusters, Mat allocObjMat, Mat srcImg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingDataDialog)
{
    ui->setupUi(this);
    connect(ui->matDisplayLabel, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(showMousePosition(QPoint&)));
    seedVect = QVector<Seed>(seedVector);
    this->countOfClusters = countOfClusters;
    ui->Cluster3GroupBox->hide();
    ui->Cluster4GroupBox->hide();
    ui->Cluster5GroupBox->hide();

    this->allocObjMat = allocObjMat.clone();
    this->srcImg = srcImg.clone();
    countOfObjs = 0;
    countOfThirds = 0;
    float cols = this->srcImg.cols;
    float rows = this->srcImg.rows;
    int width = ui->matDisplayLabel->width();
    float div =  cols / rows ;
    int height = width / div;
    ui->matDisplayLabel->setFixedSize(width, height);
    showOnSrcLabel(this->srcImg);

    printf("label x = %d, y = %d\n", ui->matDisplayLabel->width(), ui->matDisplayLabel->height());
    printf("srcimg x = %d, y = %d", this->srcImg.cols, this->srcImg.rows);
}

TrainingDataDialog::~TrainingDataDialog()
{
    delete ui;
}

void TrainingDataDialog::colorOfСircuit(QPoint &pos)
{
    float x = pos.x();
    float y = pos.y();

    float imgX = x/ui->matDisplayLabel->width();
    float imgY = y/ui->matDisplayLabel->height();

     imgX = imgX * srcImg.cols;
     imgY = imgY * srcImg.rows;
//    imshow("src", srcImg);
//    imshow("all", allocObjMat);
    for(int i = 0; i < seedVect.length(); i++)
    {
        int c1 = allocObjMat.at<Vec3b>(imgY, imgX)[0];
        int c2 = allocObjMat.at<Vec3b>(imgY, imgX)[1];
        int c3 = allocObjMat.at<Vec3b>(imgY, imgX)[2];
        printf(" %d %d %d = ",c3,c2,c1);
        printf("%f %f %f\n",seedVect[i].GetColor()[2],seedVect[i].GetColor()[1],seedVect[i].GetColor()[0]);
        if(     allocObjMat.at<Vec3b>(imgY, imgX)[0] == seedVect[i].GetColor().val[0] &&
                allocObjMat.at<Vec3b>(imgY, imgX)[1] == seedVect[i].GetColor().val[1] &&
                allocObjMat.at<Vec3b>(imgY, imgX)[2] == seedVect[i].GetColor().val[2])
        {
            fillLabels(i);
            contourDetection(seedVect[i].GetColor());
            countOfObjs++;
            showOnSrcLabel(this->srcImg);
            break;
        }
    }

}

void TrainingDataDialog::contourDetection(Scalar sc)
{


    Scalar color = getColor( (countOfObjs - countOfObjs % 3) /3);
    for( int y = 0; y < srcImg.rows; y++ )
    {
        for( int x = 0; x < srcImg.cols; x++ )
        {
            if( allocObjMat.at<Vec3b>(y, x)[0] == sc.val[0] &&
                allocObjMat.at<Vec3b>(y, x)[1] == sc.val[1] &&
                allocObjMat.at<Vec3b>(y, x)[2] == sc.val[2] )
            {
                if(HaveBlackNeighbors(x, y))
                {
                    srcImg.at<Vec3b>(y, x)[0] = srcImg.at<Vec3b>(y, x+1)[0] = color.val[2];
                    srcImg.at<Vec3b>(y, x)[1] = srcImg.at<Vec3b>(y, x+1)[1] = color.val[1];
                    srcImg.at<Vec3b>(y, x)[2] = srcImg.at<Vec3b>(y, x+1)[2] = color.val[0];
                }
            }
        }
    }
}


void TrainingDataDialog::fillLabels(int numberOfObject)
{
    switch (countOfObjs) {
    case 0:
        ui->label->setText(QString::number(numberOfObject));
        break;
    case 1:
        ui->label_2->setText(QString::number(numberOfObject));
        break;
    case 2:
        ui->label_3->setText(QString::number(numberOfObject));
        break;
    case 4:
        ui->label_5->setText(QString::number(numberOfObject));
        break;
    case 5:
        ui->label_6->setText(QString::number(numberOfObject));
        break;
    case 6:
        ui->label_7->setText(QString::number(numberOfObject));
        break;
    case 7:
        ui->label_8->setText(QString::number(numberOfObject));
        break;
    case 8:
        ui->label_9->setText(QString::number(numberOfObject));
        break;
    case 9:
        ui->label_10->setText(QString::number(numberOfObject));
        break;
    case 10:
        ui->label_11->setText(QString::number(numberOfObject));
        break;
    case 11:
        ui->label_12->setText(QString::number(numberOfObject));
        break;
    case 12:
        ui->label_13->setText(QString::number(numberOfObject));
        break;
    case 13:
        ui->label_14->setText(QString::number(numberOfObject));
        break;
    case 14:
        ui->label_15->setText(QString::number(numberOfObject));
        break;

    default:
        break;
    }
}


void TrainingDataDialog::showMousePosition(QPoint &pos)
{
    colorOfСircuit(pos);
//    ui->mouse_position_label->setText("x: " + QString::number(pos.x()) + "y: " + QString::number(pos.y()));
    printf( QString::number(pos.x()).toStdString().c_str());
    printf(" ");
    printf( QString::number(pos.y()).toStdString().c_str());
    printf("\n");
}

void TrainingDataDialog::on_okButton_clicked()
{
    this->close();
}

void TrainingDataDialog::showOnSrcLabel(Mat matImage)
{
    QImage imageView = ImageConverter::MatToQImage(matImage);
    ui->matDisplayLabel->setPixmap(QPixmap::fromImage(imageView));
    ui->matDisplayLabel->setScaledContents(true);
}

Scalar TrainingDataDialog::getColor(int cluster)
{
    if(cluster == 0)
        return Scalar(0,0,255);
    if(cluster == 1)
        return Scalar(255,0,0);
    if(cluster == 2)
        return Scalar(0,255,0);
    if(cluster == 3)
        return Scalar(200,200,200);
    if(cluster == 4)
        return Scalar(100,200,255);
    if(cluster == 5)
        return Scalar(100,255,20);
    if(cluster == 6)
        return Scalar(10,255,255);
    else
        return Scalar(255,255,255);
}

bool TrainingDataDialog::HaveBlackNeighbors( int x, int y)
{
    if((allocObjMat.at<Vec3b>(y-1,x)[0] == 0 &&
            allocObjMat.at<Vec3b>(y-1,x)[1] == 0 &&
            allocObjMat.at<Vec3b>(y-1,x)[2] == 0) ||
            (allocObjMat.at<Vec3b>(y+1,x)[0] == 0 &&
             allocObjMat.at<Vec3b>(y+1,x)[1] == 0 &&
             allocObjMat.at<Vec3b>(y+1,x)[2] == 0) ||
            (allocObjMat.at<Vec3b>(y,x-1)[0] == 0 &&
            allocObjMat.at<Vec3b>(y,x-1)[1] == 0 &&
            allocObjMat.at<Vec3b>(y,x-1)[2] == 0) ||
            (allocObjMat.at<Vec3b>(y,x+1)[0] == 0 &&
             allocObjMat.at<Vec3b>(y,x+1)[1] == 0 &&
             allocObjMat.at<Vec3b>(y,x+1)[2] == 0))
    {
        return true;
    }
    else
    {
        return false;
    }

}
