#include "ProbkaRegolitu.hh"
#include "Lazik.hh"


TypKolizji ProbkaRegolitu::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const
 {  
        if(PokazObrys().CzySieNaklada(Wsk_Lazik->PokazObrys()) == true) 
        {
               
              Wektor2D V_L = Wsk_Lazik->WektorPredkosci();
              Wektor2D r = (Wsk_Lazik->PokazPolozenie2D() - (PokazPolozenie2D()));
       
              double d = (fabs(r & V_L))/(sqrt(V_L * V_L));
              double warunekKolizji = 0.2 * 20;  // 0,2 szeorkości łazika (tutaj 20 ) 

              if(d>warunekKolizji) return TK_Kolizja;
              
              return TK_PrzejazdNadProbka;
               
        }
        return TK_BrakKolizji;
 }
