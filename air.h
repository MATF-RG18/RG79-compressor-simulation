extern void air_timer(int id);
static void move_air(int i);
//struktura za cuvanje kretanje kuglica vazduha
typedef struct{
    //koordinate
    float x;
    float y;
    float z;

    int in;//da li se prikazuje

    //uglovi kroz koje prolazi i njihovo pomeranje
    float angle_air1;
    float angle_air2;
    float angle_air3;
    float angle_air4;
    float angle_air5 ;
    float angle_air6 ;
    float angle_air7 ;
    float angle_air8 ;
    float angle_air9 ;
    float angle_air10;
    float angle_air11;
    float angle_air12;

    //indeks koj sluzi za proveru da li je odredjeno pomeranje vec izvrseno
    int indeks1;
    int indeks2;
    int indeks3;
    int indeks4;
    int indeks5;
    int indeks6;
    int indeks7;
    int indeks8;
    int indeks9;
    int indeks10;
    int indeks11;

} Air;

int n_air;
extern Air arr_air[57]; //inicijalizacja niza loptica
extern int air_ongoing; //da li je animacija u toku