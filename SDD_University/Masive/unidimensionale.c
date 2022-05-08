#include<stdio.h>
#include<malloc.h>


int main(){

    int uniDimensionale1[10] = {1,2,3,4,5,6,7,8,9,10};
    int uniDimensionale2[10];

    for (int i = 0; i <= sizeof(uniDimensionale2) ; i++)
    {
        uniDimensionale2[i] = i;
    }

    for (int i = 0; i <= sizeof(uniDimensionale2) / sizeof(int) ; i++)
    {
        printf("%d\n", uniDimensionale2[i]);
    }

    // printf("%d\n", uniDimensionale1[10]);
    printf("%d\n", uniDimensionale2[67]);
    return 0;
}