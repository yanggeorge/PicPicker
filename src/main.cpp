#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(application);
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return QApplication::exec();
}
