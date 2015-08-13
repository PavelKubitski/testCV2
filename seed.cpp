#include "seed.h"

Seed::Seed()
{
//    this->level = 0;
    this->area = 0;
    this->perimetr = 0;
    this->compactness = 0;
    this->cluster = -1;
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


