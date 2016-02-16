#include "FeaturesCaculation.h"

FeaturesCalculation::FeaturesCalculation(Mat img, QVector<Seed> seedVector, Mat first)
{
    srcImg = img.clone();
    firstImg = first.clone();
    seedVect = QVector<Seed>(seedVector);
    calculateTextureGLCM();
//    GLCM = Mat::zeros(256, 256, CV_8UC1);
}

FeaturesCalculation::~FeaturesCalculation()
{

}

void FeaturesCalculation::calculateArea()
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

void FeaturesCalculation::calculatePerimetr()
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
                    if(HaveBlackNeighbors( x, y))
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

void FeaturesCalculation::calculateCompactness()
{
    double compact = 0;
    for(int i = 0; i < seedVect.length(); i++)
    {
        compact = seedVect[i].GetPerimetr()*seedVect[i].GetPerimetr() / seedVect[i].GetArea();
        seedVect[i].SetCompactness(compact);
    }
}

bool FeaturesCalculation::HaveBlackNeighbors( int x, int y)
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

QVector<Seed> FeaturesCalculation::GetSeedVector()
{
    return seedVect;
}

void FeaturesCalculation::calculateLumaParametre(Mat srcImage)
{
    Mat channel[3], YCRImage;
    cvtColor(srcImage, YCRImage, COLOR_BGR2YCrCb);

    split(YCRImage, channel);
    imshow("luma", channel[0]);

    int oldLuma, i, oldPixel;

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

                            oldLuma = s.GetLuma();
                            int l = channel[0].at<uchar>(y, x);
                            seedVect[i].SetLuma(oldLuma + l);
                            oldPixel = s.GetCountOfPixels();
                            seedVect[i].SetCountOfPixels(oldPixel+1);
                            break;
                        }
                        i++;
                    }
                }
            }
       }
    float luma = 0;
    for(int k = 0; k < seedVect.length(); k++)
    {
        luma = seedVect[k].GetLuma() / seedVect[k].GetCountOfPixels();
        seedVect[k].SetLuma(luma);
        luma = 0;
    }

}

void FeaturesCalculation::calculateTextureGLCM()
{
    int leftP = 0, rightP = 0;
    int count;
    Mat gray = Mat::zeros(srcImg.size(), CV_8UC1);
    cvtColor(firstImg, gray, CV_BGR2GRAY);
    imshow("srcImg",srcImg);
    imshow("gray", gray);
    imshow("firstImg", firstImg);
    for( int y = 0; y < srcImg.rows; y++ )
       {
            for( int x = 0; x < srcImg.cols; x++ )
            {

                //printf("p(%d,%d)[%d][%d][%d]\n",y,x, srcImg.at<Vec3b>(y,x)[0],srcImg.at<Vec3b>(y,x)[1],srcImg.at<Vec3b>(y,x)[2]);
                if(!(srcImg.at<Vec3b>(y,x)[0] == 0 &&
                        srcImg.at<Vec3b>(y,x)[1] == 0 &&
                        srcImg.at<Vec3b>(y,x)[2] == 0))
                {
                    int i = 0;
                    for(Seed s: seedVect)
                    {

                        if((s.GetColor().val[0] == srcImg.at<Vec3b>(y,x)[0] &&
                           s.GetColor().val[1] == srcImg.at<Vec3b>(y,x)[1] &&
                           s.GetColor().val[2] == srcImg.at<Vec3b>(y,x)[2]) &&
                                !(srcImg.at<Vec3b>(y,x+1)[0] == 0 &&
                                 srcImg.at<Vec3b>(y,x+1)[1] == 0 &&
                                 srcImg.at<Vec3b>(y,x+1)[2] == 0 ))
                        {

                            leftP = gray.at<uchar>(y,x)/8;
                            rightP = gray.at<uchar>(y,x+1)/8;


                            count = seedVect[i].GLCM.at<uchar>(leftP, rightP);
                            count++;
                            seedVect[i].GLCM.at<uchar>(leftP, rightP) = count;

                        }
                        i++;
                    }

                }
            }
    }


    for(int k = 0; k < seedVect.length(); k++)
    {
        for(int i=0; i< seedVect[k].GLCM.rows; i++)
            for(int j=0; j< seedVect[k].GLCM.cols; j++)
            {
                if(seedVect[k].GLCM.at<uchar>(i,j) != 0)
                    seedVect[k].countOfPairs++;
            }

    }


    for(int k = 0; k < seedVect.length(); k++)
    {
        createGLCM(k);
    }



}


void FeaturesCalculation::createGLCM(int indexOfSeed)
{
    if(!srcImg.empty())
    {
        Mat GLCMtrasposed = Mat::zeros(32, 32, CV_8UC1);
        Mat GLCMsymmetric = Mat::zeros(32, 32, CV_8UC1);

//        imshow("glcm1", seedVect[indexOfSeed].GLCM);

        for(int i=0; i< seedVect[indexOfSeed].GLCM.rows; i++)
            for(int j=0; j< seedVect[indexOfSeed].GLCM.cols; j++)
            {
                GLCMtrasposed.at<uchar>(j,i) = seedVect[indexOfSeed].GLCM.at<uchar>(i,j);
            }
//        QString str = QString::number(indexOfSeed);
//        imshow("glcmTrance " + str.toStdString(), GLCMtrasposed);
        for(int i=0; i<seedVect[indexOfSeed].GLCM.rows; i++)
            for(int j=0; j<seedVect[indexOfSeed].GLCM.cols; j++)
            {
                GLCMsymmetric.at<uchar>(i,j) = (seedVect[indexOfSeed].GLCM.at<uchar>(i,j) + GLCMtrasposed.at<uchar>(i,j));//  countOfPairs;
//                printf("%f ", GLCMsymmetric.at<float>(i,j));
            }

        seedVect[indexOfSeed].GLCM = GLCMsymmetric;
//        QString str = QString::number(indexOfSeed);
//        imshow("glcm2 "+str.toStdString(), seedVect[indexOfSeed].GLCM);
    }
}


void FeaturesCalculation::calculateContrast()
{
    calculateParametr(CONTRAST);
}


void FeaturesCalculation::calculateHomogeneity()
{
   calculateParametr(HOMOGENEITY);
}

void FeaturesCalculation::calculateDissimilarity()
{
    calculateParametr(DISSIMILARITY);
}

void FeaturesCalculation::calculateEntropy()
{
    calculateParametr(ENTROPY);
}

void FeaturesCalculation::calculateEnergy()
{
    calculateParametr(ENERGY);
}

void FeaturesCalculation::calculateCorrelation()
{
    calculateParametr(CORRELATION);
}


void FeaturesCalculation::calculateParametr(PARAMETR param)
{
    float qrt = 0, fabs = 0, thigmaSqr = 0, U = 0;
    for(int k = 0; k < seedVect.length(); k++)
    {
        for(int i=0; i< seedVect[k].GLCM.rows; i++)
            for(int j=0; j< seedVect[k].GLCM.cols; j++)
            {
                switch (param) {
                case DISSIMILARITY:
                {
                    qrt = qPow(i-j,2);
                    fabs = qSqrt(qrt);
                    seedVect[k].dissimilarity += fabs*seedVect[k].GLCM.at<uchar>(i,j);
                }
                break;
                case ENERGY:
                {
                    seedVect[k].energy += qPow(seedVect[k].GLCM.at<uchar>(i,j),2);
                }
                break;
                case ENTROPY:
                {
                    if (seedVect[k].GLCM.at<uchar>(i,j) != 0)
                    {
//                        float ln = -qLn(seedVect[k].GLCM.at<uchar>(i,j));
                        seedVect[k].entropy += -qLn(seedVect[k].GLCM.at<uchar>(i,j)) * seedVect[k].GLCM.at<uchar>(i,j);
                    }
//                    printf("ln = %f, char =%d entropy = %f\n", ln, seedVect[k].GLCM.at<uchar>(i,j), seedVect[k].entropy);
                }
                break;
                case HOMOGENEITY:
                {
                    qrt = qPow(i-j,2);
                    if(qrt != 1)
                        seedVect[k].homogeneity += (1/(1-qPow(i-j,2)))*seedVect[k].GLCM.at<uchar>(i,j);
                }
                break;
                case CONTRAST:
                {
                    int pixel = seedVect[k].GLCM.at<uchar>(i,j);
                    float dividing = pixel;
                    float qrt = qPow(i-j, 2);
                    float contr = qrt * dividing;

                    seedVect[k].contrast += contr;
                }
                break;
                case CORRELATION:
                {
                    calculateUandThigma(k, U, thigmaSqr);
                    seedVect[k].correlation += seedVect[k].GLCM.at<uchar>(i,j)*(i-U)*(j-U) / thigmaSqr;
                }
                break;
                }

            }


        switch (param) {
        case DISSIMILARITY:
            seedVect[k].dissimilarity = seedVect[k].dissimilarity / (seedVect[k].countOfPairs);
            break;
        case HOMOGENEITY:
            seedVect[k].homogeneity = seedVect[k].homogeneity / (seedVect[k].countOfPairs);
            break;
        case CONTRAST:
            seedVect[k].contrast = seedVect[k].contrast/(seedVect[k].countOfPairs);
            break;
        case ENERGY:
            seedVect[k].energy = seedVect[k].energy / (seedVect[k].countOfPairs);
            break;
        case ENTROPY:
            seedVect[k].entropy = seedVect[k].entropy / (seedVect[k].countOfPairs);
            break;
        case CORRELATION:
            seedVect[k].correlation = seedVect[k].correlation / (seedVect[k].countOfPairs);
        default:
            break;
        }



    }
}

void FeaturesCalculation::calculateUandThigma(int index, float &U, float &thigmaSqr)
{
    for(int i=0; i< seedVect[index].GLCM.rows; i++)
        for(int j=0; j< seedVect[index].GLCM.cols; j++)
        {
            U += seedVect[index].GLCM.at<uchar>(i,j)*i;
        }
    U = U / seedVect[index].countOfPairs;

    for(int i=0; i< seedVect[index].GLCM.rows; i++)
        for(int j=0; j< seedVect[index].GLCM.cols; j++)
        {
            thigmaSqr += seedVect[index].GLCM.at<uchar>(i,j)*(i-U)*(i-U);
        }
    thigmaSqr = thigmaSqr / seedVect[index].countOfPairs;
}

