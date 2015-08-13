#ifndef SEED_H
#define SEED_H
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

class Seed
{
public:
    Seed();
    ~Seed();

//    void SetLevel(int level);
    //int GetLevel();
    void SetArea(int area);
    int GetArea();
    void SetColor(Scalar color);
    Scalar GetColor();
    void SetPerimetr(int perim);
    int GetPerimetr();
    void SetCompactness(double comp);
    double GetCompactness();
    void SetCluster(int clust);
    int GetCluster();
private:

    Scalar color;
    int area;
    int perimetr;
    double compactness;
    int cluster;
};

#endif // SEED_H
