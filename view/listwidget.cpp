#include "../view/listwidget.h"

#include <QScrollBar>


ListWidget::ListWidget(QWidget* parent):
    parent(parent)
{
    setIconSize(QSize(350,350));
    addScrollBarWidget(new QScrollBar(Qt::Orientation::Vertical,parent), Qt::AlignRight);
}



void ListWidget::aggiungiAlCarrello(GeneriAlimentari *generialimentari){
    ListView* item=new ListView(generialimentari, parent);
    addItem(item);
}


ListView* ListWidget::currentItem() const {
    ListView* item= static_cast<ListView*>(QListWidget::currentItem());
    return item;
}

ListView* ListWidget::takeItem(int i){
    ListView* item=static_cast<ListView*>(QListWidget::takeItem(i));
    return item;
}

