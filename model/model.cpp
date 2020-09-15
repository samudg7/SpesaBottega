#include "../model/model.h"

#include <QSaveFile>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>


Model::Model(string path):
    ricerca(new Container<GeneriAlimentari*>),
    carrello(new Container<GeneriAlimentari*>),
    catalogo(new Container<GeneriAlimentari*>),
    pathCatalogo(path),
    pathCarrello(path)
    {}


Model::~Model(){
    for(unsigned int i=0; i<getCatalogoSize(); ++i)
        delete catalogo->at(i);

    for(unsigned int i=0; i<getCarrelloSize(); ++i)
        delete carrello->at(i);

    delete ricerca;
}

void Model::clear(){
    for(unsigned int i=0; i<getCatalogoSize(); ++i)
        delete catalogoGeneriAlimentariAt(i);

    for(unsigned int i=0; i<getCarrelloSize(); ++i)
        delete carrelloGeneriAlimentariAt(i);

    ricerca->clear();
    carrello->clear();
    catalogo->clear();
}



//ricerca
Container<GeneriAlimentari*>::const_iterator Model::ricerca_cbegin() const {return ricerca->cbegin();}

Container<GeneriAlimentari*>::const_iterator Model::ricerca_cend() const {return ricerca->cend();}

unsigned int Model::getRicercaSize() const {return ricerca->getSize();}

GeneriAlimentari* Model::ricercaGeneriAlimentariAt(unsigned int i){return ricerca->at(i);}


void Model::resetRicerca() const{
    if(!(*ricerca == *catalogo))
        *ricerca = *catalogo;
}

void Model::filterType(string type) const{
     for(auto it =ricerca_cbegin() ; it != ricerca_cend(); ++it){
        if(type != (*it)->getType()){
            ricerca->erase(*it);
            --it;
        }
    }
}

void Model::filterConsistenza(string consistenza) const{
    const Panini* panini=nullptr;
    for(auto it= ricerca->cbegin(); it!= ricerca->cend(); ++it){
        panini= dynamic_cast<const Panini*>(*it);
        if(consistenza != (panini)->getConsistenza()){
            ricerca->erase(*it);
            --it;
        }
    }
}

void Model::filterConservazione(string conservazione) const {
    const Panini* panini=nullptr;
    for(auto it= ricerca->cbegin(); it!= ricerca->cend(); ++it){
        panini= dynamic_cast<const Panini*>(*it);
        if(conservazione != (panini)->getConservazione()){
            ricerca->erase(*it);
            --it;
        }
    }
}

void Model::filterDigeribilita(string digeribilita) const{
    const Panini* panini=nullptr;
    for(auto it= ricerca->cbegin(); it!= ricerca->cend(); ++it){
        panini= dynamic_cast<const Panini*>(*it);
        if(digeribilita != (panini)->getDigeribilita()){
            ricerca->erase(*it);
            --it;
        }
    }
}

void Model::filterVitamineFibre(string vitaminefibre) const{
    const Panini* panini=nullptr;
    for(auto it= ricerca->cbegin(); it!= ricerca->cend(); ++it){
        panini= dynamic_cast<const Panini*>(*it);
        if(vitaminefibre != (panini)->getVitamineFibre()){
            ricerca->erase(*it);
            --it;
        }
    }
}






//carrello
Container<GeneriAlimentari*>::iterator Model::carrello_begin(){return carrello->begin();}

Container<GeneriAlimentari*>::iterator Model::carrello_end(){return carrello->end();}

Container<GeneriAlimentari*>::const_iterator Model::carrello_cbegin() const {return carrello->cbegin();}

Container<GeneriAlimentari*>::const_iterator Model::carrello_cend() const {return carrello->cend();}


unsigned int Model::getCarrelloSize() const {return carrello->getSize();}

GeneriAlimentari* Model::carrelloGeneriAlimentariAt(unsigned int i){return carrello->at(i);}

void Model::erase(GeneriAlimentari* generiAlimentari){carrello->erase(generiAlimentari);}

void Model::push_backCarrello(GeneriAlimentari* generiAimentari){carrello->push_back(generiAimentari);}


void Model::saveCarrello(){
    QSaveFile fileCarrello(QString::fromStdString(pathCarrello));
    if(!fileCarrello.open(QIODevice::WriteOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato salvato correttamente", QMessageBox::Ok);
        box.exec();
    }

    QXmlStreamWriter write(&fileCarrello);

    write.setAutoFormatting(true);
    write.writeStartDocument();

    write.writeStartElement("carrello");

    const GeneriAlimentari* save= nullptr;
    for(auto it=carrello_cbegin();it!=carrello_cend();++it){

        save= *it;

        const QString type=QString::fromStdString(save->getType());
        write.writeEmptyElement(type);


        write.writeAttribute("immagine",QString::fromStdString(save->getImmagine()));
        write.writeAttribute("nome",QString::fromStdString(save->getNome()));
        write.writeAttribute("descrizione",QString::fromStdString(save->getDescrizione()));

        if(type=="Pane"){
            const Pane* pane = dynamic_cast<const Pane*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(pane->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(pane->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(pane->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(pane->getPrezzo()));
            write.writeAttribute("consistenza",QString::fromStdString(pane->getConsistenza()));
        }

        if(type=="Salumi"){
            const Salumi* salumi = dynamic_cast<const Salumi*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(salumi->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(salumi->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(salumi->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(salumi->getPrezzo()));
            write.writeAttribute("conservazione",QString::fromStdString(salumi->getConservazione()));
        }

        if(type=="Latticini"){
            const Latticini* latticini = dynamic_cast<const Latticini*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(latticini->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(latticini->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(latticini->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(latticini->getPrezzo()));
            write.writeAttribute("digeribilita",QString::fromStdString(latticini->getDigeribilita()));
        }

        if(type=="GastronomiaVegetale"){
            const GastronomiaVegetale* gastronomiavegetale = dynamic_cast<const GastronomiaVegetale*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(gastronomiavegetale->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(gastronomiavegetale->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(gastronomiavegetale->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(gastronomiavegetale->getPrezzo()));
            write.writeAttribute("vitaminefibre",QString::fromStdString(gastronomiavegetale->getVitamineFibre()));
        }

        if(type=="Panini"){
            const Panini* panini = dynamic_cast<const Panini*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(panini->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(panini->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(panini->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(panini->getPrezzo()));
            write.writeAttribute("consistenza",QString::fromStdString(panini->getConsistenza()));
            write.writeAttribute("conservazione",QString::fromStdString(panini->getConservazione()));
            write.writeAttribute("digeribilita",QString::fromStdString(panini->getDigeribilita()));
            write.writeAttribute("vitaminefibre",QString::fromStdString(panini->getVitamineFibre()));
            write.writeAttribute("ingredienti",QString::fromStdString(panini->getIngredienti()));
        }

        if(type=="Bevande"){
            const Bevande* bevande = static_cast<const Bevande*>(save);
            write.writeAttribute("prezzoAlLitro",QString("%1").arg(bevande->getPrezzoAlLitro()));
            write.writeAttribute("peso",QString("%1").arg(bevande->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(bevande->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(bevande->getPrezzo()));
        }

        if (write.hasError()){
            QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato salvato correttamente", QMessageBox::Ok);
            box.exec();
        }
    }

    write.writeEndElement();
    write.writeEndDocument();
    fileCarrello.commit();
}



void Model::loadCarrello(){
    QFile fileCarrello(QString::fromStdString(pathCarrello));

    if(!fileCarrello.open(QIODevice::ReadOnly)){
        QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato caricato correttamente", QMessageBox::Ok);
        box.exec();
    }

    QXmlStreamReader reader(&fileCarrello);
    if(reader.readNextStartElement()){
        if(reader.name()=="carrello") {

            GeneriAlimentari* load= nullptr;

            while(reader.readNextStartElement()) {
                const QXmlStreamAttributes item=reader.attributes();

                string immagine=item.hasAttribute("immagine")? item.value("immagine").toString().toStdString(): "";
                string nome=item.hasAttribute("nome")? item.value("nome").toString().toStdString(): "";
                string descrizione=item.hasAttribute("descrizione")? item.value("descrizione").toString().toStdString(): "";

                double prezzoAlKg= item.hasAttribute("prezzoAlKg")? item.value("prezzoAlKg").toDouble():0;

                double prezzoAlLitro= item.hasAttribute("prezzoAlLitro")? item.value("prezzoAlLitro").toDouble():0;

                double peso= item.hasAttribute("peso")? item.value("peso").toDouble():0;
                unsigned int quantita=item.hasAttribute("quantita")? item.value("quantita").toInt(): 0;
                double prezzo=item.hasAttribute("prezzo")? item.value("prezzo").toDouble(): 0;

                if(reader.name()=="Pane"){
                    string consistenza= item.hasAttribute("consistenza")? item.value("consistenza").toString().toStdString():"";
                    load= new Pane(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,consistenza);
                }

                if(reader.name()=="Salumi"){
                    string conservazione= item.hasAttribute("conservazione")? item.value("conservazione").toString().toStdString():"";
                    load= new Salumi(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,conservazione);
                }

                if(reader.name()=="Lattcini"){
                    string digeribilita= item.hasAttribute("digeribilita")? item.value("digeribilita").toString().toStdString():"";
                    load= new Latticini(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,digeribilita);
                }

                if(reader.name()=="GastronomiaVegetale"){
                    string vitaminefibre= item.hasAttribute("vitaminefibre")? item.value("vitaminefibre").toString().toStdString():"";
                    load= new GastronomiaVegetale(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,vitaminefibre);
                }

                if(reader.name()=="Panini"){
                    string consistenza= item.hasAttribute("consistenza")? item.value("consistenza").toString().toStdString():"";
                    string conservazione= item.hasAttribute("conservazione")? item.value("conservazione").toString().toStdString():"";
                    string digeribilita= item.hasAttribute("digeribilita")? item.value("digeribilita").toString().toStdString():"";
                    string vitaminefibre= item.hasAttribute("vitaminefibre")? item.value("vitaminefibre").toString().toStdString():"";
                    string ingredienti= item.hasAttribute("ingredienti")? item.value("ingredienti").toString().toStdString():"";
                    load= new Panini(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,consistenza,conservazione,digeribilita,vitaminefibre,ingredienti);
                }

                if(reader.name()=="Bevande"){
                    load= new Bevande(immagine,nome,descrizione,prezzoAlLitro,peso/quantita,quantita,prezzo/quantita);
                }

                if(load!= nullptr){
                    push_backCarrello(load);
                }

                if(!reader.isEndDocument())
                    reader.skipCurrentElement();
            }
        }
    }

    fileCarrello.close();
}


void Model::setNewPathCarrello(std::string path){
    pathCarrello=path;
    delete carrello;
    carrello=new Container<GeneriAlimentari*>;
}









//catalogo
Container<GeneriAlimentari*>::const_iterator Model::catalogo_cbegin() const {return catalogo->cbegin();}

Container<GeneriAlimentari*>::const_iterator Model::catalogo_cend() const {return catalogo->cend();}

GeneriAlimentari *Model::catalogoGeneriAlimentariAt(unsigned int i){
    return catalogo->at(i);}

unsigned int Model::getCatalogoSize() const {return catalogo->getSize();}


void Model::push_backCatalogo(GeneriAlimentari* generiAlimentari){
    catalogo->push_back(generiAlimentari);
    if(!(*ricerca == *catalogo))
        *ricerca=*catalogo;
}


void Model::saveCatalogo(){
    QSaveFile fileCatalogo(QString::fromStdString(pathCatalogo));

    if(!fileCatalogo.open(QIODevice::WriteOnly)) {
        QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato salvato correttamente", QMessageBox::Ok);
        box.exec();
    }

    QXmlStreamWriter write(&fileCatalogo);

    write.setAutoFormatting(true);
    write.writeStartDocument();

    write.writeStartElement("catalogo");

    const GeneriAlimentari* save= nullptr;

    for(auto it=catalogo_cbegin();it!=catalogo_cend();++it){

        save= *it;

        const QString type=QString::fromStdString(save->getType());
        write.writeEmptyElement(type);


        write.writeAttribute("immagine",QString::fromStdString(save->getImmagine()));
        write.writeAttribute("nome",QString::fromStdString(save->getNome()));
        write.writeAttribute("descrizione",QString::fromStdString(save->getDescrizione()));

        if(type=="Pane"){
            const Pane* pane = dynamic_cast<const Pane*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(pane->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(pane->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(pane->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(pane->getPrezzo()));
            write.writeAttribute("consistenza",QString::fromStdString(pane->getConsistenza()));
        }

        if(type=="Salumi"){
            const Salumi* salumi = dynamic_cast<const Salumi*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(salumi->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(salumi->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(salumi->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(salumi->getPrezzo()));
            write.writeAttribute("conservazione",QString::fromStdString(salumi->getConservazione()));
        }

        if(type=="Latticini"){
            const Latticini* latticini = dynamic_cast<const Latticini*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(latticini->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(latticini->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(latticini->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(latticini->getPrezzo()));
            write.writeAttribute("digeribilita",QString::fromStdString(latticini->getDigeribilita()));
        }

        if(type=="GastronomiaVegetale"){
            const GastronomiaVegetale* gastronomiavegetale = dynamic_cast<const GastronomiaVegetale*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(gastronomiavegetale->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(gastronomiavegetale->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(gastronomiavegetale->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(gastronomiavegetale->getPrezzo()));
            write.writeAttribute("vitaminefibre",QString::fromStdString(gastronomiavegetale->getVitamineFibre()));
        }

        if(type=="Panini"){
            const Panini* panini = dynamic_cast<const Panini*>(save);
            write.writeAttribute("prezzoAlKg",QString("%1").arg(panini->getPrezzoAlKg()));
            write.writeAttribute("peso",QString("%1").arg(panini->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(panini->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(panini->getPrezzo()));
            write.writeAttribute("consistenza",QString::fromStdString(panini->getConsistenza()));
            write.writeAttribute("conservazione",QString::fromStdString(panini->getConservazione()));
            write.writeAttribute("digeribilita",QString::fromStdString(panini->getDigeribilita()));
            write.writeAttribute("vitaminefibre",QString::fromStdString(panini->getVitamineFibre()));
            write.writeAttribute("ingredienti",QString::fromStdString(panini->getIngredienti()));
        }

        if(type=="Bevande"){
            const Bevande* bevande = static_cast<const Bevande*>(save);
            write.writeAttribute("prezzoAlLitro",QString("%1").arg(bevande->getPrezzoAlLitro()));
            write.writeAttribute("peso",QString("%1").arg(bevande->getPeso()));
            write.writeAttribute("quantita",QString("%1").arg(bevande->getQuantita()));
            write.writeAttribute("prezzo",QString("%1").arg(bevande->getPrezzo()));
        }

        if(write.hasError()){
            QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato salvato correttamente", QMessageBox::Ok);
            box.exec();
        }
    }

    write.writeEndElement();
    write.writeEndDocument();
    fileCatalogo.commit();
}

void Model::loadCatalogo(){
    QFile fileCatalogo(QString::fromStdString(pathCatalogo));

    if(!fileCatalogo.open(QIODevice::ReadOnly)){
        QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato caricato correttamente", QMessageBox::Ok);
        box.exec();
    }

    QXmlStreamReader reader(&fileCatalogo);
    if(reader.readNextStartElement()) {
        if(reader.name()=="catalogo") {

            GeneriAlimentari* load=nullptr;

            while(reader.readNextStartElement()) {
                const QXmlStreamAttributes item=reader.attributes();

                string immagine=item.hasAttribute("immagine")? item.value("immagine").toString().toStdString(): "";
                string nome=item.hasAttribute("nome")? item.value("nome").toString().toStdString(): "";
                string descrizione=item.hasAttribute("descrizione")? item.value("descrizione").toString().toStdString(): "";
                double prezzoAlKg= item.hasAttribute("prezzoAlKg")? item.value("prezzoAlKg").toDouble():0;
                double prezzoAlLitro= item.hasAttribute("prezzoAlLitro")? item.value("prezzoAlLitro").toDouble():0;
                double peso= item.hasAttribute("peso")? item.value("peso").toDouble():0;
                unsigned int quantita=item.hasAttribute("quantita")? item.value("quantita").toInt(): 0;
                double prezzo=item.hasAttribute("prezzo")? item.value("prezzo").toDouble(): 0;

                if(reader.name()=="Pane"){
                    string consistenza= item.hasAttribute("consistenza")? item.value("consistenza").toString().toStdString():"";
                    load= new Pane(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,consistenza);
                }

                if(reader.name()=="Salumi"){
                    string conservazione= item.hasAttribute("conservazione")? item.value("conservazione").toString().toStdString():"";
                    load= new Salumi(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,conservazione);
                }

                if(reader.name()=="Latticini"){
                    string digeribilita= item.hasAttribute("digeribilita")? item.value("digeribilita").toString().toStdString():"";
                    load= new Latticini(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,digeribilita);
                }

                if(reader.name()=="GastronomiaVegetale"){
                    string vitaminefibre= item.hasAttribute("vitaminefibre")? item.value("vitaminefibre").toString().toStdString():"";
                    load= new GastronomiaVegetale(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,vitaminefibre);
                }

                if(reader.name()=="Panini"){
                    string consistenza= item.hasAttribute("consistenza")? item.value("consistenza").toString().toStdString():"";
                    string conservazione= item.hasAttribute("conservazione")? item.value("conservazione").toString().toStdString():"";
                    string digeribilita= item.hasAttribute("digeribilita")? item.value("digeribilita").toString().toStdString():"";
                    string vitaminefibre= item.hasAttribute("vitaminefibre")? item.value("vitaminefibre").toString().toStdString():"";
                    string ingredienti= item.hasAttribute("ingredienti")? item.value("ingredienti").toString().toStdString():"";
                    load= new Panini(immagine,nome,descrizione,prezzoAlKg,peso/quantita,quantita,prezzo/quantita,consistenza,conservazione,digeribilita,vitaminefibre,ingredienti);
                }

                if(reader.name()=="Bevande"){
                    load= new Bevande(immagine,nome,descrizione,prezzoAlLitro,peso/quantita,quantita,prezzo/quantita);
                }

                if(load!= nullptr){
                    push_backCatalogo(load);
                }
                else{
                    QMessageBox box(QMessageBox::Warning, "Errore", "Il file non è stato caricato correttamente", QMessageBox::Ok);
                    box.exec();
                }

                if(!reader.isEndDocument())
                    reader.skipCurrentElement();
            }
        }
    }

    fileCatalogo.close();

}


void Model::setNewPathCatalogo(std::string path){
    pathCatalogo=path;
    delete catalogo;
    catalogo=new Container<GeneriAlimentari*>;
}



