#include <stdio.h>

int main()
{
    int numar;
    int factorial=1;
    printf("Introdu numarul: ");
    scanf("%d", &numar);
    if(numar>1 && numar <10)
    {
        for(int i=1;i<=numar;i++)
        {
            factorial=factorial*i;
        }
    }
    else
    {
        printf("Alege un numar intre 1 si 10\n");
    }
    printf("Factorialul numarului: %d este %d\n",numar,factorial);
    return 0;
}
