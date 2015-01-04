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
 * This file is used to introduce the "Status" data type, used to compare two polygons' locations.
 * Since no new specifications where given, we decided to add a new status called "SAMESHAPE".
 * This status defines two polygons that take the exact same space, but can't be defined as equal.
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

