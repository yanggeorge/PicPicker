#include <QApplication>
#include <QStandardPaths>
#include "mainwindow.h"
#include "log.h"

int main(int argc, char *argv[]) {
    // init log
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString logfile = QString(homeDir + QDir::separator() +  AppModel::APP_DIR + QDir::separator() + "log.txt");
    QT_LOG::logInit(logfile, QtDebugMsg);

    Q_INIT_RESOURCE(application);
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return QApplication::exec();
}
