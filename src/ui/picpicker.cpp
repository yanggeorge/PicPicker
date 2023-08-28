//
// Created by 杨明 on 2023/6/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PicPicker.h" resolved

#include "picpicker.h"
#include "ui_PicPicker.h"
#include "../model/appconstants.h"
#include "aboutdialog.h"
#include "opendialog.h"
#include <QDebug>
#include <QShowEvent>
#include <QMessageBox>
#include <QJsonDocument>


PicPicker::PicPicker(PicPickerController *controller, QWidget *parent) :
        m_controller(controller), QMainWindow(parent), ui(new Ui::PicPicker) {
    ui->setupUi(this);

    ui->centralwidget->setFixedHeight(Fixed_Height);
    ui->centralwidget->setFixedWidth(Fixed_Width);
    ui->imageLabel->setFixedHeight(Fixed_Height);
    ui->imageLabel->setFixedWidth(Fixed_Width);

    //Menu
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openPicsFolder()));

    //toolbar
    connect(ui->actionDelPic, SIGNAL(triggered()), this, SLOT(delPic()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionPrevPic, SIGNAL(triggered()), this, SLOT(prevPic()));
    connect(ui->actionNextPic, SIGNAL(triggered()), this, SLOT(nextPic()));

    ui->actionDelPic->setShortcut(QKeySequence(Qt::Key_Up));
    ui->actionUndo->setShortcut(QKeySequence(Qt::Key_Down));
    ui->actionNextPic->setShortcut(QKeySequence(Qt::Key_Right));
    ui->actionPrevPic->setShortcut(QKeySequence(Qt::Key_Left));
    ui->actionOpen->setShortcut(QKeySequence::Open);
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
            QMessageBox::warning(nullptr, "Warning", tr("fail to create file"));
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
    QImage scaled = image.scaled(Fixed_Width, Fixed_Height, Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(QPixmap::fromImage(scaled));
}

void PicPicker::about() {
    AboutDialog dlg;
    dlg.exec();
}

void PicPicker::openPicsFolder() {
    qDebug() << "open Pics Folder";
    OpenDialogController controller;
    controller.setPicsFolder(m_controller->getPicsFolder());
    controller.setTempFolder(m_controller->getTempFolder());

    OpenDialog dlg(&controller);
    dlg.exec();
    qDebug() << "openPicsFolder closed" ;
    if(m_controller->getPicsFolder() != controller.getPicsFolder()){
        qDebug() << "pics Folder changed!" ;
        m_controller->init(controller.getPicsFolder());
        auto pic = m_controller->currPic();
        if(pic == nullptr) {
            return;
        }
        showImage(pic);
        ui->statusbar->showMessage(m_controller->debugInfo());
    }
}

void PicPicker::delPic() {
    QString delPic = m_controller->delCurrPic();
    qDebug() << "del Pic[" << delPic << "]";

    QString pic = m_controller->currPic();
    if (pic == nullptr) {
        ui->imageLabel->setPixmap(QPixmap());
        return;
    }
    pic = m_controller->prevPic();
    showImage(pic);
    ui->statusbar->showMessage(m_controller->debugInfo());
}

void PicPicker::undo() {
    QString unDelPic = m_controller->unDelPic();
    if (unDelPic == nullptr) {
        return;
    }

    QString pic = m_controller->currPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    ui->statusbar->showMessage(m_controller->debugInfo());
}

void PicPicker::prevPic() {
    QString pic = m_controller->prevPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    ui->statusbar->showMessage(m_controller->debugInfo());
}

void PicPicker::nextPic() {
    QString pic = m_controller->nextPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    ui->statusbar->showMessage(m_controller->debugInfo());
}

void PicPicker::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing the application...";
    m_controller->close();
}
