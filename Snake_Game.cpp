#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

int width;
int height;
int score;
int speed;
pair<int, int> header_position;
pair<int, int> target_position;
vector<pair<int, int>> tail;
bool game_over = false;
enum dir { PAUSE, DOWN, LEFT, RIGHT, UP };
dir direction;


void setup_game();
void print_map();
void get_input();
void judge_movement();
void game_setting();
int main()
{
	game_setting();
	setup_game();
	while (!game_over)
	{
		print_map();
		get_input();
		judge_movement();
		Sleep(speed);
	}
	cout << endl << "Your score is : " << score << endl;
    return 0;
}

void game_setting()
{
	int size, speed_factor;
	cout << "Enter a number that represent the map size (number should between 1 and 10)  ";
	cin >> size;
	height = size * 5;
	width = height * 1.2;
	cout << "Enter a number that represent the moving speed (number should between 1 and 10)  ";
	cin >> speed_factor;
	speed = (10 - speed_factor) * 50;
}

void setup_game()
{
	srand(time(NULL));
	score = 0;
	header_position.first = height / 2;
	header_position.second = width / 2;
	target_position.first = (rand() % (height - 2)) + 1;
	target_position.second = (rand() % (width - 2)) + 1;
	while (target_position.first == header_position.first&&target_position.second == header_position.second)
	{
		target_position.first = rand() % height;
		target_position.second = rand() % width;
	}
}

void print_map()
{
	system("cls");
	for (int a = 0; a < height; a++)
	{
		for (int b = 0; b < width; b++)
		{
			if (a == 0 || a == height - 1 || b == 0 || b == width - 1)
				printf("%c", '#');
			else if (a == header_position.first&&b == header_position.second)
				printf("%c", 'O');
			else if (a == target_position.first&&b == target_position.second)
				printf("%c", 'X');
			else
			{
				bool print_check = true;
				for (auto position : tail)
				{
					if (a == position.first&&b == position.second)
					{
						cout << "0";
						print_check = false;
					}
				}
				if (print_check)
					printf(" ");
			}

			
			
		}
		cout << endl;
	}
}

void get_input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			direction = UP;
			break;
		case 's':
			direction = DOWN;
			break;
		case 'a':
			direction = LEFT;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'p':
			direction = PAUSE;
			break;
		default:
			break;
		}
	}
}

void judge_movement()
{
	auto header_copy = header_position;
	switch (direction)
	{
	case UP:
		header_position.first--;
		break;
	case DOWN:
		header_position.first++;
		break;
	case LEFT:
		header_position.second--;
		break;
	case RIGHT:
		header_position.second++;
		break;
	case PAUSE:
		break;
	}
	for (auto position : tail)
	{
		if (header_position.first == position.first&&header_position.second == position.second)
			game_over = true;
	}
	if (header_position.first == 0 || header_position.first == height - 1)
		game_over = true;
	if (header_position.second == 0 || header_position.second == width - 1)
		game_over = true;
	if (header_position.first == target_position.first&&header_position.second == target_position.second)
	{
		target_position.first = (rand() % (height - 2)) + 1;
		target_position.second = (rand() % (width - 2)) + 1;
		score++;
		tail.resize(tail.size() + 1);
	}
	pair<int, int> tail_copy;
	for (int i = 0; i < tail.size(); i++)
	{
		if (i == 0)
		{
			tail_copy = tail[i];
			tail[i] = header_copy;
			continue;
		}
		swap(tail_copy, tail[i]);
	}
}
