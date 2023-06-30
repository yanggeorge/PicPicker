#include <QApplication>
#include <QStandardPaths>
#include "src/controller/picpickercontroller.h"
#include "src/ui/picpicker.h"
#include "log.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(application);

    QApplication a(argc, argv);
    a.setApplicationName("PicPicker");

    PicPickerController controller;
    // init log
    QT_LOG::logInit(controller.logfile(), QtDebugMsg);

    PicPicker picker(&controller);
    picker.show();

    int result = a.exec();

    controller.close();

    return result;
}
