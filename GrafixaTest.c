// Grafixa.c

#pragma once
#include "Grafixa.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow,struct RECT* rect)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	HDC hdc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "GrafixaTesteV1";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Erro na registração da janela", "Erro!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd = CreateWindow("GrafixaTesteV1", "Grafixa Teste V1", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
	CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

	if(!hwnd){
		MessageBox(NULL, "Erro na criaçao da janela", "Erro!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	G_UpdatePositionPlayer(&rect, hwnd, hdc);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
int main(){
	
    return 0;
}
