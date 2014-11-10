/* Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Deadline: 01/05/2015
 */

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>

/* ----- TYPEDEF ----- */

/* ----- HEADERS ----- */

/* ----- PROTOTYPES ----- */

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
