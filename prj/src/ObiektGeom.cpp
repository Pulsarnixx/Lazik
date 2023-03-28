#include <iostream>
#include <fstream>
#include <limits.h>
#include "ObiektGeom.hh"
#include "Lazik.hh"

using namespace std;



ObiektGeom::ObiektGeom( const char*  sNazwaPliku_BrylaWzorcowa,
		        const char*  sNazwaObiektu,
		        int          KolorID,
            double X_polozenie,double Y_polozenie,double Z_polozenie
		       ):
  _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  
  //Inicjalizacja wektora skali:

  Skala[0] = 20;  Skala[1] = 20;  Skala[2] = 10;

  //Inicjalizacja wektora położenia:

  Polozenie[0] = X_polozenie;  Polozenie[1] = Y_polozenie;  Polozenie[2] = Z_polozenie;

  //Inicjalizacja macierzy rotacji (podstawowo 0 stopni):

  for(int i=0;i<3;++i) {MacierzRot(i,i)=1;}

}

 Wektor2D ObiektGeom::PokazPolozenie2D()const
 {
   Wektor2D Polozenie2D;

   Polozenie2D[0] = Polozenie[0];
   Polozenie2D[1] = Polozenie[1];
   
   return Polozenie2D;
 }

bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
  ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
	 << "    " << _NazwaPliku_BrylaWzorcowa << endl
	 << "    " << _NazwaPliku_BrylaRysowana << endl
	 << endl;
    return false;
  }

int Indeks_Wiersza = 0;


  Wektor3D Wsp;

  StrmWe >> Wsp;
  
  Wektor2D Wsp_min(__DBL_MAX__,__DBL_MAX__);
  Wektor2D Wsp_max(-(__DBL_MAX__),-(__DBL_MAX__)); 

  
  if (StrmWe.fail())return false; 
  
  do {
    
    for(int i = 0;i<cSize;++i){ Wsp[i]= (Wsp[i] * Skala[i]); }
    Wsp = (Rotacja() * Wsp ) + Polozenie;

 
    if(Wsp[2] ==  0 ){
      if(Wsp[0] < Wsp_min[0]) {Wsp_min[0] = Wsp[0];}
      if(Wsp[1] < Wsp_min[1]) {Wsp_min[1] = Wsp[1];}
      if(Wsp[0] > Wsp_max[0]) {Wsp_max[0] = Wsp[0];}
      if(Wsp[1] > Wsp_max[1]) {Wsp_max[1] = Wsp[1];}
    }
    
    StrmWy << Wsp;
    ++Indeks_Wiersza;
    
    if (Indeks_Wiersza >= 4) {
      StrmWy << endl;
      Indeks_Wiersza = 0;
    }
    
    StrmWe >> Wsp;
    
  } while (!StrmWe.fail());

_Obrys.ZmienObrys(Wsp_min,Wsp_max);


  if (!StrmWe.eof()) return false;
  
  return Indeks_Wiersza == 0 && !StrmWy.fail();
}

TypKolizji ObiektGeom::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const
 {  
  
        if(_Obrys.CzySieNaklada(Wsk_Lazik->PokazObrys()) == true) return TK_Kolizja;
       
        return TK_BrakKolizji;
    
 }



