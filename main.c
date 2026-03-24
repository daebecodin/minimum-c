#include <stdio.h>
#include <stddef.h>

typedef struct {
    char x;
    int y;
    char z;

}A;

typedef struct {
    int x;
    char y;
    char z;
}B;

int main(void) {

    A a = {'X', 67, 'Z'};
    B b = {69, 'Y', 'Z'};

    printf("=== Struct A ===\n");
    printf("sizeof(struct A) = %zu\n", sizeof( A)); // total size of the struct
    printf("_Alignof(struct A) = %zu\n", _Alignof( A)); // gives the alignment requirement of the struct; objects must start at an addr divisible by this number
    printf("offsetof(struct A, x) = %zu\n", offsetof(A, x)); // how far the member is from the start of the struct
    printf("offsetof(struct A, y) = %zu\n", offsetof(A, y));
    printf("offsetof(struct A, z) = %zu\n", offsetof(A, z));

    printf("\n=== Struct B ===\n");
    printf("sizeof(struct B) = %zu\n", sizeof(B));
    printf("_Alignof(Struct B) = %zu\n", _Alignof(B));
    printf("offsetof(struct B, x) = %zu\n", offsetof(B, x));
    printf("offsetof(struct B, y) = %zu\n", offsetof(B, y));
    printf("offsetof(struct B, z) = %zu\n", offsetof(B, z));



    return 0;
}