//
// Created by 杨明 on 2023/5/24.
//

#ifndef PICKPIC_APPMODEL_H
#define PICKPIC_APPMODEL_H


#include <QObject>

class AppModel : public QObject {
Q_OBJECT
public:
    AppModel();

    static const int Fixed_Height = 600;
    static const int Fixed_Width = 800;

    void setPicsFolder(const QString &dir);

    QString getPicsFolder();

    void initPics(const QStringList &filenames);

    QStringList getPics();

    int getIndex() const;

    QString currPic() const;
    QString nextPic();
    QString prevPic();

    QString debugInfo() const;

private:
    QString picsFolder = QString{};
    QString tmpFolder = QString{};

    QStringList pics = QStringList{};
    int index = 0;
};


#endif //PICKPIC_APPMODEL_H
