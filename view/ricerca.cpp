#include "../view/ricerca.h"
#include "../controller/controller.h"


Ricerca::Ricerca(QWidget* parent):
    QWidget(parent),
    labelRicerca(new QLabel("Categorie \n",this)),

    buttonPane(new QPushButton("Pane",this)),
    buttonSalumi(new QPushButton("Salumi",this)),
    buttonLatticini(new QPushButton("Latticini",this)),
    buttonGastronomiaVegetale(new QPushButton("GastronomiaVegetale",this)),
    buttonPanini(new QPushButton("Panini",this)),
    buttonBevande(new QPushButton("Bevande",this)),

    buttonAggiungi(new QPushButton("Aggiungi al carrello",this)),
    buttonModifica(new QPushButton("Modifica quantità",this)),
    buttonReset(new QPushButton("Reset",this)),

    dialogFilterPanini(nullptr),
    dialogModificaGeneriAlimentari(nullptr),
    listaGeneriAlimentari(new ListWidget(this))
{

    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    listaGeneriAlimentari->setFixedWidth(460);

    buttonAggiungi->setEnabled(false);
    buttonModifica->setEnabled(false);
    buttonReset->setEnabled(false);

    mainLayout->addWidget(labelRicerca);

    QHBoxLayout* buttonCategorie = new QHBoxLayout();
    mainLayout->addLayout(buttonCategorie);
    buttonCategorie->addWidget(buttonPane);
    buttonCategorie->addWidget(buttonSalumi);
    buttonCategorie->addWidget(buttonLatticini);
    buttonCategorie->addWidget(buttonGastronomiaVegetale);
    buttonCategorie->addWidget(buttonPanini);
    buttonCategorie->addWidget(buttonBevande);

    mainLayout->addWidget(listaGeneriAlimentari);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(buttonAggiungi);
    buttonLayout->addWidget(buttonModifica);
    buttonLayout->addWidget(buttonReset);

    connect(listaGeneriAlimentari, SIGNAL(currentRowChanged(int)), this, SLOT(slotSelectedItem()));

}




QPushButton* Ricerca::getButtonPane() const {return buttonPane;}
QPushButton* Ricerca::getButtonSalumi() const {return buttonSalumi;}
QPushButton* Ricerca::getButtonLatticini() const {return buttonLatticini;}
QPushButton* Ricerca::getButtonGastronomiaVegetale() const {return buttonGastronomiaVegetale;}
QPushButton* Ricerca::getButtonPanini() const {return buttonPanini;}
QPushButton* Ricerca::getButtonBevande() const {return buttonBevande;}

QPushButton* Ricerca::getButtonReset() const {return buttonReset;}
QPushButton* Ricerca::getButtonModifica() const {return buttonModifica;}
QPushButton* Ricerca::getButtonAggiungi() const {return buttonAggiungi;}

ListWidget* Ricerca::getListaGeneriAlimentari() const {return listaGeneriAlimentari;}



void Ricerca::slotResetRicerca() const {
    listaGeneriAlimentari->clear();

    buttonAggiungi->setEnabled(false);
    buttonModifica->setEnabled(false);
    buttonReset->setEnabled(false);
}


void Ricerca::slotSelectedItem(bool b) const {
    buttonAggiungi->setEnabled(b);
    buttonModifica->setEnabled(b);
    buttonReset->setEnabled(b);
}

