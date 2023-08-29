//
// Created by 杨明 on 2023/7/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OpenDialog.h" resolved

#include "opendialog.h"
#include "ui_OpenDialog.h"
#include <QDebug>
#include <QFileDialog>


OpenDialog::OpenDialog(OpenDialogController *controller, QWidget *parent) :
        m_controller(controller), QDialog(parent), ui(new Ui::OpenDialog) {
    ui->setupUi(this);

    ui->picsFolderLineEdit->insert(m_controller->getPicsFolder());
    ui->tempFolderLineEdit->insert(m_controller->getTempFolder());

    connect(ui->picsFolderIcon, SIGNAL(clicked()), this, SLOT(picsFolderSelection()));
    connect(ui->tempFolderIcon, SIGNAL(clicked()), this, SLOT(tempFolderSelection()));
}

OpenDialog::~OpenDialog() {
    delete ui;
}

void OpenDialog::accept() {
    QDialog::accept();
    qDebug() << "accepted";
    const QString &oldPicsFolder = m_controller->getPicsFolder();
    const QString &oldTempFolder = m_controller->getTempFolder();
    const QString &picsFolder = this->ui->picsFolderLineEdit->text();
    const QString &tempFolder = this->ui->tempFolderLineEdit->text();
    this->m_controller->setPicsFolder(picsFolder);
    this->m_controller->setTempFolder(tempFolder);
    if(oldPicsFolder != picsFolder) {
        qDebug() << "change pics folder from [" << oldPicsFolder << "]" << "to [" << picsFolder << "]";
    }
    if(oldTempFolder != tempFolder) {
        qDebug() << "change temp folder from [" << oldTempFolder << "]" << "to [" << tempFolder << "]";
    }
}

void OpenDialog::reject() {
    QDialog::reject();
    qDebug() << "rejected";
}

void OpenDialog::picsFolderSelection() {
    qDebug() << "picsFolderSelection";
    auto old = this->ui->picsFolderLineEdit->text();
    QString directory = QFileDialog::getExistingDirectory(this, tr("select a folder"), old);
    this->ui->picsFolderLineEdit->setText(directory);
}

void OpenDialog::tempFolderSelection() {
    qDebug() << "tempFolderSelection";
    auto old = this->ui->tempFolderLineEdit->text();
    QString directory = QFileDialog::getExistingDirectory(this, tr("select a folder"), old);
    this->ui->tempFolderLineEdit->setText(directory);
}
