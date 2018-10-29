#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Adresat
{
    int idZapisanegoKontaktu;
    string imie, nazwisko, numerTelefonu, email, adres;
};

Adresat zapisanieNowejOsoby (vector <Adresat> &adresaci)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    fstream plik;
    Adresat tymczasowyZapisNowejOsoby;

    cout << "Podaj imie:";
    cin >> tymczasowyZapisNowejOsoby.imie;
    cout << "Podaj nazwisko:";
    cin >> tymczasowyZapisNowejOsoby.nazwisko;
    cout << "Podaj numer telefonu:";
    cin.sync();
    getline(cin, tymczasowyZapisNowejOsoby.numerTelefonu);
    cout << "Podaj adres:";
    cin.sync();
    getline(cin, tymczasowyZapisNowejOsoby.adres);
    cout << "Podaj e-mail:";
    cin >> tymczasowyZapisNowejOsoby.email;

    int ostatniAdresat = adresaci.size()-1;

    tymczasowyZapisNowejOsoby.idZapisanegoKontaktu = adresaci[ostatniAdresat].idZapisanegoKontaktu +1;

    plik.open("ksiazkaadresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << tymczasowyZapisNowejOsoby.idZapisanegoKontaktu <<'|';
        plik << tymczasowyZapisNowejOsoby.imie << '|';
        plik << tymczasowyZapisNowejOsoby.nazwisko << '|';
        plik << tymczasowyZapisNowejOsoby.numerTelefonu << '|';
        plik << tymczasowyZapisNowejOsoby.adres << '|';
        plik << tymczasowyZapisNowejOsoby.email << '|' << endl;
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system ("pause");
    }

    cout << "Nowy kontakt zostal dodany do ksiazki adresowej" << endl;
    Sleep(1000);

    return tymczasowyZapisNowejOsoby;
}

Adresat zapiszPobranaLinieDoStruktury (string linia)
{
    Adresat tymczasowy;
    string znakOddzielenia = "";
    string idZapisanegoKontaktu ="";
    string imie ="";
    string nazwisko = "";
    string numerTelefonu = "";
    string email ="";
    string adres = "";

    for (int i = 0; i < linia.length(); i++)
    {
        if (linia[i] == '|')
        {
            znakOddzielenia +=linia[i];
        }
        else
        {
            if (znakOddzielenia.length() == 0)
                idZapisanegoKontaktu += linia[i];

            else if (znakOddzielenia.length() == 1)
                tymczasowy.imie += linia[i];

            else if (znakOddzielenia.length() == 2)
                tymczasowy.nazwisko += linia[i];

            else if (znakOddzielenia.length() == 3)
                tymczasowy.numerTelefonu+= linia[i];

            else if (znakOddzielenia.length() == 4)
                tymczasowy.adres += linia[i];

            else if (znakOddzielenia.length() == 5)
                tymczasowy.email += linia[i];
        }
    }
    int idZapisanegoKontaktuInt = atoi(idZapisanegoKontaktu.c_str());
    tymczasowy.idZapisanegoKontaktu = idZapisanegoKontaktuInt;
    return tymczasowy;
}

vector <Adresat> wczytajZnajomych ()
{
    vector <Adresat> adresaci;
    fstream plik;
    string linia;
    plik.open ("ksiazkaadresowa.txt", ios::in);

    if (plik.good() == true)
    {
        while (getline(plik, linia))
        {
            adresaci.push_back(zapiszPobranaLinieDoStruktury(linia));
        }
        plik.close();
    }
    return adresaci;
}
void wyszukajWedlugImienia (vector <Adresat> &adresaci)
{
    string imie;
    cout << "Podaj imie do wyszukania: " << endl;
    cin >> imie;

    for (int i=0; i< adresaci.size(); i++)
    {
        if (imie == adresaci[i].imie)
        {
            cout << adresaci[i].idZapisanegoKontaktu <<'|';
            cout << adresaci[i].imie << '|';
            cout << adresaci[i].nazwisko << '|';
            cout << adresaci[i].numerTelefonu << '|';
            cout << adresaci[i].adres << '|';
            cout << adresaci[i].email << '|' << endl;

        }
    }
    system ("pause");
}

void wyszukajWedlugNazwiska (vector <Adresat> &adresaci)
{
    string nazwisko;
    cout << "Podaj nazwisko do wyszukania: " << endl;
    cin >> nazwisko;

    for (int i=0; i< adresaci.size(); i++)
    {
        if (nazwisko == adresaci[i].nazwisko)
        {
            cout << adresaci[i].idZapisanegoKontaktu <<'|';
            cout << adresaci[i].imie << '|';
            cout << adresaci[i].nazwisko << '|';
            cout << adresaci[i].numerTelefonu << '|';
            cout << adresaci[i].adres << '|';
            cout << adresaci[i].email << '|' << endl;
        }
    }
    system ("pause");
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    for (int i=0; i< adresaci.size(); i++)
    {
        cout << adresaci[i].idZapisanegoKontaktu <<'|';
        cout << adresaci[i].imie << '|';
        cout << adresaci[i].nazwisko << '|';
        cout << adresaci[i].numerTelefonu << '|';
        cout << adresaci[i].adres << '|';
        cout << adresaci[i].email << '|' << endl;
    }
    system ("pause");
}

void usunPlikIZapiszOdNowa (vector <Adresat> &adresaci)
{
    remove ("ksiazkaadresowa.txt");
    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        for (int i=0; i< adresaci.size(); i++)
        {
            plik << adresaci[i].idZapisanegoKontaktu <<'|';
            plik << adresaci[i].imie << '|';
            plik << adresaci[i].nazwisko << '|';
            plik << adresaci[i].numerTelefonu << '|';
            plik << adresaci[i].adres << '|';
            plik << adresaci[i].email << '|' << endl;
        }
        plik.close();
    }
}

void usunAdresata (vector <Adresat> &adresaci)
{
    wyswietlWszystkichAdresatow(adresaci);
    int idAdresata;
    cout << "Wybierz ID adresata, ktorego chcesz usunac: ";
    cin >> idAdresata;
    for (int i =0; i< adresaci.size(); i++)
    {
        if (adresaci[i].idZapisanegoKontaktu == idAdresata)
            adresaci.erase(adresaci.begin() + i);
    }
    usunPlikIZapiszOdNowa(adresaci);
}

void edytujInformacjeOAdreacie (vector <Adresat> &adresaci)
{
    int idAdresata;

    wyswietlWszystkichAdresatow(adresaci);
    cout << "Wybierz ID adresata, ktorego chcesz edytowac: ";
    cin >> idAdresata;
    cout << "Wybierz, ktora z inforamcji chcesz edytowac:" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Podwrot do menu" << endl;
    char wyborOpcji;
    cin >> wyborOpcji;

    switch (wyborOpcji)
    {
    case '1':
    {
        string imie;
        cout << "Podaj nowe imie: ";
        cin >> imie;

        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idZapisanegoKontaktu == idAdresata)
            {
                adresaci[i].imie = imie;
            }
        }
        break;
    }
    case '2':
    {
        string nazwisko;
        cout << "Podaj nowe nazwisko: ";
        cin >> nazwisko;

        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idZapisanegoKontaktu == idAdresata)
                adresaci[i].nazwisko = nazwisko;
        }
        break;
    }
    case '3':
    {
        string numerTelefonu;
        cout << "Podaj nowy numer telefonu: ";
        cin >> numerTelefonu;

        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idZapisanegoKontaktu == idAdresata)
                adresaci[i].numerTelefonu = numerTelefonu;
        }
        break;
    }
    case '4':
    {
        string email;
        cout << "Podaj nowy e-mail: ";
        cin >> email;

        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idZapisanegoKontaktu == idAdresata)
                adresaci[i].email = email;
        }
        break;
    }
    case '5':
    {
        string adres;
        cout << "Podaj nowy adres: ";
        cin >> adres;

        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idZapisanegoKontaktu == idAdresata)
                adresaci[i].adres = adres;
        }
        break;
    }
    case '6':
    {
        break;
    }
    }
    usunPlikIZapiszOdNowa(adresaci);
}

int main ()
{
    vector <Adresat> adresaci;
    fstream plik;
    char wybor;

    adresaci = wczytajZnajomych();

    while (true)
    {
        system("cls");
        cout << "1. Zapisz nowa osobe do ksiazki adresowej." << endl;
        cout << "2. Wyszukaj znajomego wedlug imienia." << endl;
        cout << "3. Wyszukaj znajomego wedlug nazwiska." << endl;
        cout << "4. Wyswietl cala liste znajomych."<< endl;
        cout << "5. Usun adresata." << endl;
        cout << "6. Edytuj adresata." << endl;
        cout << "9. Koniec pracy." << endl;

        cin >> wybor;

        if (wybor == '1')
        {
            adresaci.push_back(zapisanieNowejOsoby(adresaci));
        }
        else if (wybor == '2')
        {
            wyszukajWedlugImienia(adresaci);
        }
        else if (wybor == '3')
        {
            wyszukajWedlugNazwiska(adresaci);
        }
        else if (wybor == '4')
        {
            wyswietlWszystkichAdresatow(adresaci);
        }
        else if (wybor == '5')
        {
            usunAdresata(adresaci);
        }
        else if (wybor == '6')
        {
           edytujInformacjeOAdreacie(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}

