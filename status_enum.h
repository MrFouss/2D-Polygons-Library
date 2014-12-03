/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 * maxime.brodat@fouss.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Deadline of the project: 01/05/2015
 */

#ifndef STATUS_H
#define STATUS_H

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>

/* ----- TYPEDEF ----- */

typedef enum
{
    ERROR = -1, /* if some Polygon is not a polygon : less than 3 points */
    OUTSIDE = 0, /* if the second polygon is fully outside the first one */
    INSIDE = 1, /* if the second polygon is fully inside the first one */
    INTERSECT = 2, /* if the second polygon is partially inside and outside the first one */
    ENCLOSING = 3, /* if the first polygon is fully inside the second one */
    EQUAL = 4, /* if both polygons are exactly equal */
    SAMESHAPE = 5 /* if both polygons have the same shape but aren't equal */
} Status;


#endif

