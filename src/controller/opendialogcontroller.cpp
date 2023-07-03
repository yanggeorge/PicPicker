//
// Created by 杨明 on 2023/7/4.
//

#include "opendialogcontroller.h"


const QString &OpenDialogController::getPicsFolder() const {
    return m_picsFolder;
}

void OpenDialogController::setPicsFolder(const QString &picsFolder) {
    m_picsFolder = picsFolder;
}

const QString &OpenDialogController::getTempFolder() const {
    return m_tempFolder;
}

void OpenDialogController::setTempFolder(const QString &tempFolder) {
    m_tempFolder = tempFolder;
}
