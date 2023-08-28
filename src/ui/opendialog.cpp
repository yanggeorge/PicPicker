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
}

OpenDialog::~OpenDialog() {
    delete ui;
}

void OpenDialog::accept() {
    QDialog::accept();
    qDebug() << "accepted";
    this->m_controller->setPicsFolder(this->ui->picsFolderLineEdit->text());
    qDebug() << "set pics folder[" << this->m_controller->getPicsFolder() << "]" ;
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
