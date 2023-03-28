#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <cassert>
#include "Wektor.hh"

template <typename Mtype,int Msize>
class Macierz
{
    Wektor<Mtype,cSize>  col [cSize];
    public:
    /*
  *  Metoda przeciazenia ()
  *
  *   row - indeks wiersza Macierzy
  *   column - indeks kolumny Macierzy
  *
  *  Warunki wstepne:
  *  -brak
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  referencje do odpowiedniego elementu w macierzy
  */ 
    Mtype &operator() (unsigned int row, unsigned int column){return col[column][row];}
    /*
  *  Metoda przeciazenia ()
  *
  *   row - indeks wiersza Macierzy
  *   column - indeks kolumny Macierzy
  *
  *  Warunki wstepne:
  *  -brak
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Wartosc odpowiedniego elementu w Macierzy
  */
    Mtype operator()(unsigned int row, unsigned int column) const{return col[column][row];}
    Wektor<Mtype,Msize>  Column (unsigned int idx)const{ return col[idx];}
    Wektor<Mtype,Msize> &Column (unsigned int idx){return col[idx];}
    Macierz<Mtype,Msize> Transponowana()const;
    Wektor<Mtype,Msize> operator*(const Wektor<Mtype,Msize> &v) const;
    bool CzyZerowaMacierz()const;
    void ZamianaWierszyTransp(unsigned int idx,unsigned int idx2);
    void ZerowanieKolumnyTransp(unsigned int idx);
    Mtype Wyznacznik()const;

};
 /*
  *  Metoda sluzaca do transponowania macierzy
  *
  *
  *  Warunki wstepne:
  *  -istnienie macierzy
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Macierz po operacji transponowania
  */   
template<typename Mtype,int Msize>
Macierz<Mtype,Msize> Macierz<Mtype,Msize>::Transponowana()const
{
    Macierz<Mtype,cSize>temp;
    for(int i=0; i<cSize ;++i)
    {
        for(int j =0; j<cSize; ++j)
        {
            temp.col[i][j] = col[j][i];
        }
    }
    //std::cout<<temp;
    return temp;
}
 /*
  *  Metoda sluzaca do mnozenia macierzy przez wektor
  *
  *  v- wektor przez ktory mnozymy macierz
  * 
  *  Warunki wstepne:
  *  -istnienie macierzy i wektora o takich samych rozmiarach
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Wektor jako wynik operacji.
  */ 

template<typename Mtype,int Msize>
Wektor<Mtype,Msize> Macierz<Mtype,Msize>::operator*(const Wektor<Mtype,Msize> &v) const
{
    Wektor<Mtype,cSize> Wynik;
    Macierz<Mtype,cSize> B = *this;
    for(int i=0;i<cSize;++i)
    {
        Wynik[i]= B.Column(i) * v;
    }
    return Wynik;
}

 /*
  *  Metoda sluzaca do sprawdzania czy macierz posiada wiersze z samymi zerami
  * 
  *  Warunki wstepne:
  *  -istnienie macierzy
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  true - jesli znalezniona jakis wiersz
  *  false - jesli nie znaleziono wiersza
  */ 
template<typename Mtype,int Msize>
bool Macierz<Mtype,Msize>::CzyZerowaMacierz()const
{   
    Wektor<Mtype,cSize> temp;// wektor {0,0,0}
    for (int i=0;i<cSize;++i)
    {
       if (Column(i)==temp) return true;
    }
    return false;
    
}


 /*
  *  Metoda sluzaca do zamiany dwoch wierszy ze soba
  *   
  *   idx - indeks pierwszwgo wiersza
  *   idx - indeks drugiego wiersza
  * 
  *  Warunki wstepne:
  *  -istnienie macierzy
  *  -indeksy oznaczajace numer wiersza musza byc < od rozmiaru macierzy
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Zamienia wiersze w macierzy pierwotnej
  */
template<typename Mtype,int Msize>
void Macierz<Mtype,Msize>::ZamianaWierszyTransp(unsigned int idx,unsigned int idx2)
{
    assert((idx < cSize) && (idx2 < cSize));
    std::swap(Column(idx),Column(idx2));
}



/*
  *  Metoda sluzaca do wyliczania wyznacznika
  * 
  *  Warunki wstepne:
  *  -istnienie macierzy kwadratowej
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Wartosc wyznacznika.
  */
template<typename Mtype,int Msize>
Mtype Macierz<Mtype,Msize>::Wyznacznik()const
{   
    Macierz<Mtype,cSize> Wynik = *this;
    Mtype temp;
    temp=0;
    short int znak = 1;
    if(Wynik.CzyZerowaMacierz()){return temp;} 

    for (int j=0 ;j<cSize -1 ; ++j) {  
        if((col[j][j])==temp){
            if((col[j][j+1]) != temp) {Wynik.ZamianaWierszyTransp(j,j+1);}
            else {Wynik.ZamianaWierszyTransp(j,j+2);}
            znak *= -1;
            }
        Wynik.ZerowanieKolumnyTransp(j); 
        }
    Mtype wynik = Wynik(0,0); 
    for (int i=1; i <cSize ; ++i)   { wynik =(wynik *Wynik.col[i][i]) ;}  
    wynik = (wynik * znak);
    if(wynik == temp ) return temp;
    else return wynik;
}

 /*
  *  Metoda sluzaca do wyzerowywania kolumny aby powstawala czesciowo macierz schodkowa
  *  
  * 
  *  idx - indeks kolumny 
  * 
  *  np.
  *  dla macierzy:
  *  2 1 1
  *  2 2 3                po wyborze idx = 0 kolumna zostanie wyzerowana w dol od elementu [idx][idx]
  *  1 1.5 1
  * 
  * po operacji:
  * 
  *  2 1 1
  *  0 1 2
  *  0 1 0.5
  *
  *  Warunki wstepne:
  *  -istnienie macierzy kwadratowej
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Wyzerowanie kolumny w dol od elementu idx idx 
  */
template<typename Mtype,int Msize>
void Macierz<Mtype,Msize>::ZerowanieKolumnyTransp(unsigned int idx)
{  
    assert(idx < cSize);
    for (int i = idx+1;i<cSize;++i) // zerowanie kolumny "w dol" od elementu idx idx 
    {
    Column(i)=(Column(i) - (Column(idx) * (this->col[i][idx]/this->col[idx][idx]))); 
    }
}


 
 /*
  *  Funkcja wczytuje obiekty Macierz ze standardowego wejscia
  *
  *   s_in  - strumień wejścia (cin, plik ect.),
  *   Mac  - Macierz
  *
  *  Warunki wstepne:
  *  - funkcja bazuje na przeciazeniu operatora wejscia dla wektorow 
  *    (bez tego funkcja nie dziala poprawnie)
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Odpowiedni stan standardowego wejsca
  * - goodbit - jeżeli operacje powiodły się
  * - failbit - jeżeli operacja wczytania się nie powiodła
  *  
  */
template<typename Mtype,int Msize>
std::istream& operator >> (std::istream &s_in, Macierz<Mtype,Msize> &Mac)
{   
    for (int i =0;i<cSize;++i){
        s_in >> Mac.Column(i);
        if(s_in.fail()) return s_in;
    }
    return s_in;
}



/*
  *  Funkcja wyswietla obiekty Macierz na standardowe wyjscie
  *
  *   s_out  - strumień wyjscia (cout, plik ect.),
  *   Mac  - Macierz
  *
  *  Warunki wstepne:
  *  - funkcja bazuje na przeciazeniu operatora wyjscia dla wektorow 
  *    (bez tego funkcja nie dziala poprawnie)
  *  - istnienie w programie obiekty typu Macierz
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Strumien s_out wraz z zawartoscia (wartosci Macierzy)
  *  
  */
template<typename Mtype,int Msize>
std::ostream& operator << (std::ostream &s_out, const Macierz<Mtype,Msize> &Mac)
{   
    for (int i =0;i<cSize;++i){ s_out  << Mac.Column(i);} 
    return s_out;
}


#endif