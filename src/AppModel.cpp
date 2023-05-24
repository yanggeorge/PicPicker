//
// Created by 杨明 on 2023/5/24.
//

#include "AppModel.h"

#include <utility>

QString AppModel::getPicsFolder() {
    return this->picsFolder;
}

void AppModel::setPicsFolder(const QString &dir) {
    this->picsFolder = dir;
}

void AppModel::initPics(const QStringList &filenames) {
    this->pics = filenames;
    this->index = 0;
}

QStringList AppModel::getPics() {
    return this->pics;
}

int AppModel::getIndex() const {
    return this->index;
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

QString AppModel::debugInfo() const {
    if(pics.length() == 0) {
        return "pics hasn't inited";
    }

    return QString("current pic [%1/%2] %3").arg(index+1)
            .arg(pics.length())
            .arg(currPic());
}


AppModel::AppModel() = default;
