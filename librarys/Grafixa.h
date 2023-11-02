struct player(){
	int x = 0;
	int y = 0;
	int width  = 2;
	int height = 1;
	int speed  = 2;
	int score  = 0;
	int lives  = 6;
	int level  = 1;
	int health = 100;
	int ammo;
	int weapon;
	int ammo_max;
	int health_max = 100;
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASS);
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
	while (GetMessage(&msg, NULL, 0, 0) > 0){
		translateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

float G_DrTriangle(float b, float h, char a)
{
	float area = b * h / 2;
	int linha = 0;
	int coluna = 0;
	for (linha; linha <= area; linha++)
	{
		for (coluna; coluna <= linha / h; coluna++)
		{
			if (coluna <= area)
			{
				printf("\n");
			}
		}
		printf("%c", a);
	}
	return area;
}

float G_DrRect(float b, float h, char a)
{
	float area = b * h - 1;
	int x1 = 0;
	int y1 = 0;
	for (x1; x1 <= area; x1++)
	{
		for (y1; y1 <= x1 / b; y1++)
		{
			if (y1 <= area)
			{
				printf("\n");
			}
		}
		printf("%c", a);
	}
	return area;
}

float G_CaQuad(float L)
{
	float area = L * L;
	printf("%f\n", area);
	return area;
}

float G_CaRect(float b, float h)
{
	float area = b * h;
	printf("%f\n", area);
	return area;
}

float G_CaCircle(double R)
{
	float area = PI * (R * R);
	printf("%f\n", area);
	return area;
}

float G_CaCube(float a1)
{
	float area = a1 * a1 * a1;
	printf("%f\n", area);
	return area;
}

float G_CaTriangleT1(float b, float h)
{
	float area = b * h / 2;
	printf("%f\n", area);
	return area;
}
#endif
