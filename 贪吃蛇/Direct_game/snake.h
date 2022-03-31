#pragma once
#include"Game_map.h"

#define head_left		0
#define head_top		4
#define head_right		8
#define head_bottom		12

#define body_left		1
#define body_top		5
#define body_right		9
#define body_bottom		13

#define body_left_bottom	2
#define body_left_top		6
#define body_right_top		10
#define body_right_bottom	14

#define keep	0

#define tail_left		3
#define tail_top		7
#define tail_right		11
#define tail_bottom		15

#define LEFT		1
#define TOP			2
#define RIGHT		3
#define BOTTOM		4

struct snake_data
{
	int part_X;
	int part_Y;
	int part;
	int direction;
};
class snake
{
private:
	bool IfDead = false;

	int recovery_capbility=0;

	int MAX_size = 0;

	int head = 0;
	int tail = 0;

	snake_data* snake_info = nullptr;
public:
	snake(int Max_length);
	~snake();

	void reSetSnake(Game_map * a_map);
	void snake_eat_food(int come_about);
	void snake_eat_tail();

	bool move_possibility(int targetX,int targetY, Game_map * a_map);
	void snake_move(Game_map * a_map);
	void snake_alter_direction(int direction, Game_map* a_map);
	bool ifEat(int targetX, int targetY, Game_map* a_map);

	bool GetIfDead();

	int GetHead();
	int GetTail();
	snake_data* GetInfo();

};