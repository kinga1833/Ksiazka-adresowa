#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Uzytkownik
{
    int id;
    string login, haslo;
};

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

string konwerjsaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

Adresat zapiszPobranaLinieDanychAdresataDoStruktury (string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int i = 0; i < daneAdresataOddzielonePionowymiKreskami.length(); i++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[i] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[i];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.idAdresata = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plikTekstowy;
    plikTekstowy.open("Adresaci.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << adresat.idAdresata << '|';
        plikTekstowy << adresat.idUzytkownika << '|';
        plikTekstowy << adresat.imie << '|';
        plikTekstowy << adresat.nazwisko << '|';
        plikTekstowy << adresat.numerTelefonu << '|';
        plikTekstowy << adresat.email << '|';
        plikTekstowy << adresat.adres << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

Uzytkownik zapiszPobranaLinieDoStruktury (string daneUzytkownikaOddzielonePionowymiKreskami)
{
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int i = 0; i < daneUzytkownikaOddzielonePionowymiKreskami.length(); i++)
    {
        if (daneUzytkownikaOddzielonePionowymiKreskami[i] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[i];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.login = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;

            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku (vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami))
        {
            uzytkownik = zapiszPobranaLinieDoStruktury(daneJednegoUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}

void dopiszNowegoUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.id << '|';
        plikTekstowy << uzytkownik.login << '|';
        plikTekstowy << uzytkownik.haslo << '|' << endl;

        plikTekstowy.close();

        cout << endl << "Rejestracja przebiegla pomyslnie" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
void rejestracjaNowegoUzytkownika(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string loginNowegoUzytkownika, hasloNowegoUzytkownika;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO UZYTKOWNIKA <<<" << endl << endl;

    if (uzytkownicy.empty() == true)
    {
        uzytkownik.id = 1;
    }
    else
    {
        uzytkownik.id= uzytkownicy.back().id+ 1;
    }

    cout << "Podaj login: ";
    cin >> loginNowegoUzytkownika;
    if (uzytkownicy.empty() == true)
    {
        uzytkownik.login = loginNowegoUzytkownika;
    }
    else
    {
        for (int i = 0; i< uzytkownicy.size(); i++)
        {
            if (loginNowegoUzytkownika == uzytkownicy[i].login)
            {
                cout << "Taki uzytkownik istnieje, podaj inny login!" << endl;
                cin >> loginNowegoUzytkownika;
                i = 0;
            }
        }
        uzytkownik.login = loginNowegoUzytkownika;
    }

    cout << "Podaj haslo: ";
    cin >> hasloNowegoUzytkownika;
    if (uzytkownicy.empty() == true)
    {
        uzytkownik.haslo = hasloNowegoUzytkownika;
    }
    else
    {
        for (int i = 0; i< uzytkownicy.size(); i++)
        {
            if (hasloNowegoUzytkownika == uzytkownicy[i].haslo)
            {
                cout << "Takie haslo zostalo juz uzyte, podaj inne haslo!";
                cin >> hasloNowegoUzytkownika;
                i = 0;
            }
        }
        uzytkownik.haslo = hasloNowegoUzytkownika;
    }
    uzytkownicy.push_back(uzytkownik);

    dopiszNowegoUzytkownikaDoPliku(uzytkownik);
}
int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    system("cls");
    cout << ">>> LOGOWANIE <<<" << endl << endl;
    int idZalogowanegoUzytkownika;
    string hasloUzytkownika, loginUzytkownika;
    cout << "Podaj login: " << endl;
    cin >> loginUzytkownika;


    for (int i =0; i< uzytkownicy.size(); i++)
    {
        if (loginUzytkownika == uzytkownicy[i].login)
        {
            cout << "Podaj haslo: " << endl;
            cin >> hasloUzytkownika;

            while (true)
            {
                if (hasloUzytkownika == uzytkownicy[i].haslo)
                {
                    cout << "Zalogowales sie! " << endl;
                    Sleep (1000);
                    return uzytkownicy[i].id;
                }
                else
                {
                    cout << "Podales bledne haslo, sprobuj ponownie!" << endl;
                    cin >> hasloUzytkownika;
                }
            }

        }
    }
    cout << "Taki uzytkownik nie istnieje, podaj inny login lub zarejestruj sie,  aby moc korzystac z ksiazki adresowej." << endl;
    return 0;
}

void wczytajWszystkichAdresatowZPliku (vector <Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open("Adresaci.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            adresat = zapiszPobranaLinieDanychAdresataDoStruktury (daneJednegoAdresataOddzielonePionowymiKreskami);

            adresaci.push_back(adresat);
        }
        plikTekstowy.close();
    }
}

void wczytajZPlikuAdresatowZalogowanegoUzytkownika (int idZalogowanegoUzytkownika, vector <Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open("Adresaci.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            adresat = zapiszPobranaLinieDanychAdresataDoStruktury(daneJednegoAdresataOddzielonePionowymiKreskami);

            if (adresat.idUzytkownika == idZalogowanegoUzytkownika)
            {
                adresaci.push_back(adresat);
            }
        }
        plikTekstowy.close();
    }
}

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    if (adresaci.empty() == true)
    {
        adresat.idAdresata= 1;
    }
    else
    {
        adresat.idAdresata= adresaci.back().idAdresata+ 1;
    }

    adresat.idUzytkownika = idZalogowanegoUzytkownika;

    cout << "Podaj imie: ";
    cin >> adresat.imie;
    cin.ignore();
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.imie);

    cout << "Podaj nazwisko: ";
    cin >> adresat.nazwisko;
    cin.ignore();
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);

    cout << "Podaj numer telefonu: ";
    cin.sync();
    cin.clear();
    getline(cin, adresat.numerTelefonu);

    cout << "Podaj email: ";
    cin >> adresat.email;
    cin.ignore();

    cout << "Podaj adres: ";
    cin.sync();
    cin.clear();
    getline(cin, adresat.adres);

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat);
}

void wyszukajAdresatowPoImieniu(vector<Adresat> &adresaci)
{
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW PO IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        cin >> imiePoszukiwanegoAdresata;
        cin.ignore();

        imiePoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (int i = 0; i< adresaci.size(); i++)
        {
            if (adresaci[i].imie == imiePoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << adresaci[i].idAdresata << endl;
                cout << "Imie:               " << adresaci[i].imie << endl;
                cout << "Nazwisko:           " << adresaci[i].nazwisko << endl;
                cout << "Numer Telefonu:     " << adresaci[i].numerTelefonu << endl;
                cout << "Nr Email:           " << adresaci[i].email << endl;
                cout << "Adres:              " << adresaci[i].adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajAdresatowPoNazwisku(vector<Adresat> &adresaci)
{
    string nazwiskoPoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW PO NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        cin >> nazwiskoPoszukiwanegoAdresata;
        nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (int i=0; i< adresaci.size(); i++)
        {
            if (adresaci[i].nazwisko == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << adresaci[i].idAdresata<< endl;
                cout << "Imie:               " << adresaci[i].imie << endl;
                cout << "Nazwisko:           " << adresaci[i].nazwisko << endl;
                cout << "Numer Telefonu:     " << adresaci[i].numerTelefonu << endl;
                cout << "Nr Email:           " << adresaci[i].email << endl;
                cout << "Adres:              " << adresaci[i].adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyswietlWszystkichAdresatow(vector<Adresat> &adresaci)
{
    system("cls");
    if (!adresaci.empty())
    {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            cout << "Id:                 " << itr->idAdresata<< endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void zapiszWszystkichAdresatowDoPlikuTekstowegoPoUsunieciu(int idUsunietegoAdresata)
{
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plikTekstowy, plikTekstowyTymczasowy;
    string idAdresataPobraneZPliku = "";
    int idAdresataInt;
    string nazwaPliku = "Adresaci.txt";
    string nazwaPlikuTymczasowy = "Adresaci_tymczasowy.txt";

    plikTekstowy.open(nazwaPliku.c_str(), ios::in);
    plikTekstowyTymczasowy.open(nazwaPlikuTymczasowy.c_str(), ios::in | ios::app);

    if (plikTekstowy.good() == true)
    {
        if (plikTekstowyTymczasowy.good() == true)
        {
            while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                int i = 0;

                while (true)
                {
                    if (daneJednegoAdresataOddzielonePionowymiKreskami[i] !=  '|')
                    {
                        idAdresataPobraneZPliku += daneJednegoAdresataOddzielonePionowymiKreskami[i];
                        i++;
                    }
                    else
                        break;
                }
                idAdresataInt = atoi (idAdresataPobraneZPliku.c_str());
                if (idAdresataInt != idUsunietegoAdresata)
                {
                    plikTekstowyTymczasowy << daneJednegoAdresataOddzielonePionowymiKreskami << endl;
                }
                idAdresataPobraneZPliku.clear();
            }

            plikTekstowy.close();
            remove (nazwaPliku.c_str());
            plikTekstowyTymczasowy.close();
        }
    }
}

void usunAdresata(vector<Adresat> &adresaci)
{
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        cin >> idUsuwanegoAdresata;
        cin.ignore();

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr->idAdresata == idUsuwanegoAdresata)
                {
                    czyIstniejeAdresat = true;
                    cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                    cin >> znak;
                    if (znak == 't')
                    {
                        itr = adresaci.erase(itr);
                        cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoUsunieciu(idUsuwanegoAdresata);
                        rename ("Adresaci_tymczasowy.txt", "Adresaci.txt");

                        break;
                    }
                    else
                    {
                        cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false)
            {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
            }
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }

    system("pause");
}

void zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji (vector <Adresat>adresaci, int idEdytowanegoAdresata)
{
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy, plikTekstowyTymczasowy;
    string idAdresataPobraneZPliku = "";
    int idAdresataInt;
    string nazwaPliku = "Adresaci.txt";
    string nazwaPlikuTymczasowy = "Adresaci_tymczasowy.txt";

    plikTekstowy.open(nazwaPliku.c_str(), ios::in);
    plikTekstowyTymczasowy.open(nazwaPlikuTymczasowy.c_str(), ios::in | ios::app);

    if (plikTekstowy.good() == true)
    {
        if (plikTekstowyTymczasowy.good() == true)
        {
            while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                int i = 0;

                while (true)
                {
                    if (daneJednegoAdresataOddzielonePionowymiKreskami[i] !=  '|')
                    {
                        idAdresataPobraneZPliku += daneJednegoAdresataOddzielonePionowymiKreskami[i];
                        i++;
                    }
                    else
                        break;
                }

                idAdresataInt = atoi (idAdresataPobraneZPliku.c_str());
                if (idAdresataInt != idEdytowanegoAdresata)
                {
                    plikTekstowyTymczasowy << daneJednegoAdresataOddzielonePionowymiKreskami << endl;
                }
                else
                {
                    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
                    {
                        if (itr->idAdresata == idEdytowanegoAdresata)
                        {
                            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idAdresata) + '|';
                            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idUzytkownika) + '|';
                            liniaZDanymiAdresata += itr->imie + '|';
                            liniaZDanymiAdresata += itr->nazwisko + '|';
                            liniaZDanymiAdresata += itr->numerTelefonu + '|';
                            liniaZDanymiAdresata += itr->email + '|';
                            liniaZDanymiAdresata += itr->adres + '|';

                            plikTekstowyTymczasowy << liniaZDanymiAdresata << endl;
                            liniaZDanymiAdresata = "";
                        }
                    }
                }
                idAdresataPobraneZPliku.clear();
            }
            plikTekstowy.close();
            remove (nazwaPliku.c_str());
            plikTekstowyTymczasowy.close();
            rename ("Adresaci_tymczasowy.txt", "Adresaci.txt");
        }
    }
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    int idEdytowanegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> EDYCJA WYBRANEGO ADRESATA <<<" << endl << endl;
        cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
        cin >> idEdytowanegoAdresata;
        cin.ignore();

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr->idAdresata== idEdytowanegoAdresata)
                {
                    czyIstniejeAdresat = true;

                    cout << endl << "Ktore dane zaktualizowac: " << endl;
                    cout << "1 - Imie" << endl;
                    cout << "2 - Nazwisko" << endl;
                    cout << "3 - Numer telefonu" << endl;
                    cout << "4 - Email" << endl;
                    cout << "5 - Adres" << endl;
                    cout << "6 - Powrot " << endl;
                    cout << endl << "Wybierz 1-6: ";
                    cin >> wybor;

                    switch (wybor)
                    {
                    case '1':
                        cout << "Podaj nowe imie: ";
                        cin >> itr->imie;
                        cin.ignore();
                        itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                        cout << endl << "Imie zostalo zmienione" << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji(adresaci, idEdytowanegoAdresata);
                        break;
                    case '2':
                        cout << "Podaj nowe nazwisko: ";
                        cin >> itr->nazwisko;
                        cin.ignore();
                        itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                        cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji(adresaci, idEdytowanegoAdresata);
                        break;
                    case '3':
                        cout << "Podaj nowy numer telefonu: ";
                        cin.sync();
                        cin.clear();
                        getline(cin, itr->numerTelefonu);
                        cout << endl << "Numer telefonu zostal zmieniony." << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji(adresaci, idEdytowanegoAdresata);
                        break;
                    case '4':
                        cout << "Podaj nowy email: ";
                        cin >> itr->email;
                        cin.ignore();
                        cout << endl << "Email zostal zmieniony." << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji(adresaci, idEdytowanegoAdresata);
                        break;
                    case '5':
                        cout << "Podaj nowy adres zamieszkania: ";
                        cin.sync();
                        cin.clear();
                        getline(cin, itr->adres);
                        itr->adres = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->adres);
                        cout << endl << "Adres zostal zmieniony." << endl << endl;
                        zapiszWszystkichAdresatowDoPlikuTekstowegoPoEdycji(adresaci, idEdytowanegoAdresata);
                        break;
                    case '6':
                        cout << endl << "Powrot do menu glownego" << endl << endl;
                        break;
                    default:
                        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false)
            {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
            }
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}
void zapiszWszystkichUzytkownikowDoPlikuTekstowego(vector<Uzytkownik> &uzytkownicy)
{
    fstream plikTekstowy;
    string liniaZDanymiAdresata = "";

    plikTekstowy.open("Uzytkownicy.txt", ios::out);

    if (plikTekstowy.good())
    {
        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiAdresata += itr->login + '|';
            liniaZDanymiAdresata += itr->haslo + '|';

            plikTekstowy << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
    }
}
void zmienHaslo (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo;
    system ("cls");
    cout << ">>> ZMIANA HASLA <<<" << endl << endl;
    cout << "Podaj nowe haslo:" << endl;
    cin >> noweHaslo;

    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = noweHaslo;
        }
    }
    cout << "Haslo zostalo zmienione!" << endl;
    Sleep (1000);
    zapiszWszystkichUzytkownikowDoPlikuTekstowego(uzytkownicy);
}
int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaciZalogowanegoUzytkownika;
    vector <Adresat> wszyscyAdresaci;
    char wybor;
    char wyborOpcjiPoZalogowaniu;
    int idZalogowanegoUzytkownika = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while (1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system ("cls");
            cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "3. Zakoncz program"<< endl;

            cin >> wybor;

            if (wybor == '1')
            {
                rejestracjaNowegoUzytkownika(uzytkownicy);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            else if (wybor == '3')
            {
                exit (0);
            }
        }
        else
        {
            wczytajZPlikuAdresatowZalogowanegoUzytkownika(idZalogowanegoUzytkownika, adresaciZalogowanegoUzytkownika);
            while (1)
            {
                system ("cls");
                cout << ">>> OPCJE LOGOWANIA <<<" << endl << endl;
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "8. Wyloguj sie" << endl;

                cin >> wyborOpcjiPoZalogowaniu;

                if (wyborOpcjiPoZalogowaniu == '1')
                {
                    wczytajWszystkichAdresatowZPliku(wszyscyAdresaci);
                    dodajAdresata(wszyscyAdresaci, idZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '2')
                {
                    wyszukajAdresatowPoImieniu(adresaciZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '3')
                {
                    wyszukajAdresatowPoNazwisku(adresaciZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '4')
                {
                    wyswietlWszystkichAdresatow(adresaciZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '5')
                {
                    usunAdresata(adresaciZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '6')
                {
                    edytujAdresata(adresaciZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '7')
                {
                    zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                }
                else if (wyborOpcjiPoZalogowaniu == '8')
                {
                    idZalogowanegoUzytkownika = 0;
                    adresaciZalogowanegoUzytkownika.clear();
                    break;
                }
                else
                {
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
    }
    return 0;
}
