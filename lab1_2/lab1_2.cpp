#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

struct Student
{
    int num;
    char firstname[20];
    char name[20];
    char faculty[20];
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    //Задание 3 + Задание 5. Ввод массива произвольного размера и поиск структур
   
    printf("Задание 3 + Задание 5. Ввод массива произвольного размера и поиск структур\n");

    int n;
    printf("Введите количество студентов:");
    scanf("%d", &n);

    Student* a;
    a = (Student*)malloc(n * sizeof(Student));

    for (int i = 0; i < n; i++)
    {
        a[i].num = 100 + i;                             
        snprintf(a[i].firstname, 20, "Фамилия%d", i);
        snprintf(a[i].name, 20, "Имя%d", i);
        snprintf(a[i].faculty, 20, "Факультет%d", i);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%4d", a[i].num);
        printf("%15s", a[i].firstname);
        printf("%15s", a[i].name);
        printf("%20s", a[i].faculty);
        printf("\n");
    }

    int m;
    printf("\n");
    printf("Введите номер зачетки: ");
    scanf("%d", &m);

    for (int i = 0; i < n; i++)
    {
        if (m == a[i].num)
        {
            printf("%4d", a[i].num);
            printf("%15s", a[i].firstname);
            printf("%15s", a[i].name);
            printf("%20s", a[i].faculty);
            printf("\n");
        }
    }

    free(a);
    return 0;
}