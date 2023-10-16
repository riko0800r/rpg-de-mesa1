#ifndef _RIKOS_H
#define _RIKOS_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159
#define MAX_MONSTERS 100
#define MAX_PLAYERS 2

struct item {
  char *name;
  char type[20];
  int  attack_bonus;
  int  defense_bonus;
  int  health_bonus;
  int  chance;
};
struct monster
{
  char name[100];
  int health;
  int attack;
  int defense;
  int level;
  struct item *drop;
  int weakness;
  int resistance;
  int x[640];
  int y[480];
};

struct player {
  char name[100];
  int  x;
  int  y;
  int  health;
  int  attack;
  int  defense;
  int  experience;
  int  level;
  int  attacks[5];
  int  typeOfAttacks;
  int  items[];
};

// Estrutura para representar uma janela
struct window {
  HWND handle;
  HDC hdc;
  PAINTSTRUCT ps;
};

// Estrutura para representar um ataque.
typedef struct attack{
  char name[30];
  int damage;
} attack;

// Lista de ataques.
attack attacks[] = {
  { "Ataque normal", 10 },
  { "Ataque especial", 20 },
  { "Magia", 30 },
};


// Função para imprimir o menu de seleção de ataques.
void print_attack_menu(struct player *player, struct window *window,struct attack *attack) {
  // Obtém o contexto de pintura da janela.
  PAINTSTRUCT ps;
  BeginPaint(window->handle, &ps);

  // Imprime o título do menu.
  TextOut(window->hdc, 10, 10, "** Menu de ataques **", 16);

  // Imprime a lista de ataques.
  for (int i = 0; i < sizeof(attacks) / sizeof(attacks[0]); i++) {
    TextOut(window->hdc, 10, 30 + i * 20, "%d. %s (%d)", i + 1);
  }
  
  // Finaliza a pintura da janela.
  EndPaint(window->handle, &ps);
}

int rand_range(int min, int max);

#endif