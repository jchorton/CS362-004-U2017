/*
 * Author: Jonathan Horton
 * Date:   2017-07-05
 * Desc:   Customized assert function that allows program
 * 	   to keep running, used for coverage tests.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "assertTrue.h"

/* 
 *	assertTrue
 * This is a customized assert function that will allow the program
 * to keep running when tests fail. This is for using gcov analysis.
 * A label may be sent along with a command to exit if desired.
 */
int assertTrue(int testBool, char *label, int exitBool) {

	// exitBool == 0, normal output and program continues
	// exitBool == 1, normal output and program halts
	// exitBool == 2, only report failures and program continues

	// Prints results of tests
	if (testBool && exitBool != 2)
		printf("PASS : %s\n", label);
	else if (!testBool)
		printf("FAIL : %s\n", label);

	// Exit program if desired
	if (!testBool && exitBool == 1) {
		printf("Terminating Program!\n");
		exit(1);
	}
	
	if (testBool)
		return 0;
	else
		return 1;
}
