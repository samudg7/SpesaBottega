#ifndef WIDGET_H
#define WIDGET_H

#include "../view/ricerca.h"
#include "../view/carrello.h"
#include "../view/menu.h"
#include "../view/filterpanini.h"
#include "../model/model.h"

#include <QWidget>
#include <QVBoxLayout>



class Controller : public QWidget{
    Q_OBJECT
private:
    Model* model;
    Menu* menu;
    QHBoxLayout* layout;
    Ricerca* ricerca;
    Carrello* carrello;
    ModificaGeneriAlimentari* dialogModificaGeneriAlimentari;
    FilterPanini* dialogFilterPanini;

public:
    Controller(Model*, QWidget* =nullptr);
    ~Controller();
    Model* getModel();


public slots:
    void slotLoadData();
    void slotLoadCarrello();
    void slotMostraRicerca() const;
    void slotMostraCarrello() const;
    void slotRimuoviDalCarrello();
    void slotRicercaPane();
    void slotRicercaSalumi();
    void slotRicercaLatticini();
    void slotRicercaGastronomiaVegetale();
    void slotRicercaPanini();    
    void slotRicercaBevande();
    void slotFilterPanini();
    void slotResetRicerca() const;
    void slotModificaRicerca();
    void slotModificaCarrello();
    void slotAggiungiElemento();
    void slotLabelPrezzo()const;

};

#endif // WIDGET_H
