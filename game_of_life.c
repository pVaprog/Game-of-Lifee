#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h> 

//создаём константы длины и ширины поля
#define h 15
#define w 15

//создаём поле, образованное константами
int mas[h][w];

//описываем приоритеты функций
void setcur(int x, int y);
void show();
void newShow();
void updateStatus();

//основная часть программы
int main()
{
    int i;
    printf("Number of generations: "); //спрашваем у пользователя кол-во поколений
    scanf("%d", &i); //считываем введённое значение
    system("cls");  //очищаем консоль
    newShow();  //генерируем начальное поле
    for (i; i > 0; i--)  //сколько поколений - столько раз и будет выполнен цикл
    {
            updateStatus();
            show();
    }

	return 0;
}


//используем функцию для установки положения курсора в консоле
void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//создаем живые организмы в виде "*"
void show()
{
    setcur(0, 0); //возвращаем курсор в начало поля
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (mas[i][j] == 1)
                printf("*");  //живой организм
            else
                printf(" ");  //мертвый организм
        }
        printf("\n");
    }
    Sleep(100);
}

//генерируется рандомное местоположение живых и мертвых организмов
void newShow()
{
    srand(time(NULL));
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            mas[i][j] = rand() % 2;
    show();
}


//правила игры в жизнь
void updateStatus()
{
    show();
    int FolksCount;
    int copy[h][w];  //поле, которое изменяется в соответствии с правилами игы
    //рассчитываем кол-во соседей, и по нему смотрим выживет или погибнет организм
    for (int i = 1; i < h; i++)
    {
        for (int j = 1; j < w; j++)
        {
            FolksCount = mas[i - 1][j - 1] + mas[i - 1][j] + mas[i - 1][j + 1] + mas[i][j - 1] + mas[i][j + 1] + mas[i + 1][j - 1] + mas[i + 1][j] + mas[i + 1][j + 1];
            if (FolksCount == 3)
                copy[i][j] = 1;
            else if (FolksCount == 2)
                copy[i][j] = mas[i][j];
            else
                copy[i][j] = 0;
        }
    }

    //заменяем прошлое поле на новое с учётом местоположения соседей
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            mas[i][j] = copy[i][j];
}