#ifndef IMAGEFILTERTHREAD_H
#define IMAGEFILTERTHREAD_H
#include<QThread>
#include<QImage>

class ImageFilterThread : QThread
{
public:
    ImageFilterThread(QImage image);
    void run();
private:
    QImage outImage;
};

#endif // IMAGEFILTERTHREAD_H
