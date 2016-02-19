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
    Mat GLCM;
    int countOfPairs;
    float contrast;
    float homogeneity;
    float dissimilarity;
    float entropy;
    float energy;
    float correlation;
    int *countOfPixelsOnLevel;
    float matExpect;
    float dispersion;
    Point centerMass;
    double elongation;


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
//    void SetCountOfFeatures(int countOfFeatures);
    int GetCountOfFeatures();

    void SetLuma(int luma);
    int GetLuma();
    void SetCountOfPixels(int countOfPixels);
    int GetCountOfPixels();
private:

    Scalar color;
    int area;
    int perimetr;
    double compactness;
    int cluster;
    int countOfFeatures;
    int luma;
    int countOfPixels;


};

#endif // SEED_H
