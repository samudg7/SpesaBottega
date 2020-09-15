#include "../view/filterpanini.h"

#include <QVBoxLayout>


FilterPanini::FilterPanini(QWidget* parent):
    labelFilterPanini(new QLabel("Filtri Panino \n",parent)),
    labelConsistenza(new QLabel("Consistenza \n",parent)),
    checkboxCroccante(new QCheckBox("Croccante",parent)),
    checkboxMorbido(new QCheckBox("Morbido",parent)),
    labelConservazioneSalume(new QLabel("Conservazione Salume \n",parent)),
    checkboxCrudo(new QCheckBox("Crudo",parent)),
    checkboxCotto(new QCheckBox("Cotto",parent)),
    labelDigeribilita(new QLabel("Digeribilità \n",parent)),
    checkboxDigeribilita(new QCheckBox("Alta",parent)),
    labelVitamineFibre(new QLabel("Contenuto di vitamine e fibre \n",parent)),
    checkboxVitamineFibre(new QCheckBox("Alto",parent)),

    buttonClose(new QPushButton("Azzera",parent)),
    buttonMostra(new QPushButton("Mostra",parent))
{

    setWindowIcon(QIcon(":Logo/logo.png"));
    setFixedSize(QSize(500, 400));

    QVBoxLayout* mainLayout= new QVBoxLayout();

    mainLayout->addWidget(labelFilterPanini);
    mainLayout->addWidget(labelConsistenza);
    mainLayout->addWidget(checkboxCroccante);
    mainLayout->addWidget(checkboxMorbido);
    mainLayout->addWidget(labelConservazioneSalume);
    mainLayout->addWidget(checkboxCrudo);
    mainLayout->addWidget(checkboxCotto);
    mainLayout->addWidget(labelDigeribilita);
    mainLayout->addWidget(checkboxDigeribilita);
    mainLayout->addWidget(labelVitamineFibre);
    mainLayout->addWidget(checkboxVitamineFibre);



    QHBoxLayout* buttonsLayout= new QHBoxLayout();
    buttonsLayout->addWidget(buttonClose);
    buttonsLayout->addWidget(buttonMostra);


    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    connect(buttonClose,SIGNAL(clicked()),this,SLOT(close()));

}


QPushButton* FilterPanini::getButtonMostra() const{return buttonMostra;}

QCheckBox* FilterPanini::getcheckboxCroccante() const {return checkboxCroccante;}
QCheckBox* FilterPanini::getcheckboxMorbido() const {return checkboxMorbido;}
QCheckBox* FilterPanini::getcheckboxCrudo() const {return checkboxCrudo;}
QCheckBox* FilterPanini::getcheckboxCotto() const {return checkboxCotto;}
QCheckBox* FilterPanini::getcheckboxDigeribilita() const {return checkboxDigeribilita;}
QCheckBox* FilterPanini::getcheckboxVitamineFibre() const {return checkboxVitamineFibre;}
