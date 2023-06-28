//
// Created by 杨明 on 2023/6/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AboutDialog.h" resolved

#include "aboutdialog.h"
#include "ui_AboutDialog.h"


AboutDialog::AboutDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);
}

AboutDialog::~AboutDialog() {
    delete ui;
}
