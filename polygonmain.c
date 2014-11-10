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
    int bool1, choice, choice2, moveon;
    polygonList polygon1, polygon2;

    do{
        printf("\n---------------------------------------------------------");
        printf("\n|     WELCOME TO THIS 2D-POLYGON MANAGEMENT PROGRAM     |");
        printf("\n---------------------------------------------------------");

        printf("\n\n---------------------------------");
        printf("\n| Creation of the first polygon |");
        printf("\n---------------------------------");

        moveon = 0;

        polygon1 = createPolygon();
        do{
            printf("\n\n| What do you want to do?");
            printf("\n|------------------------");
            printf("\n| 1) Create a new point");
            printf("\n| 2) Remove a point");
            printf("\n| 3) Empty the polygon");
            printf("\n| 0) End the creation of the first polygon");
            printf("\n| Choice: ");
            scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                    printf("\n\t| Creating a new point");
                    printf("\n\t|---------------------");
                    printf("\n\t| Coordinates of the new point:");
                    printf("\n\t|   x=");
                    scanf("%lf",&x);
                    printf("\t|   y=");
                    scanf("%lf",&y);
                    tmpPoint=createPoint(x,y);
                    printf("\t|\n\t| Point created: ");
                    printPoint(tmpPoint);
                    polygon1=addPoint(tmpPoint,polygon1);
                    printf("\n\t|");
                    break;
                case 2:
                    printf("\n\t| Removing a point");
                    printf("\n\t|-----------------");
                    printf("\n\t| Polygon 1: ");
                    printPolygon(polygon1);
                    printf("\n\t|\n\t| Number of the point you want to remove: ");
                    scanf("%d",&choice2);
                    polygon1=removePoint(polygon1,choice2);
                    printf("\t|");
                    break;
                case 3:
                    printf("\n\t| Emptying the polygon");
                    printf("\n\t|---------------------");
                    polygon1 = emptyPolygon(polygon1);
                    if(polygon1.size == 0)
                    {
                        printf("\n\t| The polygon is now empty");
                    }
                    else
                    {
                        printf("\n\t| An error occured while emptying the polygon");
                    }
                    printf("\n\t|");
                    break;
                case 0:
                    moveon = 1;
                    break;
                default:
                    printf("\n| Wrong input!");
                    break;
            }

            printf("\n\t| Polygon 1: ");
            printPolygon(polygon1);

        }while(moveon == 0);

	    moveon = 0;

        printf("\n\n----------------------------------");
        printf("\n| Creation of the second polygon |");
        printf("\n----------------------------------");

        polygon2 = createPolygon();
        do{
            printf("\n\n| What do you want to do?");
            printf("\n|------------------------");
            printf("\n| 1) Create a new point");
            printf("\n| 2) Remove a point");
            printf("\n| 3) Empty the polygon");
            printf("\n| 0) End the creation of the second polygon");
            do{
                printf("\n| Choice: ");
                scanf("%d",&choice);
            }while(choice != 1 && choice != 2 && choice != 3 && choice != 0);

            if(choice == 1){
                printf("\n\t| Creating a new point");
                printf("\n\t|---------------------");
                printf("\n\t| Coordinates of the new point:");
                printf("\n\t|   x=");
                scanf("%lf",&x);
                printf("\t|   y=");
                scanf("%lf",&y);
                tmpPoint=createPoint(x,y);
                printf("\t|\n\t| Point created: ");
                printPoint(tmpPoint);
                polygon2=addPoint(tmpPoint,polygon2);
                printf("\n\t|");
            }

            if(choice == 2){
                printf("\n\t| Removing a point");
                printf("\n\t|-----------------");
                printf("\n\t| Polygon 2: ");
                printPolygon(polygon2);
                printf("\n\t|\n\t| Number of the point you want to remove: ");
                scanf("%d",&choice2);
                polygon2=removePoint(polygon2,choice2);
                printf("\t|");
            }

            if(choice == 3){
                printf("\n\t| Emptying the polygon");
                printf("\n\t|---------------------");
                polygon2 = emptyPolygon(polygon2);
                if(polygon2.size == 0)
                {
                    printf("\n\t| The polygon is now empty");
                }
                else
                {
                    printf("\n\t| An error occured while emptying the polygon");
                }
                printf("\n\t|");
            }

            printf("\n\t| Polygon 2: ");
            printPolygon(polygon2);

        }while(choice != 0);

        printf("\n\n| Polygon 1: ");
        printPolygon(polygon1);
        printf("\n| Polygon 2: ");
        printPolygon(polygon2);

        polygon1 = emptyPolygon(polygon1);
        polygon2 = emptyPolygon(polygon2);

        do{
            printf("\n|\n| Do you wanna restart? (yes=1;no=0) ");
            scanf("%d", &bool1);
        }while(bool1 != 1 && bool1 != 0);
    }while(bool1);

    printf("\n\n-------------------------------------------------");
    printf("\n|     THANKS FOR USING THIS LITTLE PROGRAM!     |");
    printf("\n-------------------------------------------------\n\n");

    return EXIT_SUCCESS;
}

