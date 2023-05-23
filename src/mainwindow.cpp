//
// Created by 杨明 on 2023/5/23.
//

#include "mainwindow.h"
#include <QFileDialog>
#include <QIcon>
#include <QtWidgets>

QT_BEGIN_NAMESPACE

class QMenuBar;
class QStatusBar;
class QToolBar;
class QMenu;
class QAction;

QT_END_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Create the toolbar
    QToolBar *toolbar = new QToolBar(this);
    addToolBar(toolbar);

    // Create the "Source Dir" button
    QAction *sourceDirButton = new QAction(QIcon(":/icons/open.png"), tr("Source"), this);
    toolbar->addAction(sourceDirButton);

    // Create the "Tmp Dir" button
    QAction *tmpDirButton = new QAction(QIcon(":/icons/save.png"), tr("Tmp"), this);
    toolbar->addAction(tmpDirButton);

    // Create the "Del" button
    QAction *delButton = new QAction(QIcon(":/icons/cut.png"), tr("Del"), this);
    toolbar->addAction(delButton);

    // Create the "Re-Del" button
    QAction *reDelButton = new QAction(QIcon(":/icons/paste.png"), tr("ReDel"), this);
    toolbar->addAction(reDelButton);

    // Connect the button signals to slots
    connect(sourceDirButton, &QAction::triggered, this, &MainWindow::onSourceDirClicked);
    connect(tmpDirButton, &QAction::triggered, this, &MainWindow::onTmpDirClicked);
    connect(delButton, &QAction::triggered, this, &MainWindow::onDelClicked);
    connect(reDelButton, &QAction::triggered, this, &MainWindow::onReDelClicked);
}

void MainWindow::onSourceDirClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Source Directory"), QDir::homePath());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
    }
}

void MainWindow::onTmpDirClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Tmp Directory"), QDir::homePath());
    if (!dir.isEmpty()) {
        // Do something with the selected directory
    }
}

void MainWindow::onDelClicked()
{
    // Implement the functionality for the "Del" button
}

void MainWindow::onReDelClicked()
{
    // Implement the functionality for the "Re-Del" button
}