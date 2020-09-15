#ifndef GENERIALIMENTARI_H
#define GENERIALIMENTARI_H

#include <sstream>
#include <iomanip>

using std::string;


class GeneriAlimentari {
private:
    string immagine;
    string nome;
    string descrizione;

public:
    GeneriAlimentari(string immagine="", string nome="", string descrizione="");
    GeneriAlimentari(const GeneriAlimentari&);

    virtual GeneriAlimentari* clone() const =0;
    virtual bool operator==(const GeneriAlimentari&) const;
    virtual bool operator!=(const GeneriAlimentari&) const;
    virtual ~GeneriAlimentari() =default;

    virtual string getType() const =0;
    virtual string getInfo() const;

    string getImmagine() const;
    string getNome() const;
    string getDescrizione() const;

    void setImmagine(string);
    void setNome(string);
    void setDescrizione(string);
};



class GeneriSolidi: public GeneriAlimentari{
private:
    double prezzoAlKg;                  //espresso in €/kg
    double peso;                        //espresso in grammi
    unsigned int quantita;
    double prezzo;
    static unsigned int calcoloGrammi;

public:
    GeneriSolidi(string immagine="", string nome="", string descrizione="",
                 double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0);
    GeneriSolidi(const GeneriSolidi&);

    GeneriSolidi* clone() const =0;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    double getPrezzoAlKg()const;
    void setPrezzoAlKg(double prezzoAlKg);

    double getPeso() const;
    void setPeso(double);

    unsigned int getQuantita()const;
    void setQuantita(unsigned int);

    double getPrezzo() const;
    void setPrezzo(double);
};



class Bevande: public GeneriAlimentari{
private:
    double prezzoAlLitro;                   //espresso in €/L
    double peso;                            //espresso in cl
    unsigned int quantita;
    double prezzo;
    static unsigned int calcoloCl;

public:
    Bevande(string immagine="", string nome="", string descrizione="",
            double prezzoAlLitro=0, double peso=0, unsigned int quantita=0, double prezzo=0);
    Bevande(const Bevande&);

    Bevande* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    double getPrezzoAlLitro() const;
    void setPrezzoAlLitro(double);

    double getPeso() const;
    void setPeso(double);

    unsigned int getQuantita()const;
    void setQuantita(unsigned int);

    double getPrezzo() const;
    void setPrezzo(double);
};



class Pane: virtual public GeneriSolidi{
private:
    string consistenza;

public:
    Pane(string immagine="", string nome="", string descrizione="",
         double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0,
         string consistenza="");

    Pane(const Pane &);

    Pane* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    string getConsistenza()const;
    void setConsistenza(string);
};



class Salumi: virtual public GeneriSolidi{
private:
    string conservazione;

public:
    Salumi(string immagine="", string nome="", string descrizione="",
           double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0,
           string conservazione="");

    Salumi(const Salumi &);

    Salumi* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    string getConservazione()const;
    void setConservazione(string);
};



class Latticini: virtual public GeneriSolidi{
private:
    string digeribilita;

public:
    Latticini(string immagine="", string nome="", string descrizione="",
              double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0,
              string digeribilita="");

    Latticini(const Latticini &);

    Latticini* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    string getDigeribilita()const;
    void setDigeribilita(string);
};



class GastronomiaVegetale: virtual public GeneriSolidi{
private:
    string vitaminefibre;

public:
    GastronomiaVegetale(string immagine="", string nome="", string descrizione="",
                        double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0,
                        string vitaminefibre="");

    GastronomiaVegetale(const GastronomiaVegetale &);

    GastronomiaVegetale* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    string getVitamineFibre()const;
    void setVitamineFibre(string);
};



class Panini: public Pane, public Salumi, public Latticini, public GastronomiaVegetale{
private:
    string ingredienti;

public:
    Panini(string immagine="", string nome="", string descrizione="",
           double prezzoAlKg=0, double peso=0, unsigned int quantita=0, double prezzo=0,
           string consistenza="", string conservazione="", string digeribilita="", string vitaminefibre="",
           string ingredienti="");

    Panini(const Panini &);

    Panini* clone() const;
    bool operator==(const GeneriAlimentari&) const;
    bool operator!=(const GeneriAlimentari&) const;

    string getType() const;
    string getInfo() const;

    string getIngredienti()const;
    void setIngredienti(string);
};


#endif // GENERIALIMENTARI_H
