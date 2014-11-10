/* Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Deadline: 01/05/2015
 */

#ifndef USEFUL_FCTS_H
#define USEFUL_FCTS_H

/* ----- TYPEDEF ----- */

/* Definition of the boolean type which can take to states:
 * TRUE - associated to an integer with the value 1
 * FALSE - associated to an integer with the value 0
 */
typedef enum
{
    TRUE = 1,
    FALSE = 0
} boolean;

/* ----- PROTOTYPES ----- */

/* Function that empties the input buffer */
void emptBuff ();

#endif

