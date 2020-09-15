#ifndef MODIFICAGENERIALIMENTARI_H
#define MODIFICAGENERIALIMENTARI_H

#include "../view/listview.h"

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>

class ModificaGeneriAlimentari: public QDialog{
    Q_OBJECT

private:
    ListView* generialimentariView;
    QPushButton* buttonClose;
    QPushButton* buttonSave;
    GeneriAlimentari* generialimentari;
    QSpinBox* spin;

public:
     ModificaGeneriAlimentari(ListView*, QWidget* = nullptr);

     QPushButton* getButtonSave()const;

public slots:
    void slotSave() const;

};

#endif // MODIFICAGENERIALIMENTARI_H

