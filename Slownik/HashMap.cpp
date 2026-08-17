//
// Created by mf on 8/15/26.
//

#include "HashMap.h"
#include <cstring>

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
                Wezel *wskNastepny = m_tablica[i]->next;
                while (wskAktualnyDoUsun!=nullptr) {
                    delete wskAktualnyDoUsun;
                    wskAktualnyDoUsun = wskNastepny;
                    wskNastepny = wskNastepny->next;
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
                Wezel *wskNastepny = m_tablica[i]->next;
                while (wskNastepny!=nullptr) {
                    aktualny->next = new Wezel;
                    aktualny = aktualny->next;
                    aktualny->klucz = wskNastepny->klucz;
                    aktualny->wartosc = wskNastepny->wartosc;
                    wskNastepny = wskNastepny->next;
                }
            }
        }
    }
    return *this;
}

HashMap::~HashMap() {
    for (int i =0; i<m_rozmiar; i++) {
        if (m_tablica[i]!=nullptr) {
            Wezel* wskAktuanyDoUsun = m_tablica[i];
            Wezel* wskNastepny = m_tablica[i]->next;
            while (wskAktuanyDoUsun!=nullptr) {
                delete wskAktuanyDoUsun;
                wskAktuanyDoUsun = wskNastepny;
                wskNastepny = wskNastepny->next;
            }
        }
    }
    delete [] m_tablica;
}


//funkcje pomocnicze
size_t HashMap::hash(std::string str) {
    size_t hash = 5381;
    for (auto i : str) {
        hash += (hash *33)+i;
    }
    return hash;
}

void HashMap::insert(std::string str,double wartosc) {
    
}

void HashMap::serch() {
}

void HashMap::usun() {
}
