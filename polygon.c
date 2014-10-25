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
    Element* newElem = (Element*)malloc(sizeof(Element));
    newElem->value.x = point.x;
    newElem->value.y = point.y;
    newElem->index = polygon.size + 1;
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
    polygon.size++;
    return polygon;
}

/**
 * Removes a specified point from the specified polygon
 * polygon - polygonList, specified polygon on which we want to remove a point
 * i - integer, rank of the point from the head of the list of points
 */
polygonList removePoint (polygonList polygon, int i){
    if(i <= polygon.size){
        int k=1;
        Element* p = polygon.head;
        Element* n = polygon.head->prev;
        if(i==1){
            polygon.head = p->next;
        }
        while(k<i){
            k++;
            p = p->next;
        }
        p->next->prev = p->prev;
        p->prev->next = p->next;
        free(p);
        if(polygon.size != 1){
            for(k=polygon.size;k>i;k--){
                n->index--;
                n = n->prev;
            }
        }
        polygon.size--;
        printf("Point removed.");
    }
    else{
        printf("The chosen point doesn't exist...");
    }
    return polygon;
}

int main (){

    return EXIT_SUCCESS;
}
