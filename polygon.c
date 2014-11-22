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


/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>
#include <polygon.h>

/* ----- FUNCTIONS ----- */

/**
 * Creates a 2D-Point according to the Point data type
 *     newX - abscissa coordinate
 *     newY - ordinate coordinate
 *     newPoint - newly created point
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
 * newPolygon - newly created empty polygon
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
 * Shows if a point is contained within a polygon
 * polygon - polygon in which we want to know if the point is included
 * point - point we want to know if included or not in the polygon
 * isContained - Boolean, TRUE if the point is inside the polygon, false otherwise
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
 * A and B define the segment to check
 * P is the point to check
 * Returns TRUE if P is on [A,B], false otherwise
 */
Boolean isOnTheLine (Point A, Point B, Point P)
{
    Boolean colinear = FALSE, middleX = FALSE, middleY = FALSE;

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
        colinear = TRUE;
    }

    if(middleX && middleY && colinear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
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
 * coordString - array of characters, dynamically allocated
 */
/* char* toString (polygonList polygon); */
