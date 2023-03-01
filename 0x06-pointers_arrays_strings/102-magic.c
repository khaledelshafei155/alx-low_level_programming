#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int a[5];
    int *p;

    a[0] = 98;
    a[1] = 198;
    a[2] = 298;
    a[3] = 398;
    a[4] = 498;
    p = &a[2];

    /* Add your code here */
    printf("a[2] = %d\n", *p);

    return (0);
}
