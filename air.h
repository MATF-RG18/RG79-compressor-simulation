extern void air_timer(int id);
static void move_air(int i);

typedef struct{
    float x;
    float y;
    float z;

    int in;

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
extern Air arr_air[57];

extern int air_ongoing;