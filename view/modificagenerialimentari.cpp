#include "../view/modificagenerialimentari.h"
#include "../model/generialimentari.h"

#include <QLabel>
#include <QVBoxLayout>


ModificaGeneriAlimentari::ModificaGeneriAlimentari(ListView* g, QWidget* parent):
    generialimentariView(g),
    buttonClose(new QPushButton("Annulla",parent)),
    buttonSave(new QPushButton("Salva",parent)),
    generialimentari(g->getItem()),

    spin(new QSpinBox(parent))

{
    setWindowIcon(QIcon(":Logo/logo.png"));
    setFixedSize(QSize(300,100));

    QVBoxLayout* mainLayout = new QVBoxLayout();

    GeneriSolidi *generisolidi= dynamic_cast<GeneriSolidi*>(generialimentari);

    if(generisolidi!=nullptr)           
            spin->setValue(generisolidi->getQuantita());
    else{    
        Bevande *bevande= dynamic_cast<Bevande*>(generialimentari);
        if(bevande!=nullptr)
            spin->setValue(bevande->getQuantita());
    }


    mainLayout->addWidget(new QLabel("Nuova quantità : "));
    mainLayout->addWidget(spin);


    QHBoxLayout* buttonsLayout= new QHBoxLayout();
    buttonsLayout->addWidget(buttonClose);
    buttonsLayout->addWidget(buttonSave);

    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);


    connect(buttonClose,SIGNAL(clicked()),this,SLOT(close()));
    connect(buttonSave,SIGNAL(clicked()),this,SLOT(slotSave()));
    connect(buttonSave,SIGNAL(clicked()), this,SLOT(close()));

}


QPushButton *ModificaGeneriAlimentari::getButtonSave() const{
    return buttonSave;
}


void ModificaGeneriAlimentari::slotSave() const{

    spin->setRange(1,20);                           //range di scelta per la quantità di un genere alimentare

    GeneriSolidi* generisolidi= dynamic_cast<GeneriSolidi*>(generialimentari);
    if(generisolidi!=nullptr)
         generisolidi->setQuantita(spin->value());
    else{
        Bevande *bevande= dynamic_cast<Bevande*>(generialimentari);
        if(bevande!=nullptr)
             bevande->setQuantita(spin->value());
    }

    generialimentariView->updateView();

}


