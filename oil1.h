
extern void oil1_timer(int id);
static void move_ball(int i);

typedef struct{
    float x;
    float y;
    float z;
    int in;

    float angle1 ;
    float angle2 ;
    float angle3 ;
    float angle4 ;
    int indeks1 ;
    int indeks2 ;
    int indeks3 ;
    int indeks4 ;
} Oil1;
extern int n;
extern Oil1 arr[100]; 

extern int oil1_ongoing;