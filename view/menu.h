#ifndef MENU_H
#define MENU_H

#include <QMenuBar>

class Menu : public QMenuBar{
    Q_OBJECT

private:
    QWidget* parent;

    QMenu* menu;
    QAction* loadCarrello;
    QAction* esci;
    QAction* ricerca;
    QAction* carrello;

public:
    Menu(QWidget* = nullptr);

    QMenu* getMenu() const;
    QAction* getLoadCarrello() const;
    QAction* getEsci() const;
};

#endif // MENU_H
