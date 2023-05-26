//
// Created by 杨明 on 2023/5/24.
//

#include "AppModel.h"
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonArray>
#include <QJsonParseError>

QString AppModel::getPicsFolder() {
    return picsFolder;
}

QString AppModel::getTempFolder() {
    return tempFolder;
}

void AppModel::setPicsFolder(const QString &dir) {
    picsFolder = dir;
}

void AppModel::initPics(const QStringList &filenames) {
    pics.clear();
    pics.append(filenames);
}

QStringList AppModel::getPics() {
    return pics;
}

int AppModel::getIndex() const {
    return index;
}

QString AppModel::currPic() const {
    if (pics.length() == 0) return nullptr;
    return pics[index];
}

QString AppModel::nextPic() {
    if (pics.length() == 0) return nullptr;
    if (index + 1 == pics.length()) {
        return nullptr;
    }
    index += 1;
    return pics[index];
}

QString AppModel::prevPic() {
    if (pics.length() == 0) return nullptr;
    if (index == 0) {
        return nullptr;
    }
    index -= 1;
    return pics[index];
}


QString AppModel::delCurrPic() {
    auto delPic = pics[index];
    delPics.push(delPic);
    pics.removeAt(index);
    if (index + 1 < pics.length()) {
        index += 1;
    }
    return delPic;
};

QString AppModel::unDelPic() {
    if (delPics.length() == 0) {
        return nullptr;
    }
    QString pic = delPics.pop();
    pics.insert(index, pic);
    return pic;
}

QString AppModel::debugInfo() const {
    if (pics.length() == 0) {
        return "pics is not found";
    }

    return QString("%1 [%2/%3] %4")
            .arg(picsFolder)
            .arg(index + 1)
            .arg(pics.length())
            .arg(currPic());
}


AppModel::AppModel() = default;

int AppModel::init() {
    // firstly, normal init
    index = 0;
    picsFolder = QDir::homePath();
    if (tempFolder == nullptr) {
        QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        qInfo() << "homeDir = " << homeDir;
        QString tmpPath = QDir(homeDir).filePath(DEFAULT_TEMP_DIR);
        qInfo() << "tmpPath = " << tmpPath;
        QDir tmpDir(tmpPath);
        if (!tmpDir.exists()) {
            if (tmpDir.mkpath(tmpPath)) {
                // Directory created successfully
                qInfo() << "tmpPath = " << tmpPath;
            } else {
                // Error creating directory
                return 1;
            }
        } else {
            //TODO Directory already exists
        }
        tempFolder = tmpPath;
    }
    qInfo() << "picsFolder = " << picsFolder;
    qInfo() << "tempFolder = " << tempFolder;
    // secondly, init from data.json
    QString dataJsonPath = this->getStoreDataPath();

    QFile file(dataJsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return 2;
    }

    QByteArray jsonData = file.readAll();
    QJsonParseError error{};
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON: " << error.errorString();
        return 3;
    }

    if (!doc.isObject()) {
        qDebug() << "JSON is not an object";
        return 4;
    }

    this->fromJson(doc.object());
    return 0;
}

QJsonObject AppModel::toJson() const {
    QJsonObject obj;
    obj["picsFolder"] = picsFolder;
    obj["tempFolder"] = tempFolder;
    QJsonArray picsArray;
            foreach (const QString &s, pics) {
            picsArray.append(s);
        };
    obj["pics"] = picsArray;
    obj["index"] = index;
    QJsonArray delPicsArray;
            foreach (const QString &s, delPics) {
            delPicsArray.append(s);
        };
    obj["delPics"] = delPicsArray;
    return obj;
}

int AppModel::fromJson(const QString &jsonString) {
    QJsonParseError error{};
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &error);

    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON: " << error.errorString();
        return 1;
    }

    if (!doc.isObject()) {
        qDebug() << "JSON is not an object";
        return 2;
    }
    this->fromJson(doc.object());
    return 0;
}

int AppModel::fromJson(const QJsonObject &obj) {
    picsFolder = obj["picsFolder"].toString();
    tempFolder = obj["tempFolder"].toString();
    index = obj["index"].toInt();
    QJsonArray picsArray = obj["pics"].toArray();
            foreach(const QJsonValue &v, picsArray) {
            pics.append(v.toString());
        }
    QJsonArray delPicsArray = obj["delPics"].toArray();
            foreach(const QJsonValue &v, delPicsArray) {
            delPics.push(v.toString());
        }
    return 0;
}


QString AppModel::getStoreDataPath() {
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return QDir(homeDir).filePath(APP_DIR + QDir::separator() + "data.json");
}

QString AppModel::getStoreDataBakPath() {
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return QDir(homeDir).filePath(APP_DIR + QDir::separator() + "data.json.bak");
}



