#include <QApplication>
#include <QFile>

#include "controller/controller.h"
#include "model/model.h"

int main(int argc, char *argv[]){
    QApplication application(argc, argv);
    Controller controller(new Model());
    QFile file(":/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    application.setStyleSheet(stylesheet);
    controller.show();
    return application.exec();
}
