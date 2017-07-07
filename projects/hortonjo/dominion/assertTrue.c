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

	// Prints results of tests
	if (testBool)
		printf("PASS");
	else
		printf("FAIL");
	printf(" : %s", label);
	printf("\n");

	// Exit program if desired
	if (!testBool && exitBool) {
		printf("Terminating Program!\n");
		exit(1);
	}
	
	return testBool;
}
