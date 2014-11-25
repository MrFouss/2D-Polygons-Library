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
#include <polygon.h>

/* ----- FUNCTIONS ----- */

/**
 * Creates a 2D-Point according to the Point data type
 * newX - abscissa coordinate
 * newY - ordinate coordinate
 * Returns the newly created point
 */
Point createPoint (double newX, double newY)
{
    Point newPoint;

    newPoint.x = newX;
    newPoint.y = newY;

    return newPoint;
}

/**
 * Creates an empty polygon
 * Returns the newly created empty polygon
 */
Polygon createPolygon ()
{
    Polygon newPolygon;

    newPolygon.head = NULL;
    newPolygon.size = 0;

    return newPolygon;
}

/**
 * Empties a polygon's data
 * polygon - specified polygon to empty
 * Returns the empty polygon
 */
Polygon emptyPolygon(Polygon polygon)
{
    if(polygon.size != 0)
    {
        Element* p = polygon.head->prev->prev; /* p - temporary pointer on an Element */

        while(p->index > 1) /* deletes all elements until the first one is reached */
        {
            free(p->next);
            p = p->prev;
        }

        /* when you reach the first one */
        if(polygon.size != 1) /* delete the second one if it does exist */
        {
            free(p->next);
        }

        free(p); /* delete the first one */
        polygon.head = NULL; /* reset the polygon's informations */
        polygon.size = 0;
    }

    return polygon;
}

/**
 * Adds the specified point at the end of the specified polygon
 * polygon - polygon to which we want to add a point
 * point - point we want to add at the end of the polygon
 * Returns the polygon containing the new point
 */
Polygon addPoint (Point point, Polygon polygon)
{
    Element* newElem = (Element*)malloc(sizeof(Element)); /* memory allocation for the new element */

    newElem->value = point;
    newElem->index = polygon.size + 1; /* the new element will be putted at the end of the list */

    if(polygon.size == 0) /* if the polygon is empty */
    {
        newElem->prev = newElem; /* the next and prev pointers of newElem are set */
        newElem->next = newElem;
        polygon.head = newElem; /* the head of the polygon is set */
    }

    else /* if the polygon contains at least one element */
    {
        newElem->prev = polygon.head->prev; /* the next and prev pointers of newElement are set */
        newElem->next = polygon.head;
        newElem->prev->next = newElem; /* the next and prev pointers of the new neighbours of newElem are set */
        newElem->next->prev = newElem;
    }

    polygon.size++; /* polygon's size is increased */

    return polygon;
}

/**
 * Removes a specified point from the specified polygon
 * polygon - polygon for which we want to remove a point
 * i - index of the point we want to remove
 * Returns the polygon without the specified point
 */
Polygon removePoint (Polygon polygon, int i)
{
    if(i > 0 && i <= polygon.size) /* if the chosen point does exist */
    {
        int k = 1;
        Element* p = polygon.head; /* pointer on the first element of the list */
        Element* n = polygon.head->prev; /* pointer on the last element of the list */
        if(i==1 && polygon.size != 1)
        {
            polygon.head = p->next; /* the head of the list is changed iff the first element is targeted */
        }

        while(k<i)
        {
            k++;
            p = p->next; /* temporary pointer is moved until the targeted point is reached */
        }

        if(polygon.size != 1)
        {
            p->next->prev = p->prev; /* links between the elements around the targeted element changed */
            p->prev->next = p->next;
            free(p);

            for(k=polygon.size;k>i;k--)
            {
                n->index--; /* index of the next elements after the removed one are decreased */
                n = n->prev;
            }
        }

        else
        {
            polygon.head = NULL; /* if no element left, polygon turned into an empty one */
            free(p);
        }

        polygon.size--; /* polygon size is decreased */
    }

    return polygon;
}


/**
 * Checks if two points have the same coordinates
 * po1, po2 - the two points checked
 * Returns TRUE if the points are equal and FALSE otherwise
 */
Boolean arePointsEqual(Point po1, Point po2)
{
    if(po1.x == po2.x && po1.y == po2.y)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * Checks if a polygon is really a polygon
 * polygon - list of points to test
 * Returns TRUE if the argument is really a polygon, FALSE otherwise
 */
Boolean isPolygon (Polygon polygon)
{
    Element* p;
    Boolean collinear = TRUE;

    if(polygon.size >= 3)
    {
        p = polygon.head;

        do{
            if(((p->next->next->value.y - p->value.y)*(p->next->next->value.x - p->next->value.x)) != ((p->next->next->value.y - p->next->value.y)*(p->next->next->value.x - p->value.x)))
            {
                collinear = FALSE;
            }
        } while (p != polygon.head);
    }

    if((polygon.size >= 3) && (collinear == FALSE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Shows if a point is contained within a polygon
 * polygon - polygon in which we want to know if the point is included
 * point - point we want to know if included or not in the polygon
 * Returns TRUE if the point is inside the polygon, FALSE otherwise
 */
Boolean containsPoint (Polygon polygon, Point point)
{
    if(polygon.size < 3)
    {
        return FALSE;
    }

    else
    {
        int crossings = 0;
        Element* p = polygon.head;
        double slope;
        Boolean condition, above;
        do
        {
            /**
             * In this loop, we are working with 2 consecutive points (let's call them A and B)
             * of the polygon creating a segment [A,B].
             * We want to check for all A and B of the polygon if or not an infinite ray coming
             * from the studied point does or not cross each segment [A,B].
             * We count how many times it does cross each segment, in the variable "crossings".
             *
             * If "crossings" is odd, that means the studied point is inside the polygon.
             * Otherwise, the studied point is outside the polygon.
             *
             * We also suppose that if a point is on a side of the polygon, it's considered
             * as contained by polygon.
             */

            if(isOnTheLine(p->value, p->next->value, point))
            {
                return TRUE;
            }

            condition = FALSE;
            above = FALSE;

            slope = (p->next->value.y - p->value.y) / (p->next->value.x - p->value.x);

            /* In the two next tests, we want to know the position of the two points of the polygon */

            if((p->value.x <= point.x) && (point.x < p->next->value.x))
            /**
             * If A is to the left of the studied point
             *  AND
             * if B is to the right of the studied point
             */
            {
                condition = TRUE;
            }
            else
            {
                if((p->next->value.x <= point.x) && (point.x < p->value.x))
                /**
                 * If A is to the right of the studied point
                 *  AND
                 * if B is to the left of the studied point
                 */
                {
                    condition = TRUE;
                }
            }

            /* Tests if [A,B] is above the studied point, using the slope of [A,B] */
            if(point.y < ((slope * (point.x - p->value.x)) + p->value.y))
            {
                above = TRUE;
            }

            if(condition && above)
            {
                crossings++;
            }

            p = p->next;
        } while(p != polygon.head);

        return (crossings % 2);
    }
}

/**
 * Checks if a point is or not on a finite line
 * A, B - define the segment [A,B] to check
 * P - point to check
 * Returns TRUE if P is on [A,B], FALSE otherwise
 */
Boolean isOnTheLine (Point A, Point B, Point P)
{
    Boolean collinear = FALSE, middleX = FALSE, middleY = FALSE;

    if((A.x <= P.x) && (P.x <= B.x))
    /**
     * If A is to the left of the studied point
     *  AND
     * if B is to the right of the studied point
     */
    {
        middleX = TRUE;
    }
    else
    {
        if((B.x <= P.x) && (P.x <= A.x))
        /**
         * If A is to the right of the studied point
         *  AND
         * if B is to the left of the studied point
         */
        {
            middleX = TRUE;
        }
    }

    if((A.y <= P.y) && (P.y <= B.y))
    /**
     * If A is below the studied point
     *  AND
     * if B is above the studied point
     */
    {
        middleY = TRUE;
    }
    else
    {
        if((B.y <= P.y) && (P.y <= A.y))
        /**
         * If A is above the studied point
         *  AND
         * if B is below the studied point
         */
        {
            middleY = TRUE;
        }
    }

    if(((P.y - A.y)*(P.x - B.x)) == ((P.y - B.y)*(P.x - A.x)))
    /* If it's equal, then the three points are aligned */
    {
        collinear = TRUE;
    }

    if(middleX && middleY && collinear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Checks if a polygon is in another one
 * p1, p2 - the two polygons tested
 * Return TRUE if p1 is in p2 (inside or equal), FALSE otherwise
 */
Boolean isInsidePolygon (Polygon p1, Polygon p2)
{
    Boolean inside = TRUE;
    if (isPolygon(p1) && isPolygon(p2))
    {
        Element* point; /* To go trough p1 */
        point = p1.head;
        do
        {
           if (!containsPoint(p2, point->value))
           {
                inside = FALSE;
           }
           point = point->next;
        }while (point != p1.head && inside == TRUE); /* stops if it ran the complete polygon */
                                                     /* or if a point is outside             */
    }
    return inside;
}

/**
 * Checkes if a polygon equal to another one
 * p1, p2 - the two polygons tested
 * Returns TRUE if p1 and p2 are equal, FALSE otherwise
 */
Boolean areEqualPolygons (Polygon p1, Polygon p2)
{
    Boolean equal = FALSE;
    if (isPolygon(p1) && isPolygon(p2))
    {
        Element* point = p1.head; /* to go throught p1*/
        while (isOnTheLine(p2.head->prev->value, p2.head->next->value, p2.head->value))
        {
            p2.head = p2.head->next;
        }/* moving the head of p2 out of a line */
        do
        {
            point = point->next;
        }while( arePointsEqual(point->value, p2.head->value) && point != p1.head);
        /* places point on an element which coordonates are the ones of the head of p2 if theres one */
        p1.head = point;
        if (point == p2.head)
        {
            Element* point2 = p2.head; /* to go throught p2 */
            do
            {
                do
                {
                    point = point->next;
                }while (isOnTheLine(point->prev->value, point->next->value, point->value));

                do
                {
                    point2 = point2->next;
                }while (isOnTheLine(point2->prev->value, point2->next->value, point2->value));

            }while(arePointsEqual(point->value, point2->value) && point2 != p2.head);
            if(arePointsEqual(point->value, point2->value))
            {
                equal = TRUE;
            }
            else
            {
                point = p1.head;
                point2 = p2.head;
                do
                {
                    do
                    {
                        point = point->prev;
                    }while (isOnTheLine(point->prev->value, point->next->value, point->value));

                    do
                    {
                        point2 = point2->next;
                    }while (isOnTheLine(point2->prev->value, point2->next->value, point2->value));

                }while(arePointsEqual(point->value, point2->value) && point2 != p2.head);
                if(arePointsEqual(point->value, point2->value))
                {
                equal = TRUE;
                }
            }
        }
    }
    return equal;
}

/**
 * Checkes if a polygon is outside another one
 * p1, p2 - the two polygons tested
 * Return TRUE if p1 is outside of p2, FALSE otherwise
 */
Boolean isOutsidePolygon (Polygon p1, Polygon p2)
{
     Boolean outside = TRUE;
    if (isPolygon(p1) && isPolygon(p2))
    {
        Element* point; /* To go trough p1 */
        point = p1.head;
        do
        {
           if (containsPoint(p2, point->value))
           {
                outside = FALSE;
           }
           point = point->next;
        }while (point != p1.head && outside == TRUE); /* stops if it ran the complete polygon */
                                                      /* or if a point is inside              */
    }
    return outside;
}


/**
 * Shows if a polygon is inside, outside, equal, intersecting or enclosing an other polygon
 * p1, p2 - the two polygons tested
 * Returns the corresponding value of Status, and error if one of the polygons is not valid (less than 3 points)
 */
Status containsPolygon (Polygon p1, Polygon p2)
{
    if (isPolygon(p1) && isPolygon(p2))
    {
        if(isInsidePolygon(p1, p2))
        {
            if(areEqualPolygons (p1, p2))
            {
                return EQUAL;
            }
            return INSIDE;
        }
        if( isOutsidePolygon(p1, p2))
        {
            /* we need to check if p2 is in p1 */
            if( isInsidePolygon(p2, p1))
            {
                return ENCLOSING;
            }
            return OUTSIDE;
        }
        return INTERSECT;
    }
    return ERROR;
}


/**
 * Displays int the console the coordinates of the specified point
 * point - point containing the coordinates to display
 */
void printPoint (Point point)
{
    printf("[%.2f,%.2f]",point.x, point.y);
}

/**
 * Displays the coordinates of all points of a specified polygon
 * polygon - specified polygon to display
 */
void printPolygon (Polygon polygon)
{
    Element* p = polygon.head;
    printf("[");

    if(polygon.size != 0)
    {
        do
        {
            if(p->index != 1)
            {
                printf(",");
            }

            printPoint(p->value);
            p = p->next;
        } while(p != polygon.head);
    }

    printf("]");
}

/**
 * Stores the coordinates of all points of a specified polygon in an array of characters
 * polygon - specified polygon containing the coordinates to store
 * Returns the array of characters, dynamically allocated, containing the coordinates of the polygon
 */
/* char* toString (polygonList polygon); */
