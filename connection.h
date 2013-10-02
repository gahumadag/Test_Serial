#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <cmath>
#include <bitset>
#include <string>
#include <QLabel>

//#define id_ 2
#define numbytes 12
using namespace std;
class connection
{
public:
    connection();
    void setWheel1(float);
    void setWheel2(float);
    void setWheel3(float);
    void setWheel4(float);
    void setKickSpeedx(float);
    void send(int, QLabel**);
    bool conectar(const char*);
    void desconectar();
    void velocityTransformation(double vx_tmp, double vy_tmp, double w);
    int getwheel(int);
    void prt(int i, char*);
private:    
    int port;
    float wheel1, wheel2, wheel3, wheel4, kickspeedx, velx, vely;
    bool spinner,teamYellow;
    char* buffer2;
    int port_usb;
    char bytes;
    char bytes_ar[13];
};

#endif // CONNECTION_H
