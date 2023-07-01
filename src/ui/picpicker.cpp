//
// Created by 杨明 on 2023/6/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PicPicker.h" resolved

#include "picpicker.h"
#include "ui_PicPicker.h"
#include "../model/appconstants.h"
#include <QDebug>
#include <QShowEvent>
#include <QMessageBox>


PicPicker::PicPicker(PicPickerController *controller, QWidget *parent) :
        m_controller(controller), QMainWindow(parent), ui(new Ui::PicPicker) {
    ui->setupUi(this);

    ui->centralwidget->setFixedHeight(Fixed_Height);
    ui->centralwidget->setFixedWidth(Fixed_Width);
    ui->imageLabel->setFixedHeight(Fixed_Height);
    ui->imageLabel->setFixedWidth(Fixed_Width);
}

PicPicker::~PicPicker() {
    delete ui;
}

void PicPicker::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    if (!event->spontaneous()) {
        qDebug() << "show event";
        int result = m_controller->init();
        if (result == 1) {
            QMessageBox::warning(nullptr, "Warning", tr("创建文件失败"));
            return;
        }

        ui->statusbar->showMessage(m_controller->debugInfo());
        if (m_controller->currPic() != nullptr) {
            showImage(m_controller->currPic());
        }
    }
}


void PicPicker::showImage(const QString &pic) {
    QImage image(m_controller->getPicsFolder() + QDir::separator() + pic);
    QImage scaled = image.scaled(Fixed_Width,Fixed_Height, Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaled));
}