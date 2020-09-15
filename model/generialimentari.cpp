#include "../model/generialimentari.h"

using std::string;
using std::to_string;
using std::fixed;
using std::setprecision;


GeneriAlimentari::GeneriAlimentari(string immagine, string nome, string descrizione):
    immagine(immagine), nome(nome), descrizione(descrizione) {}

GeneriAlimentari::GeneriAlimentari(const GeneriAlimentari& generiAlimentari) :
    GeneriAlimentari(generiAlimentari.immagine, generiAlimentari.nome, generiAlimentari.descrizione) {}


bool GeneriAlimentari::operator==(const GeneriAlimentari& generiAlimentari) const {
    return nome==generiAlimentari.nome && descrizione==generiAlimentari.descrizione;}

bool GeneriAlimentari::operator!=(const GeneriAlimentari& generiAlimentari) const {
    return !(*this==generiAlimentari);}

string GeneriAlimentari::getInfo()const {
    string str=getNome();
    return str.append("\n")
            .append("\n"+ getDescrizione());
}


string GeneriAlimentari::getImmagine() const {return immagine;}

string GeneriAlimentari::getNome() const {return nome;}

string GeneriAlimentari::getDescrizione() const {return descrizione;}

void GeneriAlimentari::setImmagine(string immagine) {this->immagine=immagine;}

void GeneriAlimentari::setNome(string nome) {this->nome=nome;}

void GeneriAlimentari::setDescrizione(string descrizione) {this->descrizione=descrizione;}







GeneriSolidi::GeneriSolidi(string immagine, string nome, string descrizione,
                           double prezzoAlKg, double peso, unsigned int quantita, double prezzo):
    GeneriAlimentari(immagine,nome,descrizione),
    prezzoAlKg(prezzoAlKg),peso(peso), quantita(quantita), prezzo(prezzo) {}

GeneriSolidi::GeneriSolidi(const GeneriSolidi &generiSolidi) :
    GeneriSolidi(generiSolidi.getImmagine(), generiSolidi.getNome(), generiSolidi.getDescrizione(), generiSolidi.getPrezzoAlKg(),
                 generiSolidi.getPeso(), generiSolidi.getQuantita(), generiSolidi.getPrezzo()){}

bool GeneriSolidi::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto generiSolidi=dynamic_cast<const GeneriSolidi*>(&generiAlimentari);
    return generiSolidi && GeneriAlimentari::operator==(generiAlimentari) && prezzoAlKg==generiSolidi->prezzoAlKg;
}

bool GeneriSolidi::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto generiSolidi=dynamic_cast<const GeneriSolidi*>(&generiAlimentari);
    return !generiSolidi || GeneriAlimentari::operator!=(generiAlimentari) || prezzoAlKg!=generiSolidi->prezzoAlKg;
}

string GeneriSolidi::getType() const {return string("Generi Solidi"); }

string GeneriSolidi::getInfo() const {
    string str=GeneriAlimentari::getInfo();
    std::stringstream kg, peso, prezzo;
    kg<<setprecision(2)<<fixed<<getPrezzoAlKg();
    peso<<setprecision(0)<<fixed<<getPeso();
    prezzo<<setprecision(2)<<fixed<<getPrezzo();
    return str.append("\n") +kg.str().append(" €/kg")
           .append("\n") +peso.str().append(" g")
           .append("\nQuantità: " + to_string(getQuantita()))
           .append("\n") +prezzo.str().append(" €");
}



double GeneriSolidi::getPrezzoAlKg() const {return prezzoAlKg;}

double GeneriSolidi::getPeso() const {return peso*quantita;}

unsigned int GeneriSolidi::getQuantita() const {return quantita;}

double GeneriSolidi::getPrezzo() const {return (peso/calcoloGrammi)*prezzoAlKg*quantita;}

void GeneriSolidi::setPrezzoAlKg(double prezzoAlKg) {this->prezzoAlKg=prezzoAlKg;}

void GeneriSolidi::setPeso(double peso) {this->peso=peso;}

void GeneriSolidi::setQuantita(unsigned int quantita) {this->quantita=quantita;}

void GeneriSolidi::setPrezzo(double prezzo) {this->prezzo=prezzo;}

unsigned int GeneriSolidi::calcoloGrammi = 1000;







Bevande::Bevande(string immagine, string nome, string descrizione, double prezzoAlLitro, double peso,
                 unsigned int quantita, double prezzo):
    GeneriAlimentari(immagine,nome,descrizione),
    prezzoAlLitro(prezzoAlLitro), peso(peso), quantita(quantita), prezzo(prezzo) {}

Bevande::Bevande(const Bevande &bevande) :
    Bevande(bevande.getImmagine(), bevande.getNome(), bevande.getDescrizione(), bevande.getPrezzoAlLitro(),
                 bevande.getPeso(),bevande.getQuantita(),bevande.getPrezzo()){}

Bevande* Bevande::clone() const {return new Bevande(*this);}

bool Bevande::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto bevande=dynamic_cast<const Bevande*>(&generiAlimentari);
    return bevande && GeneriAlimentari::operator==(generiAlimentari) && prezzoAlLitro==bevande->prezzoAlLitro;
}

bool Bevande::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto bevande=dynamic_cast<const Bevande*>(&generiAlimentari);
    return !bevande || GeneriAlimentari::operator!=(generiAlimentari) || prezzoAlLitro!=bevande->prezzoAlLitro;
}

string Bevande::getType() const {return string("Bevande");}

string Bevande::getInfo() const {
    string str=GeneriAlimentari::getInfo();
    std::stringstream litro, peso, prezzo;
    litro<<setprecision(2)<<fixed<<getPrezzoAlLitro();
    peso<<setprecision(0)<<fixed<<getPeso();
    prezzo<<setprecision(2)<<fixed<<getPrezzo();
    return str.append( "\n") +litro.str().append(" €/L")
           .append("\n") +peso.str().append(" cl")
           .append("\nQuantità: " + to_string(getQuantita()))
           .append("\n") +prezzo.str().append(" €")
           .append("\n");
}


double Bevande::getPrezzoAlLitro() const {return prezzoAlLitro;}

double Bevande::getPeso() const {return peso*quantita;}

unsigned int Bevande::getQuantita() const {return quantita;}

double Bevande::getPrezzo() const {return (peso/calcoloCl)*prezzoAlLitro*quantita;}


void Bevande::setPrezzoAlLitro(double prezzoAlLitro) {this->prezzoAlLitro=prezzoAlLitro;}

void Bevande::setPeso(double peso) {this->peso=peso;}

void Bevande::setQuantita(unsigned int quantita) {this->quantita=quantita;}

void Bevande::setPrezzo(double prezzo) {this->prezzo=prezzo;}

unsigned int Bevande::calcoloCl = 100;






Pane::Pane(string immagine, string nome, string descrizione, double prezzoAlKg, double peso, unsigned int quantita, double prezzo, string consistenza) :
    GeneriSolidi(immagine,nome,descrizione,prezzoAlKg,peso,quantita,prezzo),
    consistenza(consistenza) {}

Pane::Pane(const Pane &pane):
    Pane(pane.getImmagine(), pane.getNome(), pane.getDescrizione(), pane.getPrezzoAlKg(),pane.getPeso(), pane.getQuantita(), pane.getPrezzo(),
         pane.getConsistenza()){}


Pane* Pane::clone() const {return new Pane(*this);}

bool Pane::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto pane=dynamic_cast<const Pane*>(&generiAlimentari);
    return pane && GeneriSolidi::operator==(generiAlimentari) && consistenza==pane->consistenza;
}

bool Pane::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto pane=dynamic_cast<const Pane*>(&generiAlimentari);
    return !pane || GeneriSolidi::operator!=(generiAlimentari) || consistenza!=pane->consistenza;
}

string Pane::getType() const {return string("Pane");}

string Pane::getInfo() const {
    string str=GeneriSolidi::getInfo();
    return str.append("\nConsistenza: " +getConsistenza())
           .append("\n");
}


string Pane::getConsistenza() const {return consistenza;}

void Pane::setConsistenza(string consistenza) {this->consistenza=consistenza;}





Salumi::Salumi(string immagine, string nome, string descrizione, double prezzoAlKg, double peso, unsigned int quantita, double prezzo, string conservazione) :
    GeneriSolidi(immagine,nome,descrizione,prezzoAlKg,peso,quantita,prezzo),
    conservazione(conservazione) {}

Salumi::Salumi(const Salumi &salumi):
    Salumi(salumi.getImmagine(), salumi.getNome(), salumi.getDescrizione(), salumi.getPrezzoAlKg(), salumi.getPeso(), salumi.getQuantita(), salumi.getPrezzo(),
           salumi.getConservazione()){}


Salumi* Salumi::clone() const {return new Salumi(*this);}

bool Salumi::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto salumi=dynamic_cast<const Salumi*>(&generiAlimentari);
    return salumi && GeneriSolidi::operator==(generiAlimentari) && conservazione==salumi->conservazione;
}

bool Salumi::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto salumi=dynamic_cast<const Salumi*>(&generiAlimentari);
    return !salumi || GeneriSolidi::operator!=(generiAlimentari) || conservazione!=salumi->conservazione;
}

string Salumi::getType() const {return string("Salumi"); }

string Salumi::getInfo() const {
    string str=GeneriSolidi::getInfo();
    return str.append("\nConservazione: " +getConservazione())
           .append("\n");
}

string Salumi::getConservazione() const {return conservazione;}

void Salumi::setConservazione(string conservazione) {this->conservazione=conservazione;}






Latticini::Latticini(string immagine, string nome, string descrizione, double prezzoAlKg, double peso, unsigned int quantita, double prezzo,string digeribilita) :
    GeneriSolidi(immagine,nome,descrizione, prezzoAlKg, peso, quantita, prezzo),
    digeribilita(digeribilita) {}

Latticini::Latticini(const Latticini &latticini) :
    Latticini(latticini.getImmagine(), latticini.getNome(), latticini.getDescrizione(), latticini.getPrezzoAlKg(), latticini.getPeso(), latticini.getQuantita(), latticini.getPrezzo(),
              latticini.getDigeribilita()){}


Latticini* Latticini::clone() const {return new Latticini(*this);}

bool Latticini::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto latticini=dynamic_cast<const Latticini*>(&generiAlimentari);
    return latticini && GeneriSolidi::operator==(generiAlimentari) && digeribilita==latticini->digeribilita;
}

bool Latticini::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto latticini=dynamic_cast<const Latticini*>(&generiAlimentari);
    return !latticini || GeneriSolidi::operator!=(generiAlimentari) || digeribilita!=latticini->digeribilita;
}

string Latticini::getType() const {return string("Latticini"); }

string Latticini::getInfo() const {
    string str=GeneriSolidi::getInfo();
    return str.append("\nDigeribilità: " +getDigeribilita())
           .append("\n");
}

string Latticini::getDigeribilita() const {return digeribilita;}

void Latticini::setDigeribilita(string digeribilita) {this->digeribilita=digeribilita;}






GastronomiaVegetale::GastronomiaVegetale(string immagine, string nome, string descrizione,
                                         double prezzoAlKg, double peso, unsigned int quantita, double prezzo, string vitaminefibre):
    GeneriSolidi(immagine,nome,descrizione,prezzoAlKg,peso,quantita,prezzo),
    vitaminefibre(vitaminefibre) {}

GastronomiaVegetale::GastronomiaVegetale(const GastronomiaVegetale &gastronomiaVegetale) :
    GastronomiaVegetale(gastronomiaVegetale.getImmagine(), gastronomiaVegetale.getNome(), gastronomiaVegetale.getDescrizione(), gastronomiaVegetale.getPrezzoAlKg(),
                        gastronomiaVegetale.getPeso(),gastronomiaVegetale.getQuantita(), gastronomiaVegetale.getPrezzo(), gastronomiaVegetale.getVitamineFibre()){}


GastronomiaVegetale* GastronomiaVegetale::clone() const {return new GastronomiaVegetale(*this);}

bool GastronomiaVegetale::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto gastronomiaVegetale=dynamic_cast<const GastronomiaVegetale*>(&generiAlimentari);
    return gastronomiaVegetale && GeneriSolidi::operator==(generiAlimentari) && vitaminefibre==gastronomiaVegetale->vitaminefibre;
}

bool GastronomiaVegetale::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto gastronomiaVegetale=dynamic_cast<const GastronomiaVegetale*>(&generiAlimentari);
    return !gastronomiaVegetale || GeneriSolidi::operator!=(generiAlimentari) || vitaminefibre!=gastronomiaVegetale->vitaminefibre;
}

string GastronomiaVegetale::getType() const {return string("GastronomiaVegetale"); }

string GastronomiaVegetale::getInfo() const {
    string str=GeneriSolidi::getInfo();
    return str.append("\nContenuto di vitamine e fibre: " +getVitamineFibre())
           .append("\n");
}

string GastronomiaVegetale::getVitamineFibre() const {return vitaminefibre;}

void GastronomiaVegetale::setVitamineFibre(string vitaminefibre) {this->vitaminefibre=vitaminefibre;}





Panini::Panini(string immagine, string nome, string descrizione, double prezzoAlKg, double peso, unsigned int quantita, double prezzo, string consistenza, string conservazione, string digeribilita, string vitaminefibre, string ingredienti) :
    GeneriSolidi(immagine, nome, descrizione, prezzoAlKg, peso, quantita, prezzo),
    Pane(immagine, nome, descrizione, prezzoAlKg, peso, quantita, prezzo, consistenza),
    Salumi(immagine, nome, descrizione, prezzoAlKg, peso, quantita, prezzo, conservazione),
    Latticini(immagine, nome, descrizione, prezzoAlKg, peso, quantita, prezzo, digeribilita),
    GastronomiaVegetale(immagine, nome, descrizione, prezzoAlKg, peso, quantita, prezzo, vitaminefibre),
    ingredienti(ingredienti) {}

Panini::Panini(const Panini &panini):
    Panini(panini.getImmagine(), panini.getNome(), panini.getDescrizione(), panini.getPrezzoAlKg(), panini.getPeso(), panini.getQuantita(), panini.getPrezzo(),
           panini.getConsistenza(), panini.getConservazione(),panini.getDigeribilita(), panini.getVitamineFibre(),
           panini.getIngredienti()){}


Panini* Panini::clone() const {return new Panini(*this);}


bool Panini::operator==(const GeneriAlimentari& generiAlimentari) const {
    auto panini=dynamic_cast<const Panini*>(&generiAlimentari);
    return panini && GeneriSolidi::operator==(generiAlimentari) && ingredienti==panini->ingredienti;
}

bool Panini::operator!=(const GeneriAlimentari& generiAlimentari) const {
    auto panini=dynamic_cast<const Panini*>(&generiAlimentari);
    return !panini || GeneriSolidi::operator!=(generiAlimentari) || ingredienti!=panini->ingredienti;
}

string Panini::getType() const {return string("Panini"); }

string Panini::getInfo() const {
    string str=GeneriSolidi::getInfo();
    return str.append("\nConsistenza: " +getConsistenza())
           .append("\nConservazione salume: " +getConservazione())
           .append("\nDigeribilità: " +getDigeribilita())
           .append("\nContenuto di vitamine e fibre: " +getVitamineFibre())
           .append("\nIngredienti: " +getIngredienti())
           .append("\n");
}


string Panini::getIngredienti() const {return ingredienti;}

void Panini::setIngredienti(string ingredienti) {this->ingredienti=ingredienti;}
