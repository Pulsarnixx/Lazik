#include "LazikSFR.hh"

TypKolizji LazikSFR::CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const
{
    if(PokazObrys().CzySieNaklada(WskLazik->PokazObrys()) == true) return TK_Kolizja;

    return TK_BrakKolizji;
}

void LazikSFR::PodjecieProbki(const std::shared_ptr<ProbkaRegolitu> &WskProbka, Scena &_Scena)
{
    _Scena.getObiektySceny().remove(WskProbka);
    getListaProbek().push_back(WskProbka);
    PrzesuniecieProbki();
}

void LazikSFR::WyswietlPosiadaneProbki()const
{
    unsigned int i = 1;
    bool CzyPosiadaProbki = 0;
    for(auto ite = _ListaProbek.begin( ); ite != _ListaProbek.end( ); ++ite)
    {
        if((*(*ite)).WezTypObiektu() == 2)
        {   CzyPosiadaProbki = 1;
            std::cout << i << ". " << (*(*ite)).WezNazweObiektu()<<"\n";
            ++i;
        }
    }
    if(CzyPosiadaProbki == 0) std::cout << "(brak probek)";
}

void LazikSFR::PrzesuniecieProbki()
{
    for(auto ite = _ListaProbek.begin( ); ite != _ListaProbek.end( ); ++ite)
    {
        if((*(*ite)).WezTypObiektu() == 2)
        {
            (*(*ite)).ZamienIstniejacePolozenie() = PokazPolozenie();
            (*(*ite)).Przelicz_i_Zapisz_Wierzcholki();
        }
    }
}



void LazikSFR::Przesuniecie(Scena &_Scena)
{   

    bool CzyJestKolizja = 0;
    double klatka = 50;

    Wektor3D Kierunek(1,0,0);
    Kierunek = ((Macierz_rotacji(Kat()) * Kierunek)*Odl())/klatka;

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
                                std::cout<<"Przejazd nad próbka: "<<(*(*ite)).WezNazweObiektu()<<". Mozna ja podniesc!\n";   
                                break;
                                
                                default:
                        
                                    break;
                            }

                   
                        }
  
                    if(CzyJestKolizja == 1) break; 
                }
            
            
            if(CzyJestKolizja == 1){ goto powrot;}
            PrzesuniecieProbki();
             _Scena.getLacze().Rysuj();
             sleep(1/Szyb());
        

        }

 powrot:
 if(CzyJestKolizja == 1)
            {
                
                Kierunek = Kierunek * (-1);
                ZmienPolozenie(Kierunek);
                PrzesuniecieProbki();
                Przelicz_i_Zapisz_Wierzcholki();
                _Scena.getLacze().Rysuj();
            }
 
}
