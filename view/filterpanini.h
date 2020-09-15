#ifndef FILTERPANINI_H
#define FILTERPANINI_H

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>
#include <QLabel>


class FilterPanini: public QDialog{
    Q_OBJECT

private:
    QLabel* labelFilterPanini;

    QLabel* labelConsistenza;
    QCheckBox* checkboxCroccante;
    QCheckBox* checkboxMorbido;
    QLabel* labelConservazioneSalume;
    QCheckBox* checkboxCrudo;
    QCheckBox* checkboxCotto;
    QLabel* labelDigeribilita;
    QCheckBox* checkboxDigeribilita;
    QLabel* labelVitamineFibre;
    QCheckBox* checkboxVitamineFibre;

    QPushButton* buttonClose;
    QPushButton* buttonMostra;

public:
    FilterPanini(QWidget* = nullptr);

    QCheckBox* getcheckboxCroccante() const;
    QCheckBox* getcheckboxMorbido() const;
    QCheckBox* getcheckboxCrudo() const;
    QCheckBox* getcheckboxCotto() const;
    QCheckBox* getcheckboxDigeribilita() const;
    QCheckBox* getcheckboxVitamineFibre() const;

    QPushButton* getButtonMostra() const;

};

#endif // FILTERPANINI_H
