#include "snake.h"

snake::snake(int Max_length)
{
	MAX_size = Max_length;

	snake_info = new snake_data[MAX_size + 1];
}

snake::~snake()
{
	delete[] snake_info;
}

void snake::reSetSnake(Game_map * a_map)
{
	IfDead = false;

	snake_info[0].part_X = a_map->Getheight() - 1;
	snake_info[0].part_Y = a_map-> Getwidth() - 1;
	snake_info[0].direction = LEFT;
	snake_info[0].part = tail_left;
	a_map->setSnakeData(_Snake_, a_map->Getheight() - 1, a_map->Getwidth() - 1);

	snake_info[1].part_X = a_map->Getheight() - 1;
	snake_info[1].part_Y = a_map->Getwidth() - 2;
	snake_info[1].direction = LEFT;
	snake_info[1].part = body_left;
	a_map->setSnakeData(_Snake_, a_map->Getheight() - 1, a_map->Getwidth() - 2);

	snake_info[2].part_X = a_map->Getheight() - 1;
	snake_info[2].part_Y = a_map->Getwidth() - 3;
	snake_info[2].direction = LEFT;
	snake_info[2].part = body_left;
	a_map->setSnakeData(_Snake_, a_map->Getheight() - 1, a_map->Getwidth() - 3);

	snake_info[3].part_X = a_map->Getheight() - 1;
	snake_info[3].part_Y = a_map->Getwidth() - 4;
	snake_info[3].direction = LEFT;
	snake_info[3].part = head_left;
	a_map->setSnakeData(_Snake_, a_map->Getheight() - 1, a_map->Getwidth() - 4);

	head = 4;
	tail = 0;
}

void snake::snake_eat_food(int come_about)
{
	snake_info[head] = snake_info[(head + MAX_size) % (MAX_size + 1)];

	switch (snake_info[head].direction)
	{
	case LEFT:
		snake_info[head].part_Y--;
		snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_left;
		snake_info[(head + MAX_size) % (MAX_size + 1)].direction = LEFT;
		break;
	case TOP:
		snake_info[head].part_X--;
		snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_top;
		snake_info[(head + MAX_size) % (MAX_size + 1)].direction = TOP;
		break;
	case RIGHT:
		snake_info[head].part_Y++;
		snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_right;
		snake_info[(head + MAX_size) % (MAX_size + 1)].direction = RIGHT;
		break;
	case BOTTOM:
		snake_info[head].part_X++;
		snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_bottom;
		snake_info[(head + MAX_size) % (MAX_size + 1)].direction = BOTTOM;
		break;
	}
	switch (come_about)
	{
	case 0:
		//nothing
		break;
	default:
		snake_info[(head + MAX_size) % (MAX_size + 1)].part = come_about;
	}
	head = (head + 1) % (MAX_size + 1);
}

void snake::snake_eat_tail()
{
}

bool snake::move_possibility(int targetX, int targetY, Game_map* a_map)
{
	if (targetX < 0 || targetY < 0 || targetX == a_map->Getheight() || targetY == a_map->Getwidth())
		return false;
	else
		if (a_map->GetpointData(targetX, targetY) == _Stone_ + 1)
			return false;

	return true;
}

void snake::snake_move(Game_map* a_map)
{
	bool ok = false;
	switch (snake_info[(head + MAX_size) % (MAX_size + 1)].direction)
	{
	case LEFT:
		ok = ifEat(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y - 1, a_map);
		break;
	case TOP:
		ok = ifEat(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X - 1, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y, a_map);
		break;
	case RIGHT:
		ok = ifEat(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y + 1, a_map);
		break;
	case BOTTOM:
		ok = ifEat(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X + 1, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y, a_map);
		break;
	}

	if (ok)
	{
		snake_eat_food(0);
		a_map->snake_eat_food();
	}
	else
	{
		ok = false;

		switch (snake_info[(head + MAX_size) % (MAX_size + 1)].direction)
		{
		case LEFT:
			ok = move_possibility(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y - 1, a_map);
			break;
		case TOP:
			ok = move_possibility(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X - 1, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y, a_map);
			break;
		case RIGHT:
			ok = move_possibility(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y + 1, a_map);
			break;
		case BOTTOM:
			ok = move_possibility(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X + 1, snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y, a_map);
			break;
		}
		if (ok)
		{
			snake_info[head] = snake_info[(head + MAX_size) % (MAX_size + 1)];

			switch (snake_info[head].direction)
			{
			case LEFT:
				snake_info[head].part_Y--;
				snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_left;
				break;
			case TOP:
				snake_info[head].part_X--;
				snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_top;
				break;
			case RIGHT:
				snake_info[head].part_Y++;
				snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_right;
				break;
			case BOTTOM:
				snake_info[head].part_X++;
				snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_bottom;
				break;
			}


			a_map->setSnakeData(_Snake_, snake_info[head].part_X, snake_info[head].part_Y);
			head = (head + 1) % (MAX_size + 1);
			a_map->setSnakeData(0, snake_info[tail].part_X, snake_info[tail].part_Y);
			tail = (tail + 1) % (MAX_size + 1);

			switch (snake_info[tail].direction)
			{
			case LEFT:
				snake_info[tail].part = tail_left;
				break;
			case TOP:
				snake_info[tail].part = tail_top;
				break;
			case RIGHT:
				snake_info[tail].part = tail_right;
				break;
			case BOTTOM:
				snake_info[tail].part = tail_bottom;
				break;
			}
		}
		else
		{
			IfDead = true;
		}
	}
}

void snake::snake_alter_direction(int direction, Game_map* a_map)
{
	if ((snake_info[(head + MAX_size) % (MAX_size + 1)].direction == direction)
		|| (snake_info[(head + MAX_size) % (MAX_size + 1)].direction == LEFT && direction == RIGHT)
		|| (snake_info[(head + MAX_size) % (MAX_size + 1)].direction == RIGHT && direction == LEFT)
		|| (snake_info[(head + MAX_size) % (MAX_size + 1)].direction == TOP && direction == BOTTOM)
		|| (snake_info[(head + MAX_size) % (MAX_size + 1)].direction == BOTTOM && direction == TOP))
		return;

	if(snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y == 0&& direction == LEFT)return;
	else
		if(snake_info[(head + MAX_size) % (MAX_size + 1)].part_Y == a_map->Getwidth()-1 && direction == RIGHT)return;
		else
			if(snake_info[(head + MAX_size) % (MAX_size + 1)].part_X == 0 && direction == TOP)return;
			else
				if (snake_info[(head + MAX_size) % (MAX_size + 1)].part_X == a_map->Getheight() - 1 && direction == BOTTOM)return;


	int old_direction = snake_info[(head + MAX_size) % (MAX_size + 1)].direction;
	snake_info[head] = snake_info[(head + MAX_size) % (MAX_size + 1)];
	snake_info[(head + MAX_size) % (MAX_size + 1)].direction = snake_info[head].direction = direction;


	switch (old_direction)//获得身体
	{
	case LEFT:
		if (direction == TOP)
		{
			snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_right_top;
			snake_info[head].part_X--;
			snake_info[head].part = head_top;
		}
		else
			if (direction == BOTTOM)
			{
				snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_right_bottom;
				snake_info[head].part_X++;
				snake_info[head].part = head_bottom;
			}
		break;
	case TOP:
		if (direction == LEFT)
		{
			snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_left_bottom;
			snake_info[head].part_Y--;
			snake_info[head].part = head_left;
		}
		else
			if (direction == RIGHT)
			{
				snake_info[(head + MAX_size) % (MAX_size + 1)].part = body_right_bottom;
				snake_info[head].part_Y++;
				snake_info[head].part = head_right;
			}
		break;
	case RIGHT:
		if (direction == TOP)
		{
			snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_left_top;
			snake_info[head].part_X--;
			snake_info[head].part = head_top;
		}
		else
			if (direction == BOTTOM)
			{
				snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_left_bottom;
				snake_info[head].part_X++;
				snake_info[head].part = head_bottom;
			}
		break;
	case BOTTOM:
		if (direction == LEFT)
		{
			snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_left_top;
			snake_info[head].part_Y--;
			snake_info[head].part = head_left;
		}
		else
			if (direction == RIGHT)
			{
				snake_info[(head + MAX_size) % (MAX_size + 1)].part  = body_right_top;
				snake_info[head].part_Y++;
				snake_info[head].part = head_right;
			}
		break;
	}

	if (ifEat(snake_info[head % (MAX_size + 1)].part_X, snake_info[head % (MAX_size + 1)].part_Y, a_map))
	{
		a_map->snake_eat_food();
	}
	else
	{
		if (a_map->GetpointData(snake_info[tail].part_X, snake_info[tail].part_Y) <= 0)
		a_map->setSnakeData(0, snake_info[tail].part_X, snake_info[tail].part_Y);
		tail = (tail + 1) % (MAX_size + 1);
	}
	a_map->setSnakeData(_Snake_, snake_info[head].part_X, snake_info[head].part_Y);
	head = (head + 1) % (MAX_size + 1);

	switch (snake_info[tail].direction)
	{
	case LEFT:
		snake_info[tail].part = tail_left;
		break;
	case TOP:
		snake_info[tail].part = tail_top;
		break;
	case RIGHT:
		snake_info[tail].part = tail_right;
		break;
	case BOTTOM:
		snake_info[tail].part = tail_bottom;
		break;
	}

}

bool snake::ifEat(int targetX, int targetY, Game_map * a_map)
{
	if (targetX < 0 || targetY < 0 || targetX == a_map->Getheight() || targetY == a_map->Getwidth())
		return false;

	if (0 < a_map->GetpointData(targetX, targetY) && a_map->GetpointData(targetX, targetY) <= FoodType)
	{
		a_map->setSnakeData(-1, targetX, targetY);
		return true;
	}

	return false;
}

bool snake::GetIfDead()
{
	return IfDead;
}

int snake::GetHead()
{
	return head;
}

int snake::GetTail()
{
	return tail;
}

snake_data * snake::GetInfo()
{
	return snake_info;
}
