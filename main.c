#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kocka.h"

#define MAXLEVEL 20

void ermek_generalasa(int szint)
{
    //beolvasni az ermetablát
    int d100 = dob((Dobas){1, 100});
    for(int i = 1; i <= 100; i++)
    {
        if(d100>=)//táblázat megfelelő eleme
        {
            //todo inventoryhoz hozzáadni a megfelelőt.
            break;
        }
    }
}

void ekko_generalasa()//todo kapott táblázat kezelése
{
    int d100 = dob((Dobas){1, 100});
    for(int i = 1; i <= 100)
    {
        if(i == )//táblázat megfelelő eleme
        {
            //todo inventoryhoz hozzáadni a megfelelőt
            break;
        }
    }
}

void mutargy_generalasa()//todo kapott táblázat kezelése
{
    int d100 = dob((Dobas){1, 100});
    for(int i = 1; i <= 100)
    {
        if(i == )//táblázat megfelelő eleme
        {
            //todo inventoryhoz hozzáadni a megfelelőt
            break;
        }
    }
}

void javak_generalasa(int szint)
{
    //todo belovasni a táblázatot
    //szint és d100 alapján beolvasott dobás darab ékkövek, vagy műtárgyat generálni
    int d100 = dob((Dobas){1, 100});
    if(d100>=)//műtárgy
    {
        int mennyi = dob((Dobas){, });//todo
        //todo itt beolvasni a táblát, hogy ne kelljen a ciklusban mindig
        for(int i = 1; i <= mennyi)
        {
            mutargy_generalasa();//todo táblázatot átadni
        }
    }
    else if(d100>=)//ékkő
    {
        int mennyi = dob((Dobas){, });//todo
        //todo itt beolvasni a táblát, hogy ne kelljen a ciklusban mindig
        for(int i = 1; i <= mennyi)
        {
            ekko_generalasa();//todo táblázatot átadni
        }
    }
}

void targyak_generalasa(int szint)
{

}

void kincs_generalasa(int szint)
{
    ermek_generalasa(szint);
    javak_generalasa(szint);
    targyak_generalasa(szint);
}

int main()
{
    srand(time(NULL));
    int szint = 1;
    kincs_generalasa(szint);
    return 0;
}
