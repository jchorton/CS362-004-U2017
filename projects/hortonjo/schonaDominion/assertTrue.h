/*
 * Author: Jonathan Horton
 * Date:   2017-07-05
 * Desc:   Header file for custom assert function.
 */

#ifndef _ASSERTTRUE_H
#define _ASSERTTRUE_H

int assertTrue(int testBool, char *label, int exitBool);
/* Custom assert function called with a test, a text label
 * to display, and a 0 or 1 to tell it whether to exit when
 * the test boolean is false. */

#endif
