#ifndef MODEL_H
#define MODEL_H

#include "../model/generialimentari.h"
#include "../model/container.h"


class Model {
private:
    Container<GeneriAlimentari*>* ricerca;
    Container<GeneriAlimentari*>* carrello;
    Container<GeneriAlimentari*>* catalogo;

    string pathCatalogo;
    string pathCarrello;

public:
    Model(string path="../newData");
    ~Model();
    void clear();

    //ricerca
    Container<GeneriAlimentari*>::const_iterator ricerca_cbegin() const;
    Container<GeneriAlimentari*>::const_iterator ricerca_cend() const;

    unsigned int getRicercaSize() const;
    GeneriAlimentari* ricercaGeneriAlimentariAt(unsigned int);
    void resetRicerca() const;

     //filtro di ricerca per Generi Alimentari
    void filterType(string type) const;

     //filtri di ricerca per Panino in base alle caratteristiche delle sue superclassi
    void filterConsistenza(string consistenza) const;
    void filterConservazione(string conservazione) const;
    void filterDigeribilita(string digeribilita) const;
    void filterVitamineFibre(string vitaminefibre) const;




    //carrello
    Container<GeneriAlimentari*>::iterator carrello_begin();
    Container<GeneriAlimentari*>::iterator carrello_end();
    Container<GeneriAlimentari*>::const_iterator carrello_cbegin() const;
    Container<GeneriAlimentari*>::const_iterator carrello_cend() const;

    unsigned int getCarrelloSize() const;
    GeneriAlimentari* carrelloGeneriAlimentariAt(unsigned int);
    void erase(GeneriAlimentari*);
    void push_backCarrello(GeneriAlimentari*);

    //input/output
    void saveCarrello();
    void loadCarrello();
    void setNewPathCarrello(string);




    //catalogo
    Container<GeneriAlimentari*>::const_iterator catalogo_cbegin() const;
    Container<GeneriAlimentari*>::const_iterator catalogo_cend() const;

    unsigned int getCatalogoSize() const;
    GeneriAlimentari* catalogoGeneriAlimentariAt(unsigned int);
    void push_backCatalogo(GeneriAlimentari*);

    //input/output
    void saveCatalogo();
    void loadCatalogo();
    void setNewPathCatalogo(string);

};

#endif // MODEL_H
