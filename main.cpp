#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>

using namespace std;

struct daneZnajomych
{
    string imie, nazwisko, numerTelefonu, email, adres;
    int idZapisanegoKontaktu;
};

int zapisanieNowejOsoby (daneZnajomych znajomi[], int liczbaZnajomych)
{
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Podaj imie:";
    cin >> imie;
    cout << "Podaj nazwisko:";
    cin >> nazwisko;
    cout << "Podaj numer telefonu:";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj adres:";
    cin.sync();
    getline(cin, adres);
    cout << "Podaj e-mail:";
    cin >> email;

    znajomi[liczbaZnajomych].idZapisanegoKontaktu = liczbaZnajomych + 1;
    znajomi[liczbaZnajomych].imie = imie;
    znajomi[liczbaZnajomych].nazwisko = nazwisko;
    znajomi[liczbaZnajomych].numerTelefonu = numerTelefonu;
    znajomi[liczbaZnajomych].adres = adres;
    znajomi[liczbaZnajomych].email = email;

    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << znajomi[liczbaZnajomych].idZapisanegoKontaktu << endl;
        plik << znajomi[liczbaZnajomych].imie << endl;
        plik << znajomi[liczbaZnajomych].nazwisko << endl;
        plik << znajomi[liczbaZnajomych].numerTelefonu << endl;
        plik << znajomi[liczbaZnajomych].adres << endl;
        plik << znajomi[liczbaZnajomych].email << endl;
        plik.close();
    }
    else
    {
        cout << "Nie uda³o sie otworzyc pliku i zapisac do niego danych." << endl;
        system ("pause");
    }

    cout << "Nowy kontakt zostal dodany do ksiazki adresowej"<< endl;
    Sleep(1000);
    return liczbaZnajomych+1;
}

int wczytajLiczbeZnajomych (daneZnajomych znajomi[])
{
    string linia;
    int nr_linii = 1;
    int liczbaZnajomych = 0;

    fstream plik;
    plik.open ("ksiazkaadresowa.txt", ios::in);

    if (plik.good() == true)
    {
        while (getline(plik, linia))
        {
            switch (nr_linii)
            {
            case 1:
                znajomi[liczbaZnajomych].idZapisanegoKontaktu = atoi(linia.c_str());
                break;
            case 2:
                znajomi[liczbaZnajomych].imie = linia;
                break;
            case 3:
                znajomi[liczbaZnajomych].nazwisko = linia;
                break;
            case 4:
                znajomi[liczbaZnajomych].numerTelefonu = linia;
                break;
            case 5:
                znajomi[liczbaZnajomych].adres = linia;
                break;
            case 6:
                znajomi[liczbaZnajomych].email = linia;
                break;
            }
            if (nr_linii >= 6)
            {
                nr_linii = 1;
                liczbaZnajomych++;
            }
            else
            {
                nr_linii++;
            }
        }
    }
    return liczbaZnajomych;
}

void wyszukajWedlugImienia (daneZnajomych znajomi[], int liczbaZnajomych)
{
    string imieZnajomego;
    cout << "Wpisz imie: ";
    cin >> imieZnajomego;

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (imieZnajomego == znajomi[i].imie)
        {
            cout << endl;
            cout << znajomi[i].idZapisanegoKontaktu << endl;
            cout << znajomi[i].imie << endl;
            cout << znajomi[i].nazwisko<< endl;
            cout << znajomi[i].numerTelefonu<< endl;
            cout << znajomi[i].adres<< endl;
            cout << znajomi[i].email << endl;
        }
    }
    system ("pause");
}

void wyszukajWedlugNazwiska (daneZnajomych znajomi[], int liczbaZnajomych)
{
    string nazwiskoZnajomego;
    cout << "Wpisz nazwisko: ";
    cin >> nazwiskoZnajomego;

    for (int i = 0; i < liczbaZnajomych; i++)
    {
        if (nazwiskoZnajomego == znajomi[i].nazwisko)
        {
            cout << endl;
            cout << znajomi[i].idZapisanegoKontaktu << endl;
            cout << znajomi[i].imie << endl;
            cout << znajomi[i].nazwisko<< endl;
            cout << znajomi[i].numerTelefonu<< endl;
            cout << znajomi[i].adres<< endl;
            cout << znajomi[i].email << endl;
        }
    }
    system ("pause");
}

void wyswietlListeZnajomych (daneZnajomych znajomi [], int liczbaZnajomych)
{
    for (int i = 0; i< liczbaZnajomych; i++)
    {
        cout << endl;
        cout << znajomi[i].idZapisanegoKontaktu << endl;
        cout << znajomi[i].imie << endl;
        cout << znajomi[i].nazwisko<< endl;
        cout << znajomi[i].numerTelefonu<< endl;
        cout << znajomi[i].adres<< endl;
        cout << znajomi[i].email << endl;
    }
    system("pause");
}

int main()
{
    daneZnajomych znajomi [1000];
    int liczbaZapisanychZnajomych = 0;
    char wybor;

    liczbaZapisanychZnajomych = wczytajLiczbeZnajomych(znajomi);
    cout << liczbaZapisanychZnajomych << endl;

    while (true)
    {
        system("cls");
        cout << "1. Zapisz nowa osobe do ksiazki adresowej." << endl;
        cout << "2. Wyszukaj znajomego wed³ug imienia." << endl;
        cout << "3. Wyszukaj znajomego wed³ug nazwiska." << endl;
        cout << "4. Wyswietl cala liste znajomych."<< endl;
        cout << "9. Koniec pracy." << endl;

        cin >> wybor;
        if (wybor == '1')
        {
            liczbaZapisanychZnajomych = zapisanieNowejOsoby (znajomi,liczbaZapisanychZnajomych);
        }
        else if (wybor == '2')
        {
            wyszukajWedlugImienia(znajomi, liczbaZapisanychZnajomych);
        }
        else if (wybor == '3')
        {
            wyszukajWedlugNazwiska(znajomi, liczbaZapisanychZnajomych);
        }
        else if (wybor == '4')
        {
            wyswietlListeZnajomych(znajomi, liczbaZapisanychZnajomych);
        }

        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
# Ksiazka-adresowa
