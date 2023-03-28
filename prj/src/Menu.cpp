#include "Menu.hh"

using namespace std;

int WyswietlMenu(Scena &Scena)
{
    system("clear");
    char x;
    do{   
        std::cout<<"\nAktywny lazik"<<endl;
        Scena.getLazik()->WyswietlInformacje();
        std::cout << "\nAktualna ilosc Wektorow: " <<Wektor<double,cSize>::Wyswietl_aktualna()<<endl;
        std::cout << "Łaczna ilosc Wektorow: " << Wektor<double,cSize>::Wyswietl_lacznie()<<"\n\n\n";


        std::cout<<"j - jazda na wprost\n";
        std::cout<<"o - zmien orientacje\n";
        std::cout<<"p - podejmij probke (tylko dla SFR)\n";
        std::cout<<"w - wybor lazika\n";
        std::cout<<"m - wyswietl menu\n";
        std::cout<<"l - lista próbek na scenie\n\n";

        std::cout<<"k - koniec dzialania programu\n\n";

        std::cout <<"Twoj wybor, m - menu> ";
        std::cin >> x;
      switch (x)
        {
            case 'j':
            {
                std::cout << "Podaj odleglosc, na ktora ma sie przemiescic lazik (w jednostkach sceny).\n";
                std::cout<<"Odleglosc > ";
                cin >> Scena.getLazik()->Odl();

                 if(cin.fail()) return -2; //Blad wartosci

                std::cout<<"\n";
                std::cout << "Podaj szybkość z jaką ma poruszać się łazik.\n";
                std::cout<<"Szybkosc > ";
                cin >> Scena.getLazik()->Szyb();

                
                if(cin.fail()) return -2; //Blad wartosci
                Scena.getLazik()->Przesuniecie(Scena);

            }
            break;

            case 'o':
            {
                std::cout << "Podaj kat obrotu w stopniach.\n";
                std::cout<<"Wartosc kata > ";
                double kat = 0;
                cin >> kat;

                if(cin.fail()) return -2; //Blad wartosci


                std::cout<<"\n";
                std::cout << "Podaj szybkość z jaką ma obracać się łazik.\n";
                std::cout<<"Szybkosc > ";
                cin >> Scena.getLazik()->Szyb();
                
                if(cin.fail()) return -2; //Blad wartosci

                Scena.getLazik()->Obrot(kat,Scena);
            }
            break;

            case 'p':
            {
                    Scena.getLazik()->PodniesienieProbki(Scena);
            }
            break;

            case 'w':
            {
                std::cout<<"1. -------- ";
                Scena(1)->WyswietlInformacje();
                std::cout<<std::endl;

                std::cout<<"2. -------- ";
                Scena(2)->WyswietlInformacje();
                std::cout<<std::endl;

                std::cout<<"3. -------- ";
                Scena(3)->WyswietlInformacje();
                std::cout<<std::endl;

                std::cout<<"Podaj numer lazika > ";
                unsigned int numer_lazika = 1;
                cin >> numer_lazika;
                if(cin.fail()) return -2; //Blad wartosci
                Scena.ZmianaAktywnyLazik(numer_lazika);

            }
            break;

            case 'k':
            {   
        
            std::cout << "Koniec programu\n";
            return 0;

            }
            break;

            case 'm':
            {   
                std::system("clear");
            }
            break;

            case 'l':
            {   
            
            std::system("clear");
            std::cout << "Lista próbek na scenie\n";
            Scena.WyswietlProbki();
            
            }
            break;
    
            default:
            { 
                return -1; //Zly wybor w menu
            }
            break;
            
        }
  }while(x!='k');

    return 0;
}