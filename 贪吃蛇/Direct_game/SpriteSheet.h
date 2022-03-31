#pragma once
#include<wincodec.h>
#include"Graphics.h"
//windowscodecs.lib;
class SpriteSheet
{
	Graphics * graphics;
	ID2D1Bitmap* bmp;
	int spriteWidth = 0, spriteHeight = 0;
	int spriteAccross_W = 1;
	int spriteAccross_H = 1;
public:
	SpriteSheet(LPCWSTR filename, Graphics * gfx);
	SpriteSheet(LPCWSTR filename, Graphics * gfx,int width,int height);
	~SpriteSheet();

	void Draw();//ֱ�ӻ���
	void Draw(int index, int x, int y,float zoom);//����������
	void Draw(int index, int x, int y, int width, int height);//���ؼ�����
};