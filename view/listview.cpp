#include "../view/listview.h"
#include "../view/convertimage.h"


ListView::ListView(GeneriAlimentari* item, QWidget* parent):
    item(item),
    parent(parent)
{
    updateView();
}

void ListView::updateView(){
    QPixmap immagine=ConvertImage::getImage(item->getImmagine());
    setIcon(immagine);
    setText(QString::fromStdString(item->getInfo()));
}

GeneriAlimentari* ListView::getItem() const {return item;}
