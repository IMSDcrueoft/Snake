#pragma once
#include"game_level.h"
#include"Game_map.h"
#include"snake.h"

#define sprite_width 64
#define sprite_height 64

//��ʼ��ͼλ��
#define DrawX 64
#define DrawY 64
//���Ƽ��
//#define spacing 64
class Level1 :public game_level
{
	SpriteSheet * sprites1 =NULL;
	SpriteSheet * sprites2 =NULL;
	SpriteSheet * sprites3 = NULL;

	int frame = 0;
	int StartX = DrawX,StartY = DrawY;//��ͼ��

	Game_map* a_map = NULL;
	snake * a_snake = NULL;
public:
	void Load()	override;
	void Unload()  override;
	void Render()  override;
	void Update()  override;

	void ReStartLevel() override;
	void KEY_ARROW(int direction) override;
};