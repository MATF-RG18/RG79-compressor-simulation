#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "air.h"

#define Pi 3.14159265359
#define TIMER_INTERVAL 20
#define TIMER_ID 0

extern void air_timer(int id)
{
    if(id == TIMER_ID)
    {   
        
        for(int i=0; i<n_air; i++){
            if(arr_air[i].in)
                move_air(i);
            else {
                arr_air[i].y -= 0.02;
                if(arr_air[i].y <= 4.5)
                    arr_air[i].in = 1;
            }
        }
        
    }


    glutPostRedisplay();

    if(air_ongoing)
        glutTimerFunc(TIMER_INTERVAL, air_timer, TIMER_ID);

}

static void move_air(int i){
    float airX = arr_air[i].x;
    float airY = arr_air[i].y;
    float airZ = arr_air[i].z;
    float angle_air1 = arr_air[i].angle_air1;
    float angle_air2 = arr_air[i].angle_air2;
    float angle_air3 = arr_air[i].angle_air3;
    float angle_air4 = arr_air[i].angle_air4;
    float angle_air5 = arr_air[i].angle_air5;
    float angle_air6 = arr_air[i].angle_air6;
    float angle_air7 = arr_air[i].angle_air7;
    float angle_air8 = arr_air[i].angle_air8;
    float angle_air9 = arr_air[i].angle_air9;
    float angle_air10 = arr_air[i].angle_air10;
    float angle_air11 = arr_air[i].angle_air11;
    float angle_air12 = arr_air[i].angle_air12;
    int indeks1 = arr_air[i].indeks1;
    int indeks2 = arr_air[i].indeks2;
    int indeks3 = arr_air[i].indeks3;
    int indeks4 = arr_air[i].indeks4;
    int indeks5 = arr_air[i].indeks5;
    int indeks6 = arr_air[i].indeks6;
    int indeks7 = arr_air[i].indeks7;
    int indeks8 = arr_air[i].indeks8;
    int indeks9 = arr_air[i].indeks9;
    int indeks10 = arr_air[i].indeks10;
    int indeks11 = arr_air[i].indeks11;

    if(airY >= 2.5 && !indeks5){
            airY -= 0.02;
        }else if(airX >= -4 && !indeks5){
            airX -=0.02;
        }else if(angle_air8 <= 3*Pi/2){
            indeks5 = 1;
            airX = 1.5*cos(angle_air8) + -4.02;
            airY = 1.5*sin(angle_air8) + 0.980002;
            angle_air8 += 0.02;
        } else if(airX <= -3 && !indeks6){
            airX += 0.02;
        } else if(airY >= -4.1 && !indeks6){
            airY -= 0.02;
        } else if(angle_air9 >= 0.25){
            indeks6 = 1;
            airX = 1.2*cos(angle_air9) + -2.98;
            airY = sin(angle_air9) + -5.12;
            angle_air9 -= 0.02;
            airZ -= 0.014;
        } else if(airX <= 3.2 && !indeks8){
            airX += 0.05;
        } else if(angle_air10 <= 2*Pi){
            indeks8 = 1;
            airX = 0.45*cos(angle_air10) + 3.202;
            airY = 0.45*sin(angle_air10) + -4.422;
            angle_air10 += 0.1;

        } else if(airY <= -3.5 && !indeks9){
            airY += 0.05;

        } else if(angle_air11 >= Pi/2){
            indeks9 = 1;
            airX = 0.5*cos(angle_air11) + 4.152;
            airY = 0.5*sin(angle_air11) + -3.486;
            angle_air11 -= 0.1;
        } else if(airX <= 4.5 && !indeks10){
            airX += 0.05;

        } else if(angle_air12 <= 2*Pi){
            indeks10 = 1;
            airX = 1.63*cos(angle_air12) + 4.5066;
            airY = 1.5*sin(angle_air12) + -1.486;
            angle_air12 += 0.04;
            airZ += 0.0073;
        } else if(airY <= 1.3 && !indeks1){
            airY += 0.05;

        }else if(airX >= 4.6 && !indeks1){
            airX -= 0.05;
        }else if(angle_air1 >= Pi){
            airX = cos(angle_air1) + 4.6;
            airY = sin(angle_air1) + 2.3;
            angle_air1 -= 0.05;
        } else if(angle_air2 <= Pi/2){
            airX = 0.35 * cos(angle_air2) + 3.2;
            airY = 0.35 * sin(angle_air2) + 2.3;
            angle_air2 += 0.07;
        } else if(airX >= 1.5 && !indeks1){
            airX -= 0.05;
        }
        else if(angle_air3 >= Pi){
            airX = 0.6*cos(angle_air3) + 1.48;
            airY = 0.6*sin(angle_air3) + 3.3;
            angle_air3 -= 0.07;
            
        } 
        else if(airY <= 5.6 && !indeks1){
            airY += 0.05;
        }else if(angle_air4 >= 0){
            indeks1 = 1;
            airX = 0.55*cos(angle_air4) + 1.43;
            airY = 0.55*sin(angle_air4) + 5.61;
            angle_air4 -= 0.07;
        } else if(airY >= 4.7 && !indeks2){
            airY -= 0.05;

        } else if(angle_air5 <= 2*Pi){
            indeks2 = 1;
            airX = 0.55*cos(angle_air5) + 2.53;
            airY = 0.55*sin(angle_air5) + 4.68;
            angle_air5 += 0.07;
            
        }else if(airY <= 5.7 && !indeks3){
            airY += 0.05;
        } else if(angle_air6 >= 0){
            indeks3 = 1;
            airX = 0.55*cos(angle_air6) + 3.63;
            airY = 0.55*sin(angle_air6) + 5.708;
            angle_air6 -= 0.07;            
        } else if(airY >= 4.7 && !indeks4){
            airY -= 0.05;

        }else if(angle_air7 <= 3*Pi/2){
            indeks4 = 1;
            airX = 0.55*cos(angle_air7) + 4.73;
            airY = 0.55*sin(angle_air7) + 4.69;
            angle_air7 += 0.07;
            
        } else if(airX <= 9){
            airX += 0.05;
        }
        else {
            airX = -2;
            airY = 4.5;
            airZ = 0.75;
            angle_air1 = 3*Pi/2;
            angle_air2 = 0;
            angle_air3 = 3*Pi/2;
            angle_air4 = Pi;
            angle_air5 = Pi;
            angle_air6 = Pi;
            angle_air7 = Pi;
            angle_air8 = Pi/2;
            angle_air9 = Pi/2;
            angle_air10 = 3*Pi/2;
            angle_air11 = Pi;
            angle_air12 = 3*Pi/2;
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
            arr_air[i].in = 0;
        }



    arr_air[i].x = airX;
    arr_air[i].y = airY;
    arr_air[i].z = airZ;
    arr_air[i].angle_air1 = angle_air1 ;
    arr_air[i].angle_air2 = angle_air2 ;
    arr_air[i].angle_air3 = angle_air3 ;
    arr_air[i].angle_air4 = angle_air4 ;
    arr_air[i].angle_air5 = angle_air5 ;
    arr_air[i].angle_air6 = angle_air6 ;
    arr_air[i].angle_air7 = angle_air7 ;
    arr_air[i].angle_air8 = angle_air8 ;
    arr_air[i].angle_air9 = angle_air9 ;
    arr_air[i].angle_air10 = angle_air10;
    arr_air[i].angle_air11 = angle_air11;
    arr_air[i].angle_air12 = angle_air12;
    arr_air[i].indeks1 = indeks1; 
    arr_air[i].indeks2 = indeks2; 
    arr_air[i].indeks3 = indeks3; 
    arr_air[i].indeks4 = indeks4; 
    arr_air[i].indeks5 = indeks5; 
    arr_air[i].indeks6 = indeks6; 
    arr_air[i].indeks7 = indeks7; 
    arr_air[i].indeks8 = indeks8; 
    arr_air[i].indeks9 = indeks9; 
    arr_air[i].indeks10 = indeks10;
    arr_air[i].indeks11 = indeks11;
}