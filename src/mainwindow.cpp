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
        : QMainWindow(parent) {
    appModel = new AppModel();
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

    // Create the "Back" button
    QAction *backButton = new QAction(QIcon(":/icons/back.png"), tr("Previous Pic"), this);
    toolbar->addAction(backButton);
    backButton->setShortcut(QKeySequence(Qt::Key_Left));

    // Create the "Forward" button
    QAction *forwardButton = new QAction(QIcon(":/icons/forward.png"), tr("Next Pic"), this);
    toolbar->addAction(forwardButton);
    forwardButton->setShortcut(QKeySequence(Qt::Key_Right));


    // Connect the button signals to slots
    connect(sourceDirButton, &QAction::triggered, this, &MainWindow::onPicsFolderClicked);
    connect(tmpDirButton, &QAction::triggered, this, &MainWindow::onTmpFolderClicked);
    connect(delButton, &QAction::triggered, this, &MainWindow::onDelClicked);
    connect(reDelButton, &QAction::triggered, this, &MainWindow::onUndoClicked);
    connect(backButton, &QAction::triggered, this, &MainWindow::onBackClicked);
    connect(forwardButton, &QAction::triggered, this, &MainWindow::onForwardClicked);

    imageLabel = new QLabel(this);
    imageLabel->setFixedHeight(AppModel::Fixed_Height);
    imageLabel->setFixedWidth(AppModel::Fixed_Width);
    this->setCentralWidget(imageLabel);

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->showMessage(appModel->debugInfo());
}

void MainWindow::onPicsFolderClicked() {
    auto openDir = appModel->getPicsFolder() == nullptr ? QDir::homePath() : appModel->getPicsFolder();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Pictures Folder"), openDir);
    if (dir.isEmpty()) {
        return;
    }
    // Do something with the selected directory
    qInfo() << dir;
    appModel->setPicsFolder(dir);
    const QStringList &files = QDir(appModel->getPicsFolder()).entryList(QDir::Filter::Files,
                                                                         QDir::SortFlag::Name |
                                                                         QDir::SortFlag::Time);
    QRegExp regexp("\\.(png|jpg)$");
    const QStringList &pics = files.filter(regexp);
    if (pics.length() < 1) {
        //TODO : 这里Information没有显示
        QMessageBox::information(nullptr, "Information", tr("没有找到图片"));
        return;
    }
    qInfo() << QString("there are %1 pics.").arg(pics.length());
    appModel->initPics(pics);
    showImage(appModel->currPic());
    statusBar->showMessage(appModel->debugInfo());
}

void MainWindow::showImage(const QString &pic) {
    QImage image(appModel->getPicsFolder() + QDir::separator() + pic);
    QImage scaled = image.scaled(AppModel::Fixed_Width, AppModel::Fixed_Height, Qt::KeepAspectRatio);
    imageLabel->setPixmap(QPixmap::fromImage(scaled));
}

void MainWindow::onTmpFolderClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Tmp Folder"), QDir::homePath());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
    }
}

void MainWindow::onDelClicked() {
    // Implement the functionality for the "Del" button
}

void MainWindow::onUndoClicked() {
    // Implement the functionality for the "Re-Del" button
}

void MainWindow::onBackClicked() {
    // Implement the functionality for the "Back" button
    QString pic = appModel->prevPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    statusBar->showMessage(appModel->debugInfo());
}

void MainWindow::onForwardClicked() {
    // Implement the functionality for the "Forward" button
    QString pic = appModel->nextPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    statusBar->showMessage(appModel->debugInfo());
}
