#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    brightnessUsed = false;
//    contrastUsed = false;
    binarizated = false;
    ui->srcImageLabel->setStyleSheet("QLabel { background-color : white;}");
    ui->grayImageLabel->setStyleSheet("QLabel { background-color : white;}");
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(OpenPicture()));
    connect(ui->toGrayScaleButton, SIGNAL(clicked()), this, SLOT(ToGrayScale()));

    connect(ui->customContrSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ChangeContrast()));
    connect(ui->customSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ChangeBrightness()));
    connect(ui->adaptiveThresButton, SIGNAL(clicked()), this, SLOT(AdaptiveThreshold()));
    connect(ui->medianFilterButton, SIGNAL(clicked()), this, SLOT(MedianFilter()));
    connect(ui->denyFilterButton, SIGNAL(clicked()), this, SLOT(DenyFilter()));
    connect(ui->minFilterButton, SIGNAL(clicked()), this, SLOT(ErodeFilter()));
    connect(ui->maxFilterButton, SIGNAL(clicked()), this, SLOT(DilatingFilter()));
    connect(ui->allocateObjButton, SIGNAL(clicked()), this, SLOT(AllocateObjects()));
    connect(ui->kmeansButton, SIGNAL(clicked()), this , SLOT(Kmeans()));
    connect(ui->CMYKButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoCMYK()));
    connect(ui->HSVButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoHSV()));
    connect(ui->HLSButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoHLS()));
    connect(ui->LABButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoLab()));
}

MainWindow::~MainWindow()
{
    matsrc.release();
    duplicateMatSrc.release();
    delete ui;
}

void MainWindow::OpenPicture()
{
    QString nameOfOpenFile;
    String nameOfFile;
    nameOfOpenFile = QFileDialog::getOpenFileName(this,
                                        tr("Open File"), QDir::currentPath(),tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if(!nameOfOpenFile.isEmpty())
    {
            nameOfFile = nameOfOpenFile.toUtf8().constData();

            ClearForm();
            matsrc = imread(nameOfFile);

            if(!matsrc.empty())
            {
//                imgStack.push(matsrc);
                showOnSrcLabel(matsrc);
            }
            else
            {
                QMessageBox::information(this, tr("Loading image"), tr("Can't load %1.").arg(nameOfOpenFile));
            }
    }
}

void MainWindow::ToGrayScale()
{

    Mat gray = Mat::zeros(matsrc.size(), matsrc.type());
    if(!matsrc.empty())
    {
        cvtColor(matsrc, gray, CV_BGR2GRAY);
        matsrc = gray.clone();
        QImage imageView = ImageConverter::MatToQImage(matsrc);
        ui->grayImageLabel->setPixmap(QPixmap::fromImage(imageView));
        ui->grayImageLabel->setScaledContents(true);
        imgStack.clear();
    }
    else
    {
        QMessageBox::information(this, tr("To gray scale"), tr("Image is not downloaded"));
    }
    gray.release();
}

void MainWindow::ClearForm()
{
    //matsrc = null;
    binarizated = false;
    matsrc.release();
    duplicateMatSrc.release();
    ui->srcImageLabel->clear();
    ui->grayImageLabel->clear();
    imgStack.clear();
    seedVect.clear();
    ui->blockSizeSpinBox->setValue(145);
    ui->cSpinBox->setValue(9);
    ui->customContrSpinBox->setValue(0);
    ui->customSpinBox->setValue(0);
    ui->medianSpinBox->setValue(3);
    ui->toGrayScaleButton->setEnabled(true);
    ui->adaptiveThresButton->setEnabled(true);
    ui->medianFilterButton->setEnabled(true);
    ui->maxFilterButton->setEnabled(true);
    ui->minFilterButton->setEnabled(true);
    ui->denyFilterButton->setEnabled(true);
    ui->allocateObjButton->setEnabled(true);
    ui->customSpinBox->setEnabled(true);
    ui->customContrSpinBox->setEnabled(true);
}

void MainWindow::BrightnessAdjust ( Mat &srcImg, Mat &dstImg, float brightness)
{
    // пробегаемся по всем пикселям изображения
    for( int y = 0; y < srcImg.rows; y++ )
       {
            for( int x = 0; x < srcImg.cols; x++ )
            {
                for( int c = 0; c < 3; c++ )
                {
                    dstImg.at<Vec3b>(y,x)[c] =
                             saturate_cast<uchar>(  srcImg.at<Vec3b>(y,x)[c]  + brightness );
                }
            }
       }
}

void MainWindow::ContrastAdjust ( Mat &srcImg, Mat &dstImg, float contrast)
{
        for( int y = 0; y < srcImg.rows; y++ )
           {
                for( int x = 0; x < srcImg.cols; x++ )
                {
                    for( int c = 0; c < 3; c++ )
                    {
                        dstImg.at<Vec3b>(y,x)[c] =
                                 saturate_cast<uchar>(  srcImg.at<Vec3b>(y,x)[c]*contrast );
                    }
                }
           }
}

void MainWindow::ChangeBrightness()
{
    if(!matsrc.empty())
    {
        ui->customContrSpinBox->setEnabled(false);
        Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
        //float bright = ui->brightnesslSlider->value();
//        float bright = ui->brightnessSpinBox->value()*10;
        float bright = ui->customSpinBox->GetNextStep();

        if(ui->customSpinBox->value() == 0)
        {
            ui->customContrSpinBox->setEnabled(true);
        }

        if(ui->customSpinBox->GetDirection() == 1)
        {
            imgStack.push(matsrc);
            BrightnessAdjust(matsrc, dst, bright);
            matsrc = dst.clone();
//            brightnessUsed = true;
//            contrastUsed = false;
        }
        else
        {
            matsrc = imgStack.pop();
        }
        ui->customSpinBox->SetOldValue(ui->customSpinBox->value());
        showOnSrcLabel(matsrc);
        dst.release();
    }
}

void MainWindow::ChangeContrast()
{
    float contrast;
    if(!matsrc.empty())
    {
        ui->customSpinBox->setEnabled(false);
        Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
//      contrast = GetValidContrast(ui->contrastSlider->value());
//        contrast = GetValidContrast(ui->contrastSpinBox->value());
        contrast = GetValidContrast(ui->customContrSpinBox->value());
        if(ui->customContrSpinBox->value() == 0)
        {
            ui->customSpinBox->setEnabled(true);
        }

        if(ui->customContrSpinBox->GetDirection() == 1)
        {
            imgStack.push(matsrc);
            ContrastAdjust(matsrc, dst, contrast);
            matsrc = dst.clone();           
//            contrastUsed = true;
//            brightnessUsed = false;
        }
        else
        {
                matsrc = imgStack.pop();
        }
        ui->customContrSpinBox->SetOldValue(ui->customContrSpinBox->value());
        //matsrc = dst.clone();
        showOnSrcLabel(matsrc);
        dst.release();
    }
}

void MainWindow::showOnSrcLabel(Mat matImage)
{
    QImage imageView = ImageConverter::MatToQImage(matImage);
    ui->srcImageLabel->setPixmap(QPixmap::fromImage(imageView));
    ui->srcImageLabel->setScaledContents(true);
}

void MainWindow::showOnGrayLabel(Mat image)
{
    QImage imageView = ImageConverter::MatToQImage(image);
    ui->grayImageLabel->setPixmap(QPixmap::fromImage(imageView));
    ui->grayImageLabel->setScaledContents(true);
}

float MainWindow::GetValidContrast(float contrast)
{
    if(contrast < 0)
    {
        contrast = -1/(contrast-1);
    } else if(contrast > 0)
    {
        contrast += 1;
    } else
    {
        contrast = 1;
    }
    return contrast;
}

void MainWindow::AdaptiveThreshold()
{
    if(!matsrc.empty())
    {
        if(matsrc.channels() == 1)
        {
            ui->toGrayScaleButton->setEnabled(false);
            int blockSize = ui->blockSizeSpinBox->value();
            int constantC = ui->cSpinBox->value();
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            adaptiveThreshold(matsrc, dst, 255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constantC);
            duplicateMatSrc = dst.clone();
            showOnGrayLabel(duplicateMatSrc);
            binarizated = true;
            dst.release();
        }
        else
        {
            QMessageBox::information(this, tr("Binarization"), tr("Your image must be in grayscale.\n Press button ToGrayScale."));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Adaptive threshold"), tr("Image is not downloaded"));
    }
}

void MainWindow::MedianFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            if(!duplicateMatSrc.empty())
            {
                matsrc = duplicateMatSrc.clone();
                duplicateMatSrc.release();
            }
            ui->adaptiveThresButton->setEnabled(false);
            imgStack.push(matsrc);
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            medianBlur(matsrc, dst, ui->medianSpinBox->value());
            matsrc = dst.clone();
            showOnSrcLabel(matsrc);
            dst.release();
        }
        else
        {
            QMessageBox::information(this, tr("Median filter"), tr("Image is not binarizated"));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Median filter"), tr("Image is not downloaded"));
    }
}

void MainWindow::DenyFilter()
{
    if(!imgStack.empty())
    {
        matsrc = imgStack.pop();
        showOnSrcLabel(matsrc);
    }
}

void MainWindow::ErodeFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
        ui->toGrayScaleButton->setEnabled(false);
        ui->adaptiveThresButton->setEnabled(false);
        if(!duplicateMatSrc.empty())
        {
            matsrc = duplicateMatSrc.clone();
            duplicateMatSrc.release();
        }
        imgStack.push(matsrc);
        Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
        int kSize = ui->minSpinBox->value();
        Mat element(kSize, kSize, CV_8U, Scalar(1));
        erode(matsrc, dst, element);
        matsrc = dst.clone();
        showOnSrcLabel(dst);
        dst.release();
        }
        else
        {
            QMessageBox::information(this, tr("Erode filter"), tr("Image is not binarizated"));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Erode filter"), tr("Image is not downloaded"));
    }
}

void MainWindow::DilatingFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            ui->toGrayScaleButton->setEnabled(false);
            ui->adaptiveThresButton->setEnabled(false);
            if(!duplicateMatSrc.empty())
            {
                matsrc = duplicateMatSrc.clone();
                duplicateMatSrc.release();
            }
            imgStack.push(matsrc);
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            int kSize = ui->maxSpinBox->value();
            Mat element(kSize, kSize, CV_8U, Scalar(1));
            dilate(matsrc, dst, element);
            matsrc = dst.clone();
            showOnSrcLabel(dst);
            dst.release();
        }
        else
        {
            QMessageBox::information(this, tr("Dilating filter"), tr("Image is not binarizated"));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Dilating filter"), tr("Image is not downloaded"));
    }
}

void MainWindow::AllocateObjects()
{

    RNG rng(12345);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            if(!duplicateMatSrc.empty())
            {
                matsrc = duplicateMatSrc.clone();
                duplicateMatSrc.release();
            }
            ui->toGrayScaleButton->setEnabled(false);
            ui->adaptiveThresButton->setEnabled(false);
            ui->medianFilterButton->setEnabled(false);
            ui->maxFilterButton->setEnabled(false);
            ui->minFilterButton->setEnabled(false);
            ui->denyFilterButton->setEnabled(false);

            findContours( matsrc, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0) );

            Mat drawing = Mat::zeros( matsrc.size(), CV_8UC3 );
            for( int i = 0; i < (int)contours.size(); i++ )
            {
               Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
               drawContours( drawing, contours, i, color, CV_FILLED, 8, hierarchy, 0, Point() );
               Seed s;
               s.SetColor(color);
               seedVect.append(s);
            }

            showOnSrcLabel(drawing);

            calculateArea(drawing);
            calculatePerimetr(drawing);
            calculateCompactness();
            matsrc = drawing.clone();
            drawing.release();
        }
        else
        {
            QMessageBox::information(this, tr("Allocate"), tr("Image is not binarizated"));
        }
    }
    else
    {
        QMessageBox::information(this, tr("Allocate objects"), tr("Image is not downloaded"));
    }
}

void MainWindow::calculateArea(Mat srcImg)
{
    int oldArea, i;

    for( int y = 0; y < srcImg.rows; y++ )
       {
            for( int x = 0; x < srcImg.cols; x++ )
            {
                if(!(srcImg.at<Vec3b>(y,x)[0] == 0 &&
                        srcImg.at<Vec3b>(y,x)[1] == 0 &&
                        srcImg.at<Vec3b>(y,x)[2] == 0))
                {
                    i = 0;
                    for(Seed s: seedVect)
                    {

                        if(s.GetColor().val[0] == srcImg.at<Vec3b>(y,x)[0] &&
                           s.GetColor().val[1] == srcImg.at<Vec3b>(y,x)[1] &&
                           s.GetColor().val[2] == srcImg.at<Vec3b>(y,x)[2])
                        {

                            oldArea = s.GetArea();
                            seedVect[i].SetArea(oldArea+1);
                            break;
                        }
                        i++;
                    }
                }
            }
       }
}

void MainWindow::calculatePerimetr(Mat srcImg)
{
    int oldPerimetr, i;

    for( int y = 0; y < srcImg.rows; y++ )
       {
            for( int x = 0; x < srcImg.cols; x++ )
            {
                if(!(srcImg.at<Vec3b>(y,x)[0] == 0 &&
                        srcImg.at<Vec3b>(y,x)[1] == 0 &&
                        srcImg.at<Vec3b>(y,x)[2] == 0))
                {
                    if(HaveBlackNeighbors(srcImg, x, y))
                    {
                        i = 0;
                        for(Seed s: seedVect)
                        {

                            if(s.GetColor().val[0] == srcImg.at<Vec3b>(y,x)[0] &&
                               s.GetColor().val[1] == srcImg.at<Vec3b>(y,x)[1] &&
                               s.GetColor().val[2] == srcImg.at<Vec3b>(y,x)[2])
                            {
                                oldPerimetr = s.GetPerimetr();
                                seedVect[i].SetPerimetr(oldPerimetr+1);
                                break;
                            }
                            i++;
                        }
                    }
                }
            }
       }
}

void MainWindow::calculateCompactness()
{
    double compact = 0;
    for(int i = 0; i < seedVect.length(); i++)
    {
        compact = seedVect[i].GetPerimetr()*seedVect[i].GetPerimetr() / seedVect[i].GetArea();
        seedVect[i].SetCompactness(compact);
    }
}

bool MainWindow::HaveBlackNeighbors(Mat srcImg, int x, int y)
{
    if((srcImg.at<Vec3b>(y-1,x)[0] == 0 &&
            srcImg.at<Vec3b>(y-1,x)[1] == 0 &&
            srcImg.at<Vec3b>(y-1,x)[2] == 0) ||
            (srcImg.at<Vec3b>(y+1,x)[0] == 0 &&
             srcImg.at<Vec3b>(y+1,x)[1] == 0 &&
             srcImg.at<Vec3b>(y+1,x)[2] == 0) ||
            (srcImg.at<Vec3b>(y,x-1)[0] == 0 &&
            srcImg.at<Vec3b>(y,x-1)[1] == 0 &&
            srcImg.at<Vec3b>(y,x-1)[2] == 0) ||
            (srcImg.at<Vec3b>(y,x+1)[0] == 0 &&
             srcImg.at<Vec3b>(y,x+1)[1] == 0 &&
             srcImg.at<Vec3b>(y,x+1)[2] == 0))
    {
        return true;
    }
    else
    {
        return false;
    }

}

void MainWindow::Kmeans()
{
    if(!matsrc.empty())
    {
        if(seedVect.empty())
        {
            QMessageBox::information(this, tr("Allocate objects"), tr("Objects are not allocated"));
        }
        else
        {
            ui->allocateObjButton->setEnabled(false);
            int attribute = 3;
            Mat samples(seedVect.length(), attribute, CV_32F);
            for(int i = 0; i < seedVect.length(); i++)
            {
                samples.at<float>(i,0) = seedVect[i].GetArea();
                samples.at<float>(i,1) = seedVect[i].GetCompactness();
                samples.at<float>(i,2) = seedVect[i].GetPerimetr();
            }

              int clusterCount = ui->clusterSpinBox->value();
              Mat labels;
              int attempts = 5;
              Mat centers;
              kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );

              for(int i = 0 ;i < seedVect.length(); i++)
              {
                  int cluster_idx = labels.at<int>(i,0);
                  seedVect[i].SetCluster(cluster_idx);
              }
            showClusters(matsrc);
            ShowKmeansStatistics();
            samples.release();
            labels.release();
            centers.release();
        }
    }
    else
    {
        QMessageBox::information(this, tr("Allocate objects"), tr("Image is not downloaded"));
    }
    //showOnSrcLabel(matsrc);

}

void MainWindow::showClusters(Mat srcImg)
{
    int i;


    for( int y = 0; y < srcImg.rows; y++ )
       {
            for( int x = 0; x < srcImg.cols; x++ )
            {
                if(!(srcImg.at<Vec3b>(y,x)[0] == 0 &&
                        srcImg.at<Vec3b>(y,x)[1] == 0 &&
                        srcImg.at<Vec3b>(y,x)[2] == 0))
                {
                    i = 0;
                    for(Seed s: seedVect)
                    {

                        if(s.GetColor().val[0] == srcImg.at<Vec3b>(y,x)[0] &&
                           s.GetColor().val[1] == srcImg.at<Vec3b>(y,x)[1] &&
                           s.GetColor().val[2] == srcImg.at<Vec3b>(y,x)[2])
                        {
                            srcImg.at<Vec3b>(y,x)[0] = getColor(seedVect[i].GetCluster()).val[2];
                            srcImg.at<Vec3b>(y,x)[1] = getColor(seedVect[i].GetCluster()).val[1];
                            srcImg.at<Vec3b>(y,x)[2] = getColor(seedVect[i].GetCluster()).val[0];
                            break;
                        }
                        i++;
                    }
                }
            }
       }
    showOnSrcLabel(srcImg);
//    showOnGrayLabel(srcImg);
}




void MainWindow::ShowKmeansStatistics()
{
    QStandardItemModel *model = new QStandardItemModel(ui->clusterSpinBox->value(),2,this); //2 Rows and 2 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Object")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Percentage")));
    ui->clusterTableView->setModel(model);

    double allSeeds = 0;
    QVector<int> clusters(ui->clusterSpinBox->value(), 0);

    for(Seed s: seedVect)    
    {
        clusters[s.GetCluster()]++;
        allSeeds++;
    }

    for(int i = 0; i < ui->clusterSpinBox->value(); i++)
    {
        QStandardItem *item = new QStandardItem();
        QStandardItem *itemText = new QStandardItem();
        itemText->setText(QString::number((clusters[i]*100)/allSeeds) + "%");
        item->setData(QColor(getColor(i).val[0], getColor(i).val[1], getColor(i).val[2]), Qt::BackgroundRole);
        model->setItem(i,0,item);
        model->setItem(i,1,itemText);
    }
}


Scalar MainWindow::getColor(int cluster)
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


void MainWindow::ChangeColorSystemRGBtoCMYK()
{
    std::vector<cv::Mat> CMYKvector;
    Mat img = ColorSystemConverter::rgb2cmyk(this->matsrc, CMYKvector);
//    this->showOnGrayLabel(img);

//    main1();
}

void MainWindow::ChangeColorSystemRGBtoHSV()
{

    Mat img = ColorSystemConverter::rgb2hsv(this->matsrc);
//    this->showOnGrayLabel(img);
}

void MainWindow::ChangeColorSystemRGBtoHLS()
{

    Mat img = ColorSystemConverter::rgb2hls(this->matsrc);
//    this->showOnGrayLabel(img);
}

void MainWindow::ChangeColorSystemRGBtoLab()
{

    Mat img = ColorSystemConverter::rgb2lab(this->matsrc);
//    this->showOnGrayLabel(img);
}


void MainWindow::rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk) {
    // Allocate cmyk to store 4 componets
    for (int i = 0; i < 4; i++) {
        cmyk.push_back(cv::Mat(img.size(), CV_8UC1));
    }

    // Get rgb
    std::vector<cv::Mat> rgb;
    cv::split(img, rgb);

    // rgb to cmyk
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            float r = (int)rgb[2].at<uchar>(i, j) / 255.;
            float g = (int)rgb[1].at<uchar>(i, j) / 255.;
            float b = (int)rgb[0].at<uchar>(i, j) / 255.;
            float k = std::min(std::min(1- r, 1- g), 1- b);

            cmyk[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
            cmyk[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
            cmyk[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
            cmyk[3].at<uchar>(i, j) = k * 255.;
        }
    }

    int r = img.at<Vec3b>(0,0)[2];
    int g = img.at<Vec3b>(0,0)[1];
    int b = img.at<Vec3b>(0,0)[0];

    int c = cmyk[0].at<uchar>(0,0);
    int m = cmyk[1].at<uchar>(0,0);
    int y = cmyk[2].at<uchar>(0,0);
    int k = cmyk[3].at<uchar>(0,0);

    printf("r = %d, g = %d, b = %d", r, g, b);
    printf("c = %d, m = %d, y = %d, k = %d", c, m, y, k);


}

// Test rgb2cmyk function
int MainWindow::main1() {
    // TODO: change filename
    cv::Mat src = this->matsrc;
    std::vector<cv::Mat> dst;
    rgb2cmyk(src, dst);

    // Display results
    cv::imshow("src", src);
    cv::imshow("c", dst[0]);
    cv::imshow("m", dst[1]);
    cv::imshow("y", dst[2]);
    cv::imshow("k", dst[3]);


    return 0;
}


