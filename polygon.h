/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 * contact@fouss.fr
 *
 * Stéphane Perrez
 * stéphane.perrez@utbm.fr
 *
 * Deadline of the project: 01/05/2015
 */

#ifndef POLYGON_H
#define POLYGON_H

/* ----- INCLUDE ----- */

#include <boolean.h>
#include <status_enum.h>

/* ----- TYPEDEF ----- */

/**
 * Data type of a point in a 2D-plane with the following specifications:
 *     x - real number containing the abscissa of the point
 *     y - real number containing the ordinate of the point
 */
typedef struct
{
    double x;
    double y;
} Point;

/**
 * Data type of an element of the polygon-linked-list with the following specifications:
 *     value - Point data type with the abscissa and ordinate of the point
 *     index - index of the point contained in the polygon
 *     prev - pointer on the previous element of the polygon
 *     next - pointer on the next element of the polygon
 */
typedef struct elem
{
    Point value;
    int index;
    struct elem* prev;
    struct elem* next;
} Element;

/**
 * Data type of a polygon defined as a linked list containing the elements defined above
 * This data type is defined with the following specifications:
 *     head - pointer on the first element of the polygon
 *     size - number of elements within the polygon
 */
typedef struct
{
    Element* head;
    int size;
} Polygon;

/* ----- PROTOTYPES ----- */

/**
 * Creates a 2D-Point according to the Point data type
 *     newX - abscissa coordinate
 *     newY - ordinate coordinate
 *     newPoint - newly created point
 */
Point createPoint (double newX, double newY);

/**
 * Creates an empty polygon
 * newPolygon - newly created empty polygon
 */
Polygon createPolygon ();

/**
 * Empties a polygon's data
 * polygon - specified polygon to empty
 */
Polygon emptyPolygon(Polygon polygon);

/**
 * Adds the specified point at the end of the specified polygon
 * polygon - polygon to which we want to add a point
 * point - point we want to add at the end of the polygon
 */
Polygon addPoint (Point point, Polygon polygon);

/**
 * Removes a specified point from the specified polygon
 * polygon - polygon for which we want to remove a point
 * i - index of the point we want to remove
 */
Polygon removePoint (Polygon polygon, int i);

/**
 * Shows if a point is contained within a polygon
 * polygon - polygon in which we want to know if the point is included
 * point - point we want to know if included or not in the polygon
 */
Boolean containsPoint (Polygon polygon, Point point);

/**
 * Checks if a point is or not on a finite line
 * A and B define the segment to check
 * P is the point to check
 * Returns TRUE if P is on [A,B], false otherwise
 */
Boolean isOnTheLine (Point A, Point B, Point P);

/**
 * Displays int the console the coordinates of the specified point
 * point - point containing the coordinates to display
 */
void printPoint (Point point);

/**
 * Displays the coordinates of all points of a specified polygon
 * polygon - specified polygon to display
 */
void printPolygon (Polygon polygon);

/**
 * Stores the coordinates of all points of a specified polygon in an array of characters
 * polygon - specified polygon containing the coordinates to store
 * coordString - array of characters, dynamically allocated
 */
/* char* toString (polygonList polygon); */

#endif

