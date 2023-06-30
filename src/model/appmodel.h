//
// Created by 杨明 on 2023/5/24.
//

#ifndef PICPICKER_APPMODEL_H
#define PICPICKER_APPMODEL_H


#include <QObject>
#include <QDir>
#include <QStack>
#include <QJsonObject>

class AppModel : public QObject {
Q_OBJECT
public:
    AppModel();

    int init();

    static const int Fixed_Height = 600;
    static const int Fixed_Width = 800;
    static const QString APP_DIR;
    const QString DEFAULT_TEMP_DIR = APP_DIR + QDir::separator() + "temp";

    void setPicsFolder(const QString &dir);

    QString getPicsFolder();

    QString getTempFolder();

    void initPics(const QStringList &filenames);

    QStringList getPics();

    int getIndex() const;

    QString currPic() const;

    QString nextPic();

    QString prevPic();

    QString delCurrPic();

    QString unDelPic();

    QString debugInfo() const;

    QJsonObject toJson() const;

    int fromJson(const QString &qString);

    int fromJson(const QJsonObject &obj);

    QString getStoreDataPath();

    QString getStoreDataBakPath();

private:
    QString picsFolder = nullptr;
    QString tempFolder = nullptr;

    QStringList pics = QStringList{};
    int index = 0;

    QStack<QString> delPics = QStack<QString>{};
};


#endif //PICPICKER_APPMODEL_H
