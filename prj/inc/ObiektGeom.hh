#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include <memory>
#include "Wektor3D.hh"
#include "Macierz3D.hh"
#include "MacierzRotacji.hh"
#include "ObrysXY.hh"
#include "TypKolizji.hh"


#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

class Lazik;


class ObiektGeom {
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;
    Wektor3D  Skala;
    Wektor3D  Polozenie;
    Macierz3D MacierzRot;
    ObrysXY _Obrys;
  
  public:


/*!
 * \brief Inicjalizuje Obiekt Geometryczny
 *
 * Konstruktor Obiektu Geometrycznego. Tworzy obiekt
 * i ustawia odpowiednie jego parametry na podstawie plików
 * z katalagu \bryly_wzorcowe oraz parametrow podanych przez programiste
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
    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID, 
                double X_polozenie,double Y_polozenie,double Z_polozenie);

    virtual ~ObiektGeom() = default;

/*!
 * \brief Zwraca ID koloru obiektu geometrycznego
 *
 * \param[in] -
 * \retval _KolorID - wartość ID koloru obiektu
 */
    int WezKolorID() const { return _KolorID; }
/*!
 * \brief Zwraca typ obiektu geometrycznego
 *
 * \param[in] -
 * \retval 0 - jeśli jest obiektem geometrycznym
 * \retval 1 - jeśli jest laziekiem
 * \retval 2 - jeśli jest próbką regolitu
 * \retval 3 - jeśli jest lazikiem SFR
 */
    virtual int WezTypObiektu() const { return 0;}

/*!
 * \brief Wyswietla Informacje Obiektu Geometryczneog
 *
 * Zapisuje do pliku powierzchnię w postaci siatki
 * oraz przekazuje nazwę tego pliku do łącza do gnuplota.
 * To spowoduje, że program gnuplot będzie rysował
 * powierzchnie na podstawie danych w tym pliku.
 * \param[in]  -
 * \retval -
 */
    void WyswietlInformacje()const;
/*!
 * \brief Zmienia kolor Obiektu Geometrycznego
 *
 * Zmienia wartość ID_Koloru na podaną przez argument funckji
 * \param[in]  ID_Koloru - wartość całkowita przypisana do koloru na który chcemy zmienić
 *                         aktulany kolor obiektu
 * \retval -
 */
    void ZmienKolor(int ID_Koloru){_KolorID = ID_Koloru;}
/*!
 * \brief Zmienia skale Obiektu Geometrycznego
 *
 * Zmienia współrzędne wektora skali obiektu 
 * \param[in]  ID_Koloru - wartość całkowita przypisana do koloru na który chcemy zmienić
 *                         aktulany kolor obiektu
 * \retval -
 */
    void ZmienSkale(double x, double y, double z){Skala[0]=x;Skala[1]=y;Skala[2]=z;}

/*!
 * \brief Metoda dostępowa do nazwy obiektu geometrycznego
 *
 * \param[in] -
 * \retval Nazwę obiektu geometrycznego
 */
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }

/*!
 * \brief Metoda dostępowa do nazwy pliku obiektu geometrycznego
 *
 * \param[in] -
 * \retval Nazwę pliku obiektu geometrycznego
 */
    const std::string & WezNazwePliku_BrylaRysowana() const
                 { return _NazwaPliku_BrylaRysowana; }


/*!
 * \brief Zwraca aktualne położenie obiektu
 *
 * \param[in]  -
 * \retval -
 */
    Wektor3D PokazPolozenie()const{return Polozenie;}

/*!
 * \brief Metoda dostępowa umożliwiająca zmianę wartości wektora położenia.
 *
 * \param[in]  -
 * \retval Adres do wektora 3D położenia obiektu geometrycznego.
 * 
 */
    Wektor3D &ZamienIstniejacePolozenie(){return Polozenie;}


/*!
 * \brief Pokazuje wektor położenia obiektu jako wektor 2D
 *
 * \param[in]  -
 * \retval Wektor położenia obiektu w postaci wektora 2D.
 * 
 */
    Wektor2D PokazPolozenie2D()const;

/*!
 * \brief Zwraca aktualny obrys obiektu
 *
 * \param[in]  -
 * \retval Obrys obiektu geometrycznego
 */
    ObrysXY PokazObrys()const{return _Obrys;} 

/*!
 * \brief Zmienia wektor położenia obiektu geometrycznego
 *
 * Funkcja dodaje do aktualnego położenia, wektor położenia,
 * który został podany jako argument funckji.
 * \param[in] WektorOdleglosci - wektor o który zmieniamy wektor położenia.
 * 
 *
 * \retval -
 */
    void ZmienPolozenie(const Wektor3D &WektorOdleglosci){{Polozenie=Polozenie + WektorOdleglosci;}}


/*!
 * \brief Zwraca adres Macierzy Rotacji.
 *
 * Funkcja zwraca adres do macierzy rotacji
 * przypisanej do obiektu geometrycznego.
 * 
 * \param[in]  -
 * \retval -
 */
    Macierz3D &Rotacja(){return MacierzRot;};

/*!
 * \brief Zwraca wartość Macierzy Rotacji.
 *
 * Funkcja zwraca wartość aktualnej macierzy
 * rotacji, które jest przypisana do obiektu.
 * 
 * \param[in]  -
 * \retval -
 */
    Macierz3D Rotacja()const{return MacierzRot;};

/*!
 * \brief Przelicza i zapisuje wierzchołki ObiektGeom do pliku dla gnuplota 
 *
 * Zapisuje do pliku w katalogu /pliki_do_rysowania 
 * wierzchołki obiektu, które posłużą do rysowania
 * przez program gnuplot
 * \param[in]  -
 * \retval true - operacja powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
    bool Przelicz_i_Zapisz_Wierzcholki();

/*!
 * \brief Sprawdza czy występuje kolizja
 *
 * Sprawdza czy między dwoma obrysami obiektów wystąpiła kolizja.
 * \param[in]  Wsk_Lazik - wskaźnik na łazik z którym sprawdzamy czy
 * wystąpiła kolizja
 * 
 *
 * \retval TK_Kolizja - jeżeli kolizja wystąpiła
 * \retval TK_BrakKolizji w przypadku przeciwnym
 */
  virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik) const;
				     
};


#endif
