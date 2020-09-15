#include "../view/menu.h"

Menu::Menu(QWidget* parent):
    parent(parent),
    menu(new QMenu("File", this)),
    loadCarrello(new QAction("Carica Carrello", menu)),
    esci(new QAction("Esci", menu)),
    ricerca(new QAction("Cerca", parent)),
    carrello(new QAction("Carrello", parent))

{
    QList<QAction*> action;
    action.push_back(loadCarrello);
    action.push_back(esci);

    menu->addActions(action);
    action.clear();

    addMenu(menu);
    addAction(ricerca);
    addAction(carrello);



    connect(loadCarrello,SIGNAL(triggered()),parent,SLOT(slotLoadCarrello()));
    connect(esci,SIGNAL(triggered()),parent,SLOT(close()));
    connect(ricerca,SIGNAL(triggered()),parent,SLOT(slotMostraRicerca()));
    connect(carrello,SIGNAL(triggered()),parent,SLOT(slotMostraCarrello()));
}



QMenu *Menu::getMenu() const {return menu;}

QAction *Menu::getLoadCarrello() const {return loadCarrello;}

QAction *Menu::getEsci() const {return esci;}
