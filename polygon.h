/* Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Deadline: 01/05/2015
 */

#ifndef POLYGON_H
#define POLYGON_H

/* ----- TYPEDEF ----- */

/* Defines a point in a 2D-plane
 * x, y - real numbers that contain the abscissa and the ordinate of the defined point
 */
typedef struct{
    double x;
    double y;
}Point;

/* Defines each element of the polygon-linked-list
 * value - variable containing the abscissa and the ordinate of the stored point
 * prev - pointer on the previous point of the polygon
 * next - pointer on the next point of the polygon
 */
typedef struct elem{
    Point value;
    int index;
    struct elem* prev;
    struct elem* next;
}Element;

/* Linked list that will contain a pointer to the first point of the polygon */
typedef struct{
    Element* head;
    int size;
}polygonList;

/* ----- PROTOTYPES ----- */

/**
 * Creates a 2D-Point according to the specified abscissa and ordinate
 * newX - double, abscissa coordinate
 * newY - double, ordinate coordinate
 */
Point createPoint (double newX, double newY);

/**
 * Creates an empty polygon
 */
polygonList createPolygon ();

/**
 * Empties a polygon's memory
 * polygon - polygonList, specified polygon to empty
 */
polygonList emptyPolygon(polygonList polygon);

/**
 * Adds the specified point to the specified polygon
 * polygon - polygonList, specified polygon to which we want to add a point
 * point - Point, specified point we want to add to the polygon
 */
polygonList addPoint (Point point, polygonList polygon);

/**
 * Removes a specified point from the specified polygon
 * polygon - polygonList, specified polygon on which we want to remove a point
 * i - integer, rank of the point from the head of the list of points
 */
polygonList removePoint (polygonList polygon, int i);

/**
 *
 */
void printPoint (Point point);

/**
 *
 */
void printPolygon (polygonList polygon);

/**
 *
 */
/* char* toString (polygonList polygon); */

#endif

