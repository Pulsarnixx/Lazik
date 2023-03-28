#ifndef Wektor_HH
#define Wektor_HH

#include <iostream>
#include "rozmiar.hh"

template <typename type, unsigned int size>
class Wektor
{   
    
    static int Ilosc_aktualna;
    static int Ilosc_lacznie;
    type tab[size];
    public:
    type operator [] (unsigned int idx) const {return tab[idx];}
    type &operator [] (unsigned int idx){return tab[idx];}

    Wektor() {++Ilosc_aktualna; ++Ilosc_lacznie; for (type &Wsp: tab) Wsp = 0; }
    Wektor(double x,double y ,double z ){++Ilosc_aktualna; ++Ilosc_lacznie; tab[0]=x; tab[1]=y; tab[2]=z; }
    Wektor(double x,double y){++Ilosc_aktualna; ++Ilosc_lacznie; tab[0]=x; tab[1]=y;}
    Wektor(const Wektor<type,size> &Wek);
    ~Wektor(){--Ilosc_aktualna;}
    

    Wektor<type,size> operator = (Wektor<type,size> Wek);
    Wektor<type,size> operator + (Wektor<type,size> Wek)const;
    Wektor<type,size> operator - (Wektor<type,size> Wek)const;
    type operator *(const Wektor<type,size> &Wek) const;
    double operator &(const Wektor<type,size> &Wek) const;
    Wektor<type,size> operator *(double number)const;
    Wektor<type,size> operator /(double number)const;

    static int Wyswietl_aktualna(){return Ilosc_aktualna;};
    static int Wyswietl_lacznie(){return Ilosc_lacznie;};
    
};

template <typename type, unsigned int size>
int Wektor<type,size>::Ilosc_aktualna=0;

template <typename type, unsigned int size>
int Wektor<type,size>::Ilosc_lacznie=0;

template <typename type, unsigned int size>
Wektor<type,size>::Wektor(const Wektor<type,size> &Wek)
{
   ++Ilosc_aktualna; ++Ilosc_lacznie; 
   for (unsigned int i=0; i<size;++i) tab[i]=Wek[i]; 
}


/*
  *  Metoda sluzaca do dodawaia wektorow
  *
  *   v - wektor 
  *
  *  Warunki wstepne:
  *  - wektory musza byc takiego samego rozmiaru
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  
  * Wektor z dodawanymi wartosciami
  */

template <typename type,unsigned int size>
Wektor<type,size> Wektor<type,size>::operator = (Wektor<type,size> Wek)
{
     for (unsigned int i=0;i<size;++i)
    {
        tab[i] = Wek[i];
    }
    return *this;
}


template <typename type,unsigned int size>
Wektor<type,size> Wektor<type,size>::operator+ (Wektor<type,size> Wek) const
{
     for (unsigned int i=0;i<size;++i)
    {
        Wek[i] += tab[i];
    }
    return Wek;
}


  /*
  *  Metoda sluzaca do odejmowania wektorow
  *
  *  v - wektor 
  *
  *  Warunki wstepne:
  *  - wektory musza byc takiego samego rozmiaru
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  
  * Wektor z wartosciami po operacji odejmowania
  */
template <typename type,unsigned int size>
Wektor<type,size> Wektor<type,size>::operator - (Wektor<type,size> Wek)const
{
    Wektor<type,size> temp = *this;
     for (unsigned int i=0;i<size;++i)
    {
        Wek[i] = temp[i] - Wek[i];
    }
    //std::cout << "Wynik odejmowania wektorow: " << Wek << "\n";
    return Wek;
}


template <typename type,unsigned int size>
double Wektor<type,size>::operator & (const Wektor<type,size> &Wek)const
{
    return ((tab[0]*Wek[1])-(tab[1]*Wek[0]));
}

template <typename type,unsigned int size>
type  Wektor<type,size>::operator *(const Wektor<type,size> &Wek) const
{
    type number;
    number = 0; 
    for (unsigned int i=0;i<size;++i)
    {
        number = ((Wek[i]*tab[i]) + number);
    }
    return number;
}


/*
  *  Metoda sluzaca do mnozenia wektora przez liczbe
  *
  *  number - liczba przez ktora bedziemy mnozyc wektor 
  *
  *  Warunki wstepne:
  *  -brak
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  
  *  Wektor z wartosciami po operacji mnozenia wektora przez liczbe 
  */
template <typename type,unsigned int size>
Wektor<type,size> Wektor<type,size>::operator *(double number)const
{
    Wektor<type,size> Wynik;
    for (unsigned int i = 0;i<size;++i)
    {
        Wynik[i] = number * tab[i];
    }
    return Wynik;
}

/*
  *  Metoda sluzaca do dzielenia wektora przez liczbe
  *
  *  number - liczba przez ktora bedziemy mnozyc wektor 
  *
  *  Warunki wstepne:
  *  -brak
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  
  *  Wektor z wartosciami po operacji mnozenia wektora przez liczbe 
  */

template <typename type,unsigned int size>
Wektor<type,size> Wektor<type,size>::operator /(double number)const
{
    if (number == 0 || number == 1) return *this;
    Wektor<type,size> Wynik;
    for (unsigned int i = 0;i<size;++i)
    {
        Wynik[i] = tab[i]/number; //konwersja niejawna??

    }
    return Wynik;
}

/*
  *  Funkcja wczytuje zmienne wektorowe ze standardowego wejscia
  *
  *   s_in  - strumień wejścia (cin, plik ect.),
  *   Wek  - wektor
  *
  *  Warunki wstepne:
  *  -brak
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  *  Odpowiedni stan standardowego wejsca
  * - goodbit - jeżeli operacje powiodły się
  * - failbit - jeżeli operacja wczytania się nie powiodła
  *  
  *  
  */
template <typename type,unsigned int size>
std::istream& operator >> (std::istream &s_in, Wektor<type,size> &Wek)
{

    for (unsigned int i=0;i<size;++i)
    {
        s_in >> Wek[i];
        if(s_in.fail()) return s_in;
    }

return s_in;
}


/*
  *  Funkcja wyswietlajaca zmienne wektorowe na standardowego wyjscie
  *
  *   s_out  - strumień wyjscia (cout, plik ect.),
  *   Wek  - wektor
  *
  *  Warunki wstepne:
  *  -musi istniec zmienna Vector, ktora chcemy wypisac na std wyjsciu
  *
  *  Warunki koncowe:
  *  -brak
  *
  *  Funkcja zwraca:
  * Strumien s_out wraz z zawartoscia (wartosci Wek)
  *  
  *  
  */
template <typename type,unsigned int size>
std::ostream& operator << (std::ostream &s_out, const Wektor<type,size> &Wek)
{   
    for (unsigned int idx = 0; idx < size; ++idx) { s_out << Wek[idx] << " ";}  
    return s_out <<"\n";
}


#endif