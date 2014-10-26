/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Date: 01/05/2015
 */

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>

/* ----- HEADERS ----- */

#include "polygon.h"

/* ----- FUNCTIONS ----- */

/**
 * Creates a 2D-Point according to the specified abscissa and ordinate
 * newX - double, abscissa coordinate
 * newY - double, ordinate coordinate
 */
Point createPoint (double newX, double newY){
    Point newPoint;
    newPoint.x = newX;
    newPoint.y = newY;
    return newPoint;
}

/**
 * Creates an empty polygon
 */
polygonList createPolygon (){
    polygonList newPolygon;
    newPolygon.head = NULL;
    newPolygon.size = 0;
    return newPolygon;
}

/**
 * Adds the specified point to the specified polygon
 * polygon - polygonList, specified polygon to which we want to add a point
 * point - Point, specified point we want to add to the polygon
 */
polygonList addPoint (Point point, polygonList polygon){
    Element* newElem = (Element*)malloc(sizeof(Element)); /* memory allocation for the new element */
    newElem->value.x = point.x;
    newElem->value.y = point.y;
    newElem->index = polygon.size + 1; /* the new element is at the end of the list */
    if(polygon.size == 0){
        newElem->prev = newElem;
        newElem->next = newElem;
        polygon.head = newElem;
    }
    else{
        newElem->prev = polygon.head->prev;
        newElem->next = polygon.head;
        newElem->prev->next = newElem;
        newElem->next->prev = newElem;
    }
    polygon.size++; /*polygon size increased */
    return polygon;
}

/**
 * Removes a specified point from the specified polygon
 * polygon - polygonList, specified polygon on which we want to remove a point
 * i - integer, rank of the point from the head of the list of points
 */
polygonList removePoint (polygonList polygon, int i){
    if(i > 0 && i <= polygon.size){ /* if the chosen point does exist */
        int k=1;
        Element* p = polygon.head; /* pointer on the first element of the list */
        Element* n = polygon.head->prev; /* pointer on the last element of the list */
        if(i==1 && polygon.size != 1){
            polygon.head = p->next; /* first element of the list changed iff the first point is targeted */
        }
        while(k<i){
            k++;
            p = p->next;
        }
        if(polygon.size != 1){
            p->next->prev = p->prev;
            p->prev->next = p->next;
            free(p);
            for(k=polygon.size;k>i;k--){
                n->index--;
                n = n->prev;
            }
        }
        else{
            polygon.head = NULL;
            free(p);
        }
        polygon.size--;
    }
    return polygon;
}

/**
 *
 */
void printPoint (Point point){
    printf("[%.2f,%.2f]",point.x, point.y);
}

/**
 *
 */
void printPolygon (polygonList polygon){
    Element* p = polygon.head;
    printf("[");
    if(polygon.size != 0){
        do{
            printf("%d:",p->index);
            printPoint(p->value);
            p = p->next;
        }while(p != polygon.head);
    }
    printf("]");
}
