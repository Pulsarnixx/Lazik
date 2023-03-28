#ifndef LAZIK_HH
#define LAZIK_HH

#include <iostream>
#include <unistd.h>
#include "ObiektGeom.hh"

class Scena;

class Lazik : public ObiektGeom
{


    double kat_orientacji;
    double szybkosc;
    double odleglosc_do_przejechania;

    public:

/*!
 * \brief Inicjalizuje Łazik
 *
 * Konstruktor łazika. Tworzy obiekt
 * i ustawia odpowiednie jego parametry na podstawie plików
 * z katalagu \bryly_wzorcowe oraz parametrow podanych przez programiste.
 * \param[in]  k - kąt orientacji łazika
 * \param[in]  s - szybkość łazika
 * \param[in]  odl - odległość łazika
 * \param[in]  sNazwaPliku_BrylaWzorcowa - nazwa pliku wzorcowego do rysowania.
 * \param[in]  sNazwaObiektu - nazwa obiektu geometrycznego.
 * \param[in]  KolorID - kolor obiektu.
 * \param[in]  X_polozenie - współrzędna x-owa położenia pocz. obiektu.
 * \param[in]  Y_polozenie - współrzędna y-owa położenia pocz. obiektu.
 * \param[in]  Z_polozenie - współrzędna z-owa położenia pocz. obiektu.
 * 
 *
 * \retval -
 */
    Lazik(double k , double s, double odl,const char* sNazwaPliku_BrylaWzorcowa,
            const char* sNazwaObiektu, int KolorID, double X_polozenie,double Y_polozenie,
            double Z_polozenie)
    :ObiektGeom(sNazwaPliku_BrylaWzorcowa,
             sNazwaObiektu,  KolorID, X_polozenie, Y_polozenie,
             Z_polozenie)
    {
                kat_orientacji = k;
                szybkosc = s;
                odleglosc_do_przejechania = odl;
    }

/*!
 * \brief Zwraca typ obiektu geometrycznego
 *
 * \param[in] -
 * \retval 0 - jeśli jest obiektem geometrycznym
 * \retval 1 - jeśli jest laziekiem
 * \retval 2 - jeśli jest próbką regolitu
 * \retval 3 - jeśli jest lazikiem SFR
 */
    int WezTypObiektu() const override{ return 1 ;}

/*!
 * \brief Wyświetla informacje o łaziku
 *
 * Wyświetla informacje dotyczące łazika, takie jak:
 * - Nazwę
 * - Położenie
 * - Kąt orientacji
 * \param[in] -
 * \retval -
 */

    virtual void WyswietlInformacje()const{   
    std::cout<<"  Nazwa: "<<WezNazweObiektu()<<std::endl;
    std::cout<<"Polozenie (x,y,z): "<<PokazPolozenie();
    std::cout<<"Orientacja [st]: "<<kat_orientacji<<std::endl;

}




    //Metody dostępowe
    double &Kat(){return kat_orientacji;};
    double Kat()const{return kat_orientacji;};
    double &Szyb(){return szybkosc;};
    double Szyb()const{return szybkosc;};
    double &Odl(){return odleglosc_do_przejechania;};
    double Odl()const{return odleglosc_do_przejechania;};


    //Metody ruchu łazika
/*!
 * \brief Przesuwa łazik na zadaną odległość
 *
 * \param[in] _Scena - Scena na której znajduję się łazik
 * \retval -
 */
    virtual void Przesuniecie(Scena &_Scena);
/*!
 * \brief Obróca łazik o zadany kąt
 *
 * \param[in] kat - wartość kąta w stopniach o jaki chcemy go obrócić
 * \param[in] _Scena - Scena na której znajduję się łazik
 * \retval -
 */
    void Obrot(double kat,Scena &_Scena);

/*!
 * \brief Dodaje wartość do kąta orientacji łazika.
 *
 * Do kąta orientacji łazika dodaje odpowiednią wartość kąta.
 * \param[in] ZmianaKata - kąt w stopniach który chcemy dodać do aktualnej wartości kąta orientacji
 * \retval -
 */
    void DodajKatOrientacji(double ZmianaKata){kat_orientacji += ZmianaKata; if(kat_orientacji > 360){kat_orientacji -=360;}}
/*!
 * \brief Zwraca wektor 2D prędkości łazika
 *
 * \param[in] -
 * \retval Wektor prędkości łazika w postaci wektora 2D
 */
    Wektor2D WektorPredkosci()const;

/*!
 * \brief Sprawdza czy występuje kolizja
 *
 * Sprawdza czy między dwoma obrysami łazików wystąpiła kolizja.
 * \param[in]  Wsk_Lazik - wskaźnik na łazik z którym sprawdzamy czy
 * wystąpiła kolizja
 * 
 *
 * \retval TK_Kolizja - jeżeli kolizja wystąpiła
 * \retval TK_BrakKolizji w przypadku przeciwnym
 */
    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const override;

/*!
 * \brief Umożliwia podniesienie próbki przez łazik.
 *
 * Sprawdza czy łazik jest odpowiednim typem łazika dostosowanym do
 * podnoszenia próbek (czy jest łazikiem SFR). Jeśli tak - umożliwia 
 * podnoszenie próbki ze sceny, a następnie usuwa je z listy sceny.
 * \param[in]  Scena - Scena na której znajduje się łazik
 *
 * \retval Listę próbek, które podniósł łazik SFR, jeżeli operacja podnoszenia była możliwa.
 * \retval Komunikat o braku próbki w okolicy - jeżeli łazik SFR nie znajduje się blisko próbki
 * \retval Komunikat o braku możliwości wykonania akcji - jeżeli aktywny łazik nie jest łazikiem SFR
 */  
    void PodniesienieProbki(Scena &Scena);
};




#endif