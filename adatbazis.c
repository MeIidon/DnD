#include "adatbazis.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void adatbazis_inicializal(void)
{
    adatbazis.db_altalanos = adatbazis.db_fegyver = adatbazis.db_vert = adatbazis.db_varazstargy = 0;
}

void adatbazis_urit(void)
{
    for(int i = 0; i < adatbazis.db_altalanos; i++)
        free(adatbazis.altalanos_tulajdonsag[i]);
    for(int i = 0; i < adatbazis.db_fegyver; i++)
        free(adatbazis.fegyver_tulajdonsag[i]);
    for(int i = 0; i < adatbazis.db_vert; i++)
        free(adatbazis.vert_tulajdonsag[i]);
    for(int i = 0; i < adatbazis.db_varazstargy; i++)
        free(adatbazis.varazstargy_tulajdonsag[i]);
}

void adatbazis_fegyvertabla_beolvas(void)
{
    FILE *fegyvertabla_dat = fopen("minden_dat/fegyvertabla.dat", "r");
    char sor[256];
    e_fegyver_tipus fegyver_tipus;
    e_fegyver_meret fegyver_meret;
    while(fscanf(fegyvertabla_dat, "%[^\n]\n", sor) != -1)
    {
        if(sor[0] != '\t')
        {
            if(strcmp(sor, "Egyszerű Fegyverek - közelharc") == 0)
                fegyver_tipus = EGYSZERU_KOZEL;
            else if(strcmp(sor, "Egyszerű Fegyverek - távolsági harc") == 0)
                fegyver_tipus = EGYSZERU_TAVOL;
            else if(strcmp(sor, "Harci Fegyverek - közelharc") == 0)
                fegyver_tipus = HARCI_KOZEL;
            else if(strcmp(sor, "Harci Fegyverek - távolsági harc") == 0)
                fegyver_tipus = HARCI_TAVOL;
            else if(strcmp(sor, "Egzotikus Fegyverek - közelharc") == 0)
                fegyver_tipus = EGZOTIKUS_KOZEL;
            else if(strcmp(sor, "Egzotikus Fegyverek - távolsági harc") == 0)
                fegyver_tipus = EGZOTIKUS_TAVOL;
        }
        else if(sor[1] != '\t')
        {
            if(strcmp(sor, "\tPöttöm méretű") == 0)
                fegyver_meret = POTTOM;
            else if(strcmp(sor, "\tKis méretű") == 0)
                fegyver_meret = KICSI;
            else if(strcmp(sor, "\tKözepes méretű") == 0)
                fegyver_meret = KOZEPES;
            else if(strcmp(sor, "\tNagy méretű") == 0)
                fegyver_meret = NAGY;
            else if(strcmp(sor, "\tHatalmas méretű") == 0)
                fegyver_meret = HATALMAS;
        }
        else
        {
            int azon_alt = adatbazis.db_altalanos++;
            int azon_fegy = adatbazis.db_fegyver++;
            adatbazis.altalanos_tulajdonsag[azon_alt] = malloc(sizeof(Altalanos_tulajdonsag));
            adatbazis.fegyver_tulajdonsag[azon_fegy] = malloc(sizeof(Fegyver_tulajdonsag));
            adatbazis.altalanos_tulajdonsag[azon_alt]->osztaly = FEGYVER;
            adatbazis.altalanos_tulajdonsag[azon_alt]->azon2 = azon_fegy;
            /* darabolas */
            char csunya_nev[96];
            int ertek_szam;
            char ertek_mertek[8];
            char csunya_sebzes[8];
            char csunya_krit[16];
            char csunya_hatotav[8];
            float tomeg;
            char csunya_sebzes_tipus[32];
            char csunya_lovedek_nev[32];
            sscanf(sor,
                   "\t\t%[^\t]\t%d %[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%lf font\t%[^\t]\t%[]",
                   csunya_nev,
                   &ertek_szam,
                   ertek_mertek,
                   csunya_sebzes,
                   csunya_krit,
                   csunya_hatotav,
                   csunya_lovedek_nev
            );
            /* nev */
            altalanos_tulajdonsag_nev_szetbont(
                csunya_nev,
                adatbazis.altalanos_tulajdonsag[azon_alt]->nev_alapveto,
                adatbazis.altalanos_tulajdonsag[azon_alt]->nev_jelzok
            );
            /* ertek */
            char *mertekek = (char[]){'r', 'e', 'a', 'p'}; //rez, ezust, arany, platina
            for(int i = 0; i < 4 && ertek_mertek[0] != mertekek[i]; i++)
                ertek_szam *= 10;
            adatbazis.altalanos_tulajdonsag[azon_alt]->ertek = ertek_szam;
            /* sebzes */
            adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[1].darab = 0;
            adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[1].oldal = 0;
            sscanf(csunya_sebzes,
                   "%dd%d/%dd%d",
                   &adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[0].darab,
                   &adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[0].oldal,
                   &adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[1].darab,
                   &adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes[1].oldal
            );
            /* krit */
            if(sscanf(csunya_krit,
                      "%d-20/x%d",
                      &adatbazis.fegyver_tulajdonsag[azon_fegy]->krit_zona,
                      &adatbazis.fegyver_tulajdonsag[azon_fegy]->krit_szorzo
               ) != 2
            )
            {
                adatbazis.fegyver_tulajdonsag[azon_fegy]->krit_zona = 20;
                sscanf(csunya_krit,
                       "x%d",
                       &adatbazis.fegyver_tulajdonsag[azon_fegy]->krit_szorzo
                );
            }
            /* hatotav */
            if(scanf("%d láb", &adatbazis.fegyver_tulajdonsag[azon_fegy]->hatotav) != 1)
                adatbazis.fegyver_tulajdonsag[azon_fegy]->hatotav = 0;
            /* sebzes tipus */
            adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes_tipus = 0;
            csunya_sebzes_tipus[0] += 'a' - 'A';
            if(strstr(csunya_sebzes_tipus, "szúró") != NULL)
                adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes_tipus |= SZURO;
            if(strstr(csunya_sebzes_tipus, "vágó") != NULL)
                adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes_tipus |= VAGO;
            if(strstr(csunya_sebzes_tipus, "zúzó") != NULL)
                adatbazis.fegyver_tulajdonsag[azon_fegy]->sebzes_tipus |= ZUZO;
            /* lovedek */
            adatbazis.fegyver_tulajdonsag[azon_fegy]->lovedek_azon = -1;
            if(csunya_lovedek_nev[0] != '-')
            {
                char lovedek_nev_alapveto[32];
                char lovedek_nev_jelzok[64];
                altalanos_tulajdonsag_nev_szetbont(
                    csunya_lovedek_nev,
                    lovedek_nev_alapveto,
                    lovedek_nev_jelzok
                );
                for(int lov_azon_alt = 0; lov_azon_alt < adatbazis.db_altalanos; lov_azon_alt++)
                {
                    if(strcmp(adatbazis.altalanos_tulajdonsag[lov_azon_alt]->nev_alapveto, lovedek_nev_alapveto) == 0
                    && strcmp(adatbazis.altalanos_tulajdonsag[lov_azon_alt]->nev_alapveto, lovedek_nev_alapveto) == 0
                    )
                    {
                        adatbazis.fegyver_tulajdonsag[azon_fegy]->lovedek_azon = lov_azon_alt;
                        break;
                    }
                }
            }
        }
    }
    fclose(fegyvertabla_dat);
}

void adatbazis_verttabla_beolvas(void)
{
    FILE *verttabla_dat = fopen("minden_dat/verttabla.dat", "r");
    char sor[256];
    e_vert_tipus vert_tipus;
    int sebesseg_30_eseten;
    int sebesseg_20_eseten;
    int futas_szorzo;
    while(fscanf(verttabla_dat, "%[^\n]\n", sor) != -1)
    {
        if(sor[0] != '\t')
        {
            char csunya_vert_tipus[16];
            char csunya_sebesseg_30_eseten[8];
            char csunya_sebesseg_20_eseten[8];
            char csunya_futas_szorzo[4];
            sscanf(sor, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\n",
                csunya_vert_tipus[16],
                csunya_sebesseg_30_eseten[8],
                csunya_sebesseg_20_eseten[8],
                csunya_futas_szorzo[4],
            );
            if(strcmp(csunya_vert_tipus, "Könnyű vértek") == 0)
            {
                vert_tipus = KONNYU;
            }
            else if(strcmp(csunya_vert_tipus, "Közepes vértek") == 0)
            {
                vert_tipus = KOZEPNEHEZ;
            }
            else if(strcmp(csunya_vert_tipus, "Nehéz vértek") == 0)
            {
                vert_tipus = NEHEZ;
            }

            if(strcmp(csunya_sebesseg_30_eseten, "-") == 0)
            {
                sebesseg_30_eseten = 30;
            }
            else
            {
                sscanf(csunya_sebesseg_30_eseten, "%d láb", &sebesseg_30_eseten);
            }

            if(strcmp(csunya_sebesseg_20_eseten, "-") == 0)
            {
                sebesseg_20_eseten = 20;
            }
            else
            {
                sscanf(csunya_sebesseg_20_eseten, "%d láb", &sebesseg_20_eseten);
            }

            if(strcmp(csunya_futas_szorzo, "-") == 0)
            {
                futas_szorzo = 4;
            }
            else
            {
                sscanf(csunya_futas_szorzo, "%dx", futas_szorzo);
            }
        }
        else
        {
            char csunya_nev[96];
            int ertek_szam;
            char ertek_mertek[8];
            int vedelem_modosito;
            int max_ugyesseg;
            int modosito_vertben;
            int varazslat_rontas_esely;
            float tomeg
            sscanf(sor, "\t%[^\t]\t%d %[^\t]\t+%d\t+%d\t%d\t%d\t%d font",
                csunya_nev,
                ertek_szam,
                ertek_mertek,
                vedelem_modosito,
                max_ugyesseg;
                modosito_vertben,
                varazslat_rontas_esely,
                tomeg
            );//ez így elvileg már jó
            //és most mi jön?
        }
    }
}
