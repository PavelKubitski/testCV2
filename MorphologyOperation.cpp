#include "MorphologyOperation.h"
#include <QtCore/qmath.h>
#include <opencv2/core/core.hpp>

MorphologyOperation::MorphologyOperation(QObject *parent) : QObject(parent)
{

}

MorphologyOperation::~MorphologyOperation()
{

}

void MorphologyOperation::findEdgeChains(Mat img)
{

    int i,j, e = 25;
    int whites = 0,black = 0, edges = 0;
    Mat dst = img.clone();
    for(i=e; i<img.rows-e; i++)
    {
        for(j=e; j<img.cols-e; j++)
        {

            if(img.at<uchar>(i, j) == 255)
            {
                if(pixelArea(img, i, j) > 5 && pixelArea(img, i, j) < 17) //17 for r = 4
                {
                    dst.at<uchar>(i, j) = 127;
                }
            }



        }
    }


    uniteEndPoinds(dst);
//    imshow("q", dst);
}

int MorphologyOperation::pixelArea(Mat img, int i, int j)
{

    int whites = 0,black = 0, r = 4, height = 0;

    for (int x = -r; x < r ; x++)
    {
        height = (int)qSqrt(r * r - x * x);

        for (int y = -height; y < height; y++)
        {
            img.at<uchar>(x + i, y + j) == 255 ? whites++: black++;

        }
    }

    return whites;
}


void MorphologyOperation::grayPixelInArea(Mat img, int i, int j)
{
    vector<Point> grayPoints;
    int r = 6, height = 0;

    for (int x = -r; x < r ; x++)
    {
        height = (int)qSqrt(r * r - x * x);

        for (int y = -height; y < height; y++)
        {
            if(img.at<uchar>(x + i, y + j) == 127)
            {
                Point point(x + i, y + j);
                grayPoints.push_back(point);
                img.at<uchar>(x + i, y + j) = 255;
            }
        }
    }
//    imshow("endPoint1", img);
    int xLength = 0, yLength = 0;
    for(int k = 0; k < grayPoints.size(); k++)
    {
        xLength += grayPoints[k].x;
        yLength += grayPoints[k].y;
    }

    xLength /= grayPoints.size();
    yLength /= grayPoints.size();

    img.at<uchar>(xLength, yLength) = 50;
//    imshow("endPoint2", img);


}



void MorphologyOperation::uniteEndPoinds(Mat img)
{
    int e = 25, i , j;
    for(i=e; i<img.rows-e; i++)
    {
        for(j=e; j<img.cols-e; j++)
        {
            if(img.at<uchar>(i, j) == 127)
            {
                 grayPixelInArea(img, i, j);
//                 break;
            }
        }
    }
}

//int MorphologyOperation::pixelsOnArc(Mat img, int i, int j)
//{

//    int whites = 0,black = 0, r = 4, height = 0;
//    int y;
//    for (int x = -r; x < r ; x++)
//    {
//        height = (int)qSqrt(r * r - x * x);


//        img.at<uchar>(x + i, j + height) == 255 ? whites++: black++;
//        img.at<uchar>(x + i, j + height) == 255 ? whites++: black++;

//    }

//    return whites;
//}




