/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Date: 01/05/2015
 */

/* INCLUDE */

#include <stdio.h>
#include <stdlib.h>

/* TYPEDEF */

/* HEADERS */

#include "polygon.h"

/* PROTOTYPES */

/* MAIN */

int main(int argc, char *argv[]){
    double x,y;
    Point tmpPoint;
    int bool1, choice;
    polygonList polygon1, polygon2;

    do{
        printf("\nWELCOME TO THIS 2D-POLYGON MANAGEMENT PROGRAM\n\n");

        printf("\n--- Creation of a first polygon ---\n");
        polygon1 = createPolygon();
        do{
            printf("\nWhat do you want to do?");
            printf("\n   1) Create a new point");
            printf("\n   2) Remove a point");
            printf("\n   0) End the creation of the first polygon");
            do{
                printf("\n   Choice: ");
                scanf("%d",&choice);
            }while(choice != 1 && choice != 2 && choice != 0);

            if(choice == 1){
                printf("\nCoordinates of the new point:");
                printf("\n   x=");
                scanf("%lf",&x);
                printf("   y=");
                scanf("%lf",&y);
                tmpPoint=createPoint(x,y);
                printf("\nPoint created: ");
                printPoint(tmpPoint);
                polygon1=addPoint(tmpPoint,polygon1);
                printf("\n\nPolygon 1: ");
                printPolygon(polygon1);
            }

            if(choice == 2){
                printf("\nPolygon 1: ");
                printPolygon(polygon1);
                printf("\n\nNumber of the point you want to remove: ");
                scanf("%d",&choice);
                polygon1=removePoint(polygon1,choice);
                printf("\nPolygon 1: ");
                printPolygon(polygon1);
            }
        }while(choice != 0);

        printf("\n--- Creation of a second polygon ---\n");
        polygon2 = createPolygon();
        do{
            printf("\nWhat do you want to do?");
            printf("\n   1) Create a new point");
            printf("\n   2) Remove a point");
            printf("\n   0) End the creation of the second polygon");
            do{
                printf("\n   Choice: ");
                scanf("%d",&choice);
            }while(choice != 1 && choice != 2 && choice != 0);

            if(choice == 1){
                printf("\nCoordinates of the new point:");
                printf("\n   x=");
                scanf("%lf",&x);
                printf("   y=");
                scanf("%lf",&y);
                tmpPoint=createPoint(x,y);
                printf("\nPoint created: ");
                printPoint(tmpPoint);
                polygon2=addPoint(tmpPoint,polygon2);
                printf("\n\nPolygon 2: ");
                printPolygon(polygon2);
            }

            if(choice == 2){
                printf("\nPolygon 2: ");
                printPolygon(polygon2);
                printf("\n\nNumber of the point you want to remove: ");
                scanf("%d",&choice);
                polygon2=removePoint(polygon2,choice);
                printf("\nPolygon 2: ");
                printPolygon(polygon2);
            }
        }while(choice != 0);

        printf("\n\nPolygon 1: ");
        printPolygon(polygon1);
        printf("\nPolygon 2: ");
        printPolygon(polygon2);

        do{
            printf("\n\nDo you wanna restart? (yes=1;no=0) ");
            scanf("%d", &bool1);
        }while(bool1 != 1 && bool1 != 0);
    }while(bool1);

    printf("\n\nTHANKS FOR USING THIS LITTLE PROGRAM!");

    return EXIT_SUCCESS;
}

