#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "../model/generialimentari.h"

#include <QListWidgetItem>


class ListView : public QListWidgetItem{
private:
    GeneriAlimentari* item;
    QWidget* parent;

public:
    ListView(GeneriAlimentari*, QWidget* = nullptr);
    GeneriAlimentari* getItem() const;
    void updateView();

};
#endif // LISTVIEW_H
