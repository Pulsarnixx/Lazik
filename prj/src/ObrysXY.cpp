#include "ObrysXY.hh"
#include <iostream>


bool ObrysXY::CzySieNaklada (const ObrysXY &_InnyObrysXY)const 
{
   double This_Obrys[2][2]{{_Wierzch_DolnyLewy[0],_Wierzch_GornyPrawy[0]}, //        tablice posiadajace wspol. wierzcholkow  |x1,x2|
                        {_Wierzch_DolnyLewy[1],_Wierzch_GornyPrawy[1]}};   //                                                 |y1,y2|

   double Inny_Obrys[2][2]{{_InnyObrysXY._Wierzch_DolnyLewy[0],_InnyObrysXY._Wierzch_GornyPrawy[0]},
                        {_InnyObrysXY._Wierzch_DolnyLewy[1],_InnyObrysXY._Wierzch_GornyPrawy[1]}};       


        if(
            ((This_Obrys[0][0]<=Inny_Obrys[0][1])&&(Inny_Obrys[0][0]<=This_Obrys[0][1])) // porownanie współrzędnych x-owych
            &&
            ((This_Obrys[1][0]<=Inny_Obrys[1][1])&&(Inny_Obrys[1][0]<=This_Obrys[1][1]))// porownanie współrzędnych y-owych
        ) return true;

return false;
}

void ObrysXY::ZmienObrys(const Wektor2D &Dolny, const Wektor2D &Gorny)
{
    _Wierzch_DolnyLewy = Dolny;
    _Wierzch_GornyPrawy = Gorny;
}

 double ObrysXY::PromienObrysu()
 {
        
        return (sqrt(pow(_Wierzch_GornyPrawy[0]-_Wierzch_DolnyLewy[0],2)+pow(_Wierzch_GornyPrawy[1]-_Wierzch_DolnyLewy[1],2))) / 2;
 }