#pragma once
#include"Graphics.h"
#include"SpriteSheet.h"
#include<time.h>

class game_level
{
protected:
	static Graphics* graphics;
	static HWND hWnd;
public:
	static void Init(HWND hwnd,Graphics* gfx)
	{
		srand((unsigned int)time(0));//���ڳ�ʼ�����������

		hWnd = hwnd;
		graphics = gfx;
	}

	virtual void Load() =  0 ;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	//virtual void LBUTTONDOWN(int mouseX, int mouseY) = 0;
	//virtual void RBUTTONDOWN(int mouseX, int mouseY) = 0;
	//virtual void MBUTTONDOWN(int mouseX, int mouseY) = 0;
	virtual void ReStartLevel() = 0;
	//virtual void Cheating() = 0;
	//virtual void ChangeDifficulty(int degree) = 0;
	//virtual void ChangeSize(int degree) = 0;
	virtual void KEY_ARROW(int direction) = 0;
};