#include "Grafixa.h"


// funçao principal
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	HDC hdc;
	HBRUSH hbr;

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
	UpdateWindow(hwnd);
	LPCRECT rect;
	while (GetMessage(&msg, NULL, 0, 0) > 0){
		TranslateMessage(&msg);
		// Desenha o quadrado
		FillRect(hdc,rect,hbr);
		// Libera o contexto de dispositivo
		ReleaseDC(hwnd, hdc);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
