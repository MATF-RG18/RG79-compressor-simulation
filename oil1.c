#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "oil1.h"

#define Pi 3.14159265359
#define TIMER_INTERVAL 20
#define TIMER_ID 0

extern void oil1_timer(int id)
{
    if(id == TIMER_ID)
    {   
        for(int i=0; i<n; i++){
            if(arr[i].in)
                move_ball(i);
            else{
                arr[i].y += 0.02;
                if(arr[i].y >= -0.7)
                    arr[i].in = 1;
            }
        }
    }


    glutPostRedisplay();

    if(oil1_ongoing)
        glutTimerFunc(TIMER_INTERVAL, oil1_timer, TIMER_ID);

}

static void move_ball(int i){
    float oil1X = arr[i].x;
    float oil1Y = arr[i].y;
    float oil1Z = arr[i].z;

    float angle1 = arr[i].angle1;
    float angle2 = arr[i].angle2;
    float angle3 = arr[i].angle3;
    float angle4 = arr[i].angle4;
    int indeks1  = arr[i].indeks1;
    int indeks2  = arr[i].indeks2;
    int indeks3  = arr[i].indeks3;
    int indeks4  = arr[i].indeks4;

    if(oil1Y <= 0 && !indeks1){
            oil1Y += 0.02;
        } else if(angle1 < Pi/2){
            indeks1 = 1;
            oil1X = 0.45*cos(angle1) + 5.3;
            oil1Y = 0.45*sin(angle1) + 0.02;
            angle1 += 0.04;
        } else if(oil1X  > 4.55 && !indeks2){
            oil1X -= 0.02;
        } else if(angle2 < Pi){
            indeks2 = 1;
            oil1X = 0.45*cos(angle2) + 4.545;
            oil1Y = 0.45*sin(angle2) + 0.017;
            angle2 += 0.04;
        } else if(oil1Y > -1 && !indeks3){
            oil1Y -= 0.02;
        } else if(angle3 > -Pi/2){
            indeks3 = 1;
            oil1X = 0.5*cos(angle3) + 3.59;
            oil1Y = 0.5*sin(angle3) + -1.018;
            angle3 -= 0.04;
        } else if(oil1X > -1.65 && !indeks4){
            oil1X -= 0.02;
            oil1Y -= 0.0001;
        } else if(angle4 < Pi){
            indeks4 = 1;
            oil1X = 0.5*cos(angle4) - 1.665;
            oil1Y = 0.5*sin(angle4) - 2.044;
            angle4 += 0.04;
        } else if(oil1Y > -4.4){
            oil1Y -= 0.02;
        } else {
            angle1 = 0;
            angle2 = Pi/2;
            angle3 = 0;
            angle4 = Pi/2;
            indeks1 = 0;
            indeks2 = 0;
            indeks3 = 0;
            indeks4 = 0;

            oil1X = 5.75;
            oil1Y = -0.7;
            oil1Z = -0.2;
            arr[i].in = 0;
        }

        arr[i].x = oil1X;
        arr[i].y = oil1Y;
        arr[i].z = oil1Z;
            printf("%f %f %f\n", arr[i].x, arr[i].y, arr[i].z);

        arr[i].angle1 = angle1;
        arr[i].angle2 = angle2;
        arr[i].angle3 = angle3;
        arr[i].angle4 = angle4;
        arr[i].indeks1 = indeks1;
        arr[i].indeks2 = indeks2;
        arr[i].indeks3 = indeks3;
        arr[i].indeks4 = indeks4;
}