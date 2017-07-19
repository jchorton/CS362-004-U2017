#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// Want to return character with decimal value of 32 to 126 inclusive
	char randChar = rand() % 95 + 32; // should generate 32 to 126
	return randChar;
}

void inputString(char *randString)
{
	// Want to have 5 letters returned that are lowercase, 97 to 122
	// This will still take ~12,000,000 iterations to find it, SLOW
	//int count;
	//for (count = 0; count < 5; count++) {
	//	randString[count] = rand() % 26 + 97;
	//}

	//strcpy(randString, "reset"); //debugging the tester

	// Increase the probability of getting the needed letters!
	// I just produce more numbers and assign all the extras to the
	// letters that we want to make sure to find.
	int count, randInt;
	for (count = 0; count < 5; count++) {
		randInt = rand() % 215;
		if (randInt < 95) {
			randString[count] = randInt + 32;
		} else if (randInt < 125) {
			randString[count] = 113; // r
		} else if (randInt < 155) {
			randString[count] = 101; // e
		} else if (randInt < 185) {
			randString[count] = 115; // s
		} else if (randInt < 215) {
			randString[count] = 116; // t
		}
	}	
	
	// Don't forget the null terminator!
	randString[5] = '\0';
}

void testme()
{
	int tcCount = 0;
	char *s = (char*) malloc(6*sizeof(char)); // allocating memory once here
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		inputString(s); // changed how this is called
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' ' && state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
				&& s[2] == 's' && s[3] == 'e'
				&& s[4] == 't' && s[5] == '\0'
				&& state == 9)
		{
			printf("error ");
			free(s); // freeing memory once here
			exit(200);
		}
	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
