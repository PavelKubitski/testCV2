#include "seed.h"

Seed::Seed()
{
//    this->level = 0;
    area = 0;
    perimetr = 0;
    compactness = 0;
    cluster = -10;
    countOfFeatures = 3;
    luma = 0;
    countOfPixels = 0;
    GLCM = Mat::zeros(32, 32, CV_8UC1);
    countOfPairs = 0;
    contrast = 0;
    homogeneity = 0;
    dissimilarity = 0;
    entropy = 0;
    energy = 0;
    correlation = 0;
    countOfPixelsOnLevel = new int[256];
    memset(countOfPixelsOnLevel, 0, 256*sizeof(int));
    matExpect = 0;
    dispersion = 0;
    centerMass = Point(0,0);
    elongation = 0;
//    for(int i = 0; i < 256; i++)
//    {
//        printf("%d ", countOfPixelsOnLevel[i]);
//    }
//    printf("\n");
}

Seed::~Seed()
{

}

//void Seed::SetLevel(int level)
//{
//    this->level = level;
//}

//int Seed::GetLevel()
//{
//    return this->level;
//}

void Seed::SetArea(int area)
{
    this->area = area;
}

int Seed::GetArea()
{
    return area;
}

void Seed::SetColor(Scalar color)
{
    this->color = color;
    //this->color.val[1] = color.val[1];
    //this->color.val[2] = color.val[2];
    //this->color.val[4] = color.val[4];
}

Scalar Seed::GetColor()
{
    return color;
}

void Seed::SetPerimetr(int perim)
{
    this->perimetr = perim;
}

int Seed::GetPerimetr()
{
    return perimetr;
}

void Seed::SetCompactness(double comp)
{
    this->compactness = comp;
}

double Seed::GetCompactness()
{
    return compactness;
}

void Seed::SetCluster(int clust)
{
    this->cluster = clust;
}

int Seed::GetCluster()
{
    return cluster;
}

int Seed::GetCountOfFeatures()
{
    return countOfFeatures;
}

void Seed::SetLuma(int luma)
{
    this->luma = luma;
}

int Seed::GetLuma()
{
    return luma;
}


void Seed::SetCountOfPixels(int countOfPixels)
{
    this->countOfPixels = countOfPixels;
}

int Seed::GetCountOfPixels()
{
    return countOfPixels;
}
