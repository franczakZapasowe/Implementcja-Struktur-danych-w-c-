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

HashMap::HashMap(const HashMap &h) {
    if (h.m_tablica!=nullptr) {
        m_rozmiar = h.m_rozmiar;
        m_liczbaElementow = h.m_liczbaElementow;
        m_tablica = new Wezel*[m_rozmiar];
        for (int i=0; i<m_rozmiar; i++) {
            m_tablica[i] = nullptr;
        }
        for (int i=0; i<m_rozmiar; i++) {
            if (h.m_tablica[i]!=nullptr) {
                m_tablica[i] = new Wezel;
                m_tablica[i]-> wartosc = h.m_tablica[i]->wartosc;
                m_tablica[i]->klucz = h.m_tablica[i]->klucz;

                Wezel *staryWezel = h.m_tablica[i]->next; // iteruje nim
                Wezel *nowyWezelOstatni = m_tablica[i]; // buduje nim
                while (staryWezel!=nullptr) {
                    nowyWezelOstatni->next = new Wezel;
                    nowyWezelOstatni = nowyWezelOstatni->next;
                    nowyWezelOstatni->wartosc = staryWezel->wartosc;
                    nowyWezelOstatni->klucz = staryWezel->klucz;
                    staryWezel = staryWezel->next;
                }
            }
        }
    }else {
        m_rozmiar = h.m_rozmiar;
        m_tablica = new Wezel*[m_rozmiar];
        for (int i=0; i<m_rozmiar; i++) {
            m_tablica[i] = nullptr;
        }
    }
}

HashMap & HashMap::operator=(const HashMap &h) {
    if (this!=&h) {
        m_rozmiar = h.m_rozmiar;
        delete []m_tablica;
        m_tablica = nullptr;
        if (h.m_tablica!=nullptr) {
            m_tablica = new Wezel*[m_rozmiar];
            for (int i=0; i<m_rozmiar; i++) {
                m_tablica[i] = h.m_tablica[i];
            }
        }
    }
    return *this;
}

HashMap::~HashMap() {

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
