
typedef enum {ALTALANOS, FEGYVER, VERT, VARAZSTARGY} e_osztaly;

typedef struct
{
    char nev_alapveto[32];
    char nev_jelzok[64];
    e_osztaly osztaly;
    int azon2;
    int ertek;
    float tomeg;
} Altalanos_tulajdonsag;
