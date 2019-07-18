#include <windows.h> 
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include"bird.h"

#define swidth 50
#define beginx 150
#define machine  12389

static int i = 0;
static int j = 0;
int initx = 30;
int inity = 150;
int a[13];
int b[12] = {150,250,350,450,550,650,750,850,950,1050,1150,1250};

// Global variable 
HINSTANCE hinst;

// Function prototypes. 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

// Application entry point. 

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 13; i++)
	{
		int x = 450;
		while (x<=150||x >= 450)
		{
			x = rand() % 350;
		}
	    a[i] = x;
	}

	if (!InitApplication(hinstance))
		return FALSE;

	if (!InitInstance(hinstance, nCmdShow))
		return FALSE;

	BOOL fGotMessage;
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
	UNREFERENCED_PARAMETER(lpCmdLine);
}

BOOL InitApplication(HINSTANCE hinstance)
{
	WNDCLASSEX wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wcx.cbSize = sizeof(wcx);          // size of structure 
	wcx.style = CS_HREDRAW |
		CS_VREDRAW;                    // redraw if size changes 
	wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
	wcx.cbClsExtra = 0;                // no extra class memory 
	wcx.cbWndExtra = 0;                // no extra window memory 
	wcx.hInstance = hinstance;         // handle to instance 
	wcx.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);              // predefined app. icon 
	wcx.hCursor = LoadCursor(NULL,
		IDC_ARROW);                    // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);                  // white background brush 
	wcx.lpszMenuName = "MainMenu";    // name of menu resource 
	wcx.lpszClassName = "MainWClass";  // name of window class 
	wcx.hIconSm = (HICON)LoadImage(hinstance, // small class icon 
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	// Register the window class. 

	return RegisterClassEx(&wcx);
}

BOOL InitInstance(HINSTANCE hinstance, int nCmdShow)
{
	HWND hwnd;

	// Save the application-instance handle. 

	hinst = hinstance;

	// Create the main window. 

	hwnd = CreateWindow(
		"MainWClass",        // name of window class 
		"Sample",            // title-bar string 
		WS_OVERLAPPEDWINDOW, // top-level window 
		CW_USEDEFAULT,       // default horizontal position 
		CW_USEDEFAULT,       // default vertical position 
		1800,       // default width 
		600,       // default height 
		(HWND)NULL,         // no owner window 
		(HMENU)NULL,        // use class menu 
		hinstance,           // handle to application instance 
		(LPVOID)NULL);      // no window-creation data 

	if (!hwnd)
		return FALSE;

	// Show the window and send a WM_PAINT message to the window 
	// procedure. 

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return TRUE;

}
void GamePaint(HDC hdc, HWND hwnd)
{
	RECT clientRect;
	HRGN bgRgn;
	HBRUSH hbrush;

	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &clientRect);
    bgRgn = CreateRectRgnIndirect(&clientRect);
  
	hbrush = CreateSolidBrush(RGB(250, 250, 210));
	SelectObject(hdc, hbrush);
	FillRgn(hdc, bgRgn, hbrush);
	hbrush = CreateSolidBrush(RGB(255, 215, 0));
	SelectObject(hdc, hbrush);
	Rectangle(hdc, initx, inity, initx + 20, inity + 20);

	int x = beginx;
    int i;

	hbrush = CreateSolidBrush(RGB(139, 69, 19));
	SelectObject(hdc, hbrush);
	for (i = 0; i < 7; i++)
	{
        Rectangle(hdc, x,600-a[i], x +swidth, 600);
		x += 200;
	}
    x = beginx+100;
	for (i = 7; i < 13; i++)
	{
		Rectangle(hdc, x, 0, x + swidth, a[i]);
        x += 200;
	}	
    DeleteObject(hbrush);
	
	ReleaseDC(hwnd, hdc);
}

LONG CALLBACK MainWndProc(
	HWND hwnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam) 
{
	HDC hdc;
	hdc = GetDC(hwnd);

	switch (msg)
	{
		// 当窗口被创建时，收到的第一个消息就是WM_CREATE
	case WM_CREATE:
		SetTimer(hwnd, machine, 50, NULL);
		break;

		// 当系统认为窗口上的GDI对象应该被重绘时，会向窗口发送一个WM_PAINT消息。
		// 当然应用程序也可以通过调用 UpateWindow来主动向窗口发送一个WM_PAINT消息。
		// 所有使用GDI在窗口上绘制图形的程序都 “必须” 写在这里。
		// 如果不是在WM_PAINT消息的处理过程中绘制GDI图形，那么在窗口刷新时就会被新被抹除和覆盖
	case WM_PAINT:
		GamePaint(hdc, hwnd);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			inity -= 8;
			break;
		case VK_DOWN:
			inity += 8;
			break;
		default:
			break;
		}
	case WM_TIMER:
		initx += 1;
		inity += 3;
		hdc = GetDC(hwnd);
		GamePaint(hdc, hwnd);
        switch (isdead(initx, inity, a,b,i,j))
		{
		case 1:
			KillTimer(hwnd, machine);
            MessageBox(0, "你撞到了！！！", "Game Over", MB_OKCANCEL);
			ExitProcess(0);
		case 2:
			KillTimer(hwnd, machine);
			MessageBox(0, "哦！你成功了哟！！", "Game Over", MB_OKCANCEL);
			ExitProcess(0);
		default:
			break;
		}
        break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
 }