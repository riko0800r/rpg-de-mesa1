#ifndef GRAFIXA_H
#define GRAFIXA_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#include <windows.h>

double PI = 3.14;

typedef struct tagRECT {
  long left;
  long top;
  long right;
  long bottom;
} RECT;

struct player(){
	int x = 0;
	int y = 0;
	int width  = 100;
	int height = 50;
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

int G_DrawerRect(HWND hwnd,hDC hdc){
	 // Define as dimensões do quadrado
  RECT rect = {10, 10, 100, 100};

  // Define a cor do quadrado
  COLORREF color = RGB(0, 255, 0);

  // Desenha o quadrado
  FillRect(hDC, &rect, color);

  // Libera o contexto de dispositivo
  ReleaseDC(hwnd, hDC);

  return 0;
}

// Função para carregar uma imagem de todos os tipos
IMAGE *LoadImageAllTypes(LPCTSTR lpFileName) {
  // Abre o arquivo de imagem
  HANDLE hFile = CreateFile(lpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE) {
    return NULL;
  }

  // Obtém o tamanho do arquivo
  DWORD dwFileSize = GetFileSize(hFile, NULL);

  // Aloca memória para a imagem
  LPVOID lpImage = malloc(dwFileSize);
  if (lpImage == NULL) {
    CloseHandle(hFile);
    return NULL;
  }

  // Lê o arquivo de imagem para a memória
  DWORD dwBytesRead = 0;
  ReadFile(hFile, lpImage, dwFileSize, &dwBytesRead, NULL);
  CloseHandle(hFile);

  // Cria uma imagem a partir da memória
  IMAGE *pImage = ImageFromStream((BYTE *)lpImage, dwBytesRead);
  if (pImage == NULL) {
    free(lpImage);
    return NULL;
  }

  // Libera a memória da imagem
  free(lpImage);

  // Retorna a imagem
  return pImage;
}

// Cria uma função para atualizar a posição do quadrado
  void G_UpdatePositionPlayer(struct tagRECT* rect, HWND hwnd, HDC hdc) {
    // Verifica se a tecla W foi pressionada
    if (GetKeyState(VK_W) & 0x8000) {
      y--;
    }

    // Verifica se a tecla A foi pressionada
    if (GetKeyState(VK_A) & 0x8000) {
      x--;
    }

    // Verifica se a tecla S foi pressionada
    if (GetKeyState(VK_S) & 0x8000) {
      y++;
    }

    // Verifica se a tecla D foi pressionada
    if (GetKeyState(VK_D) & 0x8000) {
      x++;
    }

    // Atualiza a posição do quadrado
    rect.top = y;
    rect.left = x;
    G_DrawerRect(hwnd,hdc,hbr);
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
