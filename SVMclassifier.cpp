#include "SVMclassifier.h"

SVMclassifier::SVMclassifier(QObject *parent) : QObject(parent)
{

}

SVMclassifier::~SVMclassifier()
{

}

SVMclassifier::SVMclassifier(QVector<Seed> seedVector) : QObject(0)
{
    seedVect = QVector<Seed>(seedVector);
//    training_mat(seedVect.size(),seedVect[0].GetCountOfFeatures(), CV_32FC1);
    training_mat = Mat(4, 2, CV_32FC1);
}

void SVMclassifier::FillTrainingMat()
{

    // Set up training data
    float labels[4] = {1.0, 1.0, -1.0, -1.0};
    Mat labelsMat(4, 1, CV_32FC1, labels);

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


    float object[3];

    for(int i = 0; i < seedVect.length(); i++)
    {
        float a = seedVect[i].GetArea();
        float c = seedVect[i].GetCompactness();
        float p = seedVect[i].GetPerimetr();
        float l = seedVect[i].GetLuma();

//        object[0] = a;
        object[0] = c;
        object[1] = p;
        object[2] = l;
        Mat objectMat(1, 3, CV_32FC1, object);

        float response = SVM.predict(objectMat);

        printf("%f %f %f %f class %f\n", a, c, p, l, response);
    }




}





//float** SVMclassifier::CalculateTrainingData()
//{
//    float trainingData[4][3] = {{4000, 9, 204}, {4300, 10, 210}, {8000, 16, 350}, {8500, 17, 320}};
//    return trainingData;
//}

