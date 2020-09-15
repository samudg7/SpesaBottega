#include "../view/carrello.h"


Carrello::Carrello(QWidget* parent):
    QWidget(parent),
    listaGeneriAlimentari(new ListWidget(this)),
    labelPrezzo(new QLabel("Totale carrello:  0 € ,  0 prodotti",this)),
    buttonModifica(new QPushButton("Modifica quantità",this)),
    buttonElimina(new QPushButton("Rimuovi dal carrello", this))


{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listaGeneriAlimentari);

    labelPrezzo->setEnabled(true);
    buttonModifica->setEnabled(false);
    buttonElimina->setEnabled(false);

    QHBoxLayout* hBox = new QHBoxLayout();
    hBox->addWidget(labelPrezzo);
    hBox->addWidget(buttonModifica);
    hBox->addWidget(buttonElimina);

    mainLayout->addLayout(hBox);

    connect(listaGeneriAlimentari, SIGNAL(currentRowChanged(int)), this, SLOT(slotSelectedItem()));

}

Carrello::~Carrello() {
    delete listaGeneriAlimentari;
    delete labelPrezzo;
    delete buttonModifica;
    delete buttonElimina;
}



QLabel* Carrello::getLabelPrezzo() const {return labelPrezzo;}

QPushButton* Carrello::getButtonElimina() const {return buttonElimina;}

QPushButton* Carrello::getButtonModifica() const {return buttonModifica;}

ListWidget* Carrello::getListaGeneriAlimentari() const {return listaGeneriAlimentari;}




void Carrello::slotSelectedItem(bool b) const {
    buttonElimina->setEnabled(b);
    labelPrezzo->setEnabled(true);
    buttonModifica->setEnabled(b);
}


