#ifndef GRAFIXA_H
#define GRAFIXA_H

#include "test.h"


typedef struct TAGimage{
    int imageArray[50];
} IMAGE;

struct player{
  int x;
  int y;
  int width;
  int height;
  int score;
  int lives;
  int level;
  int health;
  int weapon;
  int health_max;
  int weapon_max;
  IMAGE *image;
};

// Função para carregar uma imagem de todos os tipos
IMAGE *G_LoadImageAllTypes(LPCSTR str1,HINSTANCE hinstance)
{
  UINT uint1 = 0;

  // Cria uma imagem a partir da memória
  IMAGE *pImage = LoadImageA(hinstance,str1,uint1,0,0,uint1);

  // Retorna a imagem
  return pImage;
}

// Função para animar as imagens
void G_AnimateImages(int imagesArray[30],LPCSTR str1, HINSTANCE hInstance)
{
  // Cria uma janela
  int count = 1;
  count = sizeof(imagesArray[count]) / sizeof(imagesArray[0]);
  // Loop para animar as imagens
  for (int i = 0; i < count; i++)
  {
    // Desenha a imagem atual
    G_LoadImageAllTypes(str1, hInstance);
    // Aguarda um tempo
    Sleep(100);
  }
}

#endif
