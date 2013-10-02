#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <QKeyEvent>
#include<QMainWindow>
#include<QMessageBox>
#include<QTimer>
#include <QDebug>
#include "connection.h"
#include <QString>
#include <sstream>
#include <QLabel>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
public slots:
    void recv();
private:
    Ui::MainWindow *ui;
    QTimer *timer2;
    connection conexion;
    int usb;
    char key;
    int potencia;
    QLabel *lb[13];
};

#endif // MAINWINDOW_H
