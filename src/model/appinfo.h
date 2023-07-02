//
// Created by 杨明 on 2023/6/30.
//

#ifndef PICPICKER_APPINFO_H
#define PICPICKER_APPINFO_H

#include <QString>
#include <QObject>
#include <QDir>
#include <QStack>
#include <QJsonObject>

class AppInfo : public QObject {
Q_OBJECT
public:

    QString currPic() const;

    QString nextPic();

    QString prevPic();

    QString delCurrPic();

    QString unDelPic();

    QString debugInfo() const;

    int fromJson(const QJsonObject &obj);

    QJsonObject toJson() const;

    const QString &getPicsFolder() const;

    void setPicsFolder(const QString &mPicsFolder);

    const QString &getTempFolder() const;

    void setTempFolder(const QString &mTempFolder);

    const QStringList &getPics() const;

    void setPics(const QStringList &mPics);

    int getIndex() const;

    void setIndex(int mIndex);

    const QStack<QString> &getDelPics() const;

    void setDelPics(const QStack<QString> &mDelPics);

private:
    QString m_picsFolder = nullptr;
    QString m_tempFolder = nullptr;

    QStringList m_pics = QStringList{};
    int m_index = 0;

    QStack<QString> m_delPics = QStack<QString>{};
};


#endif //PICPICKER_APPINFO_H
