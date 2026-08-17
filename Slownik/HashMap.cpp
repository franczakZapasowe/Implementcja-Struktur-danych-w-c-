//
// Created by mf on 8/15/26.
//

#include "HashMap.h"
#include <cstring>
#include <stdexcept>

HashMap::HashMap(int rozmiar) {
    if (rozmiar>0) {
        m_rozmiar = rozmiar;
        m_tablica = new Wezel*[m_rozmiar];
        for (int i=0; i<m_rozmiar; i++) {
            m_tablica[i] = nullptr; // musze to zrobic cala tablica musi byc nullptr przy alokacji!!!!!
        }
    }
}

HashMap::HashMap(const HashMap &h):m_rozmiar(h.m_rozmiar),m_liczbaElementow(h.m_liczbaElementow) {
    if (h.m_tablica!=nullptr) {
        m_tablica = new Wezel*[m_rozmiar];
        for (int i=0; i<m_rozmiar; i++) {
            if (h.m_tablica[i]!=nullptr) {
                m_tablica[i] = new Wezel;
                m_tablica[i]->klucz = h.m_tablica[i]->klucz;
                m_tablica[i]->wartosc = h.m_tablica[i]->wartosc;

                Wezel*wskNastepny = h.m_tablica[i]->next;
                Wezel*aktualny = m_tablica[i];

                while (wskNastepny!=nullptr) {
                    aktualny->next = new Wezel;
                    aktualny = aktualny->next;
                    aktualny->klucz = wskNastepny->klucz;
                    aktualny->wartosc = wskNastepny->wartosc;
                    wskNastepny = wskNastepny->next;
                }
            }else {
                m_tablica[i] = nullptr;
            }
        }

    }else {
        m_tablica = nullptr;
        m_liczbaElementow = 0;
        m_rozmiar = 0;
    }
}

HashMap & HashMap::operator=(const HashMap &h) {
    if (this!=&h) {
        // najpierw usuwam wszystkie elementy aktualnej tablicy
        for (int i =0; i<m_rozmiar; i++) {
            if (m_tablica[i]!=nullptr) {
                Wezel *wskAktualnyDoUsun = m_tablica[i];
                while (wskAktualnyDoUsun!=nullptr) {
                    Wezel *wskNastepny = wskAktualnyDoUsun ->next;
                    delete wskAktualnyDoUsun;
                    wskAktualnyDoUsun = wskNastepny;
                }
            }
        }
        // teraz musimy przekopiowac wartosci
        delete [] m_tablica;
        m_tablica = nullptr;
        m_liczbaElementow = h.m_liczbaElementow;
        m_rozmiar = h.m_rozmiar;
        m_tablica = new Wezel *[m_rozmiar];
        for (int i=0; i<h.m_rozmiar; i++) {
            if (h.m_tablica[i]!=nullptr) {
                m_tablica[i] = new Wezel;
                m_tablica[i]->klucz = h.m_tablica[i]->klucz;
                m_tablica[i]->wartosc = h.m_tablica[i]->wartosc;

                Wezel *aktualny = m_tablica[i];
                Wezel *wskNastepny = h.m_tablica[i]->next;
                while (wskNastepny!=nullptr) {
                    aktualny->next = new Wezel;
                    aktualny = aktualny->next;
                    aktualny->klucz = wskNastepny->klucz;
                    aktualny->wartosc = wskNastepny->wartosc;
                    wskNastepny = wskNastepny->next;
                }
            }else {
                m_tablica[i] = nullptr;
            }
        }
    }
    return *this;
}

HashMap::~HashMap() {
    for (int i =0; i<m_rozmiar; i++) {
        if (m_tablica[i]!=nullptr) {
            Wezel* wskAktuanyDoUsun = m_tablica[i];
            while (wskAktuanyDoUsun!=nullptr) {
                Wezel* wskNastepny = wskAktuanyDoUsun->next;
                delete wskAktuanyDoUsun;
                wskAktuanyDoUsun = wskNastepny;
            }
        }
    }
    delete [] m_tablica;
}


//funkcje pomocnicze
size_t HashMap::hash(std::string str) {
    size_t hash = 5381;
    for (unsigned char i : str) {
        hash += (hash *33)+i;
    }
    return hash;
}

void HashMap::insert(std::string str,double wartosc) {
    int indeks = hash(str) % m_rozmiar;
    if (m_tablica[indeks]!=nullptr) {
        Wezel *wsk = m_tablica[indeks];
        Wezel *wskPoprzedni;
        while (wsk!=nullptr) {
            wskPoprzedni = wsk;
            if (wsk->klucz == str) {
                wsk->wartosc = wartosc;
                return;
            }
            wsk = wsk->next;
        }
            wsk = new Wezel;
            wsk->klucz = str;
            wsk->wartosc = wartosc;
            wskPoprzedni->next = wsk;
            m_liczbaElementow++;
    }else {
        m_tablica[indeks] = new Wezel;
        m_tablica[indeks]->klucz = str;
        m_tablica[indeks]->wartosc = wartosc;
        m_liczbaElementow++;
    }
}

double HashMap::serch(std::string klucz) {
    int index = hash(klucz)%m_rozmiar;
    if (m_tablica[index]!=nullptr) {
        Wezel *wsk = m_tablica[index];
        while (wsk!=nullptr) {
            if (wsk->klucz == klucz) {
                return wsk->wartosc;
            }
            wsk = wsk->next;
        }
        throw std::invalid_argument("Klucz nie istnieje");
    }else {
        throw std::invalid_argument("Klucz nie istnieje");
    }
}

void HashMap::usun(std::string klucz) {
    int index = hash(klucz)%m_rozmiar;
    if (m_tablica[index]!=nullptr) {
        // przpyadek gdy 1 elemnt tablicy pasuje odrazu m_tablica[index]->klucz == klucz
        Wezel *wsk = m_tablica[index]->next;
        if (m_tablica[index]->klucz == klucz) {
            delete m_tablica[index];
            m_tablica[index] = wsk;
            m_liczbaElementow--;
            return;
        }

        Wezel *wskDoUsuniecia = m_tablica[index]->next;
        Wezel *wskPoprzedni = m_tablica[index];
        while (wskDoUsuniecia!=nullptr) {
            if (klucz == wskDoUsuniecia->klucz) {
                wskPoprzedni->next = wskDoUsuniecia->next;
                delete wskDoUsuniecia;
                m_liczbaElementow--;
                return;
            }
            wskPoprzedni = wskDoUsuniecia;
            wskDoUsuniecia = wskDoUsuniecia->next;
        }
        throw std::invalid_argument("Klucz nie istnieje");
    }else {
        throw std::invalid_argument("Klucz nie istnieje");
    }
}
