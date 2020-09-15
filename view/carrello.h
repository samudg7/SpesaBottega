#ifndef CARRELLO_H
#define CARRELLO_H

#include "../view/listwidget.h"

#include <QPushButton>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>


class Carrello : public QWidget{
    Q_OBJECT

private:
    ListWidget* listaGeneriAlimentari;
    QLabel* labelPrezzo;
    QPushButton* buttonModifica;
    QPushButton* buttonElimina;

    QWidget* parent;


public:
    Carrello(QWidget* =nullptr);
    ~Carrello();
    ListWidget* getListaGeneriAlimentari() const;
    QLabel* getLabelPrezzo()const;
    QPushButton* getButtonModifica() const;
    QPushButton* getButtonElimina() const;


public slots:
    void slotSelectedItem(bool=true) const;

};
#endif // CARRELLO_H
