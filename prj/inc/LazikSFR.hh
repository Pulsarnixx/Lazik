#ifndef LAZIKSFR_HH
#define LAZIKSFR_HH
#include <memory>
#include <assert.h>
#include <list>
#include "ObiektGeom.hh"
#include "Lazik.hh"
#include "ProbkaRegolitu.hh"
#include "Scena.hh"

class LazikSFR: public Lazik
{
    std::list<std::shared_ptr <ProbkaRegolitu> > _ListaProbek;

    public:


/*!
 * \brief Inicjalizuje łazik SFR
 *
 * Konstruktor łazika SFR. Tworzy łazik SFR
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
    LazikSFR(double k , double s, double odl,const char* sNazwaPliku_BrylaWzorcowa,
            const char* sNazwaObiektu, int KolorID, double X_polozenie,double Y_polozenie,
            double Z_polozenie)
    :Lazik(k, s, odl, sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, X_polozenie, Y_polozenie,Z_polozenie){}

/*!
 * \brief Zwraca typ obiektu geometrycznego
 *
 * \param[in] -
 * \retval 0 - jeśli jest obiektem geometrycznym
 * \retval 1 - jeśli jest laziekiem
 * \retval 2 - jeśli jest próbką regolitu
 * \retval 3 - jeśli jest lazikiem SFR
 */
    int WezTypObiektu() const override{return 3;};
//Metoda dostępowa
    std::list<std::shared_ptr <ProbkaRegolitu> > &getListaProbek(){return _ListaProbek;};


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
    TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const override;

/*!
 * \brief Umożliwia podniesienie próbki przez łazik SFR.
 *
 * Podnosi próbkę jeżeli to możliwe.Dodatkowo usuwa ją z listy Sceny i dodaje
 * element do swojej własnej listy.
 *
 *  \param[in]  WskProbka - wskaźnik na próbkę, którą podnosimy łazikiem SFR
 *  \param[in]  _Scena - scena na której znajduje się łazik SFR i próbka 
 * \retval -
 */

    void PodjecieProbki(const std::shared_ptr<ProbkaRegolitu> &WskProbka, Scena &_Scena);

/*!
 * \brief Wyświetla posiadane próbki łazika SFR
 *
 *  \param[in] -
 * \retval Listę próbek, które łazik SFR podniósł - jeżeli występują
 * \retval Komunikat o braku próbek - w przypadku przeciwnym
 */
    void WyswietlPosiadaneProbki()const;

/*!
 * \brief Wyświetla informacje o łaziku SFR
 *
 * Wyświetla informacje dotyczące łazika, takie jak:
 * - Nazwę
 * - Położenie
 * - Kąt orientacji
 * - Listę próbek, które podniósł łazik
 * \param[in] -
 * \retval -
 */
    virtual void WyswietlInformacje()const override{   
    std::cout<<"  Nazwa: "<<WezNazweObiektu()<<std::endl;
    std::cout<<"Polozenie (x,y,z): "<<PokazPolozenie();
    std::cout<<"Orientacja [st]: "<<Kat()<<std::endl;
    std::cout<<"Lista próbek:\n"; WyswietlPosiadaneProbki(); std::cout<<"\n";

}
    
 
/*!
 * \brief Przesuwa podnoszoną próbkę do środka łazika SFR
 *
 * \param[in] -
 * \retval -
 */ 
    void PrzesuniecieProbki();  

/*!
 * \brief Przesuwa łazik  SFR na zadaną odległość oraz jego próbki
 *
 * \param[in] _Scena - Scena na której znajduję się łazik
 * \retval -
 */
    void Przesuniecie(Scena &_Scena)override;

};



#endif