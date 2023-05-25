//
// Created by 杨明 on 2023/5/24.
//

#ifndef PICKPIC_APPMODEL_H
#define PICKPIC_APPMODEL_H


#include <QObject>
#include <QDir>

class AppModel : public QObject {
Q_OBJECT
public:
    AppModel();

    int init();

    static const int Fixed_Height = 600;
    static const int Fixed_Width = 800;
    const QString APP_DIR = ".pickpic";
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

    QString debugInfo() const;

private:
    QString picsFolder = nullptr;
    QString tempFolder = nullptr;

    QStringList pics = QStringList{};
    int index = 0;

};


#endif //PICKPIC_APPMODEL_H
