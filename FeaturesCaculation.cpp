#include "FeaturesCaculation.h"

FeaturesCalculation::FeaturesCalculation(Mat img, QVector<Seed> seedVector)
{
    srcImg = img.clone();
    seedVect = QVector<Seed>(seedVector);
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















