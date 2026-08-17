#include<iostream>
#include "HashMap.h"


int main() {

    {
        try {
            std::cout<<"TEST INSERT----------------------------\n";
            HashMap mapa1(5);
            mapa1.insert("test1",10);
            mapa1.insert("test2",20);
            mapa1.insert("test3",30);
            std::cout<<"Dla test1 powinno byc 10 jest: "<<mapa1.serch("test1");
            std::cout<<"\nDla test2 powinno byc 20 jest: "<<mapa1.serch("test2");
            std::cout<<"\nDla test3 powinno byc 30 jest: "<<mapa1.serch("test3");
            std::cout<<"\nDla test4 powinno byc nic: "<<mapa1.serch("test4");



        }
        catch (std::invalid_argument& e) {
            std::cout<<e.what();
        }

        {
            try {
                std::cout<<"\nTest usun----------------------------------\n";
                HashMap mapa1(5);
                mapa1.insert("test1",10);
                mapa1.insert("test2",10);
                mapa1.insert("test3",10);
                mapa1.usun("test1");
                std::cout<<"\nDla test1 po usunieciu powinno byc nic: "<<mapa1.serch("test1");
            }catch (std::invalid_argument& e) {
                std::cout<<e.what();
            }
        }

        {
            try {
                std::cout<<"\nTest konstruktra kopiujacego i operatora przypisania\n------------------------";
                HashMap mapa1(5);
                mapa1.insert("test1",10);
                mapa1.insert("test2",20);
                mapa1.insert("test3",30);
                HashMap mapa2(mapa1);
                HashMap mapa3(5);
                mapa3 = mapa2;
                mapa2.usun("test1");
                mapa2.usun("test2");
                mapa2.usun("test3");
                std::cout<<"\nOczekiwany 10(m1):"<<mapa1.serch("test1");
                std::cout<<"\nOczekiwany 10(m3): "<<mapa3.serch("test1");
                std::cout<<"\nOczekiwany wyjatek: "<<mapa2.serch("test1");
            }catch (std::invalid_argument& e) {
                std::cout<<e.what();
            }

        }

    }



    return 0;
}

//
// funckja hashujaca -> int
// funcka zwikszajaca pamiec x2
// pair <