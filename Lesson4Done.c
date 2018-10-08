#include <stdio.h>
#include <math.h>
#define N 5
#define M 5
//Анна Зубкова
//Урок 4.
//Задача 3.
//3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.
//Здесь алгоритм решения такой же как и в задаче о 8 ферзях. Разница только в проверке положения коня.

//Создаем шахматную доску
int board[N][M];
// Набор возможных ходов коня (координаты для перемещения буквой "Г")
int HorseSteps [8][2]= {

	    { -1, -2 },
	    { -2, -1 },
	    { -2, 1 },
	    { -1, 2 },
	    { 1, 2 },
	    { 2, 1 },
	    { 2, -1 },
	    { 1, -2 }
};

int SearchSolution(int x, int y, int counter);
int checkrun(int x, int y);
void Print(int n, int m, int a[N][M]);
void Zero(int n, int m, int a[N][M]);


int main()
{
	//Изначально на доске одни 0 - непройденные точки коня
	Zero(N,M,board);
	//Вызываем функцию, координату первой позиции коня задаем сами (то есть место, с которого он начнет обход)
	SearchSolution(1,1,1);
	printf("\n\n");
	//Выводим путешествие коня по доске на экран
	Print(N,M,board);
	return 0;
}
//Поиск пути коня по доске
int SearchSolution(int x, int y, int counter)
{

	//Проверяем координату клетки (что она находится в пределах доски)
	if (checkrun(x, y)==0) return 0;
	//Конь использовал все клетки, проход закончен
	if (counter>N*M) return 1;

//Цикл проверки текущего и следующего хода коня
	for (int i=0; i<8; i++)
	{
		//Если клетка пустая
			if (board[x][y]==0)
		{
		//Теперь здесь стоит конь
			board[x][y]=counter;
			//Прогоняем его по следующим возможным шагам
			int xmove=x+HorseSteps[i][0];
			int ymove=y+HorseSteps[i][1];
			//Важно убедиться, что после этого шага есть еще и следующий (по сути метод Эйлера, ищем тупиковые ходы заранее, чтобы в них не попадать)
			if (SearchSolution(xmove, ymove, counter+1))
				return 1;
			board[x][y]=0;
		}
	}
	return 0;
}

//Функция проверки клетки на доске - находится ли она в ее пределах
int checkrun(int x, int y)
{
	if (x<0 || y<0 || x>=N || y>=M)
		return 0;
	return 1;
}

void Print(int n, int m, int a[N][M])
 {
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<m;j++)
			printf("%4d", a[i][j]);
		printf("\n");
	}
 }

void Zero(int n, int m, int a[N][M])
{
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			a[i][j] = 0;
}

