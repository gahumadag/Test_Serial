#include "connection.h"

#include <cmath>
#include <bitset>
#include "arduino-serial.hpp"


using namespace std;
connection::connection()
{    
    wheel1=0;
    wheel2=0;
    wheel3=0;
    wheel4=0;
    kickspeedx=0;
    velx=0;
    vely=0;
    spinner=false;
    teamYellow=false;
}


void connection::setWheel1(float wheel){
    wheel1= wheel;
}

void connection::setWheel2(float wheel){
    wheel2 = wheel;
}

void connection::setWheel3(float wheel){
    wheel3 = wheel;
}

void connection::setWheel4(float wheel){
    wheel4 = wheel;
}

void connection::setKickSpeedx(float kick){
    kickspeedx = kick;
}
bool connection::conectar(const char* st){

    port_usb = serialport_init(st , 115200 );
    if(port_usb == -1){
        cout << "Puerto NO abierto" << endl;
        return false;
    }
    else{
        cout << "USB abierto en fd: " << port_usb << endl;
        return true;
    }

}
void connection::desconectar(){
    serialport_close(port_usb);
}

void connection::send(int id_, QLabel** text){


    int i=0;
    int aux2;
    //char bytes;
    bitset<8> mybits[numbytes];

    for(int i = 0; i < numbytes; i++ ){
        mybits[i].reset();
    }

    // Seteo ID robot en Byte's
    switch(id_){
        case 0: {
                // No necesario
                mybits[0].set(6,false);
                mybits[0].set(5, false);
                mybits[0].set(4, false);
                break;
        }
        case 1: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(4);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }
        case 2: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(5);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }
        case 3: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(5);
                    mybits[i].set(4);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }
        case 4: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(6);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }
        case 5: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(6);
                    mybits[i].set(4);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }
        default: {
                i = 0;
                while(i<numbytes){
                    mybits[i].set(6);
                    mybits[i].set(5);
                    mybits[i].set(4);
                    if(i>0) i = i+3;
                    else i++;
                }
                break;
        }

    }

    // Seteo Byte 0
    if(spinner) mybits[0].set(1);
    if(kickspeedx != 0) mybits[0].set(0);
    int aux = mybits[0].to_ulong();


    bytes = (char)aux;
    bytes_ar[0] = (char)aux;

    //write(hSerial,1,&bytes);
    //Sleep(500);
    //cout << "B0: " << aux << endl;

        // Seteo por defecto Byte 1
    mybits[1].set(3);
    // Seteo Signo Vel
    if(wheel1 > 0.0)mybits[1].set(0);
    else mybits[1].reset(0);
    //cout << "dir[0]: " << mybits[1][0]<< "  wheel:  " << wheel1 <<  endl;
    aux = mybits[1].to_ulong();


    bytes = (char)aux;
    bytes_ar[1] = (char)aux;

    //write(hSerial,1,&bytes);
    //Sleep(500);
    //cout << "B1: " << aux << endl;

    // Seteo Velocidad Byte 2
    if(wheel1 > 85)wheel1 = 85;
    else if(wheel1 < -85) wheel1 = -85;
    aux2 = fabs(wheel1) * 4095 /85;
    // Seteo Byte 2

    bytes = (char)(((aux2>>6) | 128)& 191);
    bytes_ar[2] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    int hola =0;
    hola = (unsigned char)bytes;
    //cout << "B2: " << hola << endl;

    // Seteo por defecto Byte 3


    bytes = (char) ((aux2&63) | 192);
    bytes_ar[3] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    hola =0;
    hola = (unsigned char)bytes;
   //cout << "B3: " <<  hola << endl;

    // Seteo por defecto Byte 4
    mybits[4].set(3);
    // seteo ID Rueda
    mybits[4].set(1);
    // Seteo Signo Vel
    if(wheel2 > 0)mybits[4].set(0);
    else mybits[4].reset(0);
    //cout << "dir[1]: " << mybits[4][0]<< "  wheel:  " << wheel2 <<  endl;
    aux = mybits[4].to_ulong();


    bytes = (char) aux;
    bytes_ar[4] = (char) aux;

    //write(hSerial,1,&bytes);
    //Sleep(500);
    //cout << "B4: " << aux << endl;



    // Seteo por defecto Byte 5
    if(wheel2>85)wheel2 = 85;
    else if(wheel2 < -85) wheel2 = -85;
    aux2 = fabs(wheel2) * 4095 /85;
    // Seteo Byte 2


    bytes = (char) ((aux2>>6) | 128)& 191;
    bytes_ar[5] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    hola =0;
    hola = (unsigned char)bytes;
    //cout << "B5: " << hola << endl;

    // Seteo por defecto Byte 6

    bytes = (char) ((aux2&63) | 192);
    bytes_ar[6] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    hola =0;
    hola = (unsigned char)bytes;
    //cout << "B6: " << hola << endl;

    //===========================================================================
    // Seteo por defecto Byte 7
    mybits[7].set(3);
    // Seteo ID Rueda
    mybits[7].set(2);
    // Seteo Signo Vel
    if(wheel3 > 0)mybits[7].set(0);
    else mybits[7].reset(0);
    //cout << "dir[2]: " << mybits[7][0]<< "  wheel:  " << wheel3 <<  endl;
    aux = mybits[7].to_ulong();


    bytes = (char) aux;
    bytes_ar[7] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);
    //cout << "B7: " << aux << endl;

    // Seteo por defecto Byte 8
    if(wheel3>85)wheel3 = 85;
    else if(wheel3 < -85) wheel3 = -85;
    aux2 = fabs(wheel3) * 4095 /85;


    bytes = (char) ((aux2>>6) | 128)& 191;
    bytes_ar[8] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    hola =0;
    hola = (unsigned char)bytes;
    //cout << "B8: " << hola << endl;

    // Seteo por defecto Byte 9


    bytes = (char) (((aux2&63) | 192));
    bytes_ar[9] = bytes;

    //write(hSerial,1,&bytes);
    //Sleep(500);

    hola =0;
    hola = (unsigned char)bytes;
    //cout << "B9: " << hola << endl;

    //command->set_wheel4(wheel4);
    //Seteo por defecto Byte 10
    mybits[10].set(3);
    // Seteo ID Rueda
    mybits[10].set(2);
    mybits[10].set(1);
    // Seteo Signo Vel
    if(wheel4 > 0)mybits[10].set(0);
    else mybits[10].reset(0);
    //cout << "dir[3]: " << mybits[10][0]<< "  wheel:  " << wheel4 <<  endl;
    aux = mybits[10].to_ulong();

    bytes = (char) aux;
    bytes_ar[10] = bytes;

    // Seteo por defecto Byte 11
    if(wheel4>85)wheel4 = 85;
    else if(wheel4 < -85) wheel4 = -85;
    aux2 = fabs(wheel4) * 4095 /85;

    bytes = (char) ((aux2>>6) | 128)& 191;
    bytes_ar[11] = bytes;

    hola =0;
    hola = (unsigned char)bytes;

    // Seteo por defecto Byte 12
    bytes = (char) ((aux2&63) | 192);
    bytes_ar[12] = bytes;

    hola =0;
    hola = (unsigned char)bytes;

    for(int j =0; j < 13; j++){
        char st[8];
        prt(bytes_ar[j],st);
        text[j]->setText(st);

    }
    serialport_write(port_usb,bytes_ar);

}

void connection::velocityTransformation(double vx_tmp, double vy_tmp, double w)
{
    wheel1 = -vx_tmp/2 - sqrt(3)*vy_tmp/2 + w/4;
    wheel2 = sqrt(2)*vx_tmp/2 - sqrt(2)*vy_tmp/2 + w/4;
    wheel3 = (sqrt(2)*vx_tmp/2) + sqrt(2)*vy_tmp/2 + (w/4);
    wheel4 = -vx_tmp/2 + sqrt(3)*vy_tmp/2 + w/4;
}
int connection::getwheel(int id_wheel){
    if(id_wheel == 1) return wheel1;
    else if(id_wheel == 2) return wheel2;
    else if(id_wheel == 3) return wheel3;
    else if(id_wheel == 4) return wheel4;
    else return -1;
}
void connection::prt(int i, char* st)
{
    int j;
    for (j = 7; j >= 0; j--) (1<<j) & i ? st[7-j]='1' : st[7-j]='0';
}

