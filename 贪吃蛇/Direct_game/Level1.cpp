#include "Level1.h"
#include "game_controller.h"
#include "../Resource.h"

void Level1::Load()
{
	sprites1 = new SpriteSheet(L"../game_res/grass_rock.myres", graphics);
	sprites2 = new SpriteSheet(L"../game_res/snake_.myres", graphics, sprite_width, sprite_height);
	sprites3 = new SpriteSheet(L"../game_res/items.myres", graphics, sprite_width, sprite_height);

	frame = 0;
	StartX = DrawX;
	StartY = DrawY;

	a_map = new Game_map(18, 11);
	a_snake = new snake(18 * 11);
	

	//������ʼ��
	a_snake->reSetSnake(a_map);
	a_map->spawn_food(2);
}
void Level1::Unload()
{
	delete sprites1;
	delete sprites2;
	delete a_map;
	delete a_snake;

	sprites1 = NULL;
	sprites2 = NULL;
	a_map = NULL;
	a_snake = NULL;
}
void Level1::Render()
{
	sprites1->Draw();

	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 18; j++)
			if (a_map->GetpointData(i, j) > 0)
			{
				sprites3->Draw(a_map->GetpointData(i, j) - 1, StartX + sprite_width * j, StartY + sprite_height * i, 1);
			}

	for (int it = a_snake->GetTail(); a_snake->GetHead() != it; it = (it + 1) % (18 * 11 + 1))
	{
		sprites2->Draw(a_snake->GetInfo()[it].part, StartX + a_snake->GetInfo()[it].part_Y*sprite_width, StartY + a_snake->GetInfo()[it].part_X*sprite_height, 1);
	}

	if (a_snake->GetIfDead())
	{
		MessageBox(hWnd, L"贪吃的蛇死了", L"重新开始吧", 0);

		a_map->~Game_map();
		a_snake->~snake();

		a_map = new Game_map(18, 11);
		a_snake = new snake(18 * 11);


		//������ʼ��
		a_snake->reSetSnake(a_map);
		a_map->spawn_food(2);
	}
}
void Level1::Update()//��ʱ�ò���
{
	frame++;

	if (frame >= 25)
	{
		srand((unsigned int)time(0));//////;

		frame %= 25;
		a_snake->snake_move(a_map);
	}
}
void Level1::ReStartLevel()
{

}

void Level1::KEY_ARROW(int direction)
{
	a_snake->snake_alter_direction(direction, a_map);
}
