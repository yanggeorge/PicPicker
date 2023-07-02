//
// Created by 杨明 on 2023/6/30.
//

#include "appinfo.h"
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonArray>
#include <QJsonParseError>


QString AppInfo::currPic() const {
    if (m_pics.length() == 0) return nullptr;
    return m_pics[m_index];
}

QString AppInfo::nextPic() {
    if (m_pics.length() == 0) return nullptr;
    if (m_index + 1 == m_pics.length()) {
        return nullptr;
    }
    m_index += 1;
    return m_pics[m_index];
}

QString AppInfo::prevPic() {
    if (m_pics.length() == 0) return nullptr;
    if (m_index == 0) {
        return nullptr;
    }
    m_index -= 1;
    return m_pics[m_index];
}


QString AppInfo::delCurrPic() {
    auto delPic = m_pics[m_index];
    m_delPics.push(delPic);
    m_pics.removeAt(m_index);
    if (m_index + 1 < m_pics.length()) {
        m_index += 1;
    }
    return delPic;
};

QString AppInfo::unDelPic() {
    if (m_delPics.length() == 0) {
        return nullptr;
    }
    QString pic = m_delPics.pop();
    m_pics.insert(m_index, pic);
    return pic;
}

QString AppInfo::debugInfo() const {
    if (m_pics.length() == 0) {
        return "pics is not found";
    }

    return QString("%1 [%2/%3] %4")
            .arg(m_picsFolder)
            .arg(m_index + 1)
            .arg(m_pics.length())
            .arg(currPic());
}

int AppInfo::fromJson(const QJsonObject &obj) {
    m_picsFolder = obj["picsFolder"].toString();
    m_tempFolder = obj["tempFolder"].toString();
    m_index = obj["index"].toInt();
    QJsonArray picsArray = obj["pics"].toArray();
            foreach(const QJsonValue &v, picsArray) {
            m_pics.append(v.toString());
        }
    QJsonArray delPicsArray = obj["delPics"].toArray();
            foreach(const QJsonValue &v, delPicsArray) {
            m_delPics.push(v.toString());
        }
    return 0;
}

QJsonObject AppInfo::toJson() const {
    QJsonObject obj;
    obj["picsFolder"] = m_picsFolder;
    obj["tempFolder"] = m_tempFolder;
    QJsonArray picsArray;
            foreach (const QString &s, m_pics) {
            picsArray.append(s);
        };
    obj["pics"] = picsArray;
    obj["index"] = m_index;
    QJsonArray delPicsArray;
            foreach (const QString &s, m_delPics) {
            delPicsArray.append(s);
        };
    obj["delPics"] = delPicsArray;
    return obj;
}

const QString &AppInfo::getPicsFolder() const {
    return m_picsFolder;
}

void AppInfo::setPicsFolder(const QString &mPicsFolder) {
    m_picsFolder = mPicsFolder;
}

const QString &AppInfo::getTempFolder() const {
    return m_tempFolder;
}

void AppInfo::setTempFolder(const QString &mTempFolder) {
    m_tempFolder = mTempFolder;
}

const QStringList &AppInfo::getPics() const {
    return m_pics;
}

void AppInfo::setPics(const QStringList &mPics) {
    m_pics = mPics;
}

int AppInfo::getIndex() const {
    return m_index;
}

void AppInfo::setIndex(int mIndex) {
    m_index = mIndex;
}

const QStack<QString> &AppInfo::getDelPics() const {
    return m_delPics;
}

void AppInfo::setDelPics(const QStack<QString> &mDelPics) {
    m_delPics = mDelPics;
}

