/**
 * ######################
 * # A14 - LO27 PROJECT #
 * ######################
 *
 * Created by Maxime Brodat and Stéphane Perrez
 *
 * Deadline of the project: 01/05/2015
 */

/**
 * DESCRIPTION OF THE FILE:
 * ------------------------
 * This file is used to implement all polygons-related functions.
 */


/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <polygon.h>
#include <status_enum.h>

/* ----- FUNCTIONS ----- */

/**
 * Adds the specified point at the end of the specified polygon
 * polygon - polygon to which we want to add a point
 * point - point we want to add at the end of the polygon
 * Returns the polygon containing the new point
 */
Polygon addPoint (Polygon polygon, Point point){
    Element* newElem = (Element*)malloc(sizeof(Element)); /* memory allocation for the new element */

    newElem->value = point;
    newElem->index = polygon.size + 1; /* the new element will be putted at the end of the list */

    if(polygon.size == 0){
        /* if the polygon is empty */
        newElem->prev = newElem; /* the next and prev pointers of newElem are set */
        newElem->next = newElem;
        polygon.head = newElem; /* the head of the polygon is set */
    }

    else{
        /* if the polygon contains at least one element */
        newElem->prev = polygon.head->prev; /* the next and prev pointers of newElement are set */
        newElem->next = polygon.head;
        newElem->prev->next = newElem; /* the next and prev pointers of the new neighbours of newElem are set */
        newElem->next->prev = newElem;
    }

    polygon.size++; /* polygon's size is increased */

    return polygon;
}

/**
 * Gives a sorted version of a polygon, in ascendant angle order from the vector of a point coming from his left
 * polygon - the Polygon to sort
 * point - the Point defining the vector
 * Returns the sorted version of polygon
 */
Polygon angleSortPolygon (Polygon polygon, Point point)
{
    Polygon sortedPoly = createPolygon();
    Element* tmpElem1 = polygon.head;
    Element* tmpElem2 = NULL; /* Temporary pointers on an Element */
    Element* newElem = NULL; /* Pointer on futur new elements */
    int i;
    float a1, a2; /* Temporary angles */
    Point projY = point; /* setting the point to the left creating a segment to have an angle */
    projY.x = projY.x - 1;
    if(polygon.size > 0){
        sortedPoly = addPoint(sortedPoly, tmpElem1->value);
        tmpElem1 = tmpElem1->next;

        while(tmpElem1 != polygon.head){
            tmpElem2 = sortedPoly.head;
            i = 0;
            a1 = angleThreePoints(projY, point, tmpElem1->value);
            a2 = angleThreePoints(projY, point, tmpElem2->value);

            while( (a1 < a2) && (i < sortedPoly.size) ){
                tmpElem2 = tmpElem2->next;
                i++;
                a2 = angleThreePoints(projY, point, tmpElem2->value);
            }

            newElem = (Element*) malloc(sizeof(Element));
            newElem->value = tmpElem1->value;
            newElem->prev = tmpElem2->prev;
            newElem->next = tmpElem2;
            newElem->prev->next = newElem;
            newElem->next->prev = newElem;

            if (i == 0){
                sortedPoly.head = newElem;
            }

            newElem = NULL;
            sortedPoly.size++;
            tmpElem1 = tmpElem1->next;
        }

        newElem = sortedPoly.head;
        i = 1;
        do{
            newElem->index = i;
            i++;
            newElem = newElem->next;
        } while (newElem != sortedPoly.head);

    }
    return sortedPoly;
}

/**
 * Computes the angle from 3 points
 * p1, p2, p3 - the three points
 * Returns the angle (p1p2p3) in radians, and 4 if two p1 or p2 equal p3
 */
float angleThreePoints(Point p1, Point p2, Point p3)
{
    float angle;
    if ( (p1.x == p3.x && p1.y == p3.y) || (p2.x == p3.x && p2.y == p3.y ) )
    {
        angle = 4;
    }
    else
    {
        angle = (p1.x - p2.x)*(p3.x - p2.x) + (p1.y - p2.y)*(p3.y - p2.y);
        angle = angle/(sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2))*sqrt(pow((p3.x - p2.x),2)+pow((p3.y - p2.y),2)));
        angle = acos(angle);
    }
    return angle;
}

/**
 * Checks if two polygons are the same
 * p1, p2 - the two tested polygons
 * Returns TRUE if p1 and p2 are equal, FALSE otherwise
 */
Boolean areEqualPolygons (Polygon p1, Polygon p2){
    Boolean diffPointClockwise = FALSE;
    Boolean diffPointCounterClockwise = FALSE;
    Element* tmp1 = p1.head;
    Element* tmp2 = p2.head;
    Element* tmp3 = p2.head;

    if(isPolygon(p1) && isPolygon(p2)){
        if(p1.size == p2.size){
            do{
                tmp1 = tmp1->next;
            } while(tmp1 != p1.head && arePointsEqual(tmp1->value,tmp2->value) == FALSE);

            if(arePointsEqual(tmp1->value,tmp2->value) == TRUE){
                do{
                    if(arePointsEqual(tmp1->value,tmp2->value) == FALSE){
                        diffPointClockwise = TRUE;
                    }
                    if(arePointsEqual(tmp1->value,tmp3->value) == FALSE){
                        diffPointCounterClockwise = TRUE;
                    }
                    tmp1 = tmp1->next;
                    tmp2 = tmp2->next;
                    tmp3 = tmp3->prev;
                } while(tmp2 != p2.head && diffPointClockwise == FALSE && diffPointCounterClockwise == FALSE);

                if(diffPointClockwise == FALSE || diffPointCounterClockwise == FALSE){
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/**
 * Checks if two points have the same coordinates
 * po1, po2 - the two points to check
 * Returns TRUE if the points are equal, FALSE otherwise
 */
Boolean arePointsEqual (Point po1, Point po2){
    if(po1.x == po2.x && po1.y == po2.y){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/** Create a new polygon that is the central symmetry of a specified polygon according to a specified point
 * p - the polygon for which the symmetry is computed
 * s - the point of symmetry
 * Return the polygon symmetric to p according to s
 */
Polygon centralSymmetry (Polygon p, Point s)
{
    Polygon newPoly = createPolygon();
    Element* tmp = p.head;
    Point newPoint;
    do
    {
        newPoint.x = 2*s.x - tmp->value.x;
        newPoint.y = 2*s.y - tmp->value.y;
        newPoly = addPoint(newPoly, newPoint);
        tmp = tmp->next;
    }while(tmp != p.head);
     return newPoly;
}

/**
 * Shows if a point is contained within a polygon
 * polygon - polygon in which we want to know if the point is included
 * point - point we want to know if included or not in the polygon
 * Returns TRUE if the point is inside the polygon, FALSE otherwise
 */
Boolean containsPoint (Polygon polygon, Point point){
    if(polygon.size < 3){
        return FALSE;
    }

    else{
        int crossings = 0;
        Element* p = polygon.head;
        double slope;
        Boolean condition, above;

        do{
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

            if(isOnTheLine(p->value, p->next->value, point)){
                return TRUE;
            }

            condition = FALSE;
            above = FALSE;

            slope = (p->next->value.y - p->value.y) / (p->next->value.x - p->value.x);

            /* In the two next tests, we want to know the position of the two points of the polygon */

            if((p->value.x <= point.x) && (point.x < p->next->value.x)){
                /**
                 * If A is to the left of the studied point
                 *  AND
                 * if B is to the right of the studied point
                 */
                condition = TRUE;
            }
            else{
                if((p->next->value.x <= point.x) && (point.x < p->value.x)){
                    /**
                     * If A is to the right of the studied point
                     *  AND
                     * if B is to the left of the studied point
                     */
                    condition = TRUE;
                }
            }

            /* Tests if [A,B] is above the studied point, using the slope of [A,B] */
            if(point.y < ((slope * (point.x - p->value.x)) + p->value.y)){
                above = TRUE;
            }

            if(condition && above){
                crossings++;
            }

            p = p->next;
        } while(p != polygon.head);

        return (crossings % 2);
    }
}

/**
 * Shows if a polygon is inside, outside, equal, intersecting or enclosing an other polygon
 * p1, p2 - the two polygons tested
 * Returns the corresponding value of Status, and error if one of the polygons is not valid (less than 3 points)
 */
Status containsPolygon (Polygon p1, Polygon p2){
    if(isPolygon(p1) && isPolygon(p2)){
        if(isInsidePolygon(p1, p2)){
            if(areEqualPolygons (p1, p2)){
                return EQUAL;
            }
            else if(haveSameShapePolygons(p1,p2)){
                return SAMESHAPE;
            }
            else{
                return ENCLOSING;
            }
        }
        else if( isInsidePolygon(p2, p1)){
                return INSIDE;
        }
        else if(isOutsidePolygon(p1, p2)){
            return OUTSIDE;
        }
        return INTERSECT;
    }
    return ERROR;
}

/**
 * Computes the convex hull of a list of point
 * polygon - the list of points
 * Return the convex hull of polygon
 */
Polygon convexhullPolygon (Polygon polygon){
    Polygon convPoly = createPolygon(); /* The convex hull polygon */
    if (polygon.size > 0){
        Element* tmpElem = polygon.head; /* Temporary pointer on an Element */
        Point tmpPoint = tmpElem->value; /* Temporary Point  */
        double angle;
        int i = 0; /* Counter for the position in the polygon */

        do{
            if ((tmpPoint.y > tmpElem->value.y) || (tmpPoint.y == tmpElem->value.y && tmpPoint.x > tmpElem->value.x)){
                /* Selecting the point with the smallest y, and if two are equal, the smallest x */
                tmpPoint = tmpElem->value;
            }
            tmpElem = tmpElem->next;
        } while (tmpElem != polygon.head);
        /* Stops when the head of the polygon is reached */

        convPoly = angleSortPolygon(polygon, tmpPoint);
        /* Sorts the polygon with a descendant angle with the vector made from the point chosen above and the point to its left*/
        tmpElem = convPoly.head->next->next; /* Go to the 3rd point */
        i = 3;
        while (tmpElem != convPoly.head){
            angle = (tmpElem->prev->value.x - tmpElem->prev->prev->value.x)*(tmpElem->value.y - tmpElem->prev->prev->value.y) - (tmpElem->prev->value.y - tmpElem->prev->prev->value.y)*(tmpElem->value.x - tmpElem->prev->prev->value.x);
            /* Computes the rotation direction using the scalar product */
            if (angle < 0){
                /* If the angle is counterclockwise, the previous point have to be deleted */
                convPoly = removePoint(convPoly, i - 1);
                tmpElem = tmpElem->next;
            }
            else if(angle == 0 )
            {
                /* if the points are aligned, the point in the middle have to be deleted */
                if (sqrt(pow(tmpElem->value.x - tmpPoint.x,2) + pow(tmpElem->value.y - tmpPoint.y,2)) <
                        sqrt(pow(tmpElem->prev->value.x - tmpPoint.x,2) + pow(tmpElem->prev->value.y - tmpPoint.y,2))
                        &&  fabs(angleThreePoints(tmpElem->value, tmpElem->prev->value, tmpElem->prev->prev->value) - acos(-1)) > 0.000001  ){
                    tmpElem = tmpElem->next;
                    convPoly = removePoint(convPoly, i);
                }
                else{
                    convPoly = removePoint(convPoly, i - 1);
                    i--;
                }
            }
            else{
                tmpElem = tmpElem->next;
                i++;
            }
        }
    }
    return convPoly;
}

/**
 * Creates a 2D-Point according to the Point data type
 * newX - abscissa coordinate
 * newY - ordinate coordinate
 * Returns the newly created point
 */
Point createPoint (double newX, double newY){
    Point newPoint;

    newPoint.x = newX;
    newPoint.y = newY;

    return newPoint;
}

/**
 * Creates an empty polygon
 * Returns the newly created empty polygon
 */
Polygon createPolygon (){
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
Polygon emptyPolygon (Polygon polygon){
    if(polygon.size != 0){
        Element* p = polygon.head->prev->prev; /* p - temporary pointer on an Element */

        while(p->index > 1){
            /* deletes all elements until the first one is reached */
            free(p->next);
            p = p->prev;
        }

        /* when you reach the first one */
        if(polygon.size != 1){
            /* delete the second one if it does exist */
            free(p->next);
        }

        free(p); /* delete the first one */
        polygon.head = NULL; /* reset the polygon's informations */
        polygon.size = 0;
    }

    return polygon;
}

/**
 * Checks if two polygons have the same shape
 * p1, p2 - the two tested polygons
 * Returns TRUE if p1 and p2 have the same shape, FALSE otherwise
 */
Boolean haveSameShapePolygons (Polygon p1, Polygon p2){
    if(isInsidePolygon(p1,p2) == TRUE){
        if(isInsidePolygon(p2,p1) == TRUE){
            if(areEqualPolygons(p1,p2) == FALSE){
                return TRUE;
            }
        }
    }
    return FALSE;
}

/**
 * Checks if two segments do intersect
 * A1, A2 - the two points defining the first tested segment
 * B1, B2 - the two points defining the second tested segment
 * Returns TRUE if the two lines intersect each other, FALSE otherwise
 * If the result is TRUE, the coordinates of the intersection point will be stored in the pointer i*
 */
Boolean intersectionSegments (Point A1, Point A2, Point B1, Point B2, Point* i){
    Point SA, SB;
    double s,t;

    SA.x = A2.x - A1.x;
    SA.y = A2.y - A1.y;
    SB.x = B2.x - B1.x;
    SB.y = B2.y - B1.y;

    s = (-SA.y * (A1.x - B1.x) + SA.x * (A1.y - B1.y)) / (SA.x * SB.y - SB.x * SA.y);
    t = (-SB.y * (A1.x - B1.x) + SB.x * (A1.y - B1.y)) / (SA.x * SB.y - SB.x * SA.y);

    if(s >= 0 && t >= 0 && s <= 1 && t <= 1){
        if(i != NULL){
            i->x = A1.x + (t * SA.x);
            i->y = A1.y + (t * SA.y);
        }
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/**
 * Checks if a polygon is in another one
 * p1, p2 - the two tested polygons
 * Returns TRUE if p1 is within p2 (inside or equal), FALSE otherwise
 */
Boolean isInsidePolygon (Polygon p1, Polygon p2){
    Boolean inside = TRUE;

    if (isPolygon(p1) && isPolygon(p2)){
        Element* point1; /* Pointer that will go through p1 */
        Element* point2; /* Pointer that will go through p2 */
        Point tmpPoint;
        point1 = p1.head;
        point2 = p2.head;

        do{
           if (containsPoint(p2, point1->value) == FALSE){
                inside = FALSE;
           }
           do{
               /* Tests if the line between the point and the previous one is inside */
               if(isOnTheLine(point2->value, point2->prev->value, point1->value)){
                    if(isOnTheLine(point2->value, point2->prev->value, point1->prev->value) == FALSE){
                        tmpPoint.x = (point1->value.x + point1->prev->value.x) / 2;
                        tmpPoint.y = (point1->value.y + point1->prev->value.y) / 2;
                        if (containsPoint(p2, tmpPoint) == FALSE){
                            inside = FALSE;
                        }
                    }
               }else{
                   if(isOnTheLine(point2->value, point2->prev->value, point1->prev->value) == FALSE){
                       if (intersectionSegments(point1->value, point1->prev->value, point2->value, point2->prev->value, NULL) == TRUE){
                           inside = FALSE;
                       }
                   }
               }
            point2 = point2->next;
           } while (point2 != p2.head);
           point1 = point1->next;
        } while (point1 != p1.head && inside == TRUE);
        /* Stops if the whole polygon has been analysed or if a point is outside */
    }
    return inside;
}

/**
 * Checks if a point is or not on a finite line
 * A, B - define the segment [A,B] to check
 * P - point to check
 * Returns TRUE if P is on [A,B], FALSE otherwise
 */
Boolean isOnTheLine (Point A, Point B, Point P){
    Boolean collinear = FALSE, middleX = FALSE, middleY = FALSE;

    if((A.x <= P.x) && (P.x <= B.x)){
        /**
         * If A is to the left of the studied point
         *  AND
         * if B is to the right of the studied point
         */
        middleX = TRUE;
    }
    else{
        if((B.x <= P.x) && (P.x <= A.x)){
            /**
             * If A is to the right of the studied point
             *  AND
             * if B is to the left of the studied point
             */
            middleX = TRUE;
        }
    }

    if((A.y <= P.y) && (P.y <= B.y)){
        /**
         * If A is below the studied point
         *  AND
         * if B is above the studied point
         */
        middleY = TRUE;
    }
    else{
        if((B.y <= P.y) && (P.y <= A.y)){
            /**
             * If A is above the studied point
             *  AND
             * if B is below the studied point
             */
            middleY = TRUE;
        }
    }

    if(((P.y - A.y)*(P.x - B.x)) == ((P.y - B.y)*(P.x - A.x))){
        /* If it's equal, then the three points are aligned */
        collinear = TRUE;
    }

    if(middleX && middleY && collinear){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/**
 * Checks if a polygon is outside another one
 * p1, p2 - the two tested polygons
 * Returns TRUE if p1 is outside of p2, FALSE otherwise
 */
Boolean isOutsidePolygon (Polygon p1, Polygon p2){
    Boolean outside = TRUE;
    if (isPolygon(p1) && isPolygon(p2)){
        Element* point1; /* To go trough p1 */
        Element* point2; /* to go trough p2 */
        point1 = p1.head;
        point2 = p2.head;

        do{
           if (containsPoint(p2, point1->value)){
                outside = FALSE;
           }
           do{
               if(intersectionSegments(point1->value, point1->prev->value, point2->value, point2->prev->value, NULL) == TRUE){
                   outside = FALSE;
               }
               point2 = point2->next;
           } while (point2 != p2.head);

           point1 = point1->next;
        } while (point1 != p1.head && outside == TRUE);
        /* Stops if the whole polygon has been analysed or if a point is inside */
    }
    return outside;
}

/**
 * Checks if a polygon is really a polygon
 * polygon - list of points to test
 * Returns TRUE if the argument is really a polygon, FALSE otherwise
 */
Boolean isPolygon (Polygon polygon){
    Element* p;
    Boolean collinear = TRUE;

    if(polygon.size >= 3){
        p = polygon.head;

        do{
            if(((p->next->next->value.y - p->value.y)*(p->next->next->value.x - p->next->value.x)) != ((p->next->next->value.y - p->next->value.y)*(p->next->next->value.x - p->value.x))){
                collinear = FALSE;
            }
        } while(p != polygon.head);
    }

    if((polygon.size >= 3) && (collinear == FALSE)){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/**
 * Computes the length of a vector
 * A, B - points composing the vector to study
 */
double lengthVector (Point A, Point B){
    Point vector;
    double length;

    vector.x = B.x - A.x;
    vector.y = B.y - A.y;

    length = sqrt(vector.x*vector.x + vector.y*vector.y);

    return length;
}

/**
 * Displays int the console the coordinates of the specified point
 * point - point containing the coordinates to display
 */
void printPoint (Point point){
    printf("[%.2f,%.2f]",point.x, point.y);
}

/**
 * Displays the coordinates of all points of a specified polygon
 * polygon - specified polygon to display
 */
void printPolygon (Polygon polygon){
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
 * Removes a specified point from the specified polygon
 * polygon - polygon for which we want to remove a point
 * i - index of the point we want to remove
 * Returns the polygon without the specified point
 */
Polygon removePoint (Polygon polygon, int i){
    /* if the chosen point does exist */
    if(i > 0 && i <= polygon.size){
        int k = 1;
        Element* p = polygon.head; /* pointer on the first element of the list */
        Element* n = polygon.head->prev; /* pointer on the last element of the list */
        if(i==1 && polygon.size != 1){
            polygon.head = p->next; /* the head of the list is changed iff the first element is targeted */
        }

        while(k<i){
            k++;
            p = p->next; /* temporary pointer is moved until the targeted point is reached */
        }

        if(polygon.size != 1){
            p->next->prev = p->prev; /* links between the elements around the targeted element changed */
            p->prev->next = p->next;
            free(p);

            for(k=polygon.size;k>i;k--){
                n->index--; /* index of the next elements after the removed one are decreased */
                n = n->prev;
            }
        }

        else{
            polygon.head = NULL; /* if no element left, polygon turned into an empty one */
            free(p);
        }

        polygon.size--; /* polygon size is decreased */
    }

    return polygon;
}

/**
 * Computes the rotation of a polygon according to a point and an angle in radians (counterclockwise)
 * poly - polygon about to be rotated
 * center - point of rotation of the polygon
 * angle - angle counterclockwise of rotation in radians
 */
Polygon rotatePolygon (Polygon poly, Point center, float angle){
    Element* tmpPointer = poly.head;
    Polygon resultPoly = createPolygon();
    Point tmpVector, tmpPoint;

    if(poly.size != 0){
        do{
            tmpVector.x = tmpPointer->value.x - center.x;
            tmpVector.y = tmpPointer->value.y - center.y;

            tmpPoint.x = cos(angle)*tmpVector.x - sin(angle)*tmpVector.y + center.x;
            tmpPoint.y = sin(angle)*tmpVector.x + cos(angle)*tmpVector.y + center.y;

            resultPoly = addPoint(resultPoly, tmpPoint);

            tmpPointer = tmpPointer->next;
        } while(tmpPointer != poly.head);
    }

    return resultPoly;
}

/**
 * Scales a polygon according to a factor
 * poly - specified polygon to scale
 * factor - scale factor to use
 * Returns the scaled polygon
 */
Polygon scalePolygon (Polygon poly, float factor){
    Point tmpPoint, vector;
    Element* tmp = poly.head->next;
    Polygon resultPoly = createPolygon();

    if(poly.size != 0){
        resultPoly = addPoint(resultPoly, poly.head->value);

        do{
            vector.x = factor * (tmp->value.x - poly.head->value.x);
            vector.y = factor * (tmp->value.y - poly.head->value.y);

            tmpPoint.x = vector.x + poly.head->value.x;
            tmpPoint.y = vector.y + poly.head->value.y;

            resultPoly = addPoint(resultPoly, tmpPoint);

            tmp = tmp->next;
        } while(tmp != poly.head);
    }

    return resultPoly;
}

/**
 * Outputs the list of points of a polygon into a string
 * polygon - polygon to output
 * Returns the array of characters containing the list of points formated
 */
char* toString (Polygon polygon){
    int i;
    Element* tmp = polygon.head;
    char BUFFER[50];
    char* RESULT;

    RESULT = (char*)malloc(sizeof(char)*2);

    RESULT[0] = '[';
    RESULT[1] = '\0';

    if(polygon.size >= 3){
        do{
            for(i=0;i<50;i++){
                BUFFER[i] = '\0';
            }
            sprintf(BUFFER, "[%.2f,%.2f],", tmp->value.x, tmp->value.y);

            RESULT = realloc(RESULT, sizeof(char) * (strlen(RESULT) + strlen(BUFFER) + 1));
            strcat(RESULT, BUFFER);
            tmp = tmp->next;
        } while(tmp != polygon.head->prev);

        for(i=0;i<50;i++){
            BUFFER[i] = '\0';
        }
        sprintf(BUFFER, "[%.2f,%.2f]]", tmp->value.x, tmp->value.y);

        RESULT = realloc(RESULT, sizeof(char) * (strlen(RESULT) + strlen(BUFFER) + 1));
        strcat(RESULT, BUFFER);
    }
    else{
        RESULT = realloc(RESULT, sizeof(char) * 8);
        strcat(RESULT, "ERROR]");
    }

    return RESULT;
}

/**
 * Computes the translation of a polygon according to the vector defined by two points
 * poly - specified polygon to translate
 * A, B - two points forming the vector AB
 * Returns the translated polygon
 */
Polygon translatePolygon (Polygon poly, Point A, Point B){
    Point vector, tmpPoint;
    Polygon resultPoly = createPolygon();
    Element* tmp = poly.head;

    vector.x = B.x - A.x;
    vector.y = B.y - A.y;

    do{
        tmpPoint.x = tmp->value.x + vector.x;
        tmpPoint.y = tmp->value.y + vector.y;
        resultPoly = addPoint(resultPoly, tmpPoint);

        tmp = tmp->next;
    } while(tmp != poly.head);

    return resultPoly;
}

/**
 * Computes the union between the two specified polygons
 * poly1, poly2 - the two polygons to merge
 */
Polygon unionPolygons (Polygon p1, Polygon p2){
    Polygon resultPoly = createPolygon(), tmpPoly = createPolygon();
    double minLength;
    Element *closeP1, *closeP2, *tmpPointer1, *tmpPointer2;

    if(isPolygon(p1) == FALSE && isPolygon(p2) == FALSE){
    /* if both polygons are not real polygons, return an empty polygon */
    }

    else if(isPolygon(p1) == FALSE){
    /* if only the first polygon is not a real polygon, return the second one */

        tmpPointer2 = p2.head;

        do{
            resultPoly = addPoint(resultPoly, tmpPointer2->value);
            tmpPointer2 = tmpPointer2->next;
        }while(tmpPointer2 != p2.head);
    }

    else if(isPolygon(p2) == FALSE){
    /* if only the second polygon is not a real polygon, return the first one */

        tmpPointer1 = p1.head;
        do{
            resultPoly = addPoint(resultPoly, tmpPointer1->value);
            tmpPointer1 = tmpPointer1->next;
        }while(tmpPointer1 != p1.head);
    }

    else if(containsPolygon(p1, p2) == EQUAL){
    /* if the polygons are the same, return the first one */

        tmpPointer1 = p1.head;

        do{
            resultPoly = addPoint(resultPoly, tmpPointer1->value);
            tmpPointer1 = tmpPointer1->next;
        }while(tmpPointer1 != p1.head);
    }

    else if(containsPolygon(p1, p2) == SAMESHAPE){
    /* if the polygons have the same shape, return the simplest one (the one with the smallest amount of points) */

        if(p1.size < p2.size){
            tmpPointer1 = p1.head;

            do{
                resultPoly = addPoint(resultPoly, tmpPointer1->value);
                tmpPointer1 = tmpPointer1->next;
            }while(tmpPointer1 != p1.head);
        }

        else{
            tmpPointer1 = p2.head;

            do{
                resultPoly = addPoint(resultPoly, tmpPointer1->value);
                tmpPointer1 = tmpPointer1->next;
            }while(tmpPointer1 != p2.head);
        }
    }

    else if(containsPolygon(p1,p2) == ENCLOSING){
    /* if the first polygon is fully inside the second one, return the second one */

        tmpPointer2 = p2.head;

        do{
            resultPoly = addPoint(resultPoly, tmpPointer2->value);
            tmpPointer2 = tmpPointer2->next;
        } while(tmpPointer2 != p2.head);
    }

    else if(containsPolygon(p1,p2) == INSIDE){
    /* if the second polygon is fully inside the first one, return the first one */

        tmpPointer1 = p1.head;

        do{
            resultPoly = addPoint(resultPoly, tmpPointer1->value);
            tmpPointer1 = tmpPointer1->next;
        } while(tmpPointer1 != p1.head);
    }

    else if(containsPolygon(p1, p2) == OUTSIDE  && containsPolygon(p2,p1) == OUTSIDE){
    /* if the polygons don't intersect each other, return p1 && p2 */

        tmpPointer1 = p1.head;
        tmpPointer2 = p2.head;
        closeP1 = p1.head;
        closeP2 = p2.head;

        minLength = lengthVector(tmpPointer1->value, tmpPointer2->value);

        /* searches the points where the two polygons are the closest */
        do{
            do{
                if(lengthVector(tmpPointer1->value, tmpPointer2->value) < minLength){
                    minLength = lengthVector(tmpPointer1->value, tmpPointer2->value);
                    closeP1 = tmpPointer1;
                    closeP2 = tmpPointer2;
                }

                tmpPointer2 = tmpPointer2->next;
            } while(tmpPointer2 != p2.head);

            tmpPointer1 = tmpPointer1->next;
        } while(tmpPointer1 != p1.head);

        tmpPointer1 = closeP1;
        tmpPointer2 = closeP2;

        do{
            resultPoly = addPoint(resultPoly, tmpPointer1->value);
            tmpPointer1 = tmpPointer1->next;
        } while(tmpPointer1 != closeP1);

        resultPoly = addPoint(resultPoly, closeP1->value);

        do{
            resultPoly = addPoint(resultPoly, tmpPointer2->value);
            tmpPointer2 = tmpPointer2->next;
        } while(tmpPointer2 != closeP2);

        resultPoly = addPoint(resultPoly, closeP2->value);
    }

    else if(containsPolygon(p1,p2) == INTERSECT){
    /* if the polygons intersect each other, return the convexhull of the union of the polygons */

        tmpPointer1 = p1.head;
        tmpPointer2 = p2.head;

        do{
            tmpPoly = addPoint(tmpPoly, tmpPointer1->value);
            tmpPointer1 = tmpPointer1->next;
        } while(tmpPointer1 != p1.head);

        do{
            tmpPoly = addPoint(tmpPoly, tmpPointer2->value);
            tmpPointer2 = tmpPointer2->next;
        } while(tmpPointer2 != p2.head);

        resultPoly = convexhullPolygon(tmpPoly);
    }

    return resultPoly;
}
