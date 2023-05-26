//
// Created by 杨明 on 2023/5/23.
//

#ifndef PICKPIC_MAINWINDOW_H
#define PICKPIC_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "AppModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


private slots:

    void onPicsFolderClicked();
    void onTempFolderClicked();
    void onDelClicked();
    void onUndoClicked();
    void onBackClicked();
    void onForwardClicked();

private:
    void showImage(const QString& pic);

    AppModel* appModel;

    QToolBar* toolbar;
    QStatusBar* statusBar;
    QLabel* imageLabel;

    void moveToTempFolder(const QString &qString);

    void moveToPicsFolder(const QString &qString);
};


#endif //PICKPIC_MAINWINDOW_H
