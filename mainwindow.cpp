#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ImageLabelForm.h"

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

//connecting to trainingDatawindow in ClassificationSVM

    //ui signals
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
    connect(ui->kmeansButton, SIGNAL(clicked()), this , SLOT(ClassificationSVM()));
    connect(ui->CMYKButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoCMYK()));
    connect(ui->HSVButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoHSV()));
    connect(ui->HLSButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoHLS()));
    connect(ui->LABButton, SIGNAL(clicked()), this, SLOT(ChangeColorSystemRGBtoLab()));
    connect(ui->closingButton, SIGNAL(clicked()), this, SLOT(ClosingFilter()));
    connect(ui->openingButton, SIGNAL(clicked()), this, SLOT(OpeningFilter()));
    connect(ui->otsuButton, SIGNAL(clicked()), this, SLOT(AdaptiveThresholdOtsu()));
    connect(ui->skeletonButton, SIGNAL(clicked()), this, SLOT(MorphologySkeleton()));
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
//    nameOfOpenFile = QFileDialog::getOpenFileName(this,
//                                        tr("Open File"), QDir::currentPath(),tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    nameOfOpenFile = "bob, rice, corn.png";
//    nameOfOpenFile = "sds.png";


    if(!nameOfOpenFile.isEmpty())
    {
            nameOfFile = nameOfOpenFile.toUtf8().constData();

            ClearForm();
            matsrc = imread(nameOfFile);
            firstImage = matsrc.clone();
//            matsrc = imread("bean.jpg");

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

//    ToGrayScale();
//    AdaptiveThresholdOtsu();
}





void MainWindow::ToGrayScale()
{
    if(lastColorSystem != NONE)
    {
        matsrc = CSvector[ui->tabWidget->currentIndex()].clone();
//        imshow("gray", matsrc);
        showOnGrayLabel(matsrc, "Grayscale");
    }
    else
    {
//        imshow("gray", matsrc);
        Mat gray = Mat::zeros(matsrc.size(), matsrc.type());
        if(!matsrc.empty())
        {
            cvtColor(matsrc, gray, CV_BGR2GRAY);
            matsrc = gray.clone();
            showOnGrayLabel(matsrc, "Grayscale");
            imgStack.clear();
        }
        else
        {
            QMessageBox::information(this, tr("To gray scale"), tr("Image is not downloaded"));
        }
        gray.release();
    }
}

void MainWindow::ClearForm()
{
    //matsrc = null;
    binarizated = false;
    matsrc.release();
    duplicateMatSrc.release();
    ui->srcImageLabel->clear();
    DeleteAllTabs();
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
    ui->CMYKButton->setEnabled(true);
    ui->HSVButton->setEnabled(true);
    ui->HLSButton->setEnabled(true);
    ui->LABButton->setEnabled(true);
    ui->openingButton->setEnabled(true);
    ui->closingButton->setEnabled(true);
    ui->grayScaleCheckBox->setEnabled(true);
    ui->otsuButton->setEnabled(true);
    ui->clusterTableWidget->clear();

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

void MainWindow::showOnGrayLabel(Mat image, QString title)
{
    DeleteAllTabs();
    ImageLabelForm *imgLbl = new ImageLabelForm();
    imgLbl->setImage(image);
    ui->tabWidget->insertTab(ui->tabWidget->count(), imgLbl, QIcon(QString("")), (QString)title);
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
            showOnGrayLabel(duplicateMatSrc, "Binarization");
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




void MainWindow::AdaptiveThresholdOtsu()
{
    if(!matsrc.empty())
    {
        if(matsrc.channels() == 1)
        {
            ui->toGrayScaleButton->setEnabled(false);
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            GaussianBlur(matsrc, dst, Size(5,5),0);
//            threshold(dst, matsrc, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
            threshold(dst, matsrc, 0, 255, CV_THRESH_OTSU);
            bitwise_not (matsrc, matsrc);
            duplicateMatSrc = matsrc.clone();

            showOnGrayLabel(duplicateMatSrc, "Otsu binarization");

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

void MainWindow::MorphologySkeleton()
{
    if(!matsrc.empty())
    {
//        if(matsrc.channels() == 1)
//        if(matsrc != NULL)
        {
            ui->toGrayScaleButton->setEnabled(false);

            Mat copyMat = matsrc.clone();

            cv::Mat skel(matsrc.size(), CV_8UC1, cv::Scalar(0));
            cv::Mat temp(matsrc.size(), CV_8UC1);
            cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
            bitwise_not(matsrc, matsrc);
            showOnGrayLabel(matsrc, "Morphology skeleton");
//            imshow("matsrc first", matsrc);

            bool done;
            do
            {
              cv::morphologyEx(matsrc, temp, cv::MORPH_OPEN, element);
              cv::bitwise_not(temp, temp);
              cv::bitwise_and(matsrc, temp, temp);
              cv::bitwise_or(skel, temp, skel);
              cv::erode(matsrc, matsrc, element);

              double max;
              cv::minMaxLoc(matsrc, 0, &max);
              done = (max == 0);
            } while (!done);

//            cv::imshow("Skeleton", skel);

            matsrc = skel.clone();

            DilatingFilter();

//            imshow("opening filter", matsrc);

            MorphologyOperation::findEdgeChains(matsrc);

            addWeighted( copyMat, 0.5, skel, 0.5, 0.0, matsrc);
//            imshow("2", matsrc);
            duplicateMatSrc = matsrc.clone();

//            showOnGrayLabel(duplicateMatSrc);
//            showOnGrayLabel(matsrc);

            binarizated = true;
//            dst.release();
        }
//        else
//        {
//            QMessageBox::information(this, tr("Binarization"), tr("Your image must be in grayscale.\n Press button ToGrayScale."));
//        }
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
            setEnabledAfterFilterButtonClicked(false);
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
        setEnabledAfterFilterButtonClicked(false);
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

void MainWindow::setEnabledAfterFilterButtonClicked(bool state)
{
    ui->toGrayScaleButton->setEnabled(state);
    ui->adaptiveThresButton->setEnabled(state);
    ui->otsuButton->setEnabled(state);
    ui->grayScaleCheckBox->setEnabled(state);
    ui->CMYKButton->setEnabled(state);
    ui->HSVButton->setEnabled(state);
    ui->HLSButton->setEnabled(state);
    ui->LABButton->setEnabled(state);
}


void MainWindow::DilatingFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            setEnabledAfterFilterButtonClicked(false);
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

void MainWindow::ClosingFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            setEnabledAfterFilterButtonClicked(false);
            if(!duplicateMatSrc.empty())
            {
                matsrc = duplicateMatSrc.clone();
                duplicateMatSrc.release();
            }
            imgStack.push(matsrc);
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            int kSize = ui->circuitSpinBox->value();
            Mat element(kSize, kSize, CV_8U, Scalar(1));
            dilate(matsrc, dst, element);
            matsrc = dst.clone();
            erode(matsrc, dst, element);
            matsrc = dst.clone();
            showOnSrcLabel(matsrc);
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

void MainWindow::OpeningFilter()
{
    if(!matsrc.empty())
    {
        if(binarizated == true)
        {
            setEnabledAfterFilterButtonClicked(false);
            if(!duplicateMatSrc.empty())
            {
                matsrc = duplicateMatSrc.clone();
                duplicateMatSrc.release();
            }
            imgStack.push(matsrc);
            Mat dst = Mat::zeros(matsrc.size(), matsrc.type());
            int kSize = ui->openingSpinBox->value();
            Mat element(kSize, kSize, CV_8U, Scalar(1));
            erode(matsrc, dst, element);
            matsrc = dst.clone();
            dilate(matsrc, dst, element);
            matsrc = dst.clone();
            showOnSrcLabel(matsrc);
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
//                matsrc = duplicateMatSrc.clone();
//                duplicateMatSrc.release();
            }


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


            CalculateFeatures(drawing);


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

void MainWindow::setEnabledButtonsAfterChoosingFeatures(bool state)
{
    ui->toGrayScaleButton->setEnabled(state);
    ui->adaptiveThresButton->setEnabled(state);
    ui->medianFilterButton->setEnabled(state);
    ui->maxFilterButton->setEnabled(state);
    ui->minFilterButton->setEnabled(state);
    ui->denyFilterButton->setEnabled(state);
    ui->openingButton->setEnabled(state);
    ui->closingButton->setEnabled(state);
}

void MainWindow::CalculateFeatures(Mat drawing)
{
    FeaturesCalculation calculator(drawing, seedVect, firstImage);

//    if(featuresWindow->areaBoxChecked() && !featuresWindow->compactnessBoxChecked())
    calculator.calculateArea();

    if(featuresWindow->perimetrBoxChecked() && !featuresWindow->compactnessBoxChecked())
        calculator.calculatePerimetr();
    if(featuresWindow->compactnessBoxChecked())
    {
//        calculator.calculateArea();
        calculator.calculatePerimetr();
        calculator.calculateCompactness();
    }
    if(featuresWindow->lumaBoxChecked())
        calculator.calculateLumaParameter(firstImage);
    if(featuresWindow->contrastBoxChecked())
        calculator.calculateContrast();
    if(featuresWindow->homogeneityBoxChecked())
        calculator.calculateHomogeneity();
    if(featuresWindow->dissimilarityBoxChecked())
        calculator.calculateDissimilarity();
    if(featuresWindow->correlationBoxChecked())
        calculator.calculateCorrelation();
    if(featuresWindow->entropyBoxChecked())
        calculator.calculateEntropy();
    if(featuresWindow->energyBoxChecked())
        calculator.calculateEnergy();


    calculator.calculateMatExpectation();

    if(featuresWindow->dispertionBoxChecked())
        calculator.calculateDispertion();

    calculator.calculateMassCenter();

    if(featuresWindow->elongationBoxChecked())
        calculator.calculateElongation();



    seedVect = calculator.GetSeedVector();
//    for(int i = 0; i < 256; i++)
//    {
//        printf("%d ", seedVect[0].countOfPixelsOnLevel[i]);
//    }

//    for(int i = 0; i < seedVect.length(); i++)
//        printf("%f\n", seedVect[i].elongation);
//    for(int i =0; i<seedVect.length(); i++)
//        cout << "area = " <<seedVect[i].GetArea() <<" luma = " <<seedVect[i].GetLuma() << " matexp = " << seedVect[i].matExpect
//             <<" centre = " <<seedVect[i].centerMass << " ellong = " << seedVect[i].elongation << "\n ";
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

}



void MainWindow::ShowClassificationStatistics()
{
//    QStandardItemModel *model = new QStandardItemModel(ui->clusterSpinBox->value(),2,this); //2 Rows and 2 Columns
//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Object")));
//    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Percentage")));
//    ui->clusterTableWidget->setModel(model);

////    double allSeeds = 0;
    QVector<int> clusters(ui->clusterSpinBox->value(), 0);

    for(Seed s: seedVect)
    {
        clusters[s.GetCluster()]++;
//        allSeeds++;
    }

//    for(int i = 0; i < ui->clusterSpinBox->value(); i++)
//    {
//        QStandardItem *item = new QStandardItem();
//        QStandardItem *itemText = new QStandardItem();
////        itemText->setText(QString::number((clusters[i]*100)/allSeeds) + "%");
//        itemText->setText(QString::number(clusters[i]));
//        item->setData(QColor(getColor(i).val[0], getColor(i).val[1], getColor(i).val[2]), Qt::BackgroundRole);
//        model->setItem(i,0,item);
//        model->setItem(i,1,itemText);
//    }

    ui->clusterTableWidget->setRowCount(ui->clusterSpinBox->value());
    ui->clusterTableWidget->setColumnCount(2);
    for(int i = 0; i < ui->clusterSpinBox->value(); i++)
    {
        QTableWidgetItem *itemText = new QTableWidgetItem(QString::number(clusters[i]));
        QTableWidgetItem *itemColor = new QTableWidgetItem();
        itemColor->setData( Qt::BackgroundRole, QColor(getColor(i).val[0], getColor(i).val[1], getColor(i).val[2]));
        ui->clusterTableWidget->setItem(i,0,itemColor);
        ui->clusterTableWidget->setItem(i,1 , itemText);
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
    ChangeColorSystemRGBtoAnother(CMYK ,"CMYK");
}

void MainWindow::ChangeColorSystemRGBtoHSV()
{
    ChangeColorSystemRGBtoAnother(HSV ,"HSV");
}

void MainWindow::ChangeColorSystemRGBtoHLS()
{
    ChangeColorSystemRGBtoAnother(HLS ,"HLS");
}

void MainWindow::ChangeColorSystemRGBtoLab()
{
    ChangeColorSystemRGBtoAnother(LAB , "LAB");
}


void MainWindow::ChangeColorSystemRGBtoAnother(ColorSystem cs, QString systemName)
{
    DeleteAllTabs();
    CSvector.clear();
    CSvectorColored.clear();
    lastColorSystem = cs;

    switch (cs) {
    case CMYK:
        CSvectorColored = ColorSystemConverter::rgb2cmyk(this->matsrc, CSvector);
        break;
    case HSV:
        CSvectorColored = ColorSystemConverter::rgb2hsv(this->matsrc, CSvector);
        break;
    case HLS:
        CSvectorColored = ColorSystemConverter::rgb2hls(this->matsrc, CSvector);
        break;
    case LAB:
        CSvectorColored = ColorSystemConverter::rgb2lab(this->matsrc, CSvector);
        break;
    default:
        break;
    }

    for(int i = 0; i < (int)CSvector.size(); i++)
    {
        ImageLabelForm *imgLbl = new ImageLabelForm();
        if(ui->grayScaleCheckBox->isChecked())
            imgLbl->setImage(CSvectorColored[i]);
        else
            imgLbl->setImage(CSvector[i]);
        ui->tabWidget->insertTab(ui->tabWidget->count(), imgLbl, QIcon(QString("")), (QString)systemName[i]);
    }

    ui->tabWidget->setCurrentIndex(0);

}


void MainWindow::DeleteAllTabs()
{
    while (ui->tabWidget->count() != 0)
    {
        ui->tabWidget->removeTab(0);
    }
}


void MainWindow::on_grayScaleCheckBox_clicked()
{
    currentIndex = ui->tabWidget->currentIndex();
    static const char * EnumStrings[] = { "CMYK", "HSV", "HLS", "LAB" };
    ChangeColorSystemRGBtoAnother(lastColorSystem, EnumStrings[lastColorSystem]);
    ui->tabWidget->setCurrentIndex(currentIndex);
}

void MainWindow::ClassificationSVM()
{
    trainingDataWindow = new TrainingDataDialog(seedVect, ui->clusterSpinBox->value(), matsrc, firstImage);
    trainingDataWindow->show();
    connect(trainingDataWindow, SIGNAL(trainingDataReady()), this, SLOT(StartClassification()));
}

void MainWindow::StartClassification()
{

    QVector<QVector<int> > trainingData = trainingDataWindow->getTrainDataObjsVectrs();
    if(!trainingData.empty())
    {

        QVector<int> feat = featuresWindow->features;

        SVMclassifier svm(seedVect, feat, ui->clusterSpinBox->value(), trainingData);
        svm.FillTrainingMat();
        seedVect = svm.GetSeedVector();

        showClusters(matsrc);
        ShowClassificationStatistics();


    } else {
        QMessageBox::information(this, tr("Classification"), tr("Need training data, click on \"SVM\" button again"));
    }
    if(trainingData.length() < ui->clusterSpinBox->value())
    {
        QMessageBox::information(this, tr("Classification"), tr("Need more training data, click on \"SVM\" button again"));
    }
    for(int i=0;i<trainingData.length(); i++)
    {
        if(trainingData[i].length() == 0)
        {
            QMessageBox::information(this, tr("Classification"), tr("Need more training data in cluster № %1, click on \"SVM\" button again").arg(i));
        }
    }

}


void MainWindow::on_featuresButton_clicked()
{
//    imshow("matsrc", matsrc);
    seedVectorOldVertion = QVector<Seed>(seedVect);
    duplicateMatSrc = matsrc.clone();
//    imshow("duplicateMatSrc", duplicateMatSrc);
    featuresWindow = new ChooseFeaturesWindow();
    setEnabledButtonsAfterChoosingFeatures(false);
    featuresWindow->show();
}

void MainWindow::on_tryAgainClassifButton_clicked()
{
    matsrc = duplicateMatSrc.clone();
//    imshow("matsrc2", matsrc);
//    imshow("duplicateMatSrc2", duplicateMatSrc);
    seedVect = QVector<Seed>(seedVectorOldVertion);
    showOnSrcLabel(matsrc);
}
