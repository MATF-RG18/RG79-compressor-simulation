
extern void oil2_timer(int id);
static void move_oil2(int i);

typedef struct {
    float x;
    float y;
    float z;
    int in;

    float angle1;
    float angle2; 
    float angle3;
    float angle4;
    float angle5;
    float angle6;
    float angle7; 
    float angle8;
    float angle9;
    float angle10;
    float angle11;
    float angle12;

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
    int indeks12;
    int indeks13;
    int indeks14;

} Oil2;

int n_oil2;
extern Oil2 arr_oil2[150];

extern int oil2_ongoing;