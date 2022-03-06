#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include<conio.h>
using namespace std;

struct point
{
	int x;
	int y;
};

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displaysnake(point p[], int size)
{
	int index;
	gotoxy(p[0].x, p[0].y);
	cout << "O";
	for (index = 1; index < size; index++)
	{
		gotoxy(p[index].x, p[index].y);
		cout << "o";
	}
}

void removesnake(point p[], int size)
{
	int index;
	for (index = 0; index < size; index++)
	{
		gotoxy(p[index].x, p[index].y);
		cout << " ";
	}
}

void moveup(point p[], int size)
{
	int index;
	for (index = size - 1; index > 0; index--)
	{
		p[index].x = p[index - 1].x;
		p[index].y = p[index - 1].y;
	}
	p[index].y = p[index].y - 1;
}

void movedown(point p[], int size)
{
	int index;
	for (index = size - 1; index > 0; index--)
	{
		p[index].x = p[index - 1].x;
		p[index].y = p[index - 1].y;
	}
	p[index].y = p[index].y + 1;
}

void moveright(point p[], int size)
{
	int index;
	for (index = size - 1; index > 0; index--)
	{
		p[index].x = p[index - 1].x;
		p[index].y = p[index - 1].y;
	}
	p[index].x = p[index].x + 1;
}

void moveleft(point p[], int size)
{
	int index;
	for (index = size - 1; index > 0; index--)
	{
		p[index].x = p[index - 1].x;
		p[index].y = p[index - 1].y;
	}
	p[index].x = p[index].x - 1;
}

void movement(char input, point p[], int size)
{
	if (input == 'w')
	{
		moveup(p, size);
	}
	else if (input == 's')
	{
		movedown(p, size);
	}
	else if (input == 'd')
	{
		moveright(p, size);
	}
	else if (input == 'a')
	{
		moveleft(p, size);
	}
}

void checkkeywords(point p[], int n, char lastinput, char input)
{
	if (lastinput == 'd' && input == 'a')
	{
		movedown(p, n);
	}
	else if (lastinput == 'a' && input == 'd')
	{
		moveup(p, n);
	}
	else if (lastinput == 'w' && input == 's')
	{
		moveleft(p, n);
	}
	else if (lastinput == 's' && input == 'w')
	{
		moveright(p, n);
	}
}

int gameoverbyhisbody(point p[], int size)
{
	int i;
	for (i = 1; i < size; i++)
	{
		if (p[0].x == p[i].x && p[0].y == p[i].y)
		{
			return 1;
		}
	}
	return 0;
}

int gameoverbyboundary(point p[])
{
	if (p[0].x >= 82)
	{
		return 1;
	}
	if (p[0].x <= 0)
	{
		return 1;
	}
	if (p[0].y >= 26)
	{
		return 1;
	}
	if (p[0].y <= 0)
	{
		return 1;
	}
	return 0;
}

int checksnakepoints(point p[], int size, int a, int b)
{
	for (int i = 0; i < size; i++)
	{
		if (a == p[i].x && b == p[i].y)
		{
			return 1;
		}
	}
	return 0;
}

int gameoverbyhurdle(point p[], point hurdle[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (p[0].x == hurdle[i].x && p[0].y == hurdle[i].y)
		{
			return 1;
		}
	}
	return 0;
}

int avoidfoodgeneratingonhurdlepoints(point hurdle[], int a, int b, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (a == hurdle[i].x && b == hurdle[i].y)
		{
			return 1;
		}
	}
	return 0;
}

int generatefood(point p[], point hurdle[], int& size, int& a, int& b, int c, int& score, int& speed, int count)
{
	int z, g;
	if (c == 1)
	{
		a = rand() % 81 + 1;
		b = rand() % 25 + 1;
		z = avoidfoodgeneratingonhurdlepoints(hurdle, a, b, count);
		if (z == 1)
		{
			return 1;
		}
		g = checksnakepoints(p, size, a, b);
		if (g == 1)
		{
			return 1;
		}
		gotoxy(a, b);
		cout << "F";
	}
	if (p[0].x == a && p[0].y == b)
	{
		size++;
		score = score + 10;
		speed = speed - 80;
		return 1;
	}
	return 0;
}

void storepoints(point p[], int size)
{
	int index;
	int x = 5; int y = 10;
	for (index = 0; index < size; index++)
	{
		p[index].x = x;
		p[index].y = y;
		y++;
	}
}
void drawhurdle(point hurdle[], int& count)
{
	char input = 220, input1 = 219;
	for (int x = 14; x < 69; x++)
	{
		hurdle[count].x = x;
		hurdle[count].y = 4;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input;
		count++;
	}
	for (int y = 5; y < 9; y++)
	{
		hurdle[count].x = 14;
		hurdle[count].y = y;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input1;
		count++;
	}
	for (int y = 5; y < 9; y++)
	{
		hurdle[count].x = 68;
		hurdle[count].y = y;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input1;
		count++;
	}
	for (int x = 14; x < 68; x++)
	{
		hurdle[count].x = x;
		hurdle[count].y = 21;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input;
		count++;
	}
	for (int y = 18; y < 22; y++)
	{
		hurdle[count].x = 14;
		hurdle[count].y = y;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input1;
		count++;
	}
	for (int y = 18; y < 22; y++)
	{
		hurdle[count].x = 68;
		hurdle[count].y = y;
		gotoxy(hurdle[count].x, hurdle[count].y);
		cout << input1;
		count++;
	}
}

void makeboundary()
{
	int x = 0, y = 0;
	for (int y = 1; y <= 26; y++)
	{
		gotoxy(x, y);
		cout << "#";
	}
	for (int y = 0; y <= 82; y++)
	{
		gotoxy(y, x);
		cout << "#";
	}
	for (int y = 1; y <= 26; y++)
	{
		gotoxy(82, y);
		cout << "#";
	}
	for (int y = 0; y <= 82; y++)
	{
		gotoxy(y, 26);
		cout << "#";
	}
}

void startgame()
{
	int x;
	cout << endl << endl;
	cout << "\t\t\t\t\tWelcome To PT Snake Game Project" << endl << endl;
	cout << "\n\n\tFALL2020 BSCS" << endl << "\tSECTION B" << endl << "\tGroup 1" << endl << "\tAbdullah Shahzad (010)" << endl << "\tDaniyal Khalid (046)" << endl << "\tMusab Rizwan (053)" << endl << endl << endl;
	cout << "\tInstructions" << endl << endl << endl;
	cout << "\tUSE \b W to moveup, \b S to move down, \b D to move right, \b A to move left" << endl << endl << endl;
	cout << "\tPress anykey and Enter to Start Game: ";
	cin >> x;
	system("cls");
}

int main()
{
	system("color 3");
	startgame();
	int a, b, c = 1, score = 0, z, j, siz = 5, speed = 800, w, count = 0;
	char input = 'd'; char lastinput;
	point p[100], hurdle[200];
	storepoints(p, siz);
	makeboundary();
	drawhurdle(hurdle, count);
	while (1)
	{
		if (_kbhit())
		{
			lastinput = input;
			input = _getch();
			checkkeywords(p, siz, lastinput, input);
		}
		displaysnake(p, siz);
		if (speed < 100)
		{
			speed = 100;
		}
		Sleep(speed);
		removesnake(p, siz);
		c = generatefood(p, hurdle, siz, a, b, c, score, speed, count);
		gotoxy(0, 27);
		cout << "score:" << score;
		movement(input, p, siz);
		z = gameoverbyboundary(p);
		if (z == 1)
		{
			break;
		}
		j = gameoverbyhisbody(p, siz);
		if (j == 1)
		{
			break;
		}
		w = gameoverbyhurdle(p, hurdle, count);
		if (w == 1)
		{
			break;
		}
	}
	displaysnake(p, siz);
	gotoxy(0, 28);
	cout << "game over" << endl << "your score is " << score << endl;
}