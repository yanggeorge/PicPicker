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

    const QString &getPicsFolder() const {
        return m_picsFolder;
    }

    void setPicsFolder(const QString &mPicsFolder) {
        m_picsFolder = mPicsFolder;
    }

    const QString &getTempFolder() const {
        return m_tempFolder;
    }

    void setTempFolder(const QString &mTempFolder) {
        m_tempFolder = mTempFolder;
    }

    QStringList getPics() const {
        return m_pics;
    }

    void setPics(const QStringList &mPics) {
        m_pics = mPics;
    }

    int getIndex() const {
        return m_index;
    }

    void setIndex(int mIndex) {
        m_index = mIndex;
    }

    const QStack<QString> &getDelPics() const {
        return m_delPics;
    }

    void setDelPics(const QStack<QString> &mDelPics) {
        m_delPics = mDelPics;
    }

    int fromJson(const QJsonObject &obj);

    QJsonObject toJson() const;

private:
    QString m_picsFolder = nullptr;
    QString m_tempFolder = nullptr;

    QStringList m_pics = QStringList{};
    int m_index = 0;

    QStack<QString> m_delPics = QStack<QString>{};
};


#endif //PICPICKER_APPINFO_H
