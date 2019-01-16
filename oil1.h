
extern void oil1_timer(int id);
static void move_ball(int i);

//struktura za cuvanje kretanje kuglica ulja
typedef struct{
    //koordinate
    float x;
    float y;
    float z;

    int in; //da li se prikazuje

    //uglovi kroz koje prolazi i njihovo pomeranje
    float angle1 ;
    float angle2 ;
    float angle3 ;
    float angle4 ;
    //indeks koj sluzi za proveru da li je odredjeno pomeranje vec izvrseno
    int indeks1 ;
    int indeks2 ;
    int indeks3 ;
    int indeks4 ;
} Oil1;
extern int n;
extern Oil1 arr[100]; //inicijalizacja niza loptica

extern int oil1_ongoing; //da li je animacija u toku