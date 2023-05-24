//
// Created by 杨明 on 2023/5/23.
//

#ifndef PICKPIC_MAINWINDOW_H
#define PICKPIC_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


private slots:

    void onPicsFolderClicked();
    void onTmpFolderClicked();
    void onDelClicked();
    void onUndoClicked();
    void onBackClicked();
    void onForwardClicked();

private:
    QString picsFolder = QString{};
    QString tmpFolder = QString{};

    QToolBar* toolbar;
    QStatusBar* statusBar;
    QLabel* imageLabel;

    const int fixedHeight = 600;
    const int fixedWidth = 800;
};


#endif //PICKPIC_MAINWINDOW_H
