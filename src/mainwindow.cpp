//
// Created by 杨明 on 2023/5/23.
//

#include "mainwindow.h"
#include <QFileDialog>
#include <QIcon>
#include <QtWidgets>
#include <QDebug>
#include <QStringList>

QT_BEGIN_NAMESPACE

class QMenuBar;
class QStatusBar;
class QToolBar;
class QMenu;
class QAction;
class QMessageBox;

QT_END_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Create the toolbar
    toolbar = new QToolBar(this);
    addToolBar(toolbar);

    // Create the "Source Dir" button
    QAction *sourceDirButton = new QAction(QIcon(":/icons/pics-folder"), tr("Pics Folder"), this);
    toolbar->addAction(sourceDirButton);

    // Create the "Tmp Dir" button
    QAction *tmpDirButton = new QAction(QIcon(":/icons/delete-folder.png"), tr("Tmp Folder"), this);
    toolbar->addAction(tmpDirButton);

    // Create the "Del" button
    QAction *delButton = new QAction(QIcon(":/icons/delete.png"), tr("Del"), this);
    toolbar->addAction(delButton);

    // Create the "Re-Del" button
    QAction *reDelButton = new QAction(QIcon(":/icons/undo.png"), tr("Undo"), this);
    toolbar->addAction(reDelButton);

    // Connect the button signals to slots
    connect(sourceDirButton, &QAction::triggered, this, &MainWindow::onPicsFolderClicked);
    connect(tmpDirButton, &QAction::triggered, this, &MainWindow::onTmpFolderClicked);
    connect(delButton, &QAction::triggered, this, &MainWindow::onDelClicked);
    connect(reDelButton, &QAction::triggered, this, &MainWindow::onUndoClicked);

    imageLabel = new QLabel(this);
    imageLabel->setFixedHeight(fixedHeight);
    imageLabel->setFixedWidth(fixedWidth);
    this->setCentralWidget(imageLabel);

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->showMessage(tr("Ready"));
}

void MainWindow::onPicsFolderClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Pictures Folder"), QDir::homePath());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
        qInfo() << dir;
        picsFolder  = dir ;
        const QStringList &files = QDir(dir).entryList(QDir::Filter::Files,
                                                       QDir::SortFlag::Name | QDir::SortFlag::Time);
        QRegExp regexp("\\.(png|jpg)$");
        const QStringList &pics = files.filter(regexp);
        if (pics.length() < 1) {
            QMessageBox::information(nullptr, "Information", tr("没有找到图片"));
            return;
        }
        qInfo() << pics[0];
        QImage image(dir + QDir::separator() + pics[0]);
        image.scaled(fixedWidth, fixedHeight);
        imageLabel->setPixmap(QPixmap::fromImage(image.scaled(fixedWidth, fixedHeight, Qt::KeepAspectRatio)));
//        foreach(const QString& pic, pics) {
//            qInfo() << pic ;
//        }
    }
}

void MainWindow::onTmpFolderClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Tmp Folder"), QDir::homePath());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
    }
}

void MainWindow::onDelClicked()
{
    // Implement the functionality for the "Del" button
}

void MainWindow::onUndoClicked()
{
    // Implement the functionality for the "Re-Del" button
}