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

typedef struct {
    char i;
    int j;
    int k;
}C;
int main(void) {

    A a = {'X', 67, 'Z'};
    B b = {69, 'Y', 'Z'};
    C c = {'i', 67, 420 };

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

    printf("\n=== Addresses in A ===\n");
    printf("&a      = %p\n", (void*)&a);
    printf("&a.x    = %p\n", (void*)&a.x);
    printf("&a.y    = %p\n", (void*)&a.y);
    printf("&a.z    = %p\n", (void*)&a.z);

    printf("\n=== Addressed in B ===\n");
    printf("&b      = %p\n", (void*)&b);
    printf("&b.x    = %p\n", (void*)&b.x);
    printf("&b.y    = %p\n", (void*)&b.y);
    printf("&b.z    = %p\n", (void*)&b.z);

    printf("\n=== Addresses in C\n");
    printf("&c      = %p\n", (void*) &c);
    printf("&c.i      = %p\n", (void*) &c.i);
    printf("&c.j      = %p\n", (void*) &c.j);
    printf("&c.k      = %p\n", (void*) &c.k);





    return 0;
}