#include "../view/convertimage.h"


#include <QByteArray>

ConvertImage::ConvertImage(){}

QPixmap ConvertImage::getImage(const string &string){
    QImage* image=new QImage;
    QByteArray array=QByteArray(string.data());
    image->loadFromData(QByteArray::fromBase64(array),"png");
    QPixmap pixmap=QPixmap::fromImage(*image);
    return pixmap.scaled(200,200,Qt::AspectRatioMode::KeepAspectRatio);
}






