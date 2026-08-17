//
// Created by mf on 8/15/26.
//

#ifndef SLOWNIK_HASHMAP_H
#define SLOWNIK_HASHMAP_H
#include <iostream>

struct Wezel {
    std::string klucz;
    double wartosc;
    Wezel *next;
    Wezel():next(nullptr){}
};

class HashMap {
    Wezel **m_tablica;
    int m_rozmiar = 1000;
    int m_liczbaElementow = 0;

    size_t hash(std::string);
public:
    HashMap() = delete;
    HashMap(int rozmiar);
    HashMap(const HashMap &h);
    HashMap &operator=(const HashMap &h);
    ~HashMap();
    void insert(std::string,double wartosc);
    double serch(std::string);
    void usun(std::string);
};

#endif //SLOWNIK_HASHMAP_H
