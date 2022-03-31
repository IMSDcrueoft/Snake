#pragma once
#include<stdlib.h>
#define FoodType 1
#define TryRand 5


#define _Snake_ -1
//#define _Food1_ 0
//#define _Food2_ 1
#define _Stone_ 2

class Game_map
{
private:
	int **lawn = nullptr;
	int food_left = 0;

	int width = 0;
	int height = 0;
public:
	Game_map(int width,int height);
	~Game_map();

	void Clear_map();

	int GetFood_left();

	bool setItem(int item, int x, int y);
	void setSnakeData(int item, int x, int y);
	int GetpointData(int X, int Y);
	bool spawn_food(int amount);
	void snake_eat_food();

	int Getwidth();
	int Getheight();
};
