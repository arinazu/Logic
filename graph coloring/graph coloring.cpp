#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct S
{
	int n;							//Номер вершины (0..N-1)
	int p;							//Степень вершины (0..N-1)
};

int N;								//Количество вершин
int** V = NULL;						//Матрица смежности [N][N]
S* Q = NULL;						//Массив вершин [N]
int* R = NULL;						//Массив цветов вершин [N]
int X;								//Хроматическое число

void random_V();
void load_V();
void print_V(FILE *f);

void make_Q();
void print_Q(FILE* f);
int compare_Q(const void* p1, const void* p2);

void make_R();
int adj(int n, int r);
void print_R(FILE* f);

void save();
void free_All();


int main()
{
	setlocale(LC_ALL, "Russian");
	//srand(time(NULL));

	while (1)
	{
		printf("\nНажмите клавишу для выбора действия:\n");
		printf("<L> - загрузить файл\n<R> - случайный граф\n<S> - сохранить результат в файл\n<ESC> - выход\n");
		int c = _getch();
		if (c == 27)									// esc
		{
			break;
		}
		else if ((c == 'R') || (c == 'r'))				// R, r
		{
			free_All();
			random_V();
			print_V(stdout);
			make_Q();
			print_Q(stdout);
			make_R();
			print_R(stdout);
		}
		else if ((c == 'L') || (c == 'l'))				// L, l
		{
			free_All();
			load_V();
			print_V(stdout);
			make_Q();
			print_Q(stdout);
			make_R();
			print_R(stdout);
		}
		else if ((c == 'S') || (c == 's'))				// S, s
		{
			save();
		}
	}
	free_All();
	return 0;
}

//Формирование графа случайным образом (матрицы смежности)
void random_V()
{
	while (1)
	{
		printf("Введите количество вершин графа (2-100): ");
		scanf("%d", &N);
		if ((N >= 2) && (N <= 100))
		{
			break;
		}
	}

	printf("\n");

	V = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) V[i] = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			if (i == j) {					
				V[i][j] = 0;
			}

			else {							
				V[i][j] = rand() % 2;
				V[j][i] = V[i][j];
			}
		}
	}

}

//Загрузка графа из файла
void load_V()
{
	char fname[20];
	printf("Введите имя файла: ");
	scanf("%s", fname);
	strcat(fname, ".input");

	FILE* f;
	f = fopen(fname, "r");
	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}
	
	fscanf(f, "%d", &N);

	if ((N < 2) || (N > 100))
	{
		printf("Недопустимое количество вершин графа\n");
		fclose(f);
		return;
	}
	printf("Количество вершин графа: %d\n", N);

	V = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) V[i] = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fscanf(f, "%d", &V[i][j]);
		}
	}

	fclose(f);
}

//Вывод матрицы смежности
void print_V(FILE* f)
{
	fprintf(f, "Матрица смежности:\n");
	fprintf(f, "   ");
	for (int i = 0; i < N; i++)
		fprintf(f, "%3d", i);
	fprintf(f, "\n");

	for (int i = 0; i < N; i++)
	{
		fprintf(f, "%3d", i);
		for (int j = 0; j < N; j++)
		{
			fprintf(f, "%3d", V[i][j]);
		}
		fprintf(f, "\n");
	}
}

//Создание упорядоченного по степени массива вершин
void make_Q()
{
	Q = (S*)malloc(sizeof(S) * N);
	for (int i = 0; i < N; i++)
	{
		Q[i].n = i;
		Q[i].p = 0;
		for (int j = 0; j < N; j++)
		{
			if (V[i][j] == 1)
			{
				Q[i].p ++;
			}
		}
	}
	qsort(Q, N, sizeof(S), compare_Q);
}

//Вывод массива вершин
void print_Q(FILE* f)
{
	fprintf(f, "Вершины по убыванию степени:\n");
	for (int i = 0; i < N; i++)
		fprintf(f, "%d ", Q[i].n);
	fprintf(f, "\n");
}

//Функция сравнения элементов массива вершин
int compare_Q(const void* p1, const void* p2)   
{
	S* s1 = (S*)p1;
	S* s2 = (S*)p2;
	if (s1->p < s2->p)
		return 1;
	if (s1->p > s2->p)
		return -1;
	return 0;
}

//Создание массива цветов
void make_R()
{
	R = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++)
	{
		R[i] = 0;
	}
	X = 0;

	for (int q = 0; q < N; q++)
	{
		int u = Q[q].n;
		int r = 1;
		while (adj(u, r) != 0)
		{
			r++;
		}
		R[u] = r;
		if (r > X)
		{
			X = r;
		}
	}
}

//Функция определения смежности
int adj(int n, int r)
{
	for (int i = 0; i < N; i++)
	{
		if (((V[n][i]) == 1) && (R[i] == r))
		{
			return 1;
		}
	}
	return 0;
}

//Вывод массива цветов
void print_R(FILE* f)
{
	HANDLE ho = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;					//структура
	GetConsoleScreenBufferInfo(ho, &csbi);
	
	fprintf(f, "Цвета вершин:\n");
	for (int i = 0; i < N; i++)
	{
		SetConsoleTextAttribute(ho, csbi.wAttributes);
		fprintf(f, "Вершина %d,", i);
		SetConsoleTextAttribute(ho, R[i]);
		fprintf(f, " цвет %d\n", R[i]);
	}
	SetConsoleTextAttribute(ho, csbi.wAttributes);
	fprintf(f, "\n");
	fprintf(f, "Хроматическое число графа = %d\n", X);
}

//Сохранение результатов в файл
void save()
{
	char fname[20];
	printf("Введите имя файла для сохранения результата: ");
	scanf("%s", fname);
	strcat(fname, ".output");

	FILE* f;
	f = fopen(fname, "w");
	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return;
	}
	print_V(f);
	print_Q(f);
	print_R(f);
	
	fclose(f);
	printf("Файл сохранен\n");
}

//Освобождение памяти
void free_All()
{
	if (V != NULL)
	{
		for (int i = 0; i < N; ++i) free(V[i]);
		free(V);
		V = NULL;
	}
	if (Q != NULL)
	{
		free(Q);
		Q = NULL;
	}
	if (R != NULL)
	{
		free(R);
		R = NULL;
	}
}
