/*#pragma warning (disable:4996)
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Stats {
    float health;
    float healthRegen;
    unsigned int mana;
    float manaRegen;
    float range;
    float attackDamage;
    float armor;
    float attackSpeed;
    float magicResist;
    unsigned int movementSpeed;
}; 

int main()
{ */
   /* float num1;
    int num2;

    scanf("%f", &num1);
    num2 = (int)num1;
    printf("%d\n", num2); */ // 심사문제 1

    /*unsigned long long* numPtr1 = malloc(sizeof(unsigned long long));
    unsigned int* numPtr2;

    scanf("%llx", numPtr1);

    numPtr2 = (unsigned int*)numPtr1;

    printf("0x%x\n", *numPtr2);

    free(numPtr1);*/ //심사문제 2

   /* long double* numPtr1 = malloc(sizeof(long double));
    void* ptr;

    scanf("%Lf", numPtr1);

    ptr = numPtr1;

    printf("%Lf\n", *(long double *)ptr);

    free(numPtr1); */ //심사문제 3

    /*void* ptr = malloc(sizeof(struct Stats));
    struct Stats st;

    scanf("%u %u", &st.mana, &st.movementSpeed);

    memcpy(ptr, &st, sizeof(struct Stats));
   st.mana = 0;
   st.movementSpeed = 0;

    printf("%d\n", ((struct Stats *)ptr)->mana);
    printf("%d\n", ((struct Stats*)ptr)->movementSpeed);

        free(ptr); */ //심사문제 4


//    return 0;
//}

    