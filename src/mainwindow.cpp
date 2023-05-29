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
    // init appModel
    appModel = new AppModel();
    if (int ret = appModel->init() != 0) {
        if (ret == 1) {
            QMessageBox::warning(nullptr, "Warning", tr("创建文件失败"));
            return;
        }
    }
    // Create the toolbar
    toolbar = new QToolBar(this);
    addToolBar(toolbar);

    // Create the "Source Dir" button
    QAction *sourceDirButton = new QAction(QIcon(":/icons/pics-folder"), tr("Pics Folder"), this);
    toolbar->addAction(sourceDirButton);

    // Create the "Temp Dir" button
    QAction *tempDirButton = new QAction(QIcon(":/icons/delete-folder.png"), tr("Temp Folder"), this);
    toolbar->addAction(tempDirButton);

    // Create the "Del" button
    QAction *delButton = new QAction(QIcon(":/icons/delete.png"), tr("Del"), this);
    toolbar->addAction(delButton);
    delButton->setShortcut(QKeySequence(Qt::Key_Up));

    // Create the "un-Del" button
    QAction *unDelButton = new QAction(QIcon(":/icons/undo.png"), tr("Undo"), this);
    toolbar->addAction(unDelButton);
    // interesting CTRL+Z become Command + Z on macOS
//    unDelButton->setShortcut(QKeySequence::fromString("CTRL+Z"));
    unDelButton->setShortcut(QKeySequence(Qt::Key_Down));

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
    connect(tempDirButton, &QAction::triggered, this, &MainWindow::onTempFolderClicked);
    connect(delButton, &QAction::triggered, this, &MainWindow::onDelClicked);
    connect(unDelButton, &QAction::triggered, this, &MainWindow::onUndoClicked);
    connect(backButton, &QAction::triggered, this, &MainWindow::onBackClicked);
    connect(forwardButton, &QAction::triggered, this, &MainWindow::onForwardClicked);

    imageLabel = new QLabel(this);
    imageLabel->setFixedHeight(AppModel::Fixed_Height);
    imageLabel->setFixedWidth(AppModel::Fixed_Width);
    this->setCentralWidget(imageLabel);

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->showMessage(appModel->debugInfo());
    if(appModel->currPic() != nullptr) {
        showImage(appModel->currPic());
    }
}

void MainWindow::onPicsFolderClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Pictures Folder"), appModel->getPicsFolder());
    if (dir.isEmpty()) {
        return;
    }
    // Do something with the selected directory
    qInfo() << dir;
    appModel->setPicsFolder(dir);
    const QStringList &files = QDir(appModel->getPicsFolder()).entryList(QDir::Filter::Files,
                                                                         QDir::SortFlag::Name |
                                                                         QDir::SortFlag::Time);
    QRegularExpression re("(?i)\\.(png|jpg)$", QRegularExpression::CaseInsensitiveOption);
    const QStringList &pics = files.filter(re);
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

void MainWindow::onTempFolderClicked() {
    qInfo() << appModel->getTempFolder();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Temp Folder"), appModel->getTempFolder());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
    }
}

void MainWindow::onDelClicked() {
    if(appModel->currPic() == nullptr) {
        qInfo() << "there no pics left";
        return;
    }
    // Implement the functionality for the "Del" button
    QString delPic = appModel->delCurrPic();

    moveToTempFolder(delPic);

    QString pic = appModel->currPic();
    if (pic == nullptr) {
        imageLabel->setPixmap(QPixmap());
        return;
    }
    pic = appModel->prevPic();
    showImage(pic);
    statusBar->showMessage(appModel->debugInfo());

    QJsonDocument doc(appModel->toJson());
    qDebug() << doc.toJson(QJsonDocument::Compact);
}

void MainWindow::onUndoClicked() {
    // Implement the functionality for the "Re-Del" button
    QString unDelPic = appModel->unDelPic();
    if (unDelPic == nullptr) {
        return;
    }
    moveToPicsFolder(unDelPic);

    QString pic = appModel->currPic();
    if (pic == nullptr) {
        return;
    }
    showImage(pic);
    statusBar->showMessage(appModel->debugInfo());
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

void MainWindow::moveToTempFolder(const QString &qString) {
    QString src = appModel->getPicsFolder() + QDir::separator() + qString;
    QString target = appModel->getTempFolder() + QDir::separator() + qString;
    QFile file(src);
    if (file.rename(target)) {
        qDebug() << "File moved successfully!";
    } else {
        qDebug() << "Failed to move file:" << file.errorString();
    }
}

void MainWindow::moveToPicsFolder(const QString &qString) {
    QString src = appModel->getTempFolder() + QDir::separator() + qString;
    QString target = appModel->getPicsFolder() + QDir::separator() + qString;
    QFile file(src);
    if (file.rename(target)) {
        qDebug() << "File moved successfully!";
    } else {
        qDebug() << "Failed to move file:" << file.errorString();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Closing the application...";
    // store state
    QJsonDocument doc(appModel->toJson());
    QFile old(appModel->getStoreDataPath());
    if (old.exists()) {
        old.rename(appModel->getStoreDataBakPath());
        qDebug() << "data.json exists and rename to data.json.bak !";
    }

    QFile dataJsonFile(appModel->getStoreDataPath());
    if (!dataJsonFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open old";
        return;
    }

    dataJsonFile.write(doc.toJson());
    dataJsonFile.close();
    qDebug() << "File saved";
}
