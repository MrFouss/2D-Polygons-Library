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

/* ----- FUNCTIONS ----- */

/* Function that empties the input buffer */
void emptBuff ()
{
    int c;

    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF); /* it empties the buffer by reading it */

}
