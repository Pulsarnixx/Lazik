#ifndef SCENA_HH
#define SCENA_HH

#include <memory>
#include <assert.h>
#include <list>
#include <ctime>
#include <cstdlib>
#include "ObiektGeom.hh"
#include "Lazik.hh"
#include "LazikSFR.hh"
#include "ProbkaRegolitu.hh"
#include "lacze_do_gnuplota.hh"
#include "Kolory.hh"
#include "PowierzchniaMarsa.hh"



class Scena
{   
    
    PzG::LaczeDoGNUPlota Lacze;
    
    std::shared_ptr<Lazik> AktywnyLazik;
    std::list<std::shared_ptr<ObiektGeom>> ObiektySceny;  
    

    public:

/*!
 * \brief Inicjalizuje Scenę
 *
 * Konstruktor tworzy scenę na której będą znajdować się obiekty.
 * Jednocześnie inicjalizuje łączę, tworzy skale sceny i inicjalizuje wszystkie
 * obiekty, które będą znajdować się na scenie.
 * \param[in] -
 * \retval -
 */   
    Scena();

    //Metody dostepowe
    PzG::LaczeDoGNUPlota &getLacze(){return Lacze;}
    PzG::LaczeDoGNUPlota getLacze()const{return Lacze;}

    std::shared_ptr<Lazik> &setLazik(){return AktywnyLazik;}
    std::shared_ptr<Lazik> getLazik()const{return AktywnyLazik;}

    std::list<std::shared_ptr<ObiektGeom>> &getObiektySceny(){return ObiektySceny;}
    //Metoda wyboru lazika

/*!
 * \brief Przeciążenie operatora ()
 *
 * Umożliwia posługiwanie się łazikiem na scenie o odpowiednim numerze.
 * \param[in] Nr_Lazika - numer łazika, z którym chcemy coś zrobić
 * \retval Wskaźnik na wybrany łazik
 */  
    std::shared_ptr<Lazik> operator()(unsigned int Nr_Lazika);

/*!
 * \brief Zmienia aktywny łazik
 *
 * Umożliwia zmianę aktywnego łazika na ten wybrany przez użytkownika.
 * \param[in] Nr_Lazika - numer łazika, który ma zostać aktywowany.
 * \retval - jesli wszystko się powiedzie
 * \retval Komunikat o braku łazika, jeżeli wybrano inny numer niż te dostępne.
 */     
    void ZmianaAktywnyLazik(unsigned int Nr_Lazika);

/*!
 * \brief Wyświetla próbki znajdujące się na scenie
 *
 * \param[in] -
 * \retval Listę próbek znajdujących się na scenie.
 */ 
    void WyswietlProbki()const;
       

};


#endif