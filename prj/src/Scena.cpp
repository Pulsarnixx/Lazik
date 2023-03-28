#include "Scena.hh"


Scena::Scena()
{
    std::shared_ptr<LazikSFR> Obiekt1 = std::make_shared<LazikSFR>(0,0,0,"bryly_wzorcowe/szescian3.dat","Sample_Fetch_Rover",Kolor_JasnoNiebieski,0,0,0);
    std::shared_ptr<Lazik> Obiekt2 = std::make_shared<Lazik>(0,0,0,"bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony,60,0,0);
    std::shared_ptr<Lazik> Obiekt3 = std::make_shared<Lazik>(0,0,0,"bryly_wzorcowe/szescian3.dat","Curiosity",Kolor_Czerwony,50,30,0);
   
    
   std::shared_ptr<ProbkaRegolitu> tab_probek[]{
       std::make_shared<ProbkaRegolitu>("Coulettes",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Salette",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Dourbes",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Robine",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Quartier",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Bellegarde",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Montdenier",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Montagnac",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Guillaumes",Kolor_Fioletowy,0,0,0),
       std::make_shared<ProbkaRegolitu>("Roubion",Kolor_Fioletowy,0,0,0)
   };
   
    ObiektySceny.push_back(Obiekt1);
    ObiektySceny.push_back(Obiekt2);
    ObiektySceny.push_back(Obiekt3);
   
    Wektor3D polozeniaRegolitu;
    bool CzySieNaklada=1;
    srand((double)time(0));

   for(const std::shared_ptr<ProbkaRegolitu> &Regolit : tab_probek)
   {    
       do{
           polozeniaRegolitu[0]=double((rand()% ROMIAR_POWIERZCHNI_X)-(ROMIAR_POWIERZCHNI_X/2));
           polozeniaRegolitu[1]=double((rand()% ROMIAR_POWIERZCHNI_Y)-(ROMIAR_POWIERZCHNI_Y/2));
           
            for(auto Iter = ObiektySceny.begin( ); Iter != ObiektySceny.end( ); ++Iter)
                {
                   if((( polozeniaRegolitu[0] >= ((*(*Iter)).PokazPolozenie()[0] + 30)) || (polozeniaRegolitu[0] <= ((*(*Iter)).PokazPolozenie()[0] - 30)))
                   &&
                   ((polozeniaRegolitu[1] >= ((*(*Iter)).PokazPolozenie()[1] + 30)) || (polozeniaRegolitu[1] <= ((*(*Iter)).PokazPolozenie()[1] - 30))))
                    
                    { CzySieNaklada = 0;}
                       
                } 

        }while(CzySieNaklada!=0);

        Regolit->ZmienPolozenie(polozeniaRegolitu);   
        ObiektySceny.push_back(Regolit);
        CzySieNaklada=1;
   }

    AktywnyLazik = Obiekt1;

    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
    Lacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
    Lacze.UstawZakresZ(-0, 90);  
    Lacze.UstawRotacjeXZ(40,60); // Tutaj ustawiany jest widok

    Lacze.Inicjalizuj(); // Uruchamiany gnuplot




    PzG::InfoPlikuDoRysowania *wInfoPliku;
  for(std::list<std::shared_ptr<ObiektGeom>>::iterator Iter = ObiektySceny.begin( ); Iter != ObiektySceny.end( ); ++Iter)
  {        
    wInfoPliku = &Lacze.DodajNazwePliku((*(*Iter)).WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor((*(*Iter)).WezKolorID());

    
  }

for(std::list<std::shared_ptr<ObiektGeom>>::iterator Iter = ObiektySceny.begin( ); Iter != ObiektySceny.end( ); ++Iter)
{
     (*(*Iter)).Przelicz_i_Zapisz_Wierzcholki();

}

 
   
}


std::shared_ptr<Lazik> Scena::operator()(unsigned int Nr_Lazika){

    assert((Nr_Lazika < 4) && (Nr_Lazika > 0) );
    unsigned int i=0;
    for(const std::shared_ptr<ObiektGeom> &Element_obiekt : ObiektySceny)
    {
        if(Element_obiekt != nullptr)
        {   
            ++i;
            if(i == Nr_Lazika)
            {
               return std::dynamic_pointer_cast<Lazik>(Element_obiekt);
            }
        }
    }
    throw std::logic_error("Brak lazika");
}

void Scena::ZmianaAktywnyLazik(unsigned int Nr_Lazika)
{
    
    AktywnyLazik->ZmienKolor(Kolor_Czerwony);
    
    PzG::InfoPlikuDoRysowania *wInfoPliku;
    wInfoPliku = Lacze.ZnajdzNazwePliku(AktywnyLazik->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(Kolor_Czerwony);
    
    AktywnyLazik = Scena::operator()(Nr_Lazika);
    AktywnyLazik->ZmienKolor(Kolor_JasnoNiebieski);
    wInfoPliku = Lacze.ZnajdzNazwePliku(AktywnyLazik->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(Kolor_JasnoNiebieski);
    AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Lacze.Rysuj();
}

void Scena::WyswietlProbki()const
{
    unsigned int i = 1;
    for(auto ite = ObiektySceny.begin( ); ite != ObiektySceny.end( ); ++ite)
    {
        if((*(*ite)).WezTypObiektu() == 2)
        {
            std::cout << i << ". " << (*(*ite)).WezNazweObiektu() << "  " << (*(*ite)).PokazPolozenie();
            ++i;
        }
    }
}
