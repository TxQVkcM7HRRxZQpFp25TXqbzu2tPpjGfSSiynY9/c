#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <utility>
#include <limits>

using namespace std;

// Typy figur szachowych
enum TypFigury { PUSTA, PION, SKOCZEK, GONIEC, WIEZA, HETMAN, KROL };
enum Kolor { BRAK, BIALY, CZARNY };

struct Figura {
    TypFigury typ;
    Kolor kolor;
    Figura(TypFigury t = PUSTA, Kolor c = BRAK) : typ(t), kolor(c) {}
};

class Szachownica {
public:
    Szachownica() {
        plansza.resize(8, vector<Figura>(8));
        ustawSzachownice();
        enPassantCel = { -1, -1 };
        bialyMozeRoszadaKrotka = bialyMozeRoszadaDluga = true;
        czarnyMozeRoszadaKrotka = czarnyMozeRoszadaDluga = true;
    }

    // Wyświetlanie szachownicy
    void wyswietl() {
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                char znakFigury = pobierzZnakFigury(plansza[i][j]);
                cout << znakFigury << " ";
            }
            cout << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    // Wykonanie ruchu figury
    bool przesunFigure(string ruch, Kolor aktualnaTura) {
        if (ruch.length() != 5 || ruch[2] != '-') {
            return false;
        }

        int wierszSrc = ruch[1] - '1';
        int kolumnaSrc = ruch[0] - 'a';
        int wierszDest = ruch[4] - '1';
        int kolumnaDest = ruch[3] - 'a';

        Figura& figuraSrc = plansza[wierszSrc][kolumnaSrc];
        if (figuraSrc.kolor != aktualnaTura) {
            return false;
        }

        if (!jestPrawidlowyRuch(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest)) {
            return false;
        }

        Figura figuraDest = plansza[wierszDest][kolumnaDest];
        Figura przesunietaFigura = figuraSrc;

        // Wykonanie ruchu
        figuraSrc = Figura();
        plansza[wierszDest][kolumnaDest] = przesunietaFigura;

        // Obsługa roszady
        if (przesunietaFigura.typ == KROL && abs(kolumnaDest - kolumnaSrc) == 2) {
            if (kolumnaDest == 6) { // roszada krótka
                plansza[wierszSrc][5] = plansza[wierszSrc][7];
                plansza[wierszSrc][7] = Figura();
            }
            else if (kolumnaDest == 2) { // roszada długa
                plansza[wierszSrc][3] = plansza[wierszSrc][0];
                plansza[wierszSrc][0] = Figura();
            }
        }

        // Obsługa bicia w przelocie
        if (przesunietaFigura.typ == PION && kolumnaDest != kolumnaSrc && figuraDest.typ == PUSTA) {
            plansza[wierszSrc][kolumnaDest] = Figura();
        }

        // Ustawienie celu en passant
        if (przesunietaFigura.typ == PION && abs(wierszDest - wierszSrc) == 2) {
            enPassantCel = { wierszSrc + (wierszDest - wierszSrc) / 2, kolumnaSrc };
        }
        else {
            enPassantCel = { -1, -1 };
        }

        // Aktualizacja praw do roszady
        if (przesunietaFigura.typ == KROL) {
            if (przesunietaFigura.kolor == BIALY) {
                bialyMozeRoszadaKrotka = bialyMozeRoszadaDluga = false;
            }
            else {
                czarnyMozeRoszadaKrotka = czarnyMozeRoszadaDluga = false;
            }
        }
        else if (przesunietaFigura.typ == WIEZA) {
            if (wierszSrc == 0 && kolumnaSrc == 0) bialyMozeRoszadaDluga = false;
            if (wierszSrc == 0 && kolumnaSrc == 7) bialyMozeRoszadaKrotka = false;
            if (wierszSrc == 7 && kolumnaSrc == 0) czarnyMozeRoszadaDluga = false;
            if (wierszSrc == 7 && kolumnaSrc == 7) czarnyMozeRoszadaKrotka = false;
        }

        // Sprawdzenie, czy ruch nie prowadzi do szacha dla aktualnego gracza
        if (czySzach(aktualnaTura)) {
            // Cofnięcie ruchu
            plansza[wierszDest][kolumnaDest] = figuraDest;
            plansza[wierszSrc][kolumnaSrc] = przesunietaFigura;
            if (przesunietaFigura.typ == KROL && abs(kolumnaDest - kolumnaSrc) == 2) {
                if (kolumnaDest == 6) {
                    plansza[wierszSrc][7] = plansza[wierszSrc][5];
                    plansza[wierszSrc][5] = Figura();
                }
                else if (kolumnaDest == 2) {
                    plansza[wierszSrc][0] = plansza[wierszSrc][3];
                    plansza[wierszSrc][3] = Figura();
                }
            }
            return false;
        }

        return true;
    }

    // Sprawdzenie, czy król jest w szachu
    bool czySzach(Kolor kolor) {
        int wierszKrola, kolumnaKrola;
        znajdzKrola(kolor, wierszKrola, kolumnaKrola);
        return czyPoleAtakowane(wierszKrola, kolumnaKrola, kolor);
    }

    // Sprawdzenie, czy jest mat
    bool czySzachMat(Kolor kolor) {
        if (!czySzach(kolor)) return false;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Figura figura = plansza[i][j];
                if (figura.kolor == kolor) {
                    for (int wiersz = 0; wiersz < 8; wiersz++) {
                        for (int kolumna = 0; kolumna < 8; kolumna++) {
                            if (jestPrawidlowyRuch(i, j, wiersz, kolumna)) {
                                Figura temp = plansza[wiersz][kolumna];
                                plansza[wiersz][kolumna] = figura;
                                plansza[i][j] = Figura();
                                bool wSzachu = czySzach(kolor);
                                plansza[i][j] = figura;
                                plansza[wiersz][kolumna] = temp;
                                if (!wSzachu) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    // Sprawdzenie, czy jest pat
    bool czyPat(Kolor kolor) {
        if (czySzach(kolor)) return false;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Figura figura = plansza[i][j];
                if (figura.kolor == kolor) {
                    for (int wiersz = 0; wiersz < 8; wiersz++) {
                        for (int kolumna = 0; kolumna < 8; kolumna++) {
                            if (jestPrawidlowyRuch(i, j, wiersz, kolumna)) {
                                Figura temp = plansza[wiersz][kolumna];
                                plansza[wiersz][kolumna] = figura;
                                plansza[i][j] = Figura();
                                bool wSzachu = czySzach(kolor);
                                plansza[i][j] = figura;
                                plansza[wiersz][kolumna] = temp;
                                if (!wSzachu) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    int ocenSzachownice() {
        int wynik = 0;
        for (const auto& rzad : plansza) {
            for (const auto& figura : rzad) {
                if (figura.kolor == BIALY) {
                    wynik += pobierzWartoscFigury(figura.typ);
                }
                else if (figura.kolor == CZARNY) {
                    wynik -= pobierzWartoscFigury(figura.typ);
                }
            }
        }
        return wynik;
    }

    // Algorytm minimax
    pair<int, string> minimax(int glebokosc, Kolor tura, int alpha, int beta) {
        if (glebokosc == 0 || czySzachMat(BIALY) || czySzachMat(CZARNY) || czyPat(BIALY) || czyPat(CZARNY)) {
            return { ocenSzachownice(), "" };
        }

        vector<string> mozliweRuchy;
        for (int wierszSrc = 0; wierszSrc < 8; wierszSrc++) {
            for (int kolumnaSrc = 0; kolumnaSrc < 8; kolumnaSrc++) {
                if (plansza[wierszSrc][kolumnaSrc].kolor == tura) {
                    for (int wierszDest = 0; wierszDest < 8; wierszDest++) {
                        for (int kolumnaDest = 0; kolumnaDest < 8; kolumnaDest++) {
                            if (jestPrawidlowyRuch(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest)) {
                                mozliweRuchy.push_back({ char(kolumnaSrc + 'a'), char(wierszSrc + '1'), '-', char(kolumnaDest + 'a'), char(wierszDest + '1') });
                            }
                        }
                    }
                }
            }
        }

        int najlepszyWynik = (tura == BIALY) ? numeric_limits<int>::min() : numeric_limits<int>::max();
        string najlepszyRuch;

        for (const auto& ruch : mozliweRuchy) {
            int wierszSrc = ruch[1] - '1';
            int kolumnaSrc = ruch[0] - 'a';
            int wierszDest = ruch[4] - '1';
            int kolumnaDest = ruch[3] - 'a';

            Figura figuraSrc = plansza[wierszSrc][kolumnaSrc];
            Figura figuraDest = plansza[wierszDest][kolumnaDest];

            plansza[wierszDest][kolumnaDest] = figuraSrc;
            plansza[wierszSrc][kolumnaSrc] = Figura();

            int wynik = minimax(glebokosc - 1, (tura == BIALY) ? CZARNY : BIALY, alpha, beta).first;

            plansza[wierszSrc][kolumnaSrc] = figuraSrc;
            plansza[wierszDest][kolumnaDest] = figuraDest;

            if (tura == BIALY) {
                if (wynik > najlepszyWynik) {
                    najlepszyWynik = wynik;
                    najlepszyRuch = ruch;
                }
                alpha = max(alpha, najlepszyWynik);
            }
            else {
                if (wynik < najlepszyWynik) {
                    najlepszyWynik = wynik;
                    najlepszyRuch = ruch;
                }
                beta = min(beta, najlepszyWynik);
            }

            if (beta <= alpha) {
                break;
            }
        }

        return { najlepszyWynik, najlepszyRuch };
    }

    // Zapis stanu gry do pliku
    bool zapiszGre(const string& nazwaPliku) {
        ofstream plik(nazwaPliku);
        if (!plik.is_open()) {
            return false;
        }

        plik << aktualnaTura << endl;
        plik << bialyMozeRoszadaKrotka << " " << bialyMozeRoszadaDluga << " "
            << czarnyMozeRoszadaKrotka << " " << czarnyMozeRoszadaDluga << endl;
        plik << enPassantCel.first << " " << enPassantCel.second << endl;

        for (const auto& rzad : plansza) {
            for (const auto& figura : rzad) {
                plik << figura.typ << " " << figura.kolor << " ";
            }
            plik << endl;
        }

        plik.close();
        return true;
    }

    // Wczytanie stanu gry z pliku
    bool wczytajGre(const string& nazwaPliku) {
        ifstream plik(nazwaPliku);
        if (!plik.is_open()) {
            return false;
        }

        int tura;
        plik >> tura;
        aktualnaTura = static_cast<Kolor>(tura);
        plik >> bialyMozeRoszadaKrotka >> bialyMozeRoszadaDluga
            >> czarnyMozeRoszadaKrotka >> czarnyMozeRoszadaDluga;
        plik >> enPassantCel.first >> enPassantCel.second;

        for (auto& rzad : plansza) {
            for (auto& figura : rzad) {
                int typ, kolor;
                plik >> typ >> kolor;
                figura.typ = static_cast<TypFigury>(typ);
                figura.kolor = static_cast<Kolor>(kolor);
            }
        }

        plik.close();
        return true;
    }

    Kolor pobierzAktualnaTura() const {
        return aktualnaTura;
    }

private:
    vector<vector<Figura>> plansza;
    pair<int, int> enPassantCel;
    bool bialyMozeRoszadaKrotka, bialyMozeRoszadaDluga;
    bool czarnyMozeRoszadaKrotka, czarnyMozeRoszadaDluga;
    Kolor aktualnaTura = BIALY;

    // Ustawienie początkowej konfiguracji szachownicy
    void ustawSzachownice() {
        for (int i = 0; i < 8; i++) {
            plansza[1][i] = Figura(PION, BIALY);
            plansza[6][i] = Figura(PION, CZARNY);
        }

        plansza[0][0] = plansza[0][7] = Figura(WIEZA, BIALY);
        plansza[0][1] = plansza[0][6] = Figura(SKOCZEK, BIALY);
        plansza[0][2] = plansza[0][5] = Figura(GONIEC, BIALY);
        plansza[0][3] = Figura(HETMAN, BIALY);
        plansza[0][4] = Figura(KROL, BIALY);

        plansza[7][0] = plansza[7][7] = Figura(WIEZA, CZARNY);
        plansza[7][1] = plansza[7][6] = Figura(SKOCZEK, CZARNY);
        plansza[7][2] = plansza[7][5] = Figura(GONIEC, CZARNY);
        plansza[7][3] = Figura(HETMAN, CZARNY);
        plansza[7][4] = Figura(KROL, CZARNY);
    }

    // Pobranie znaku figury do wyświetlenia
    char pobierzZnakFigury(Figura figura) {
        if (figura.kolor == BIALY) {
            switch (figura.typ) {
            case PION: return 'P';
            case SKOCZEK: return 'N';
            case GONIEC: return 'B';
            case WIEZA: return 'R';
            case HETMAN: return 'Q';
            case KROL: return 'K';
            default: return '.';
            }
        }
        else if (figura.kolor == CZARNY) {
            switch (figura.typ) {
            case PION: return 'p';
            case SKOCZEK: return 'n';
            case GONIEC: return 'b';
            case WIEZA: return 'r';
            case HETMAN: return 'q';
            case KROL: return 'k';
            default: return '.';
            }
        }
        else {
            return '.';
        }
    }

    // Sprawdzenie, czy ruch jest prawidłowy
    bool jestPrawidlowyRuch(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        if (wierszSrc < 0 || wierszSrc >= 8 || kolumnaSrc < 0 || kolumnaSrc >= 8 ||
            wierszDest < 0 || wierszDest >= 8 || kolumnaDest < 0 || kolumnaDest >= 8) {
            return false;
        }

        Figura figuraSrc = plansza[wierszSrc][kolumnaSrc];
        Figura figuraDest = plansza[wierszDest][kolumnaDest];
        if (figuraSrc.kolor == BRAK || figuraSrc.kolor == figuraDest.kolor) {
            return false;
        }

        switch (figuraSrc.typ) {
        case PION:
            return jestPrawidlowyRuchPionem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest, figuraSrc.kolor);
        case SKOCZEK:
            return jestPrawidlowyRuchSkoczkiem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
        case GONIEC:
            return jestPrawidlowyRuchGoncem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
        case WIEZA:
            return jestPrawidlowyRuchWieza(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
        case HETMAN:
            return jestPrawidlowyRuchHetmanem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
        case KROL:
            return jestPrawidlowyRuchKrolem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
        default:
            return false;
        }
    }

    // Sprawdzenie, czy ruch pionem jest prawidłowy
    bool jestPrawidlowyRuchPionem(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest, Kolor kolor) {
        int kierunek = (kolor == BIALY) ? 1 : -1;
        if (wierszDest == wierszSrc + kierunek && kolumnaDest == kolumnaSrc && plansza[wierszDest][kolumnaDest].typ == PUSTA) {
            return true;
        }
        if (wierszDest == wierszSrc + kierunek && abs(kolumnaDest - kolumnaSrc) == 1 && plansza[wierszDest][kolumnaDest].kolor != kolor && plansza[wierszDest][kolumnaDest].kolor != BRAK) {
            return true;
        }
        if ((wierszSrc == 1 && kolor == BIALY) || (wierszSrc == 6 && kolor == CZARNY)) {
            if (wierszDest == wierszSrc + 2 * kierunek && kolumnaDest == kolumnaSrc && plansza[wierszDest][kolumnaDest].typ == PUSTA && plansza[wierszSrc + kierunek][kolumnaSrc].typ == PUSTA) {
                return true;
            }
        }
        if (wierszDest == enPassantCel.first && kolumnaDest == enPassantCel.second && abs(kolumnaDest - kolumnaSrc) == 1 && plansza[wierszSrc][kolumnaDest].kolor != kolor) {
            return true;
        }
        return false;
    }

    // Sprawdzenie, czy ruch skoczkiem jest prawidłowy
    bool jestPrawidlowyRuchSkoczkiem(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        int roznicaWiersz = abs(wierszDest - wierszSrc);
        int roznicaKolumna = abs(kolumnaDest - kolumnaSrc);
        return (roznicaWiersz == 2 && roznicaKolumna == 1) || (roznicaWiersz == 1 && roznicaKolumna == 2);
    }

    // Sprawdzenie, czy ruch gońcem jest prawidłowy
    bool jestPrawidlowyRuchGoncem(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        if (abs(wierszDest - wierszSrc) != abs(kolumnaDest - kolumnaSrc)) return false;
        int krokWiersz = (wierszDest - wierszSrc) / abs(wierszDest - wierszSrc);
        int krokKolumna = (kolumnaDest - kolumnaSrc) / abs(kolumnaDest - kolumnaSrc);
        for (int i = 1; i < abs(wierszDest - wierszSrc); ++i) {
            if (plansza[wierszSrc + i * krokWiersz][kolumnaSrc + i * krokKolumna].typ != PUSTA) {
                return false;
            }
        }
        return true;
    }

    // Sprawdzenie, czy ruch wieżą jest prawidłowy
    bool jestPrawidlowyRuchWieza(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        if (wierszSrc != wierszDest && kolumnaSrc != kolumnaDest) return false;
        if (wierszSrc == wierszDest) {
            int krokKolumna = (kolumnaDest - kolumnaSrc) / abs(kolumnaDest - kolumnaSrc);
            for (int i = 1; i < abs(kolumnaDest - kolumnaSrc); ++i) {
                if (plansza[wierszSrc][kolumnaSrc + i * krokKolumna].typ != PUSTA) {
                    return false;
                }
            }
        }
        else {
            int krokWiersz = (wierszDest - wierszSrc) / abs(wierszDest - wierszSrc);
            for (int i = 1; i < abs(wierszDest - wierszSrc); ++i) {
                if (plansza[wierszSrc + i * krokWiersz][kolumnaSrc].typ != PUSTA) {
                    return false;
                }
            }
        }
        return true;
    }

    // Sprawdzenie, czy ruch hetmanem jest prawidłowy
    bool jestPrawidlowyRuchHetmanem(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        return jestPrawidlowyRuchWieza(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest) || jestPrawidlowyRuchGoncem(wierszSrc, kolumnaSrc, wierszDest, kolumnaDest);
    }

    // Sprawdzenie, czy ruch królem jest prawidłowy
    bool jestPrawidlowyRuchKrolem(int wierszSrc, int kolumnaSrc, int wierszDest, int kolumnaDest) {
        int roznicaWiersz = abs(wierszDest - wierszSrc);
        int roznicaKolumna = abs(kolumnaDest - kolumnaSrc);
        if (roznicaWiersz <= 1 && roznicaKolumna <= 1) {
            return true;
        }
        if (wierszSrc == wierszDest && roznicaWiersz == 0 && abs(kolumnaDest - kolumnaSrc) == 2) {
            if (kolumnaSrc == 4) {
                if (kolumnaDest == 6) { // Roszada krótka
                    return (plansza[wierszSrc][5].typ == PUSTA && plansza[wierszSrc][6].typ == PUSTA &&
                        ((plansza[wierszSrc][7].typ == WIEZA && plansza[wierszSrc][7].kolor == plansza[wierszSrc][4].kolor)));
                }
                else if (kolumnaDest == 2) { // Roszada długa
                    return (plansza[wierszSrc][1].typ == PUSTA && plansza[wierszSrc][2].typ == PUSTA && plansza[wierszSrc][3].typ == PUSTA &&
                        ((plansza[wierszSrc][0].typ == WIEZA && plansza[wierszSrc][0].kolor == plansza[wierszSrc][4].kolor)));
                }
            }
        }
        return false;
    }

    // Sprawdzenie, czy dane pole jest atakowane
    bool czyPoleAtakowane(int wiersz, int kolumna, Kolor kolor) {
        Kolor przeciwnik = (kolor == BIALY) ? CZARNY : BIALY;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Figura figura = plansza[i][j];
                if (figura.kolor == przeciwnik && jestPrawidlowyRuch(i, j, wiersz, kolumna)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Znalezienie pozycji króla danego koloru
    void znajdzKrola(Kolor kolor, int& wierszKrola, int& kolumnaKrola) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (plansza[i][j].typ == KROL && plansza[i][j].kolor == kolor) {
                    wierszKrola = i;
                    kolumnaKrola = j;
                    return;
                }
            }
        }
    }

    // Pobranie wartości figury
    int pobierzWartoscFigury(TypFigury typ) {
        switch (typ) {
        case PION: return 10;
        case SKOCZEK: return 30;
        case GONIEC: return 30;
        case WIEZA: return 50;
        case HETMAN: return 90;
        case KROL: return 900;
        default: return 0;
        }
    }
};

class GraSzachowa {
public:
    GraSzachowa() : aktualnaTura(BIALY) {}

    // Rozpoczęcie gry
    void graj() {
        string ruch;
        while (true) {
            szachownica.wyswietl();
            if (szachownica.czySzachMat(aktualnaTura)) {
                cout << (aktualnaTura == BIALY ? "Biały" : "Czarny") << " o3mał mata "
                    << (aktualnaTura == BIALY ? "Czarny" : "Biały") << " wygrywa!" << endl;
                break;
            }
            if (szachownica.czyPat(aktualnaTura)) {
                cout << "Pat! Gra kończy się remisem." << endl;
                break;
            }

            if (aktualnaTura == BIALY) {
                cout << "Ruch Białych. Wprowadź swój ruch (np. e2-e4), lub wpisz 'zapisz', aby zapisać grę, lub 'wczytaj', aby wczytać grę: ";
                cin >> ruch;
                if (ruch == "zapisz") {
                    string nazwaPliku;
                    cout << "Podaj nazwę pliku do zapisania gry: ";
                    cin >> nazwaPliku;
                    if (szachownica.zapiszGre(nazwaPliku)) {
                        cout << "Gra została zapisana pomyślnie." << endl;
                    }
                    else {
                        cout << "Nie udało się zapisać gry." << endl;
                    }
                    continue;
                }
                else if (ruch == "wczytaj") {
                    string nazwaPliku;
                    cout << "Podaj nazwę pliku do wczytania gry: ";
                    cin >> nazwaPliku;
                    if (szachownica.wczytajGre(nazwaPliku)) {
                        aktualnaTura = szachownica.pobierzAktualnaTura();
                        cout << "Gra została wczytana pomyślnie." << endl;
                    }
                    else {
                        cout << "Nie udało się wczytać gry." << endl;
                    }
                    continue;
                }
                else if (ruch == "exit") {
                    break;
                }
                if (!szachownica.przesunFigure(ruch, aktualnaTura)) {
                    cout << "Nieprawidłowy ruch. Spróbuj ponownie." << endl;
                    continue;
                }
            }
            else {
                cout << "Ruch Czarnych." << endl;
                ruch = szachownica.minimax(3, aktualnaTura, numeric_limits<int>::min(), numeric_limits<int>::max()).second;
                if (!szachownica.przesunFigure(ruch, aktualnaTura)) {
                    cout << "AI wykonało nieprawidłowy ruch." << endl;
                    break;
                }
                cout << "AI wykonało ruch: " << ruch << endl;
            }

            aktualnaTura = (aktualnaTura == BIALY) ? CZARNY : BIALY;
        }
    }

private:
    Szachownica szachownica;
    Kolor aktualnaTura;
};

int main() {
    GraSzachowa gra;
    gra.graj();
    return 0;
}
