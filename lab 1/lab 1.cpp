#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    //srand(time(NULL));

    int a[5][5];

    //Задание 2. Инициализация массива случайными числами

    printf("Задание 2. Инициализация массива случайными числами\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {

            a[i][j] = rand() - rand();
            printf("%8d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //Задание 1. Разница между макс и мин элементами массива

    printf("Задание 1. Разница между макс и мин элементами массива\n");
    
    int max = a[0][0];
    int min = a[0][0];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (max < a[i][j])
            {
                max = a[i][j];
            }
            if (min > a[i][j])
            {
                min = a[i][j];
            }
        }
    }
    
    int d = max - min;
    printf("max = %d, min = %d, разность = %d\n", max, min, d);

    printf("\n");

    //Задание 4. Сумма значений каждой строки двумерного массива

    printf("Задание 4. Сумма значений каждой строки двумерного массива\n");

    int sum;
    for (int i = 0; i < 5; i++)
    {
        sum = 0;
        for (int j = 0; j < 5; j++)
        {
            sum += a[i][j];
        }
        printf("строка %d = %d \n", i, sum);
    }
    return 0;
}