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
    ERROR = -1,
    OUTSIDE = 0,
    INSIDE = 1,
    INTERSECT = 2,
    ENCLOSING = 3,
    EQUAL = 4
} Status;


#endif

