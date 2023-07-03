//
// Created by 杨明 on 2023/7/4.
//

#ifndef PICPICKER_OPENDIALOGCONTROLLER_H
#define PICPICKER_OPENDIALOGCONTROLLER_H


#include <QObject>

class OpenDialogController : public QObject{
    Q_OBJECT
private:
public:
    const QString &getPicsFolder() const;

    void setPicsFolder(const QString &picsFolder);

    const QString &getTempFolder() const;

    void setTempFolder(const QString &tempFolder);

private:
    QString m_picsFolder = nullptr;
    QString m_tempFolder = nullptr;
};


#endif //PICPICKER_OPENDIALOGCONTROLLER_H
