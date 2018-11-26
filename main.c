#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

static float alfa, beta;
static float delta_alfa, delta_beta;

static void on_keyboard(unsigned char key, int x , int y);
static void on_display(void);
static void on_reshape(int width, int height);

int main(int argc, char *argv[])
{
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    GLfloat ambient_coeffs[] = { 0, 0, 0, 1 };
    GLfloat diffuse_coeffs[] = { .7, .7, .7, 1 };
    GLfloat specular_coeffs[] = { .2, .2, .2, 1 };
    
    GLfloat shininess = 30;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(100, 100);

    // printf("%s", argv);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);

    alfa = M_PI / 6;
    beta = M_PI / 3 + 0.1;
    delta_alfa = M_PI / 90;
    delta_beta = M_PI / 90;

    glClearColor(.66, .66, .66, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    glLineWidth(1);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x , int y) 
{
    switch(key){
        case 27:
            exit(0);
            break;
        case 'a':
            beta += delta_beta;
            // if(beta > (M_PI / 2 - M_PI / 180)){
            //     beta = (M_PI / 2 - M_PI / 180);
            // }
            glutPostRedisplay();;
            break;
        case 'd':
            beta -= delta_beta;
            // if(beta < -(M_PI / 2 - M_PI / 180)){
            //     beta = -(M_PI / 2 - M_PI / 180);
            // }
            glutPostRedisplay();
            break;
        case 'w':
            alfa -= delta_alfa;
            if(alfa > 2 * M_PI) {
                alfa -= 2 * M_PI;
            } else if(alfa < 0) {
                alfa += 2 * M_PI;
            }
            glutPostRedisplay();
            break;
        case 's':
            alfa += delta_alfa;
            if(alfa > 2 * M_PI) {
                alfa -= 2 * M_PI;
            } else if(alfa < 0) {
                alfa += 2 * M_PI;
            }
            glutPostRedisplay();
            break;
        case 'R':
        case 'r':
            alfa = M_PI / 6;
            beta = M_PI / 3 + 0.1;
            glutPostRedisplay();
            break;
    }
}

static void on_reshape(int width, int height) 
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        45,
        width/(float)height,
        1,
        25
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
        5 * cos(beta) * cos(alfa),  
        5 * cos(beta) * sin(alfa), 
        5 * sin(beta),
        0, 0, 0,
        0, 1, 0
    );

    glPushMatrix();

    glColor3f(0, 0, 0);
    // glTranslatef(1, 1, 0);
    glScalef(1, 1, 2);
    glutSolidCube(1);

    glPopMatrix();

    glutSwapBuffers();
}
