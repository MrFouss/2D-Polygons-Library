/**
 * Maxime Brodat
 * maxime.brodat@utbm.fr
 * contact@fouss.fr
 *
 * Date of creation:
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
    INTERSECT = 2, /* if the second polygon is partially inside/outside the first
one, in other words intersecting the second one */
    ENCLOSING = 3, /* if the first polygon is fully inside the second one */
    EQUAL = 4 /* both polygons are exactly equal */
} Status;


#endif

