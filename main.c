#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "air.h"
#include "oil1.h"
#include "oil2.h"


#define STEP 100
#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define Pi 3.14159265359

//model macros
#define PROPELLER_ID 1
#define CYLINDER_ID 2
#define CYLINDERHOLES_ID 3
#define SCREW1_ID 4
#define SCREW2_ID 5
#define BLOCK_ID 6
#define FILTER_ID 7
#define PIPELINE1_ID 8
#define PIPELINE2_ID 9
#define PIPELINE3_ID 10
#define PIPELINE4_ID 11
#define PIPELINE5_ID 12

//struktura za cuvanje modela
typedef struct Vertex
{
    double position[3];
    double texcoord[2];
    double normal[3];
} Vertex;

//struktura za cuvanje podataka iz .obj fajla
typedef struct VertRef
{
    int v, vt, vn;
} VertRef;

//promenljive za pomeranje kamere misom
static int mouse_x, mouse_y;
static int window_width, window_height;
static float matrix[16];

//parametri za pokretanje animacije
static float animation_parametar = 0;
static int animation_ongoing = 0;

//parametri za animaciju vazduha
int air_ongoing = 0;
Air arr_air[57];
int n_air = 57;

//parametri za animaciju ulja od filtera do bloka
int oil1_ongoing = 0;
Oil1 arr[100];
int n = 100;


//paramteri za animaciju ulja od rezervoara do bloka
int oil2_ongoing = 0;
Oil2 arr_oil2[150];
int n_oil2 = 150;

//promenljive gde se cuvaju modeli
static Vertex *model;
static int model_size = 0;

static Vertex *model_cylinderholes;
static int model_size_cylinderholes = 0;

static Vertex *model_cylinder;
static int model_size_cylinder = 0;

static Vertex *model_screw1;
static int model_size_screw1 = 0;

static Vertex *model_screw2;
static int model_size_screw2 = 0;

static Vertex *model_block;
static int model_size_block = 0;

static Vertex *model_filter;
static int model_size_filter = 0;

static Vertex *model_pipeline1;
static int model_size_pipeline1 = 0;

static Vertex *model_pipeline2;
static int model_size_pipeline2 = 0;

static Vertex *model_pipeline3;
static int model_size_pipeline3 = 0;

static Vertex *model_pipeline4;
static int model_size_pipeline4 = 0;

static Vertex *model_pipeline5;
static int model_size_pipeline5 = 0;


static void on_keyboard(unsigned char key, int x , int y);
static void on_display(void);
static void on_reshape(int width, int height);
static void on_timer(int id);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);

static void draw_propeller(void);
static void draw_pressure_chamber(void);
static void draw_block(void);
static void draw_pipeline1(void);
static void draw_pipeline2(void);
static void draw_pipeline3(void);
static void draw_pipeline4(void);
static void draw_pipeline5(void);

Vertex* LoadObj(FILE * file, int id);


int main(int argc, char *argv[])
{
    GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(900,600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);
    //inicijaliacija za animaciju ulja od filtera do bloka
    arr[0].x = 5.75;
    arr[0].y = -0.7;
    arr[0].z = -0.2;
    arr[0].in = 1;

    arr[0].angle1 = 0;
    arr[0].angle2 = Pi/2;
    arr[0].angle3 = 0;
    arr[0].angle4 = Pi/2;
    arr[0].indeks1 = 0;
    arr[0].indeks2 = 0;
    arr[0].indeks3 = 0;
    arr[0].indeks4 = 0;

    for(int i=1; i<n; i++){
        
        arr[i].x = 5.75;
        arr[i].y =  arr[0].y - i*0.2;
        arr[i].z = -0.2;
        arr[i].in = 0;
        arr[i].angle1 = 0;
        arr[i].angle2 = Pi/2;
        arr[i].angle3 = 0;
        arr[i].angle4 = Pi/2;
        arr[i].indeks1 = 0;
        arr[i].indeks2 = 0;
        arr[i].indeks3 = 0;
        arr[i].indeks4 = 0;
    } 

    //inicijalizacija za animaciju vazduha
    arr_air[0].x = -2;
    arr_air[0].y = 4.5;
    arr_air[0].z = 0.75;
    arr_air[0].in = 1;

    arr_air[0].angle_air1 = 3*Pi/2;
    arr_air[0].angle_air2 = 0;
    arr_air[0].angle_air3 = 3*Pi/2;
    arr_air[0].angle_air4 = Pi;
    arr_air[0].angle_air5 = Pi;
    arr_air[0].angle_air6 = Pi;
    arr_air[0].angle_air7 = Pi;
    arr_air[0].angle_air8 = Pi/2;
    arr_air[0].angle_air9 = Pi/2;
    arr_air[0].angle_air10 = 3*Pi/2;
    arr_air[0].angle_air11 = Pi;
    arr_air[0].angle_air12 = 3*Pi/2;
    arr_air[0].indeks1 = 0;
    arr_air[0].indeks2 = 0;
    arr_air[0].indeks3 = 0;
    arr_air[0].indeks4 = 0;
    arr_air[0].indeks5 = 0;
    arr_air[0].indeks6 = 0;
    arr_air[0].indeks7 = 0;
    arr_air[0].indeks8 = 0;
    arr_air[0].indeks9 = 0;
    arr_air[0].indeks10 = 0;
    arr_air[0].indeks11 = 0;


    for(int i=1; i<n_air; i++){
        arr_air[i].x = -2;
        arr_air[i].y = arr_air[0].y + i*0.5;
        arr_air[i].z = 0.75;
        arr_air[i].in = 0;

        arr_air[i].angle_air1 = 3*Pi/2;
        arr_air[i].angle_air2 = 0;
        arr_air[i].angle_air3 = 3*Pi/2;
        arr_air[i].angle_air4 = Pi;
        arr_air[i].angle_air5 = Pi;
        arr_air[i].angle_air6 = Pi;
        arr_air[i].angle_air7 = Pi;
        arr_air[i].angle_air8 = Pi/2;
        arr_air[i].angle_air9 = Pi/2;
        arr_air[i].angle_air10 = 3*Pi/2;
        arr_air[i].angle_air11 = Pi;
        arr_air[i].angle_air12 = 3*Pi/2;
        arr_air[i].indeks1 = 0;
        arr_air[i].indeks2 = 0;
        arr_air[i].indeks3 = 0;
        arr_air[i].indeks4 = 0;
        arr_air[i].indeks5 = 0;
        arr_air[i].indeks6 = 0;
        arr_air[i].indeks7 = 0;
        arr_air[i].indeks8 = 0;
        arr_air[i].indeks9 = 0;
        arr_air[i].indeks10 = 0;
        arr_air[i].indeks11 = 0;
    }
    
    //animacija za inicijalizaciju ulja od rezervoara do bloka
    arr_oil2[0].x = 7;
    arr_oil2[0].y = -2.6;
    arr_oil2[0].z = 0.1;
    arr_oil2[0].in = 1;

    arr_oil2[0].angle1 = Pi/2;
    arr_oil2[0].angle2 = 0;
    arr_oil2[0].angle3 = 3*Pi/2;
    arr_oil2[0].angle4 = Pi;
    arr_oil2[0].angle5 = Pi;
    arr_oil2[0].angle6 = Pi;
    arr_oil2[0].angle7 = 0;
    arr_oil2[0].angle8 = Pi/2;
    arr_oil2[0].angle9 = Pi;
    arr_oil2[0].angle10 = 3*Pi/2;
    arr_oil2[0].angle11 = Pi;
    arr_oil2[0].angle12 = 3*Pi/2;

    arr_oil2[0].indeks1 = 0;
    arr_oil2[0].indeks2 = 0;
    arr_oil2[0].indeks3 = 0;
    arr_oil2[0].indeks4 = 0;
    arr_oil2[0].indeks5 = 0;
    arr_oil2[0].indeks6 = 0;
    arr_oil2[0].indeks7 = 0;
    arr_oil2[0].indeks8 = 0;
    arr_oil2[0].indeks9 = 0;
    arr_oil2[0].indeks10 = 0;
    arr_oil2[0].indeks11 = 0;
    arr_oil2[0].indeks12 = 0;
    arr_oil2[0].indeks13 = 0;
    arr_oil2[0].indeks14 = 0;

    for(int i=0; i<n_oil2; i++){
        arr_oil2[i].x = 7 - i*0.5;
        arr_oil2[i].y = -2.6;
        arr_oil2[i].z = 0.1;
        arr_oil2[i].in = 0;
        arr_oil2[i].angle1 = Pi/2;
        arr_oil2[i].angle2 = 0;
        arr_oil2[i].angle3 = 3*Pi/2;
        arr_oil2[i].angle4 = Pi;
        arr_oil2[i].angle5 = Pi;
        arr_oil2[i].angle6 = Pi;
        arr_oil2[i].angle7 = 0;
        arr_oil2[i].angle8 = Pi/2;
        arr_oil2[i].angle9 = Pi;
        arr_oil2[i].angle10 = 3*Pi/2;
        arr_oil2[i].angle11 = Pi;
        arr_oil2[i].angle12 = 3*Pi/2;
        arr_oil2[i].indeks1 = 0;
        arr_oil2[i].indeks2 = 0;
        arr_oil2[i].indeks3 = 0;
        arr_oil2[i].indeks4 = 0;
        arr_oil2[i].indeks5 = 0;
        arr_oil2[i].indeks6 = 0;
        arr_oil2[i].indeks7 = 0;
        arr_oil2[i].indeks8 = 0;
        arr_oil2[i].indeks9 = 0;
        arr_oil2[i].indeks10 = 0;
        arr_oil2[i].indeks11 = 0;
        arr_oil2[i].indeks12 = 0;
        arr_oil2[i].indeks13 = 0;
        arr_oil2[i].indeks14 = 0;
    }


    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);
    
    glClearColor(0.1, 0.1, 0.11, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    //otvaranje .obj fajlova i prosledjivanje u funkciju za ucitavanje modela
    FILE * fileP = fopen("./blender_models/propeller.obj", "r");
    if( fileP == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model = LoadObj(fileP, PROPELLER_ID);

    FILE * fileC = fopen("./blender_models/cylinder.obj", "r");
    if( fileC == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_cylinder = LoadObj(fileC, CYLINDER_ID);

    FILE * fileCH = fopen("./blender_models/cylinderholes.obj", "r");
    if( fileCH == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_cylinderholes = LoadObj(fileCH, CYLINDERHOLES_ID);

    FILE * fileS1 = fopen("./blender_models/rotor.obj", "r");
    if( fileS1 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_screw1 = LoadObj(fileS1, SCREW1_ID);

    FILE * fileS2 = fopen("./blender_models/rotor.obj", "r");
    if( fileS2 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_screw2 = LoadObj(fileS2, SCREW2_ID);

    FILE * fileB = fopen("./blender_models/block.obj", "r");
    if( fileB == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_block = LoadObj(fileB, BLOCK_ID);

    FILE * fileF = fopen("./blender_models/filter.obj", "r");
    if( fileF == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_filter = LoadObj(fileF, FILTER_ID);

    FILE * filePL1 = fopen("./blender_models/pipeline1.obj", "r");
    if( filePL1 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_pipeline1 = LoadObj(filePL1, PIPELINE1_ID);


    FILE * filePL2 = fopen("./blender_models/pipeline2.obj", "r");
    if( filePL2 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_pipeline2 = LoadObj(filePL2, PIPELINE2_ID);

    FILE * filePL3 = fopen("./blender_models/pipeline3.obj", "r");
    if( filePL3 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_pipeline3 = LoadObj(filePL3, PIPELINE3_ID);

    FILE * filePL4 = fopen("./blender_models/pipeline4.obj", "r");
    if( filePL4 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_pipeline4 = LoadObj(filePL4, PIPELINE4_ID);

    FILE * filePL5 = fopen("./blender_models/pipeline5.obj", "r");
    if( filePL5 == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    model_pipeline5 = LoadObj(filePL5, PIPELINE5_ID);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x , int y) 
{
    switch(key){
        case 27:
            exit(0);
            break;
        case 'b':
        case 'B':
        // dugme za pocetak animacije
            if(!animation_ongoing){
                animation_ongoing = 1;
                air_ongoing = 1;
                oil1_ongoing = 1;
                oil2_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                glutTimerFunc(TIMER_INTERVAL, air_timer, TIMER_ID);
                glutTimerFunc(TIMER_INTERVAL, oil1_timer, TIMER_ID);
                glutTimerFunc(TIMER_INTERVAL, oil2_timer, TIMER_ID);
                
            }
            break;
        case 'e':
        case 'E':
        //dugme za prekid animacije
            animation_ongoing = 0;
            animation_ongoing = 0;
            air_ongoing = 0;
            oil1_ongoing = 0;
            oil2_ongoing = 0;
            break;
    }
}
//timer funkcija za propeler
static void on_timer(int id)
{
    if(id == TIMER_ID)
    {
        animation_parametar += 0.1;   
    }

    glutPostRedisplay();

    if(animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

}

static void on_reshape(int width, int height) 
{   
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        45,
        width/(float)height,
        1,
        100
    );
}

static void on_display(void)
{
    GLfloat light_position[] = { 0, 0, 0, 1 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    gluLookAt(
        0, 1, 20,
        0, 0, 0,
        0, 1, 0
    );
    glMultMatrixf(matrix);
    

    //iscrtavanje ventilatora(propelera) za hladjenje
     glPushMatrix();
    {
        glTranslatef(-3, 5.5, 0);
        glScalef(1.7, 1.7, 1.7);
        draw_propeller();
    }
    glPopMatrix();

    //iscrtavanje loptica za ulje od rezervoara do bloka
    for(int i=0; i<n_oil2; i++){
        glPushMatrix();
        {
            GLfloat diffuse3[] = {1,1,0,1};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
            if(arr_oil2[i].in){
                glTranslatef(arr_oil2[i].x, arr_oil2[i].y, arr_oil2[i].z);
                glutSolidSphere(0.04, 20, 20);
            }
        }
        glPopMatrix();
    }

    //iscrtavanje loptica za vazduh
    for(int i=0; i<n; i++){
        glPushMatrix();
        {
            GLfloat diffuse2[] = {1,1,0,1};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
            
            if(arr[i].in){
                glTranslatef(arr[i].x, arr[i].y, arr[i].z);
                glutSolidSphere(0.04, 20, 20);
            }
        }
        glPopMatrix();
    }

    // //iscrtavanje loptica za ulje od filtera do bloka
    for(int i=0; i<n_air; i++){
        glPushMatrix();
        {
            GLfloat diffuse1[] = {0,0,1,1};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
            if(arr_air[i].in){
                glTranslatef(arr_air[i].x, arr_air[i].y, arr_air[i].z);
                glutSolidSphere(0.05, 20, 20);
            }
        }
        glPopMatrix();
    }

    //iscrtavanje cevki od rezervoara do ventilatora pa do bloka
    glPushMatrix();
    {
        glTranslatef(3.3, -4, 0);
        draw_pipeline5();
    }
    glPopMatrix();

    //iscrtavanje cevke od pipeline5 do bloka
    glPushMatrix();
    {
        glTranslatef(-3.5, -5, 0);
        draw_pipeline4();
    }
    glPopMatrix();

    //iscrtavanje cevki od bloka do rezervoara
     glPushMatrix();
    {
        glTranslatef(0, -3.5, 0);
        draw_pipeline3();
    }
    glPopMatrix();

    //iscrtavanje cevki od filtera do bloka
    glPushMatrix();
    {
        glTranslatef(0, -1, 0);
        draw_pipeline2();
    }
    glPopMatrix();

    //iscrtavanje cevki od rezervoara van kompresora
    glPushMatrix();
    {
        glTranslatef(3.9, 4, 0);
        draw_pipeline1();
    }
    glPopMatrix();

    // iscrtavanje rezervoara sa filterom
    glPushMatrix();
    {
        glTranslatef(6, -2, 0);
        glScalef(1.5, 1.5, 1.5);
        draw_pressure_chamber();
    }
    glPopMatrix();

    //crtanje vicanog bloka
    glPushMatrix();
    {
        glTranslatef(-3, -5, 0);
        draw_block();
    }
    glPopMatrix();

    
    

    glutSwapBuffers();
}

//funkcija za iscrtavanje ventilatora
static void draw_propeller(void)
{
    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };
    GLfloat diffuse_coeffs[] = { .7, .7, .7, 1 };
    GLfloat specular_coeffs[] = { .2, .2, .2, 1};
    
    GLfloat shininess = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glRotatef(9*animation_parametar,0, 1, 0);
    glScalef(.5, .5, .5);
    /*
    Model ucitavamo tako sto inicijalizujemo glBegin na GL_TRIANGLES
    prolazimo petljom kroz niz tipa Vertex i citamo redom potrebne podatke
    u glnormal3f stavaljmo odgovarajuce koordinate (0=x, 1=y, 2=z)
    isto i za glVertex3f
    posle toga zavrsavamo sa glEnd
    Dalje svaki sledeci model ucitavamo po istom principu
    */
    glBegin(GL_TRIANGLES);
        for(int i=0; i<model_size; i++){
                glNormal3f(model[i].normal[0], model[i].normal[1], model[i].normal[2]);
                glVertex3f(model[i].position[0], model[i].position[1], model[i].position[2]);
        } 
    glEnd();
}

//funkcija za iscrtavanje rezervoara sa filterom
static void draw_pressure_chamber(void)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs2[] = { 0, 0, 0, .1};
    GLfloat diffuse_coeffs2[] = { 1, 1, 1, .1};
    GLfloat specular_coeffs2[] = { .2, .2, .2, .1};
    
    GLfloat shininess2 = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);

    glPushMatrix();
        glTranslatef(0,0.59,0);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_cylinderholes; i++){
                    glNormal3f(model_cylinderholes[i].normal[0], model_cylinderholes[i].normal[1], model_cylinderholes[i].normal[2]);
                    glVertex3f(model_cylinderholes[i].position[0], model_cylinderholes[i].position[1], model_cylinderholes[i].position[2]);
            } 
        glEnd();
    glPopMatrix();



    GLfloat ambient_coeffs[] = { 0, 0, 0, .3};
    GLfloat diffuse_coeffs[] = { 1, 1, 1, .3};
    GLfloat specular_coeffs[] = { .2, .2, .2, .3};
    
    GLfloat shininess = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    
    glPushMatrix();
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_cylinder; i++){
                    glNormal3f(model_cylinder[i].normal[0], model_cylinder[i].normal[1], model_cylinder[i].normal[2]);
                    glVertex3f(model_cylinder[i].position[0], model_cylinder[i].position[1], model_cylinder[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    
    glDisable(GL_BLEND);
}

//funkcija za iscrtavanje vicanog bloka
static void draw_block(void)
{
    
    GLfloat ambient_coeffs2[] = { 0, 0, 0, 1};
    GLfloat diffuse_coeffs2[] = { 0.7, 0.7, 0.7, 1};
    GLfloat specular_coeffs2[] = { .2, .2, .2, 1};
    
    GLfloat shininess2 = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
    
    double clip_plane[] = {0, 0, .9, .7};
    glClipPlane(GL_CLIP_PLANE0, clip_plane);
    glEnable(GL_CLIP_PLANE0);
        
    glPushMatrix();
        glTranslatef(-0.55, 0, 0);
        glRotatef(9*animation_parametar,0, 0, 1);
        glScalef(.25, .25, .6);
        glRotatef(90, 1, 0, 0);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_screw1; i++){
                    glNormal3f(model_screw1[i].normal[0], model_screw1[i].normal[1], model_screw1[i].normal[2]);
                    glVertex3f(model_screw1[i].position[0], model_screw1[i].position[1], model_screw1[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    

    glPushMatrix();
        glTranslatef(0.55, 0, 0);
        glRotatef(9*animation_parametar,0, 0, -1);
        glScalef(.25, .25, .6);
        glRotatef(90, 1, 0, 0);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_screw2; i++){
                    glNormal3f(model_screw2[i].normal[0], model_screw2[i].normal[1], model_screw2[i].normal[2]);
                    glVertex3f(model_screw2[i].position[0], model_screw2[i].position[1], model_screw2[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_CLIP_PLANE0);



    GLfloat ambient_coeffs[] = { .1, .1, .1, .3};
    GLfloat diffuse_coeffs[] = { .2, .3, .7, .3};
    GLfloat specular_coeffs[] = { .2, .2, .2, .3};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
    glPushMatrix();
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_block; i++){
                    glNormal3f(model_block[i].normal[0], model_block[i].normal[1], model_block[i].normal[2]);
                    glVertex3f(model_block[i].position[0], model_block[i].position[1], model_block[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    
    GLfloat ambient_coeffs3[] = { 0.1, 0.1, 0.1, .3};
    GLfloat diffuse_coeffs3[] = { 0.5, 0.5, 0.5, .3};
    GLfloat specular_coeffs3[] = { .2, .2, .2, .3};
    
    GLfloat shininess3 = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs3);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);
    
    double clip_plane2[] = {-1, 0, 0, -1};
    glClipPlane(GL_CLIP_PLANE0, clip_plane2);
    glEnable(GL_CLIP_PLANE0);
        
    glPushMatrix();
        glTranslatef(-1, 5.9, .85);
        glutSolidTorus(0.7, 1.5, 20, 20);
    glPopMatrix();
    
    glDisable(GL_CLIP_PLANE0);

    GLfloat ambient_coeffs4[] = { 0.1, 0.1, 0.1, .3};
    GLfloat diffuse_coeffs4[] = { 0.7, 0.7, 0, .3};
    GLfloat specular_coeffs4[] = { .2, .2, .2, .3};
    
    GLfloat shininess4 = 30;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs4);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs4);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs4);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess4);
    glPushMatrix();
        glTranslatef(.5, 7.4, 0.85);
        glRotatef(180, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_filter; i++){
                    glNormal3f(model_filter[i].normal[0], model_filter[i].normal[1], model_filter[i].normal[2]);
                    glVertex3f(model_filter[i].position[0], model_filter[i].position[1], model_filter[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

//funkcija za iscrtavanje cevki koje vode od rezervoara van kompresora
static void draw_pipeline1(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs[] = { .5, .1, .1, .1};
    GLfloat diffuse_coeffs[] = { .7, .2, .2, .1};
    GLfloat specular_coeffs[] = { .5, .2, .2, .1};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_pipeline1; i++){
                    glNormal3f(model_pipeline1[i].normal[0], model_pipeline1[i].normal[1], model_pipeline1[i].normal[2]);
                    glVertex3f(model_pipeline1[i].position[0], model_pipeline1[i].position[1], model_pipeline1[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

//funkcija za iscrtavanje cevi od filtera do bloka
static void draw_pipeline2(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs[] = { .1, .5, .1, .1};
    GLfloat diffuse_coeffs[] = { .2, .7, .2, .1};
    GLfloat specular_coeffs[] = { .2, .5, .2, .1};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_pipeline2; i++){
                    glNormal3f(model_pipeline2[i].normal[0], model_pipeline2[i].normal[1], model_pipeline2[i].normal[2]);
                    glVertex3f(model_pipeline2[i].position[0], model_pipeline2[i].position[1], model_pipeline2[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

//funkcija za iscrtavanje cevki od bloka do rezervoara
static void draw_pipeline3(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs[] = { .6, .3, .1, .1};
    GLfloat diffuse_coeffs[] = { .6, .3, .2, .1};
    GLfloat specular_coeffs[] = { .5, .2, .2, .1};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_pipeline3; i++){
                    glNormal3f(model_pipeline3[i].normal[0], model_pipeline3[i].normal[1], model_pipeline3[i].normal[2]);
                    glVertex3f(model_pipeline3[i].position[0], model_pipeline3[i].position[1], model_pipeline3[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}
//funkcija za iscrtavanje cevki od rezervoara do ventilatora pa do bloka
static void draw_pipeline5(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs[] = { .1, .5, .1, .1};
    GLfloat diffuse_coeffs[] = { .2, .7, .2, .1};
    GLfloat specular_coeffs[] = { .2, .5, .2, .1};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_pipeline5; i++){
                    glNormal3f(model_pipeline5[i].normal[0], model_pipeline5[i].normal[1], model_pipeline5[i].normal[2]);
                    glVertex3f(model_pipeline5[i].position[0], model_pipeline5[i].position[1], model_pipeline5[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

//funkcija iscrtavanje cevke od pipeline5 do bloka
static void draw_pipeline4(void){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    GLfloat ambient_coeffs[] = { .1, .5, .1, .1};
    GLfloat diffuse_coeffs[] = { .2, .7, .2, .1};
    GLfloat specular_coeffs[] = { .2, .5, .2, .1};
    
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.8, 0.8, 0.8);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_pipeline4; i++){
                    glNormal3f(model_pipeline4[i].normal[0], model_pipeline4[i].normal[1], model_pipeline4[i].normal[2]);
                    glVertex3f(model_pipeline4[i].position[0], model_pipeline4[i].position[1], model_pipeline4[i].position[2]);
            } 
        glEnd();
    glPopMatrix();

    GLfloat ambient_coeffs1[] = { .5, .5, .5, .1};
    GLfloat diffuse_coeffs1[] = { .7, .7, .7, .1};
    GLfloat specular_coeffs1[] = { .2, .2, .2, .1};
    
    GLfloat shininess1 = 10;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);

    glPushMatrix();
        glTranslatef(-1.3, 1.5, .1);
        glScalef(0.4, 0.4, 0.4);
        glBegin(GL_TRIANGLES);
            for(int i=0; i<model_size_cylinder; i++){
                    glNormal3f(model_cylinder[i].normal[0], model_cylinder[i].normal[1], model_cylinder[i].normal[2]);
                    glVertex3f(model_cylinder[i].position[0], model_cylinder[i].position[1], model_cylinder[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

//funkcija za ucitavanje modela iz .obj fajla. Prosledjuju joj se FILE* i id koj predstavlja koj model ucitavamo
Vertex* LoadObj(FILE * file, int id){
    //na pocetku pravimo prostor na memoriji za model
    int verts_count = 0;
    int verts_count_of = STEP;
    Vertex *verts = malloc(verts_count_of * sizeof(Vertex));
    
    //pozicija
    int num_of_pos = STEP;
    double **positions = malloc(num_of_pos * sizeof(double*));
    for(int i=0; i<num_of_pos; i++){
        positions[i] = malloc(3 * sizeof(double));
    }
    positions[0][0] = 0;
    positions[0][1] = 0;
    positions[0][2] = 0;

    //teksture
    int num_of_tc = STEP;
    double **texcoords = malloc(num_of_tc * sizeof(double*));
    for(int i=0; i<num_of_tc; i++){
        texcoords[i] = malloc(3*sizeof(double));
    }
    texcoords[0][0] = 0;
    texcoords[0][1] = 0;
    texcoords[0][2] = 0;

    //normale
    int num_of_n = STEP;
    double **normals = malloc(num_of_n * sizeof(double*));
    for(int i=0; i<num_of_n; i++){
        normals[i] = malloc(3*sizeof(double));
    }
    normals[0][0] = 0;
    normals[0][1] = 0;
    normals[0][2] = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int countPos = 1;
    int countTC = 1;
    int countN = 1;
    //citamo liniju po liniju i u odnosu na odgovarajuce slovo stavljamo koordinate u odgovarajucu matricu
    while((read = getline(&line, &len, file)) != -1){
        char type[5];
        sscanf(line, "%s ", type);
        if(strcmp(type, "v") == 0){
            //koordinate za poziciju
            double x = 0, y = 0, z = 0;
            sscanf(line, "v %lf %lf %lf",   &x, &y, &z);
            if(countPos >= num_of_pos){
                num_of_pos += STEP;
                positions = realloc(positions, num_of_pos * sizeof(double*));
                for(int i=countPos; i<num_of_pos; i++)
                    positions[i] = malloc(3 * sizeof(double));
            }
            positions[countPos][0] = x;
            positions[countPos][1] = y;
            positions[countPos][2] = z;
            countPos += 1;
        }
        
        if(strcmp(type, "vt") == 0){
            //koordinate za teksture
            double u = 0, v = 0, t = 0;
            sscanf(line, "vt %lf %lf %lf", &u, &v, &t);
            if(countTC >= num_of_tc){
                num_of_tc += STEP;
                texcoords = realloc(texcoords, num_of_tc * sizeof(double*));
                for(int i=countTC; i<num_of_tc; i++)
                    texcoords[i] = malloc(3*sizeof(double));
            }
            texcoords[countTC][0] = u;
            texcoords[countTC][1] = v;
            texcoords[countTC][2] = t;
            countTC += 1;
        }

        if(strcmp(type, "vn") == 0){
            //koordinate za normale
            double i = 0, j = 0, k = 0;
            sscanf(line, "vn %lf %lf %lf", &i, &j, &k);
            if(countN >= num_of_n){
                num_of_n += STEP;
                normals = realloc(normals, num_of_n * sizeof(double*));
                for(int i=countN; i<num_of_n; i++)
                    normals[i] = malloc(3*sizeof(double));
            }
            normals[countN][0] = i;
            normals[countN][1] = j;
            normals[countN][2] = k;
            countN += 1;
        }

        if(strcmp(type, "f") == 0){
            //koordinate koje nam govore kako su rasporedjene koordinate pozicija, tekstura i normala
            int ref_step = STEP;
            VertRef *refs = malloc(ref_step * sizeof(VertRef));
            char a[256];
            char *newF = strchr(line, 'f') + 2;
            
            int offset = 0;
            int ref_count = 0;
            while(sscanf(newF, " %s%n", a, &offset) == 1){
                char *vta = strchr(a, '/')+1;
                char *vna = strchr(vta, '/')+1;
                a[strlen(a) - strlen(vta)-1] = '\0';
                if(vta[0] == '/'){
                    vta = "0";
                }
                
                
                newF += offset;
                if(ref_count >= ref_step){
                    ref_step += STEP;
                    refs = realloc(refs, ref_step*sizeof(VertRef));
                }
                refs[ref_count].v = atoi(a);
                refs[ref_count].vn = atoi(vna);
                refs[ref_count].vt = atoi(vta);
                ref_count += 1;
            }
            //redjanju tacka tako da budu dobre za triangulaciju
            for(int i=1; i+1 < ref_count; i++){
                const VertRef *p[3] = {&refs[0], &refs[i], &refs[i+1]};
                double U[3] ={0};
                U[0] = positions[ p[1]->v ][0] - positions[ p[0]->v ][0];
                U[1] = positions[ p[1]->v ][1] - positions[ p[0]->v ][1];
                U[2] = positions[ p[1]->v ][2] - positions[ p[0]->v ][2];
                double V[3] ={0};
                V[0] = positions[ p[2]->v ][0] - positions[ p[0]->v ][0];
                V[1] = positions[ p[2]->v ][1] - positions[ p[0]->v ][1];
                V[2] = positions[ p[2]->v ][2] - positions[ p[0]->v ][2];
                double N[3] = {0};

                N[0] = U[1]*V[2] - U[2]*V[1];
                N[1] = U[2]*V[0] - U[0]*V[2];
                N[2] = U[0]*V[1] - U[1]*V[0];

                double w = sqrt(N[0]*N[0] + N[1]*N[1] + N[2]*N[2]);
                N[0] /= w;
                N[1] /= w;
                N[2] /= w;
                for(int j=0; j<3; j++){
                    Vertex vert;

                    vert.position[0] = positions[ p[j]->v ][0];
                    vert.position[1] = positions[ p[j]->v ][1];
                    vert.position[2] = positions[ p[j]->v ][2];

                    vert.texcoord[0] = texcoords[ p[j]->vt ][0];
                    vert.texcoord[1] = texcoords[ p[j]->vt ][1];
                    if(p[j]->vn != 0){
                        vert.normal[0] = normals[ p[j]->vn ][0];
                        vert.normal[1] = normals[ p[j]->vn ][1];
                        vert.normal[2] = normals[ p[j]->vn ][2];
                    } else {
                        vert.normal[0] = N[0];
                        vert.normal[1] = N[1];
                        vert.normal[2] = N[2];
                    }
                    if(verts_count >= verts_count_of){
                        verts_count_of += STEP;
                        verts = realloc(verts, verts_count_of*sizeof(Vertex));
                    }
                    verts[verts_count].position[0] = vert.position[0];
                    verts[verts_count].position[1] = vert.position[1];
                    verts[verts_count].position[2] = vert.position[2];

                    verts[verts_count].normal[0] = vert.normal[0];
                    verts[verts_count].normal[1] = vert.normal[1];
                    verts[verts_count].normal[2] = vert.normal[2];

                    verts[verts_count].texcoord[0] = vert.texcoord[0];
                    verts[verts_count].texcoord[1] = vert.texcoord[1];
                    verts_count += 1;
                }
            }
            free(refs);
        }

    }
    //pamcenje duzine niza u odnosu na odgovarajuci id
    if(id == PROPELLER_ID)
        model_size = verts_count;
    else if(id == CYLINDER_ID)
        model_size_cylinder = verts_count;
    else if(id == CYLINDERHOLES_ID)
        model_size_cylinderholes = verts_count;
    else if(id == SCREW1_ID)
        model_size_screw1 = verts_count;
    else if(id == SCREW2_ID)
        model_size_screw2 = verts_count;
    else if(id == BLOCK_ID)
        model_size_block = verts_count;
    else if(id == FILTER_ID)
        model_size_filter = verts_count;
    else if(id == PIPELINE1_ID)
        model_size_pipeline1 = verts_count;
    else if(id == PIPELINE2_ID)
        model_size_pipeline2 = verts_count;
    else if(id == PIPELINE3_ID)
        model_size_pipeline3 = verts_count;
    else if(id == PIPELINE4_ID)
        model_size_pipeline4 = verts_count;
    else if(id == PIPELINE5_ID)
        model_size_pipeline5 = verts_count;

    //oslobadjanje memorije
    for(int i=0; i<countPos; i++)
        free(positions[i]);
    free(positions);

    for(int i=0; i<countN; i++)
        free(normals[i]);
    free(normals);

    for(int i=0; i<countTC; i++)
        free(texcoords[i]);
    free(texcoords);

    return verts;
}
//funckija za koordinate misa
static void on_mouse(int button, int state, int x, int y)
{
    mouse_x = x;
    mouse_y = y;
}
//funkcija za pokret
static void on_motion(int x, int y)
{
    int delta_x, delta_y;

    
    delta_x = x - mouse_x;
    delta_y = y - mouse_y;

    
    mouse_x = x;
    mouse_y = y;

    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotatef(180 * (float) delta_x / window_width, 0, 1, 0);
        glRotatef(180 * (float) delta_y / window_height, 1, 0, 0);
        glMultMatrixf(matrix);

        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();

    
    glutPostRedisplay();
}