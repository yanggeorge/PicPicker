//
// Created by 杨明 on 2023/6/30.
//

#ifndef PICPICKER_PICPICKERCONTROLLER_H
#define PICPICKER_PICPICKERCONTROLLER_H


#include <QString>
#include "src/model/appinfo.h"

class PicPickerController : public QObject{
Q_OBJECT
public:

    PicPickerController();

    int init();

    int init(QString picsFolder, QString tempFolder = nullptr);

    QStringList getPics();

    int getIndex() const;

    QString currPic() const;

    QString nextPic();

    QString prevPic();

    QString delCurrPic();

    QString unDelPic();

    QString getPicsFolder();

    QString getTempFolder();

    QString debugInfo() const;

    QString logfile() const;

    QString getStoreDataPath();

    QString getStoreDataBakPath();

    void close();

    QString getFullTempFolderPath();

    void setTempFolderPath(const QString& path);

signals:
    void error(QString msg);

private:

    void moveToTempFolder(QString imageName);

    void moveToPicsFolder(QString imageName);

private:
    AppInfo *m_appInfo;
};


#endif //PICPICKER_PICPICKERCONTROLLER_H
