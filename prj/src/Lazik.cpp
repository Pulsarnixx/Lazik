#include "Lazik.hh"
#include "Scena.hh"
#include "LazikSFR.hh"

void Lazik::Przesuniecie(Scena &_Scena)
{   

    bool CzyJestKolizja = 0;
    double klatka = 50;

    Wektor3D Kierunek(1,0,0);
    Kierunek = ((Macierz_rotacji(kat_orientacji) * Kierunek)*odleglosc_do_przejechania)/klatka;

    TypKolizji x= TK_BrakKolizji;

for(int i = 0; i < klatka; ++i)
        {
            
            ZmienPolozenie(Kierunek);
            Przelicz_i_Zapisz_Wierzcholki();
            for(auto ite = _Scena.getObiektySceny().begin( ); ite != _Scena.getObiektySceny().end( ); ++ite)
                {
                    x=TK_BrakKolizji;
                    if((*ite != _Scena.getLazik()))
                        {
                             x = (*(*ite)).CzyKolizja(_Scena.getLazik());
                            switch (x)
                            {
                                case TK_Kolizja:
                                std::cout << "Kolizja z obiektem o nazwie: " << (*(*ite)).WezNazweObiektu() << "\n";
                                    CzyJestKolizja = 1;
                                break;

                                case TK_PrzejazdNadProbka:
                                    std::cout<<"Przejazd nad próbka: "<<(*(*ite)).WezNazweObiektu()<<"\n";  
                                break;
                                
                                default:
                        
                                    break;
                            }

                   
                        }
                    if(CzyJestKolizja == 1) break; 
                }
           
            if(CzyJestKolizja == 1){ goto powrot;}

             _Scena.getLacze().Rysuj();
             sleep(1/szybkosc);
        

        }

 powrot:
 if(CzyJestKolizja == 1)
            {
                
                Kierunek = Kierunek * (-1);
                ZmienPolozenie(Kierunek);
                Przelicz_i_Zapisz_Wierzcholki();
                _Scena.getLacze().Rysuj();
            }
 
}

void Lazik::Obrot(double kat, Scena &_Scena)
{   

    bool CzyJestKolizja = 0;
    double klatka = 50,zapisKata=kat_orientacji;
    kat /= klatka; 

  for(int i = 0; i < klatka; ++i)
        {
            DodajKatOrientacji(kat);
            Rotacja() = Macierz_rotacji(kat_orientacji);
            Przelicz_i_Zapisz_Wierzcholki();

            for(auto ite = _Scena.getObiektySceny().begin( ); ite != _Scena.getObiektySceny().end( ); ++ite)
            {
                if((*ite != _Scena.getLazik()) && ((*(*ite)).CzyKolizja(_Scena.getLazik()) == TK_Kolizja))
                {
                    std::cout << "Kolizja z obiektem o nazwie: " << (*(*ite)).WezNazweObiektu() << "\n";
                    CzyJestKolizja = 1;
                    break;
                }
            }

            if(CzyJestKolizja == 1)
            {
               // _Scena.getLacze().Rysuj();
                goto powrot;
            }

            _Scena.getLacze().Rysuj();
            sleep(1/szybkosc);
        }
        
        powrot:
        if(CzyJestKolizja == 1)
            {
                kat_orientacji = zapisKata;
                Rotacja() = Macierz_rotacji(kat_orientacji);
                Przelicz_i_Zapisz_Wierzcholki();
                 _Scena.getLacze().Rysuj();
            }

}

 Wektor2D Lazik::WektorPredkosci()const
 {
     Wektor3D Predkosc3D(1,0,0);
     Wektor2D Predkosc2D;

      Predkosc3D = (Macierz_rotacji(kat_orientacji) * Predkosc3D) * szybkosc;
    
    Predkosc2D[0] = Predkosc3D[0];
    Predkosc2D[1] = Predkosc3D[1];

    return Predkosc2D;
 }

TypKolizji Lazik::CzyKolizja(const std::shared_ptr<Lazik> &Wsk_Lazik)const
 {  
        if(PokazObrys().CzySieNaklada(Wsk_Lazik->PokazObrys()) == true) return TK_Kolizja;
        return TK_BrakKolizji;
 }

 void Lazik::PodniesienieProbki(Scena &_Scena)
{   
    if(_Scena.getLazik()->WezTypObiektu() == 3){
        bool czyPodniosl = 0;
        for(auto ite = _Scena.getObiektySceny().begin( ); ite != _Scena.getObiektySceny().end( ); ++ite)
        {
            
                if((*ite != _Scena.getLazik()) && ((*(*ite)).CzyKolizja(_Scena.getLazik()) == TK_PrzejazdNadProbka))
                {
                    std::dynamic_pointer_cast<LazikSFR>(_Scena.getLazik())->PodjecieProbki(std::dynamic_pointer_cast<ProbkaRegolitu>((*ite)), _Scena);
                    std::cout << "Probki na laziku: " << std::endl;
                    std::dynamic_pointer_cast<LazikSFR>(_Scena.getLazik())->WyswietlPosiadaneProbki();
                    czyPodniosl = 1;
                    goto wyjscie;
                }
            
        }
            if(czyPodniosl == 0)
            {
            std::cout << "Brak probki w okolicy." << std::endl;
            }
       
    }
    else std::cout << "Ten lazik nie moze zebrac probki!"<<std::endl;
    wyjscie:{}
}



