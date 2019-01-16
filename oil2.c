#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "oil2.h"

#define Pi 3.14159265359
#define TIMER_INTERVAL 20
#define TIMER_ID 0

extern void oil2_timer(int id)
{
    if(id == TIMER_ID)
    {   
        for(int i=0; i<n_oil2; i++){
            if(arr_oil2[i].in)
                move_oil2(i);//ukoliko se prikazuje pomeri lopticu
            else {
                arr_oil2[i].x += 0.02;//ukoliko se ne prikazuje priblizi je tacki odakle ce se prikazati
                if(arr_oil2[i].x >= 7)
                    arr_oil2[i].in = 1;//ukoliko je presla granicu za prikaz, prikazi je
            }
        }
        
    }


    glutPostRedisplay();

    if(oil2_ongoing)
        glutTimerFunc(TIMER_INTERVAL, oil2_timer, TIMER_ID);

}

//funkcija kretanja loptice
static void move_oil2(int i){
    //pocetna inicijalizacija
    float oil2X = arr_oil2[i].x;
    float oil2Y = arr_oil2[i].y;
    float oil2Z = arr_oil2[i].z;

    float angle1 = arr_oil2[i].angle1;
    float angle2 = arr_oil2[i].angle2; 
    float angle3 = arr_oil2[i].angle3;
    float angle4 = arr_oil2[i].angle4;
    float angle5 = arr_oil2[i].angle5;
    float angle6 = arr_oil2[i].angle6;
    float angle7 = arr_oil2[i].angle7; 
    float angle8 = arr_oil2[i].angle8;
    float angle9 = arr_oil2[i].angle9;
    float angle10 = arr_oil2[i].angle10;
    float angle11 = arr_oil2[i].angle11;
    float angle12 = arr_oil2[i].angle12;

    int indeks1 = arr_oil2[i].indeks1;
    int indeks2 = arr_oil2[i].indeks2;
    int indeks3 = arr_oil2[i].indeks3;
    int indeks4 = arr_oil2[i].indeks4;
    int indeks5 = arr_oil2[i].indeks5;
    int indeks6 = arr_oil2[i].indeks6;
    int indeks7 = arr_oil2[i].indeks7;
    int indeks8 = arr_oil2[i].indeks8;
    int indeks9 = arr_oil2[i].indeks9;
    int indeks10 = arr_oil2[i].indeks10;
    int indeks11 = arr_oil2[i].indeks11;
    int indeks12 = arr_oil2[i].indeks12;
    int indeks13 = arr_oil2[i].indeks13;
    int indeks14 = arr_oil2[i].indeks14;
    
    //pomeranja loptice
    if(oil2X < 7.5 && !indeks1){
            oil2X += 0.02;
        }else if(angle1 > 0){
            indeks1 = 1;
            oil2X = 0.45*cos(angle1) + 7.52;
            oil2Y = 0.45*sin(angle1) + -3.05;
            angle1 -= 0.04;
        } else if(oil2Y > -6.8 && !indeks2){
            oil2Y -= 0.02;
        } else if(angle2 > -Pi/2){
            indeks2 = 1;
            oil2X = 0.5*cos(angle2) + 7.47;
            oil2Y = 0.5*sin(angle2) + -6.805;
            angle2 -= 0.04;
        } else if(oil2X > -10.1 && !indeks3){
            oil2X -=0.02;
        } else if(angle3 > Pi){
            indeks3 = 1;
            oil2X = 0.45*cos(angle3) + -10.105;
            oil2Y = 0.45*sin(angle3) + -6.855;
            angle3 -= 0.04;
        } else if(oil2Y < 5.2 && !indeks4){
            oil2Y += 0.02;
        } else if(angle4 > 0){
            indeks4 = 1;
            oil2X = 0.55*cos(angle4) + -10.005;
            oil2Y = 0.55*sin(angle4) + 5.2001;
            angle4 -= 0.04;
        } else if(oil2Y > 4.7 && !indeks5){
            oil2Y -= 0.02;
        } else if(angle5 < 2*Pi){
            indeks5 = 1;
            oil2X = 0.55*cos(angle5) + -8.905;
            oil2Y = 0.55*sin(angle5) + 4.69;
            angle5 += 0.04;
        } else if(oil2Y < 5.3 && !indeks6){
            oil2Y += 0.02;

        } else if(angle6 > 0){
            indeks6 = 1;
            oil2X = 0.5*cos(angle6) + -7.855;
            oil2Y = 0.5*sin(angle6) + 5.32;
            angle6 -= 0.04;
            
        } else if(oil2Y > 4.2 && !indeks7){
            oil2Y -= 0.02;
        } else if(angle7 > -Pi/2){
            indeks7 = 1;
            oil2X = 0.5*cos(angle7) + -7.855;
            oil2Y = 0.5*sin(angle7) + 4.2;
            angle7 -= 0.04;
        } else if(oil2X > -9.5 && !indeks8){
            oil2X -= 0.02;
        } else if(angle8 < Pi){
            indeks8 = 1;
            oil2X = 0.5*cos(angle8) + -9.51;
            oil2Y = 0.5*sin(angle8) + 3.2;
            angle8 += 0.04;
        } else if(oil2Y > -5.4 && !indeks9){
            oil2Y -= 0.02;
        }
        else if(oil2X < -6 && !indeks9){
            oil2X += 0.02;
        } else if(oil2Y < -4.4 && !indeks10){
            indeks9 = 1;
            oil2Y += 0.02;
            oil2X += 0.0105;
        } else if(angle9 > Pi/2){
            indeks10 = 1;
            oil2X = 0.25*cos(angle9) + -5.204429;
            oil2Y = 0.25*sin(angle9) + -4.394595;
            angle9 -= 0.04;
            
        } else if(angle10 < 2*Pi){
            oil2X = 0.2*cos(angle10) - 5.207129;
            oil2Y = 0.2*sin(angle10) - 3.944609;
            angle10 += 0.04;
        } else if(oil2Y < -3.3 && !indeks11){
            oil2Y += 0.02;
        } else if(oil2X < -4.75 && !indeks12){
            indeks11 = 1;
            oil2X += 0.02;
            oil2Z -= 0.005;
        } else if(oil2Y > -6.1 && !indeks13){
            
            indeks12 = 1;
            oil2Y -= 0.02;
        } else if(angle11 < 3*Pi/2){
            indeks13 = 1;
            oil2X = 0.42*cos(angle11) - 4.327141;
            oil2Y = 0.42*sin(angle11) - 6.086767;
            angle11 += 0.04;
        } else if(oil2X < -2.7 && !indeks14){
            oil2X += 0.02;
        } else if(angle12 < 2*Pi){
            indeks14 = 1;
            oil2X = 0.41*cos(angle12) - 2.691678;
            oil2Y = 0.41*sin(angle12) - 6.096742;
            angle12 += 0.04;
        } else if(oil2Y < -5.5){
            oil2Y += 0.02;
        } else {
            //na kraju vracamo lopticu na pocetak
            angle1 = Pi/2;
            angle2 = 0;
            angle3 = 3*Pi/2;
            angle4 = Pi;
            angle5 = Pi;
            angle6 = Pi;
            angle7 = 0;
            angle8 = Pi/2;
            angle9 = Pi;
            angle10 = 3*Pi/2;
            angle11 = Pi;
            angle12 = 3*Pi/2;

            indeks1 = 0;
            indeks2 = 0;
            indeks3 = 0;
            indeks4 = 0;
            indeks5 = 0;
            indeks6 = 0;
            indeks7 = 0;
            indeks8 = 0;
            indeks9 = 0;
            indeks10 = 0;
            indeks11 = 0;
            indeks12 = 0;
            indeks13 = 0;
            indeks14 = 0;            

            oil2X = 7;
            oil2Y = -2.6;
            oil2Z = 0.1;
        }
//pamcenej promenjenih koordinata
    arr_oil2[i].x = oil2X;
    arr_oil2[i].y = oil2Y;
    arr_oil2[i].z = oil2Z;

    arr_oil2[i].angle1 = angle1;
    arr_oil2[i].angle2 = angle2; 
    arr_oil2[i].angle3 = angle3;
    arr_oil2[i].angle4 = angle4;
    arr_oil2[i].angle5 = angle5;
    arr_oil2[i].angle6 = angle6;
    arr_oil2[i].angle7 = angle7; 
    arr_oil2[i].angle8 = angle8;
    arr_oil2[i].angle9 = angle9;
    arr_oil2[i].angle10 = angle10;
    arr_oil2[i].angle11 = angle11;
    arr_oil2[i].angle12 = angle12;

    arr_oil2[i].indeks1 = indeks1;
    arr_oil2[i].indeks2 = indeks2;
    arr_oil2[i].indeks3 = indeks3;
    arr_oil2[i].indeks4 = indeks4;
    arr_oil2[i].indeks5 = indeks5;
    arr_oil2[i].indeks6 = indeks6;
    arr_oil2[i].indeks7 = indeks7;
    arr_oil2[i].indeks8 = indeks8;
    arr_oil2[i].indeks9 = indeks9;
    arr_oil2[i].indeks10 = indeks10;
    arr_oil2[i].indeks11 = indeks11;
    arr_oil2[i].indeks12 = indeks12;
    arr_oil2[i].indeks13 = indeks13;
    arr_oil2[i].indeks14 = indeks14;
}