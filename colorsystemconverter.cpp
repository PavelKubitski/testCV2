#include "ColorSystemConverter.h"


ColorSystemConverter::ColorSystemConverter(QObject *parent) : QObject(parent)
{

}

ColorSystemConverter::~ColorSystemConverter()
{

}

cv::Mat ColorSystemConverter::rgb2cmyk(cv::Mat& img, std::vector<cv::Mat>& cmyk) {

    Mat channel[4], src;

    for (int i = 0; i < 4; i++) {
        cmyk.push_back(cv::Mat(img.size(), CV_8UC1));
        channel[i] = Mat::eye(img.size(), CV_8UC1);
    }



    std::vector<cv::Mat> rgb;
    cv::split(img, rgb);

    for (int i = 0; i < img.rows; i++) {
          for (int j = 0; j < img.cols; j++) {
              float r = (int)rgb[2].at<uchar>(i, j) / 255.;
              float g = (int)rgb[1].at<uchar>(i, j) / 255.;
              float b = (int)rgb[0].at<uchar>(i, j) / 255.;
              float k = std::min(std::min(1- r, 1- g), 1- b);

//              cmyk[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
//              cmyk[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
//              cmyk[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
//              cmyk[3].at<uchar>(i, j) = k * 255.;
              uchar ch = channel[0].at<uchar>(i, j);
              channel[0].at<uchar>(i, j) = (1 - r - k) / (1 - k) * 255.;
              channel[1].at<uchar>(i, j) = (1 - g - k) / (1 - k) * 255.;
              channel[2].at<uchar>(i, j) = (1 - b - k) / (1 - k) * 255.;
              channel[3].at<uchar>(i, j) = k * 255.;
          }
    }

    bitwise_not(channel[0], channel[0]);      //что бы было как в фотошопе
    bitwise_not(channel[1], channel[1]);
    bitwise_not(channel[2], channel[2]);
    bitwise_not(channel[3], channel[3]);




//    imshow("c", channel[0]);
//    imshow("m", channel[1]);
//    imshow("y", channel[2]);
//    imshow("k", channel[3]);

    std::string hsv_labels[3] = {"[C]yan", "[M]agenta", "[Y]ellow"};
    double std_values[3][3] = {{255, 255, 0}, {255, 0, 255}, {0, 255, 255}};
    showChannels(img, channel, hsv_labels, std_values, COLOR_HSV2BGR, true);

    return src;
}


Mat ColorSystemConverter::rgb2hsv(Mat img)
{
    Mat hsv;
    Mat channel[3];
    cvtColor(img,hsv,CV_BGR2HSV);

    split(hsv, channel);

    std::string hsv_labels[3] = {"[H]ue", "[S]aturation", "[V]alue"};
    double std_values[3][3] = {{1, 255, 255}, {179, 1, 255}, {179, 0, 1}};
    showChannels(img, channel, hsv_labels, std_values, COLOR_HSV2BGR, false);

    return hsv;
}

Mat ColorSystemConverter::rgb2hls(Mat img)
{
    Mat hls;
    Mat channel[3];
    cvtColor(img,hls,CV_BGR2HLS);
    split(hls, channel);

    std::string hls_labels[3] = {"[H]ue", "[L]ightness", "[S]aturation"};
    double std_values[3][3] = {{1, 100, 50}, {179, 1, 255}, {179, 69, 1}};

    showChannels(img, channel, hls_labels, std_values, COLOR_HLS2BGR, false);

//    imshow("img", img);
//    imshow("hls", hls);
    return hls;
}

Mat ColorSystemConverter::rgb2lab(Mat img)
{
    Mat lab;
    Mat channel[3];
    cvtColor(img,lab,CV_BGR2Lab);
    split(lab, channel);
    std::string hsv_labels[3] = {"[L]uminance", "A (dimension)", "B (dimension)"};
    double std_values[3][3] = {{1, 127.5, 127.5}, {191.25, 1, 127.5}, {191.25, 127.5, 1}};
    showChannels(img, channel, hsv_labels, std_values, COLOR_Lab2BGR, false);
//    imshow("img", img);
//    imshow("lab", lab);
    return lab;
}

void ColorSystemConverter::showChannels(Mat inputImage, Mat channel[], std::string labels[], double scalar[][3], int convertBack, bool CMYK = false)
{
    Mat aux[3], outputImage;
    int limit = 3;
    if (CMYK) limit = 4;

    outputImage = Mat(inputImage.rows, inputImage.cols, inputImage.type());
    for(int i = 0; i < 3; i++)
    {
        // fill the base Mat with standard values based on CS143 from Brown
        aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][0];
        aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][1];
        aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][2];
        aux[i] = channel[i];
        // merge the channels back together
        merge(aux, 3, outputImage);
        // convert from output color space to BGR
        if (!CMYK)      cvtColor(outputImage, outputImage, convertBack);
        imshow(labels[i] + " (3-Channels)", outputImage);
    }

    if (CMYK)
    {
        imshow("K", channel[3]);
    }
}

void cmyk2rgb(const Mat & c,const Mat & m,const Mat & y,const Mat & k, Mat & rgb )
{
    rgb = Mat(c.size(), CV_8UC3);
    for ( size_t j=0;j<c.rows; j++ ) {
        for ( size_t i=0;i<c.rows; i++ ) {
            Vec3b & v = rgb.at<Vec3b>(i,j);
            uchar K = k.at<uchar>(i,j);
            v[2] = saturate_cast<uchar>(K - ((255 - c.at<uchar>(i,j))*K>>8));
            v[1] = saturate_cast<uchar>(K - ((255 - m.at<uchar>(i,j))*K>>8));
            v[0] = saturate_cast<uchar>(K - ((255 - y.at<uchar>(i,j))*K>>8));
        }
    }
}


