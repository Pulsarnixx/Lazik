#include "MacierzRotacji.hh"

Macierz3D Macierz_rotacji(double kat)
{   //dopisac warunek
    kat = (kat * PI / 180);
    Macierz3D temp;
    temp(0,0) = cos(kat); temp(0,1) = -sin(kat);
    temp(1,0) = sin(kat); temp(1,1) = cos(kat); temp(2,2)=1;
    return temp.Transponowana();
}