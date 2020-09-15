#ifndef CONVERTIMAGE_H
#define CONVERTIMAGE_H

#include <QPixmap>

using std::string;


//classe per la conversione delle immagini, da codifica in 64 bit a png
class ConvertImage{
public:
    ConvertImage();

    static QPixmap getImage(const string&);

};





#endif // CONVERTIMAGE_H
