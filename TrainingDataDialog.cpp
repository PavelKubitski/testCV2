#include "TrainingDataDialog.h"
#include "ui_TrainingDataDialog.h"


QVector<QVector<int> > TrainingDataDialog::getTrainDataObjsVectrs() const
{
    return trainDataObjsVectrs;
}


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

    showActiveGroupBox();
    countOfThirds = 0;

    trainDataObjsVectrs = QVector<QVector<int> >(countOfClusters);

    this->allocObjMat = allocObjMat.clone();
    this->srcImg = srcImg.clone();
    countOfObjsInCluster = 0;
    float cols = this->srcImg.cols;
    float rows = this->srcImg.rows;
    int width = ui->matDisplayLabel->width();
    float div =  cols / rows ;
    int height = width / div;
    ui->matDisplayLabel->setFixedSize(width, height);
    showOnSrcLabel(this->srcImg);
    countOfObjsInGrBox = 3;
    currentCluster = 0;
//    printf("label x = %d, y = %d\n", ui->matDisplayLabel->width(), ui->matDisplayLabel->height());
//    printf("srcimg x = %d, y = %d", this->srcImg.cols, this->srcImg.rows);
}

void TrainingDataDialog::showActiveGroupBox()
{
    if(countOfClusters == 3)
    {
        ui->Cluster3GroupBox->setHidden(false);
    }
    if(countOfClusters == 4)
    {
        ui->Cluster4GroupBox->setHidden(false);
    }
    if(countOfClusters == 5)
    {
        ui->Cluster4GroupBox->setHidden(false);
    }
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

    static QVector<int> trainObjForCluster;

    imgX = imgX * srcImg.cols;
    imgY = imgY * srcImg.rows;


    for(int i = 0; i < seedVect.length(); i++)
    {
        if(     allocObjMat.at<Vec3b>(imgY, imgX)[0] == seedVect[i].GetColor().val[0] &&
                allocObjMat.at<Vec3b>(imgY, imgX)[1] == seedVect[i].GetColor().val[1] &&
                allocObjMat.at<Vec3b>(imgY, imgX)[2] == seedVect[i].GetColor().val[2])
        {

            if(isEnoughObjForCluster(currentCluster))
            {
                currentCluster++;
                countOfObjsInCluster = 0;
            }
            countOfObjsInCluster++;
            trainDataObjsVectrs[currentCluster].push_back(i);
            fillLabels(i);

            contourDetection(seedVect[i].GetColor());
            showOnSrcLabel(this->srcImg);

            if(countOfObjsInCluster % countOfObjsInGrBox == 0)
            {
                setCheckForCheckBox(currentCluster,true);
                currentCluster++;
                countOfObjsInCluster = 0;
            }

            break;
        }
    }

}

void TrainingDataDialog::setCheckForCheckBox(int cluster, bool state)
{
    switch (cluster) {
    case 0:
    {
        ui->cluster1checkBox->setChecked(state);
        ui->cluster1checkBox->setEnabled(false);
    }
        break;
    case 1:
    {
        ui->cluster2checkBox->setChecked(state);
        ui->cluster2checkBox->setEnabled(false);
    }
        break;
    case 2:
    {
        ui->cluster3checkBox->setChecked(state);
        ui->cluster3checkBox->setEnabled(false);
    }
        break;
    case 3:
    {
        ui->cluster4checkBox->setChecked(state);
        ui->cluster4checkBox->setEnabled(false);
    }
        break;
    case 4:
    {
        ui->cluster5checkBox->setChecked(state);
        ui->cluster5checkBox->setEnabled(false);
    }
        break;
    default:
        break;
    }
}

bool TrainingDataDialog::isEnoughObjForCluster(int cluster)
{
    bool state = false;
    switch (cluster+1) {
    case 1:
    {
        if(ui->cluster1checkBox->isChecked())
        {
            state = true;
            ui->cluster1checkBox->setEnabled(false);
        }
    }
        break;
    case 2:
    {
        if(ui->cluster2checkBox->isChecked())
        {
            state = true;
            ui->cluster2checkBox->setEnabled(false);
        }
    }
        break;
    case 3:
    {
        if(ui->cluster3checkBox->isChecked())
        {
            state = true;
            ui->cluster3checkBox->setEnabled(false);
        }
    }
        break;
    case 4:
    {
        if(ui->cluster4checkBox->isChecked())
        {
            state = true;
            ui->cluster4checkBox->setEnabled(false);
        }
    }
        break;
    case 5:
    {
        if(ui->cluster5checkBox->isChecked())
        {
            state = true;
            ui->cluster5checkBox->setEnabled(false);
        }
    }
        break;
    default:
        break;
    }
    return state;
}


void TrainingDataDialog::contourDetection(Scalar sc)
{


    Scalar color = getColor( currentCluster);
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
                    srcImg.at<Vec3b>(y, x)[0] = srcImg.at<Vec3b>(y, x+1)[0] = srcImg.at<Vec3b>(y, x+2)[0] = srcImg.at<Vec3b>(y, x+3)[0] = color.val[2];
                    srcImg.at<Vec3b>(y, x)[1] = srcImg.at<Vec3b>(y, x+1)[1] = srcImg.at<Vec3b>(y, x+2)[1] = srcImg.at<Vec3b>(y, x+3)[1] = color.val[1];
                    srcImg.at<Vec3b>(y, x)[2] = srcImg.at<Vec3b>(y, x+1)[2] = srcImg.at<Vec3b>(y, x+2)[2] = srcImg.at<Vec3b>(y, x+3)[2] = color.val[0];
                }
            }
        }
    }
}


void TrainingDataDialog::fillLabels(int numberOfObject)
{
    switch (currentCluster*countOfObjsInGrBox + countOfObjsInCluster-1) {
    case 0:
        ui->label->setText(QString::number(numberOfObject));
        break;
    case 1:
        ui->label_2->setText(QString::number(numberOfObject));
        break;
    case 2:
        ui->label_3->setText(QString::number(numberOfObject));
        break;
    case 3:
        ui->label_4->setText(QString::number(numberOfObject));
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
//    if((trainDataObjsVectrs.length() <= countOfClusters))
//    {
//        if(countOfClusters == trainDataObjsVectrs.length())
//        {
//            if (trainDataObjsVectrs[countOfClusters-1].length() < countOfObjsInGrBox)
//            {
//                colorOfСircuit(pos);

//            }
//        } else if(trainDataObjsVectrs.length() < countOfClusters)
//        {
//            colorOfСircuit(pos);
//        }

//    }

    if(!isAllCheckBoxAreChecked())
        colorOfСircuit(pos);
}

bool TrainingDataDialog::isAllCheckBoxAreChecked()
{
    bool state = true;
    if(!ui->cluster1checkBox->isChecked())
        state = false;
    if(!ui->cluster2checkBox->isChecked())
        state = false;
    if(!ui->cluster3checkBox->isChecked())
        state = false;
    if(!ui->cluster4checkBox->isChecked())
        state = false;
    if(!ui->cluster5checkBox->isChecked())
        state = false;
    return state;
}

void TrainingDataDialog::on_okButton_clicked()
{
    emit trainingDataReady();
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

void TrainingDataDialog::on_denyButton_clicked()
{
    this->trainDataObjsVectrs.clear();
    emit trainingDataReady();
    this->close();

}





