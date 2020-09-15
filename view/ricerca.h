#ifndef RICERCA_H
#define RICERCA_H

#include "../view/listwidget.h"
#include "../view/modificagenerialimentari.h"
#include "../view/filterpanini.h"

#include <QPushButton>
#include <QLabel>


class Ricerca: public QWidget{
    Q_OBJECT

private:
    QLabel* labelRicerca;

    QPushButton* buttonPane;
    QPushButton* buttonSalumi;
    QPushButton* buttonLatticini;
    QPushButton* buttonGastronomiaVegetale;
    QPushButton* buttonPanini;
    QPushButton* buttonBevande;

    QPushButton* buttonAggiungi;
    QPushButton* buttonModifica;
    QPushButton* buttonReset;

    FilterPanini* dialogFilterPanini;
    ModificaGeneriAlimentari* dialogModificaGeneriAlimentari;
    ListWidget* listaGeneriAlimentari;

public:
    Ricerca(QWidget* =nullptr);

    QPushButton* getButtonPane() const;
    QPushButton* getButtonSalumi() const;
    QPushButton* getButtonLatticini() const;
    QPushButton* getButtonGastronomiaVegetale() const;
    QPushButton* getButtonPanini() const;
    QPushButton* getButtonBevande() const;

    QPushButton* getButtonAggiungi() const;
    QPushButton* getButtonModifica() const;
    QPushButton* getButtonReset() const;
    ListWidget* getListaGeneriAlimentari() const;


public slots:
    void slotResetRicerca() const;
    void slotSelectedItem(bool=true) const;

};

#endif // RICERCA_H
