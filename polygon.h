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

#ifndef POLYGON_H
#define POLYGON_H

/* ----- INCLUDE ----- */

#include <boolean.h>
#include <status_enum.h>

/* ----- TYPEDEF ----- */

/**
 * Data type of a point in a 2D-plane with the following specifications:
 * x - real number containing the abscissa of the point
 * y - real number containing the ordinate of the point
 */
typedef struct
{
    double x;
    double y;
} Point;

/**
 * Data type of an element of the polygon-linked-list with the following specifications:
 * value - Point data type with the abscissa and ordinate of the point
 * index - index of the point contained in the polygon
 * prev - pointer on the previous element of the polygon
 * next - pointer on the next element of the polygon
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
 * head - pointer on the first element of the polygon
 * size - number of elements within the polygon
 */
typedef struct
{
    Element* head;
    int size;
} Polygon;

/* ----- PROTOTYPES ----- */

/**
 * Creates a 2D-Point according to the Point data type
 * newX - abscissa coordinate
 * newY - ordinate coordinate
 * Returns the newly created point
 */
Point createPoint (double newX, double newY);

/**
 * Creates an empty polygon
 * Returns the newly created empty polygon
 */
Polygon createPolygon ();

/**
 * Empties a polygon's data
 * polygon - specified polygon to empty
 * Returns the empty polygon
 */
Polygon emptyPolygon(Polygon polygon);

/**
 * Adds the specified point at the end of the specified polygon
 * polygon - polygon to which we want to add a point
 * point - point we want to add at the end of the polygon
 * Returns the polygon containing the new point
 */
Polygon addPoint (Point point, Polygon polygon);

/**
 * Removes a specified point from the specified polygon
 * polygon - polygon for which we want to remove a point
 * i - index of the point we want to remove
 * Returns the polygon without the specified point
 */
Polygon removePoint (Polygon polygon, int i);

/**
 * Checks if two points have the same coordinates
 * po1, po2 - the two points checked
 * Returns TRUE if the points are equal and FALSE otherwise
 */
Boolean arePointsEqual(Point po1, Point po2);

/**
 * Checks if a polygon is really a polygon
 * polygon - list of points to test
 * Returns TRUE if the argument is really a polygon, FALSE otherwise
 */
Boolean isPolygon (Polygon polygon);

/**
 * Shows if a point is contained within a polygon
 * polygon - polygon in which we want to know if the point is included
 * point - point we want to know if included or not in the polygon
 * Returns TRUE if the point is inside the polygon, FALSE otherwise
 */
Boolean containsPoint (Polygon polygon, Point point);

/**
 * Checks if a point is or not on a finite line
 * A, B - define the segment [A,B] to check
 * P - point to check
 * Returns TRUE if P is on [A,B], FALSE otherwise
 */
Boolean isOnTheLine (Point A, Point B, Point P);

/**
 * Checks if a polygon is in another one
 * p1, p2 - the two polygons tested
 * Return TRUE if p1 is in p2 (inside or equal), FALSE otherwise
 */
Boolean isInsidePolygon (Polygon p1, Polygon p2);

/**
 * Checkes if a polygon equal to another one
 * p1, p2 - the two polygons tested
 * Returns TRUE if p1 and p2 are equal, FALSE otherwise
 */
Boolean areEqualPolygons (Polygon p1, Polygon p2);

/**
 * Checkes if a polygon is outside another one
 * p1, p2 - the two polygons tested
 * Return TRUE if p1 is outside of p2, FALSE otherwise
 */
Boolean isOutsidePolygon (Polygon p1, Polygon p2);

/**
 * Shows if a polygon is inside, outside, equal, intersecting or enclosing an other polygon
 * p1, p2 - the two polygons tested
 * Returns the corresponding value of Status, and error if one of the polygons is not valid (less than 3 points)
 */
Status containsPolygon (Polygon p1, Polygon p2);

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
 * Returns the array of characters, dynamically allocated, containing the coordinates of the polygon
 */
/* char* toString (polygonList polygon); */

#endif

