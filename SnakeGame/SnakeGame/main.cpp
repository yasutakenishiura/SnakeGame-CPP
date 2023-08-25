#include <iostream>
#include<conio.h>
#include <Windows.h>

using namespace std;
bool gameOver;
const int width = 20;
const int heigth = 20;
int x, y, FruitX, FruitY, Score;
int TailX[100], TailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = heigth / 2;
	FruitX = rand() % width;
	FruitY = rand() % heigth;
	Score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < heigth; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == FruitY && j == FruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << Score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}

	}
}
void Logic()
{
	int prevX = TailX[0];
	int prevY = TailY[0];
	int prev2x, prev2Y;
	TailX[0] = x;
	TailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2x = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2x;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= heigth) y = 0; else if (y < 0) y = heigth - 1;
	for (int i = 0; i < nTail; i++)
		if (TailX[i] == x && TailY[i] == y)
			gameOver = true;
	if (x == FruitX && y == FruitY)
	{
		Score += 10;
		FruitX = rand() % width;
		FruitY = rand() % heigth;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(60);
	}
	return 0;
}
