#include "mainwindow.h"
#include "ui_mainwindow.h"


#define USB_port "/dev/ttyUSB0"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(conexion.conectar(USB_port)) cout << "Conectado!!  :)"<< endl;
    else cout << "No Conectado :(" << endl;
    potencia = 15;
    timer2 = new QTimer (this);
    timer2->setInterval(1);
    timer2->start();
    connect(timer2, SIGNAL(timeout()), this, SLOT(recv()));
    conexion.velocityTransformation(0,0,0);
    lb[0] = ui->val_byte1;
    lb[1] = ui->val_byte2;
    lb[2] = ui->val_byte3;
    lb[3] = ui->val_byte4;
    lb[4] = ui->val_byte5;
    lb[5] = ui->val_byte6;
    lb[6] = ui->val_byte7;
    lb[7] = ui->val_byte8;
    lb[8] = ui->val_byte9;
    lb[9] = ui->val_byte10;
    lb[10] = ui->val_byte11;
    lb[11] = ui->val_byte12;
    lb[12] = ui->val_byte13;
    for(int i =0; i< 3; i++)conexion.send(i, lb);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent* e)
{
    int key_tmp = (int)e->text().toAscii()[0];
    //cout << key_tmp << endl;
    if(key_tmp == 27) { // EXIT
        conexion.desconectar();
        exit(1);
    }
    else if(key_tmp == 119){//'w'
        key = 'w';
    }
    else if(key_tmp == 115){ //'s'
        key = 's';
    }
    else if(key_tmp == 97){ //'a'
        key = 'a';
    }
    else if(key_tmp == 100){ //'d'
        key = 'd';
    }
    else if(key_tmp == 103){ //'d'
        key = 'g';
    }
    else if(key_tmp == 104){ //'d'
        key = 'h';
    }
    else if(key_tmp == 43){ //'d'
        potencia += 2;
    }
    else if(key_tmp == 45){ //'d'
        potencia -=2;
    }
    else key = 0;

}

void MainWindow::recv(){

    if(key == 'w'){
        ui->move->setText("Forward");
        conexion.velocityTransformation(0,potencia,0);
    }
    else if(key == 'a'){
        ui->move->setText("Left");
        conexion.velocityTransformation(potencia,0,0);
    }
    else if(key == 's'){
        ui->move->setText("Backward");
        conexion.velocityTransformation(0,-potencia,0);
    }
    else if(key == 'd'){
        ui->move->setText("Right");
        conexion.velocityTransformation(-potencia,0,0);
    }
    else if(key == 'g'){
        ui->move->setText("Turn Right");
        conexion.velocityTransformation(0,0,potencia);
    }
    else if(key == 'h'){
        ui->move->setText("Turn Left");
        conexion.velocityTransformation(0,0,-potencia);
    }
    else {
        conexion.velocityTransformation(0,0,0);
    }
    //cout << potencia << endl;
    QString qStr = QString::number(conexion.getwheel(1));
    ui->Value_w1->setText(qStr);
    qStr = QString::number(conexion.getwheel(2));
    ui->Value_w2->setText(qStr);
    qStr = QString::number(conexion.getwheel(3));
    ui->Value_w3->setText(qStr);
    qStr = QString::number(conexion.getwheel(4));
    ui->Value_w4->setText(qStr);
    for(int i =0; i< 3; i++)conexion.send(i,lb);


}
void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    key = 0;
    ui->move->setText("Stop");

}


