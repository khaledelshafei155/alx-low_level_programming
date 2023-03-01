#include <stdio.h>

/*
   * write your line of code here...
   * Remember:
   * - you are not allowed to use a
   * - you are not allowed to modify p
   * - only one statement
   * - you are not allowed to code anything else than this line of code
   */


int main() {
    int a[5] = {1, 2, 3, 4, 5};
    int *p = a;
    
    *(p + 2) = 98;
    printf("a[2] = %d\n", *(p + 2));
    
    return 0;
}
