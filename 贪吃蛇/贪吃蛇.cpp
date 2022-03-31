// 贪吃蛇.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "贪吃蛇.h"

#include "Direct_game/Graphics.h"
#include "Direct_game/game_controller.h"
#include "Direct_game/Level1.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

Graphics * graphics = NULL;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	MSG msg;
	msg.message = WM_NULL;

	// 主消息循环:
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			//update
			game_controller::Update();
			//render
			graphics->BeginDraw();
			game_controller::Render();
			graphics->EndDraw();
		}
	}
	delete graphics;

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   /*
   HWND hWnd = CreateWindowW(
	   szWindowClass,
	   szTitle,
	   WS_OVERLAPPEDWINDOW &~WS_MAXIMIZEBOX &~WS_SIZEBOX,//去除最大化功能和调整大小功能
	   100,
	   100,
	   1280,
	   832,
	   nullptr,
	   nullptr,
	   hInstance,
	   nullptr);
*/
   RECT rect = { 0,0,1280,832 };

   AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW , false, WS_EX_OVERLAPPEDWINDOW);

   HWND hWnd = CreateWindowEx(
	   WS_EX_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_SIZEBOX,
	   szWindowClass,
	   szTitle,
	   WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX&~WS_SIZEBOX,
	   100,
	   100,
	   rect.right - rect.left,
	   rect.bottom - rect.top,
	   NULL,
	   NULL,
	   hInstance,
	   0);

   if (!hWnd)
   {
	   return FALSE;
   }
   //初始化
   graphics = new Graphics();

   if (!graphics->Init(hWnd))
   {
	   delete graphics;
	   return false;
   }

   ShowWindow(hWnd, nCmdShow);

   game_level::Init(hWnd, graphics);//进入关卡
   game_controller::LoadInitialLevel(new Level1());//引入关卡1

   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			game_controller::Getcurrentlevel()->KEY_ARROW(LEFT);
			break;
		case VK_UP:
			game_controller::Getcurrentlevel()->KEY_ARROW(TOP);
				break;
		case VK_RIGHT:
			game_controller::Getcurrentlevel()->KEY_ARROW(RIGHT);
			break;
		case VK_DOWN:
			game_controller::Getcurrentlevel()->KEY_ARROW(BOTTOM);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
