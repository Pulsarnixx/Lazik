#ifndef OBRYSXY_HH
#define OBRYSXY_HH


#include <cmath>
#include "Wektor2D.hh"


class ObrysXY
{
    Wektor2D _Wierzch_DolnyLewy;
    Wektor2D _Wierzch_GornyPrawy;

    public:


 /*!
 * \brief Sprawdza czy dwa różne obrysy nakładają się
 *
 * Porównuje ze sobą współrzednę obrysów i na podstawie
 * warunku analitycznego stwierdza czy obrysy nakładają się.
 * \param[in] _InnyObrysXY - obrys innego obiektu, który sprawdzamy czy się nakłada
 * \retval true - obrysy nakładają sie,
 * \retval false - w przypadku przeciwnym.
 */
    bool CzySieNaklada (const ObrysXY &_InnyObrysXY)const;

    ObrysXY(){};
    /*!
 * \brief Inicjalizuje obrys XY
 *
 * Konstruktor obrysu. Tworzy obrys na podstawie zadanych wektorów 2D.
 * \param[in] Dolny - lewy dolny wierzchołek obrysu
 * \param[in] Gorny - prawy górny wierzchołek obrysu 
 *
 * \retval -
 */
    ObrysXY(Wektor2D Dolny,Wektor2D Gorny){_Wierzch_DolnyLewy = Dolny; _Wierzch_GornyPrawy = Gorny;}

 /*!
 * \brief Wyświetla współrzędne wierzchołków obrysu
 *
 * Wyświetla na standardowe wyjście współrzędne wierzchołków obrysu.
 * \param[in] -
 * \retval-
 */
    void PokazObrys()const{std::cout<<"Wartosci obrysu:\n"<<_Wierzch_DolnyLewy <<_Wierzch_GornyPrawy;}

 /*!
 * \brief Zmienia współrzędne wierzchołków obrysu
 *
 * Zmienia wartości wierzchołków obrysu po podaniu odpowiednich parametrów.
 * \param[in] Dolny - wektor ze współrzędnymi lewego dolnego wierzchołka obrysu
 * \param[in] Gorny - wektor ze współrzędnymi prawego górnego wierzchołka obrysu
 * \retval-
 */
    void ZmienObrys(const Wektor2D &Dolny,const Wektor2D &Gorny);

 /*!
 * \brief Wylicza promień Obrysu
 *
 * Wylicza promień obrysu jako połowa przekątnej aproksymowanego prostokąta.
 * \param[in] -
 * \retval Promień obrysu jako zmienna double.
 */
    double PromienObrysu();
};

#endif