#include "../controller/controller.h"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>


using std::string;
using std::fixed;
using std::setprecision;


Controller::Controller(Model* model, QWidget* parent) :
    QWidget(parent),
    model(model),
    menu(new Menu(this)),
    layout(new QHBoxLayout(this)),

    ricerca(new Ricerca(this)),
    carrello(new Carrello(this)),
    dialogModificaGeneriAlimentari(nullptr),
    dialogFilterPanini(nullptr)

{

    setWindowIcon(QIcon(":Logo/logo.png"));
    setFixedSize(QSize(500, 600));

    layout->setMenuBar(menu);
    layout->addWidget(ricerca);
    layout->addWidget(carrello);

    setLayout(layout);
    slotLoadData();



    //connect
    connect(ricerca->getButtonPane(),SIGNAL(clicked()),this,SLOT(slotRicercaPane()));
    connect(ricerca->getButtonSalumi(),SIGNAL(clicked()),this,SLOT(slotRicercaSalumi()));
    connect(ricerca->getButtonLatticini(),SIGNAL(clicked()),this,SLOT(slotRicercaLatticini()));
    connect(ricerca->getButtonGastronomiaVegetale(),SIGNAL(clicked()),this,SLOT(slotRicercaGastronomiaVegetale()));
    connect(ricerca->getButtonPanini(),SIGNAL(clicked()),this,SLOT(slotRicercaPanini()));
    connect(ricerca->getButtonBevande(),SIGNAL(clicked()),this,SLOT(slotRicercaBevande()));

    connect(ricerca->getButtonModifica(),SIGNAL(clicked()),this,SLOT(slotModificaRicerca()));
    connect(ricerca->getButtonReset(),SIGNAL(clicked()),ricerca,SLOT(slotResetRicerca()));
    connect(ricerca->getButtonReset(),SIGNAL(clicked()),this,SLOT(slotResetRicerca()));
    connect(ricerca->getButtonAggiungi(),SIGNAL(clicked()),this,SLOT(slotAggiungiElemento()));
    connect(carrello->getButtonElimina(),SIGNAL(clicked()),this,SLOT(slotRimuoviDalCarrello()));
    connect(carrello->getButtonModifica(),SIGNAL(clicked()),this,SLOT(slotModificaCarrello()));
}



Controller::~Controller() {
    model->saveCatalogo();
    model->saveCarrello();
}


Model* Controller::getModel() {return model;}




//load
void Controller::slotLoadData(){
    QString fileCatalogo= QFileDialog::getOpenFileName(this,tr("Scegli file"),"../catalogo","*.xml");

    if(fileCatalogo!=""){
        model->clear();
        model->setNewPathCatalogo(fileCatalogo.toStdString());

        model->loadCatalogo();

        if(model->getCatalogoSize()==0){
            QMessageBox::warning(this,"Attenzione!", "Il file del programma è vuoto.");
        }
        else{
            slotMostraRicerca();
        }
    }

    QString fileCarrello= QFileDialog::getOpenFileName(this,tr("Scegli file"),"../carrello","*.xml");

    if(fileCarrello!=""){
        model->setNewPathCarrello(fileCarrello.toStdString());
        model->loadCarrello();

        if(model->getCarrelloSize()){
            for(unsigned int i=0; i<model->getCarrelloSize(); ++i)
                carrello->getListaGeneriAlimentari()->aggiungiAlCarrello(model->carrelloGeneriAlimentariAt(i));
        }
        slotLabelPrezzo();
    }
}


void Controller::slotLoadCarrello(){
    if(model->getCarrelloSize()!=0){
        QMessageBox::warning(this,"Attenzione!", "Svuota il carrello prima di caricarne uno nuovo.");
    }
    else{
        QString fileCarrello= QFileDialog::getOpenFileName(this,tr("Scegli file"),"../carrello","*.xml");

        if(fileCarrello!=""){
            model->setNewPathCarrello(fileCarrello.toStdString());

            model->loadCarrello();

            if(model->getCarrelloSize()){
                for(unsigned int i=0; i<model->getCarrelloSize(); ++i)
                    carrello->getListaGeneriAlimentari()->aggiungiAlCarrello(model->carrelloGeneriAlimentariAt(i));
            }
            slotLabelPrezzo();
        }
    }
}




//mostra Cerca o Carrello
void Controller::slotMostraRicerca() const{
    ricerca->show();
    carrello->hide();
}

void Controller::slotMostraCarrello() const{
    ricerca->hide();
    carrello->show();
}





//rimozione
void Controller::slotRimuoviDalCarrello() {
    if(carrello->getListaGeneriAlimentari()->currentItem()!= nullptr){
        ListView* itemCarrello=carrello->getListaGeneriAlimentari()->takeItem(carrello->getListaGeneriAlimentari()->currentRow());
        model->erase(itemCarrello->getItem());
        delete itemCarrello;
        carrello->getListaGeneriAlimentari()->reset();

        slotLabelPrezzo();

        QMessageBox::information(this,"Info", "Il genere alimentare è stato rimosso dal carrello.");
    }
    else
        QMessageBox::information(this,"Info", "Scegli il genere alimentare da rimuovere.");
}





//ricerca
void Controller::slotRicercaPane(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!", "Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonPane()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }
    }
}

void Controller::slotRicercaSalumi(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!","Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonSalumi()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }
    }
}

void Controller::slotRicercaLatticini(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!","Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonLatticini()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }
    }
}

void Controller::slotRicercaGastronomiaVegetale(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!", "Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonGastronomiaVegetale()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }
    }
}


void Controller::slotRicercaPanini(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!", "Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonPanini()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }

        dialogFilterPanini=new FilterPanini(this);
        dialogFilterPanini->show();

        connect(dialogFilterPanini->getButtonMostra(),SIGNAL(clicked()),this,SLOT(slotFilterPanini()));
        connect(dialogFilterPanini->getButtonMostra(),SIGNAL(clicked()),dialogFilterPanini,SLOT(close()));
    }
}


void Controller::slotRicercaBevande(){
    slotResetRicerca();
    ricerca->getListaGeneriAlimentari()->clear();

    if(model->getCatalogoSize()==0){
        QMessageBox::warning(this, "Attenzione!", "Non ci sono generi alimentari nel catalogo.");
    }
    else{

        model->filterType(ricerca->getButtonBevande()->text().toStdString());

        if(model->getRicercaSize()==0){
            QMessageBox::warning(this, "Informazione", "Non ci sono generi alimentari che corrispondono alla categoria selezionata.");
        }
        else{
            for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
                ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
        }
    }
}



void Controller::slotFilterPanini() {
    if(dialogFilterPanini->getcheckboxCroccante()->isChecked())
        model->filterConsistenza(dialogFilterPanini->getcheckboxCroccante()->text().toStdString());
    if(dialogFilterPanini->getcheckboxMorbido()->isChecked())
        model->filterConsistenza(dialogFilterPanini->getcheckboxMorbido()->text().toStdString());
    if(dialogFilterPanini->getcheckboxCrudo()->isChecked())
        model->filterConservazione(dialogFilterPanini->getcheckboxCrudo()->text().toStdString());
    if(dialogFilterPanini->getcheckboxCotto()->isChecked())
        model->filterConservazione(dialogFilterPanini->getcheckboxCotto()->text().toStdString());
    if(dialogFilterPanini->getcheckboxDigeribilita()->isChecked())
        model->filterDigeribilita(dialogFilterPanini->getcheckboxDigeribilita()->text().toStdString());
    if(dialogFilterPanini->getcheckboxVitamineFibre()->isChecked())
        model->filterVitamineFibre(dialogFilterPanini->getcheckboxVitamineFibre()->text().toStdString());

    if(model->getRicercaSize()==0){
        QMessageBox::warning(this, "Informazione", "Non ci sono panini con le caratteristiche selezionate.");
    }
    else{
        ricerca->getListaGeneriAlimentari()->clear();
        for(auto it = model->ricerca_cbegin(); it != model->ricerca_cend(); ++it)
            ricerca->getListaGeneriAlimentari()->aggiungiAlCarrello(*it);
    }
}


void Controller::slotResetRicerca() const {model->resetRicerca();}





//modifica
void Controller::slotModificaRicerca() {
    if(ricerca->getListaGeneriAlimentari()->currentItem()!= nullptr){
        ListView* generealimentare=ricerca->getListaGeneriAlimentari()->currentItem();

        bool presente=false;
        for(auto it = model->carrello_cbegin(); it != model->carrello_cend(); ++it){
            if(generealimentare->getItem() == *it)
                presente=true;
        }

        if(!presente && generealimentare!=nullptr){
            dialogModificaGeneriAlimentari=new ModificaGeneriAlimentari(generealimentare,this);
            dialogModificaGeneriAlimentari->show();
        }
        else{
            if(presente)
                QMessageBox::information(this,"Info", "Rimuovere il genere alimentare dal carrello prima di selezionare la nuova quantità.");
        }
    }
    else
        QMessageBox::information(this,"Info", "Scegli il genere alimentare da modificare.");
}


void Controller::slotModificaCarrello() {
    if(carrello->getListaGeneriAlimentari()->currentItem()!= nullptr){
        ListView* generealimentare=carrello->getListaGeneriAlimentari()->currentItem();
        dialogModificaGeneriAlimentari=new ModificaGeneriAlimentari(generealimentare,this);
        dialogModificaGeneriAlimentari->show();

        connect(dialogModificaGeneriAlimentari->getButtonSave(),SIGNAL(clicked()),this, SLOT(slotLabelPrezzo()));
    }
    else
        QMessageBox::information(this,"Info", "Scegli il genere alimentare da modificare.");
}





//inserimento nel carrello
void Controller::slotAggiungiElemento(){
    if(ricerca->getListaGeneriAlimentari()->currentItem()!=nullptr){
        ListView* addItem=ricerca->getListaGeneriAlimentari()->currentItem();

        bool presente=false;
        for(auto it = model->carrello_begin(); it != model->carrello_end(); ++it){
            if(addItem->getItem() == *it)
                presente=true;
        }

        if(addItem!= nullptr && !presente){
            model->push_backCarrello(addItem->getItem());

            carrello->getListaGeneriAlimentari()->aggiungiAlCarrello(addItem->getItem());

            slotLabelPrezzo();

            QMessageBox::information(this,"Info", "Il genere alimentare è stato aggiunto al carrello.");
        }
        if(presente)
            QMessageBox::information(this,"Info", "Il genere alimentare è già presente nel carrello.");
    }
    else
        QMessageBox::information(this,"Info", "Scegli il genere alimentare da aggiungere al carrello.");
}





//calcola prezzo e numero prodotti
void Controller::slotLabelPrezzo() const{

    double prezzoTotale=0;
    unsigned int numeroProdottiTotale=0;

    GeneriSolidi *generisolidi=nullptr;Bevande *bevande=nullptr;Pane* pane=nullptr;Panini* panini=nullptr;

    //se il Genere Alimentare è di tipo Salumi, Latticini o GastronomiaVegetale, il numeroProdottiTotale non viene incrementato
    for(auto cit = model->carrello_cbegin(); cit != model->carrello_cend(); ++cit){
        generisolidi= dynamic_cast<GeneriSolidi*>(*cit);
        pane= dynamic_cast<Pane*>(*cit);
        panini= dynamic_cast<Panini*>(*cit);
        if(generisolidi!=nullptr){
            prezzoTotale=prezzoTotale+ generisolidi->getPrezzo();
            if(pane!=nullptr && panini==nullptr)
                numeroProdottiTotale=pane->getQuantita()+numeroProdottiTotale;
            if(panini!=nullptr)
                numeroProdottiTotale=panini->getQuantita()+numeroProdottiTotale;
            if(pane==nullptr && panini==nullptr)
                numeroProdottiTotale++;
        }
        else{
            bevande= dynamic_cast<Bevande*>(*cit);
            if(bevande!=nullptr)
                prezzoTotale=prezzoTotale+ bevande->getPrezzo();

            numeroProdottiTotale=bevande->getQuantita()+numeroProdottiTotale;
        }
    }

    std::stringstream text;
    std::stringstream s;
    s<<setprecision(2)<<fixed<<prezzoTotale;
    text<<"Totale: "<<s.str()<<" € ,   "<<numeroProdottiTotale<<" prodotti";
    carrello->getLabelPrezzo()->setText(QString::fromStdString(text.str()));

}

