#ifndef PROBKAREGOLITU_HH
#define PROBKAREGOLITU_HH

#include "ObiektGeom.hh"


class ProbkaRegolitu: public ObiektGeom
{

    public:

    /*!
 * \brief Inicjalizuje Próbkę Regolitu
 *
 * Konstruktor Próbki Regolity. Tworzy obiekt
 * i ustawia odpowiednie jego parametry na podstawie plików
 * z katalagu \bryly_wzorcowe oraz parametrow podanych przez programiste
 * \param[in]  sNazwaObiektu - nazwa obiektu geometrycznego.
 * \param[in]  KolorID - kolor obiektu.
 * \param[in]  X_polozenie - współrzędna x-owa położenia pocz. obiektu.
 * \param[in]  Y_polozenie - współrzędna y-owa położenia pocz. obiektu.
 * \param[in]  Z_polozenie - współrzędna z-owa położenia pocz. obiektu.
 * 
 *
 * \retval -
 */
    ProbkaRegolitu(const char* sNazwaObiektu, unsigned int KolorID, double X_polozenie,double Y_polozenie,
            double Z_polozenie)
    :ObiektGeom("bryly_wzorcowe/szescian2.dat",sNazwaObiektu,KolorID, X_polozenie, Y_polozenie,
             Z_polozenie)
        
        {
        ZmienSkale(2,6,2);
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
        int WezTypObiektu() const override{ return 2 ;}


/*!
 * \brief Sprawdza czy występuje kolizja
 *
 * Sprawdza czy między obrysami próbki i łazika występuje kolizja.
 * \param[in]  Wsk_Lazik - wskaźnik na łazik z którym sprawdzamy czy
 * wystąpiła kolizja.
 * 
 *
 * \retval TK_Kolizja - jeżeli odległość próbki od środka symetrii łazika jest większa niż 0,2 jego szerokości
 * \retval TK_PrzejazdNadProbka - jeżeli nie ma kolizji oraz jest możliwość przejazdu łazika przez próbkę
 * \retval TK_BrakKolizji - w przypadku przeciwnym
 */
 TypKolizji CzyKolizja(const std::shared_ptr<Lazik> & Wsk_Lazik) const override;
};

#endif