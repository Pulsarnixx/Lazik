#include <iostream>
#include <fstream>
#include <unistd.h>
#include "rozmiar.hh"
#include "Wektor.hh"
#include "Wektor2D.hh"
#include "Wektor3D.hh"
#include "Macierz.hh"
#include "Macierz3D.hh"
#include "MacierzRotacji.hh"
#include "Kolory.hh"
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObrysXY.hh"
#include "Scena.hh"
#include "Menu.hh"
#include "ProbkaRegolitu.hh"



using namespace std;

int main()
{
{
  Scena Scena1;

    if (!Inicjalizuj_PowierzchnieMarsa(Scena1.getLacze())) return 1;
  {

  Scena1.getLacze().Rysuj();

  if(WyswietlMenu(Scena1) == -1){std::cerr << "Podano zla wartosc w menu!\n";}
  }
} 
std::cout << "\nAktualna ilosc Wektorow: " <<Wektor<double,cSize>::Wyswietl_aktualna()<<endl;
std::cout << "Łaczna ilosc Wektorow: " << Wektor<double,cSize>::Wyswietl_lacznie()<<"\n\n\n";

}
