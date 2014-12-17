/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 * maxime.brodat@fouss.fr
 *
 * Stéphane Perrez
 * stéphane.perrez@utbm.fr
 *
 * Deadline of the project: 01/05/2015
 */

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>
#include <boolean.h>
#include <polygon.h>
#include <useful_fcts.h>


/* ----- MAIN ----- */

int main(int argc, char *argv[]){

    float scale;
    double x,y;
    Point tmpPoint, tmpPoint2;
    char restart;
    char* toStringSample;
    Boolean moveon;
    int choice, choice2;
    Polygon polygon1, polygon2, tmpPolygon;



        printf("\n---------------------------------------------------------");
        printf("\n|     WELCOME TO THIS 2D-POLYGON MANAGEMENT PROGRAM     |");
        printf("\n---------------------------------------------------------");


        do{

            printf("\n\n---------------------------------");
            printf("\n| Creation of the first polygon |");
            printf("\n---------------------------------");

            moveon = FALSE;

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
            emptBuff();

            switch(choice){
                case 1:
                    printf("\n\t| Creating a new point");
                    printf("\n\t|---------------------");
                    printf("\n\t| Coordinates of the new point:");
                    printf("\n\t|   x=");
                    scanf("%lf",&x);
                    emptBuff();
                    printf("\t|   y=");
                    scanf("%lf",&y);
                    emptBuff();
                    tmpPoint=createPoint(x,y);
                    printf("\t|\n\t| Point created: ");
                    printPoint(tmpPoint);
                    polygon1=addPoint(polygon1, tmpPoint);
                    printf("\n\t|\n\t| Polygon 1: ");
                    printPolygon(polygon1);
                    break;

                case 2:
                    printf("\n\t| Removing a point");
                    printf("\n\t|-----------------");
                    printf("\n\t| Polygon 1: ");
                    printPolygon(polygon1);
                    printf("\n\t|\n\t| Number of the point you want to remove: ");
                    scanf("%d",&choice2);
                    emptBuff();
                    polygon1=removePoint(polygon1,choice2);
                    printf("\t|\n\t| Polygon 1: ");
                    printPolygon(polygon1);
                    break;

                case 3:
                    printf("\n\t| Emptying the polygon");
                    printf("\n\t|---------------------");
                    polygon1 = emptyPolygon(polygon1);

                    if(polygon1.size == 0){
                        printf("\n\t| The polygon is now empty");
                    }
                    else{
                        printf("\n\t| An error occured while emptying the polygon");
                    }

                    printf("\n\t|\n\t| Polygon 1: ");
                    printPolygon(polygon1);
                    break;

                case 0:
                    moveon = TRUE;
                    printf("\n| Polygon 1: ");
                    printPolygon(polygon1);
                    break;

                default:
                    printf("\n| Wrong input!");
                    break;
            }

        } while(moveon == FALSE);

	    moveon = FALSE;

        printf("\n\n----------------------------------");
        printf("\n| Creation of the second polygon |");
        printf("\n----------------------------------");

        moveon = FALSE;

        polygon2 = createPolygon();

        do{
            printf("\n\n| What do you want to do?");
            printf("\n|------------------------");
            printf("\n| 1) Create a new point");
            printf("\n| 2) Remove a point");
            printf("\n| 3) Empty the polygon");
            printf("\n| 0) End the creation of the second polygon");
            printf("\n| Choice: ");
            scanf("%d",&choice);
            emptBuff();

            switch(choice){
                case 1:
                    printf("\n\t| Creating a new point");
                    printf("\n\t|---------------------");
                    printf("\n\t| Coordinates of the new point:");
                    printf("\n\t|   x=");
                    scanf("%lf",&x);
                    emptBuff();
                    printf("\t|   y=");
                    scanf("%lf",&y);
                    emptBuff();
                    tmpPoint=createPoint(x,y);
                    printf("\t|\n\t| Point created: ");
                    printPoint(tmpPoint);
                    polygon2=addPoint(polygon2, tmpPoint);
                    printf("\n\t|\n\t| Polygon 2: ");
                    printPolygon(polygon2);
                    break;

                case 2:
                    printf("\n\t| Removing a point");
                    printf("\n\t|-----------------");
                    printf("\n\t| Polygon 2: ");
                    printPolygon(polygon2);
                    printf("\n\t|\n\t| Number of the point you want to remove: ");
                    scanf("%d",&choice2);
                    emptBuff();
                    polygon2=removePoint(polygon2,choice2);
                    printf("\t|\n\t| Polygon 2: ");
                    printPolygon(polygon2);
                    break;

                case 3:
                    printf("\n\t| Emptying the polygon");
                    printf("\n\t|---------------------");
                    polygon2 = emptyPolygon(polygon1);

                    if(polygon2.size == 0){
                        printf("\n\t| The polygon is now empty");
                    }
                    else{
                        printf("\n\t| An error occured while emptying the polygon");
                    }

                    printf("\n\t|\n\t| Polygon 2: ");
                    printPolygon(polygon2);
                    break;

                case 0:
                    moveon = TRUE;
                    printf("\n| Polygon 2: ");
                    printPolygon(polygon2);
                    break;

                default:
                    printf("\n| Wrong input!");
                    break;
            }

        } while(moveon == FALSE);

        printf("\n\n| Polygon 1: ");
        printPolygon(polygon1);
        printf("\n| Polygon 2: ");
        printPolygon(polygon2);

        printf("\n\n---------------------------------");
        printf("\n| Let's play with the polygons! |");
        printf("\n---------------------------------");

        moveon = FALSE;

        do{
            printf("\n\n| What do you want to do?");
            printf("\n|------------------------");
            printf("\n| 1) Test if a point is inside a polygon");
            printf("\n| 2) Test where the first polygon is compared to the second one");
            printf("\n| 3) Displays the symmetric polygon of each one through a point");
            printf("\n| 4) Translates each point of the polygons through a vector");
            printf("\n| 5) Displays the polygons with a different scale");
            printf("\n| 6) Displays the Convex Hull of the polygons");
            printf("\n| 42) Tests the \"toString\" function");
            printf("\n| 0) I don't want to play with the polygons anymore...");
            printf("\n| Choice: ");
            scanf("%d",&choice);
            emptBuff();

            switch(choice){
                case 1:
                    printf("\n\t| Is this point inside or not the polygons?");
                    printf("\n\t|------------------------------------------");
                    printf("\n\t| Coordinates of the point to test:");
                    printf("\n\t|   x=");
                    scanf("%lf",&x);
                    emptBuff();
                    printf("\t|   y=");
                    scanf("%lf",&y);
                    emptBuff();
                    tmpPoint=createPoint(x,y);
                    printf("\t|\n\t| Point chosen: ");
                    printPoint(tmpPoint);
                    printf("\n\t|");

                    if(containsPoint(polygon1,tmpPoint)){
                        printf("\n\t| The point is inside the first polygon!");
                    }
                    else{
                        printf("\n\t| The point is outside the first polygon.");
                    }
                    if(containsPoint(polygon2,tmpPoint)){
                        printf("\n\t| The point is inside the second polygon!");
                    }
                    else{
                        printf("\n\t| The point is outside the second polygon.");
                    }
                    printf("\n\t|");

                    break;

                case 2:
                    switch (containsPolygon(polygon1, polygon2)){
                        case INSIDE:
                            printf("\n\t| The second polygon is inside the first one.");
                            break;
                        case OUTSIDE:
                            printf("\n\t| The second polygon is outside the first one.");
                            break;
                        case EQUAL:
                            printf("\n\t| The first polygon and the second one are the same.");
                            break;
                        case SAMESHAPE:
                            printf("\n\t| The first polygon and the second one are not exactly the same but have the same shape.");
                            break;
                        case INTERSECT:
                            printf("\n\t| The first polygon and the second one are intersecting each other.");
                            break;
                        case ENCLOSING:
                            printf("\n\t| The first polygon is inside the second one.");
                            break;
                        case ERROR:
                            printf("\n\t| There may be an error: one of the created polygons may not be really a polygon (at least 3 sides)...");
                            break;
                    }
                    printf("\n");
                    break;

                case 3:
                    printf("\n| Choose the point you want as a symmetry center :");
                    printf("\n| x = ");
                    scanf("%lf", &x);
                    printf("| y = ");
                    scanf("%lf", &y);
                    printf("|");
                    tmpPoint = createPoint(x, y);
                    tmpPolygon = centralSymmetry(polygon1, tmpPoint);
                    printf("\n| Symmetric of Polygon 1: ");
                    printPolygon(tmpPolygon);
                    emptyPolygon(tmpPolygon);
                    tmpPolygon = centralSymmetry(polygon2, tmpPoint);
                    printf("\n| Symmetric of Polygon 2: ");
                    printPolygon(tmpPolygon);
                    printf("\n|");
                    emptyPolygon(tmpPolygon);
                    break;

                case 4:
                    printf("\n| You will now choose the vector AB through which the polygons will be translated");

                    printf("\n| Point A:");
                    printf("\n|     x = ");
                    scanf("%lf", &x);
                    printf("|     y = ");
                    scanf("%lf", &y);
                    printf("|");
                    tmpPoint = createPoint(x, y);

                    printf("\n| Point B:");
                    printf("\n|     x = ");
                    scanf("%lf", &x);
                    printf("|     y = ");
                    scanf("%lf", &y);
                    printf("|");
                    tmpPoint2 = createPoint(x, y);

                    tmpPolygon = translatePolygon(polygon1, tmpPoint, tmpPoint2);
                    printf("\n| Translation of Polygon 1: ");
                    printPolygon(tmpPolygon);
                    emptyPolygon(tmpPolygon);
                    tmpPolygon = translatePolygon(polygon2, tmpPoint, tmpPoint2);
                    printf("\n| Translation of Polygon 2: ");
                    printPolygon(tmpPolygon);
                    printf("\n|");
                    emptyPolygon(tmpPolygon);
                    break;

                case 5:
                    printf("\n| New scale: ");
                    scanf("%f", &scale);
                    printf("|");
                    tmpPolygon = scalePolygon(polygon1, scale);
                    printf("\n| Polygon 1 newly rescaled: ");
                    printPolygon(tmpPolygon);
                    emptyPolygon(tmpPolygon);
                    tmpPolygon = scalePolygon(polygon2, scale);
                    printf("\n| Polygon 2 newly rescaled: ");
                    printPolygon(tmpPolygon);
                    printf("\n|");
                    emptyPolygon(tmpPolygon);
                    break;

                case 6:
                    printf("\n\n| Convex Hull of polygon 1 : ");
                    tmpPolygon = convexhullPolygon(polygon1);
                    printPolygon(tmpPolygon);
                    tmpPolygon = emptyPolygon(tmpPolygon);
                    printf("\n\n| Convex Hull of polygon 2 : ");
                    tmpPolygon = convexhullPolygon(polygon2);
                    printPolygon(tmpPolygon);
                    tmpPolygon = emptyPolygon(tmpPolygon);
                    break;

                case 42:
                    printf("\n| Test of the \"toString\" function on the Polygon 1: ");
                    toStringSample = toString(polygon1);
                    puts(toStringSample);
                    free(toStringSample);
                    toStringSample = NULL;
                    printf("| Test of the \"toString\" function on the Polygon 2: ");
                    toStringSample = toString(polygon2);
                    puts(toStringSample);
                    free(toStringSample);
                    toStringSample = NULL;
                    printf("|");
                    break;

                case 0:
                    moveon = TRUE;
                    break;

                default:
                    printf("\n| Wrong input!");
                    break;
            }

            printf("\n| Polygon 1: ");
            printPolygon(polygon1);

            printf("\n| Polygon 2: ");
            printPolygon(polygon2);

        } while(moveon == FALSE);

        polygon1 = emptyPolygon(polygon1);
        polygon2 = emptyPolygon(polygon2);

        do{
            printf("\n\n| Do you want to restart the whole program? (y/n) ");
            scanf("%c", &restart);
            emptBuff();
        } while(restart != 'y' && restart != 'n');

    } while(restart == 'y');

    printf("\n\n-------------------------------------------------");
    printf("\n|     THANKS FOR USING THIS LITTLE PROGRAM!     |");
    printf("\n-------------------------------------------------\n\n");

    return EXIT_SUCCESS;
}

