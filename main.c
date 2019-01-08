#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define STEP 100
#define TIMER_INTERVAL 20
#define TIMER_ID 0

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

typedef struct Vertex
{
    double position[3];
    double texcoord[2];
    double normal[3];
} Vertex;

typedef struct VertRef
{
    int v, vt, vn;
} VertRef;


static int mouse_x, mouse_y;
static int window_width, window_height;
static float matrix[16];

static float animation_parametar = 0;
static int animation_ongoing = 0;

static float scrollX = 0;
static float scrollY = 0;
static float scrollZ = 0;

//models
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

static void draw_axes(void);
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

    

    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);
    
    // glEnable(GL_BLEND);
    
    glClearColor(0.1, 0.1, 0.1, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

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
            if(!animation_ongoing){
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        case 'e':
        case 'E':
            animation_ongoing = 0;
            break;
    }
}

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
        0+scrollX, 1+scrollY, 25+scrollZ,
        0, 0, 0,
        0, 1, 0
    );
    glMultMatrixf(matrix);
    // glPushMatrix();
    // {
    //     draw_axes();
    // }
    // glPopMatrix();

     glPushMatrix();
    {
        glTranslatef(-3, 5.5, 0);
        draw_propeller();
    }
    glPopMatrix();

    glPushMatrix();
    {
        GLfloat diffuse1[] = {0,0,1,1};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
        glTranslatef(6.15, 1, 0.1);
        glutSolidSphere(0.05, 20, 20);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(3.3, -4, 0);
        draw_pipeline5();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-3.5, -5, 0);
        draw_pipeline4();
    }
    glPopMatrix();

     glPushMatrix();
    {
        glTranslatef(0, -3.5, 0);
        draw_pipeline3();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0, -1, 0);
        draw_pipeline2();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(3.9, 4, 0);
        draw_pipeline1();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(6, -2, 0);
        glScalef(1.5, 1.5, 1.5);
        draw_pressure_chamber();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-3, -5, 0);
        draw_block();
    }
    glPopMatrix();

    
    

    glutSwapBuffers();
}


static void draw_axes(void)
{
    glBegin(GL_LINES);
        GLfloat ambient1[] = {1,0,0,0};
        GLfloat diffuse1[] = {1,0,0,0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_BACK, GL_AMBIENT, ambient1);
        glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse1);
        glVertex3f(0, 0, -100);
        glVertex3f(0, 0, 100);

        GLfloat ambient2[] = {0,1,0,0};
        GLfloat diffuse2[] = {0,1,0,0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_BACK, GL_AMBIENT, ambient2);
        glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse2);
        glVertex3f(0, -100, 0);
        glVertex3f(0, 100, 0);

        GLfloat ambient3[] = {0,0,1,0};
        GLfloat diffuse3[] = {0,0,1,0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse3);
        glVertex3f(-100, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();
}

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
    glBegin(GL_TRIANGLES);
        for(int i=0; i<model_size; i++){
                glNormal3f(model[i].normal[0], model[i].normal[1], model[i].normal[2]);
                glVertex3f(model[i].position[0], model[i].position[1], model[i].position[2]);
        } 
    glEnd();
}

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
    
    // double clip_plane1[] = {1, , 0, 1};
    // glClipPlane(GL_CLIP_PLANE0, clip_plane1);
    // glEnable(GL_CLIP_PLANE0);
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
    // glDisable(GL_CLIP_PLANE0);
    //
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
    //
    glDisable(GL_BLEND);
}

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


static void draw_pipeline3(void){
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
            for(int i=0; i<model_size_pipeline3; i++){
                    glNormal3f(model_pipeline3[i].normal[0], model_pipeline3[i].normal[1], model_pipeline3[i].normal[2]);
                    glVertex3f(model_pipeline3[i].position[0], model_pipeline3[i].position[1], model_pipeline3[i].position[2]);
            } 
        glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

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


Vertex* LoadObj(FILE * file, int id){
    int verts_count = 0;
    int verts_count_of = STEP;
    Vertex *verts = malloc(verts_count_of * sizeof(Vertex));
    int num_of_pos = STEP;
    double **positions = malloc(num_of_pos * sizeof(double*));
    for(int i=0; i<num_of_pos; i++){
        positions[i] = malloc(3 * sizeof(double));
    }
    positions[0][0] = 0;
    positions[0][1] = 0;
    positions[0][2] = 0;

    int num_of_tc = STEP;
    double **texcoords = malloc(num_of_tc * sizeof(double*));
    for(int i=0; i<num_of_tc; i++){
        texcoords[i] = malloc(3*sizeof(double));
    }
    texcoords[0][0] = 0;
    texcoords[0][1] = 0;
    texcoords[0][2] = 0;

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
    while((read = getline(&line, &len, file)) != -1){
        char type[5];
        sscanf(line, "%s ", type);
        if(strcmp(type, "v") == 0){
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

static void on_mouse(int button, int state, int x, int y)
{
    mouse_x = x;
    mouse_y = y;

//     if ((button == 3) || (button == 4)) // It's a wheel event
//    {
//        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
//        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
//        scrollX -= 0.5;
//        scrollY -= 0.5;
//        scrollZ -= 0.5;
//        glutPostRedisplay();
//        printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
//    }else{  // normal button event
//         scrollX += 0.5;
//         scrollY += 0.5;
//         scrollZ += 0.5;
//         glutPostRedisplay();
//        printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
//    }
}

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