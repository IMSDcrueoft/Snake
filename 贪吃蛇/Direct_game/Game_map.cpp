#include"Game_map.h"

Game_map::Game_map(int width, int height)
{
	this->width = width;
	this->height = height;

	lawn = new int*[height];

	for (int i = 0; i < height; i++)
		lawn[i] = new int[width]();
}

Game_map::~Game_map()
{
	for (int i = 0; i < height; i++)
		delete[] lawn[i];

	delete[] lawn;
}

void Game_map::Clear_map()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			lawn[i][j] = 0;

	food_left = 0;
}

int Game_map::GetFood_left()
{
	return food_left;
}

bool Game_map::setItem(int item, int x, int y)
{
	if (lawn[x][y] == 0)
	{
		lawn[x][y] = item + 1;
		return true;
	}

	return false;
}
void Game_map::setSnakeData(int item, int x, int y)
{
	lawn[x][y] = item;
}
int Game_map::GetpointData(int X, int Y)
{
	return lawn[X][Y];
}
bool Game_map::spawn_food(int amount)
{
	int target_;
	bool notOK = true;
	bool NotFound = true;
	int i, j, k;

	for (i = 0; i < amount; i++)
	{
		notOK = true;

		for (j = TryRand; j > 0; j--)//ÿ����ೢ�����TryRand��λ��
		{
			target_ = rand() % (width*height);//��ȡ��ͼ���һ��

			if(setItem(rand() % FoodType, target_ / width, target_%width))//���һ��ʳ��
			{
				notOK = false;
				break;
			}
		}

		if (notOK)//������Ѱ
		{
			NotFound = true;

			switch (rand() % 2)
			{
			case 0:
				for(j=0;j<height&&NotFound;j++)
					for(k=0;k<width;k++)
						if (setItem(rand() % FoodType, j, k))//���һ��ʳ��
						{
							NotFound = false;
							break;
						}
				break;
			case 1:
				for (j = height - 1; j >= 0 && NotFound; j--)
					for (k = width - 1; k >= 0; k--)
						if (setItem(rand() % FoodType, j, k))//���һ��ʳ��
						{
							NotFound = false;
							break;
						}
				break;
			}

			if (NotFound)//����
				return false;
		}
	}

	food_left += amount;
	return true;
}

void Game_map::snake_eat_food()
{
	food_left--;
	spawn_food(1);
}

int Game_map::Getwidth()
{
	return width;
}

int Game_map::Getheight()
{
	return height;
}
