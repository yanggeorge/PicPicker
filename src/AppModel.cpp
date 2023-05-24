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

void AppModel::setPics(const QStringList &filenames) {
    this->pics = filenames;
}

QStringList AppModel::getPics() {
    return this->pics;
}

int AppModel::getIndex() const {
    return this->index;
}

QString AppModel::currPic() {
    return  pics[index];
}

QString AppModel::nextPic() {
    if (index + 1 == pics.length()) {
        return nullptr;
    }
    index += 1;
    return  pics[index];
}

QString AppModel::prevPic() {
    if (index - 1 == 0 ) {
        return nullptr;
    }
    index -= 1;
    return pics[index];
}


AppModel::AppModel() = default;
