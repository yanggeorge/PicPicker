//
// Created by 杨明 on 2023/5/23.
//

#ifndef PICKPIC_MAINWINDOW_H
#define PICKPIC_MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


private slots:

    void onSourceDirClicked();
    void onTmpDirClicked();
    void onDelClicked();
    void onReDelClicked();

};


#endif //PICKPIC_MAINWINDOW_H
