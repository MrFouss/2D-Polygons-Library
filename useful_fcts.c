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
 * This file is used to implement all functions not directly linked to polygon management, but still useful in the project.
 */

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>
#include <useful_fcts.h>

/* ----- FUNCTIONS ----- */

/**
 * Function that empties the input buffer
 */
void emptBuff ()
{
    int c;

    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF); /* it empties the buffer by reading it */
}
