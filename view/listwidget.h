#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "../view/listview.h"

#include <QListWidget>
#include <QPushButton>


class ListWidget : public QListWidget{
    Q_OBJECT

private:
    QWidget* parent;

public:
    ListWidget(QWidget* = nullptr);
    void aggiungiAlCarrello(GeneriAlimentari*);

    //ridefinizione di due metodi di QListWidget
    ListView* currentItem() const;
    ListView* takeItem(int);
};

#endif // LISTWIDGET_H
