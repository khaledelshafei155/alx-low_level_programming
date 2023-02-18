#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */

int main(void)
{
	int n; // declare a variable to hold the random number

	srand(time(0)); // seed the random number generator

	n = rand() - RAND_MAX / 2; // generate a random number and store it in n

	/* Print the last digit of n and whether it is greater than 5, less than 6 and not 0, or 0 */
	printf("Last digit of %d is ", n);
	
	/* Get the last digit of n by taking the absolute value of n modulo 10 */
	int last_digit = abs(n) % 10;
	
	if (last_digit > 5)
	{
		printf("%d and is greater than 5\n", last_digit);
	}
	else if (last_digit == 0)
	{
		printf("%d and is 0\n", last_digit);
	}
	else
	{
		printf("%d and is less than 6 and not 0\n", last_digit);
	}
	return (0); // indicate successful execution of the program
}
