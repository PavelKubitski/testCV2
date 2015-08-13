#include "converter.h"

Converter::Converter(QObject *parent) : QObject(parent)
{

}

Converter::~Converter()
{

}

QImage*  Converter::IplImage2QImage(IplImage *iplImg)
{
int h = iplImg->height;
int w = iplImg->width;
int channels = iplImg->nChannels;
QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
char *data = iplImg->imageData;

for (int y = 0; y < h; y++, data += iplImg->widthStep)
{
    for (int x = 0; x < w; x++)
    {
        char r, g, b, a = 0;
        if (channels == 1)
        {
            r = data[x * channels];
            g = data[x * channels];
            b = data[x * channels];
        }
        else if (channels == 3 || channels == 4)
        {
            r = data[x * channels + 2];
            g = data[x * channels + 1];
            b = data[x * channels];
        }

        if (channels == 4)
        {
            a = data[x * channels + 3];
            qimg->setPixel(x, y, qRgba(r, g, b, a));
        }
        else
        {
            qimg->setPixel(x, y, qRgb(r, g, b));
        }
    }
}
    return qimg;
}


IplImage* Converter::Image2IplImage(const QImage * qImage)
{

    int width = qImage->width();
    int height = qImage->height();

    // Creates a iplImage with 3 channels

    IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++ )
        {
            QRgb color = qImage->pixel(x,y);
            cvSet2D(img,y,x,cvScalar(qBlue(color),qGreen(color),qRed(color),1));
        }
    }
    return img;
}

QImage Converter::MatToQImage( const Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
            //qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
}




