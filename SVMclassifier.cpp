#include "SVMclassifier.h"

SVMclassifier::SVMclassifier(QObject *parent) : QObject(parent)
{

}

SVMclassifier::~SVMclassifier()
{

}

SVMclassifier::SVMclassifier(QVector<Seed> seedVector, QVector<int> featVector) : QObject(0)
{
    seedVect = QVector<Seed>(seedVector);
    featVect = QVector<int>(featVector);
//    training_mat(seedVect.size(),seedVect[0].GetCountOfFeatures(), CV_32FC1);
//    training_mat = Mat(4, 2, CV_32FC1);


}

void SVMclassifier::FillTrainingMat()
{

    // Set up training data
    float labels[4] = {1.0, 1.0, -1.0, -1.0};
    Mat labelsMat(4, 1, CV_32FC1, labels);
// area, compactness, perimetr, luma
//    float trainingData[4][3] = {{4000, 9, 204}, {4300, 10, 210}, {8000, 16, 350}, {8500, 17, 320}};//beans
//    float trainingData[4][3] = {{1500, 9, 120, 110}, {1700, 10, 130, 120}, {250, 10, 50,}, {300, 12, 66}};//bob and rice
//    float trainingData[4][4] = {{1700, 9, 130, 110}, {1430, 10, 130, 120}, {1800, 11, 143, 24}, {1761, 11, 141, 42}};//sds
    float trainingData[4][3] = {{ 9, 130, 110}, { 10, 130, 120}, { 11, 143, 24}, { 11, 141, 42}};//sds
    Mat trainingDataMat(4, 3, CV_32FC1, trainingData);

    // Set up SVM's parameters
    CvSVMParams params;
    params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

    // Train the SVM
    CvSVM SVM;
    SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

    int featureLength = featVect.length();
    float object[featureLength];

    for(int i = 0; i < seedVect.length(); i++)
    {
        fillObject(object, i);
        Mat objectMat(1, featureLength, CV_32FC1, object);

        float response = SVM.predict(objectMat);

        printf("class %f\n", response);
    }
}

void SVMclassifier::fillObject(float *arr, int numberOfSeed)
{
    int l = 0;

    if((featVect.indexOf(AREA)) != -1)
        arr[l++] = seedVect[numberOfSeed].GetArea();
    if((featVect.indexOf(COMPACTNESS)) != -1)
        arr[l++] = seedVect[numberOfSeed].GetCompactness();
    if((featVect.indexOf(PERIMETR)) != -1)
        arr[l++] = seedVect[numberOfSeed].GetPerimetr();
    if((featVect.indexOf(LUMA)) != -1)
        arr[l++] = seedVect[numberOfSeed].GetLuma();
}






