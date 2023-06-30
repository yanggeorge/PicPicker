//
// Created by 杨明 on 2023/6/30.
//

#ifndef PICPICKER_PICPICKERCONTROLLER_H
#define PICPICKER_PICPICKERCONTROLLER_H


#include <QString>
#include "../model/appinfo.h"

class PicPickerController {
public:

    PicPickerController();

    int init();

    QStringList getPics();

    int getIndex() const;

    QString currPic() const;

    QString nextPic();

    QString prevPic();

    QString delCurrPic();

    QString unDelPic();

    QString getPicsFolder();

    QString debugInfo() const;

    QString logfile() const;

    QString getStoreDataPath();
    QString getStoreDataBakPath();

    void close();

private:
    AppInfo *m_appInfo;
};


#endif //PICPICKER_PICPICKERCONTROLLER_H
