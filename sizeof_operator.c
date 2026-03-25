/*
 * Created by Durand Dyer-Branch on 3/24/26.
*/

#include <stdio.h>

int main(void) {
    printf("Integral\n");
    printf("size of char -> %zu\n", sizeof(char));
    printf("size of short-> %zu\n", sizeof(short));
    printf("size of int -> %zu\n", sizeof(int));
    printf("size of long -> %zu\n", sizeof(long));
    printf("size of long long -> %zu\n\n", sizeof(long long));
    printf("Floating-Point\n");
    printf("size of float -> %zu\n", sizeof(float));
    printf("size of double -> %zu\n", sizeof(double));
    printf("size of long double -> %zu\n", sizeof(long double));

    printf("\nidk\n");
    int x = 5;
    int iarr[] = {1,2,3,4,5};
    char carr[] = "abcdef";
    printf("size of x ->  %zu\n", sizeof(x));
    printf("size of iarr ->  %zu\n", sizeof(iarr));
    printf("size of carr ->  %zu\n", sizeof(carr));


    return 0;
}