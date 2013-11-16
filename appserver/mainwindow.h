#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "server.h"
#include <QString>
#include <iostream>
#include <fstream>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject *obj, QEvent *event);
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void moverMouse();
private:
    Ui::MainWindow *ui;
    void modificarVentana(QString archivo);
    //READ: Declarar un apuntador a un Server llamado ChatServer
    Server *ChatServer;



private slots:
    void on_btnQuit_clicked();
    void on_btnStop_clicked();
    void on_btnStart_clicked();

};

#endif // MAINWINDOW_H
