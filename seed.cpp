#include "seed.h"

Seed::Seed()
{
//    this->level = 0;
    this->area = 0;
    this->perimetr = 0;
    this->compactness = 0;
    this->cluster = -1;
    this->countOfFeatures = 3;
    this->luma = 0;
    this->countOfPixels = 0;
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
