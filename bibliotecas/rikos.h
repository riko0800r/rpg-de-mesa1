#ifndef _RIKOS_H
#define _RIKOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159
#define MAX_MONSTERS 100
#define MAX_PLAYERS 2
#define PLAYER_SPEED 2

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

  // Desenha um retângulo para o título do menu.
  draw_rectangle(window, 10, 10, 200, 20);

  // Desenha o texto do título do menu.
  TextOut(window->hdc, 15, 15, "** Menu de ataques **", 16);

  // Desenha um retângulo para cada ataque.
  for (int i = 0; i < sizeof(attacks) / sizeof(attacks[0]); i++) {
    draw_rectangle(window, 10, 30 + i * 20, 100, 50);

    // Desenha o texto do ataque.
   TextOut(window->hdc, 10, 30 + i * 20, "%d. %s (%d)", i + 1);
  }

  // Finaliza a pintura da janela.
  EndPaint(window->handle, &ps);
}

void add_menu_function(struct window *window, char *name, void (*function)()) {
  // Obtém o contexto de pintura da janela.
  PAINTSTRUCT ps;
  BeginPaint(window->handle, &ps);

  // Desenha um retângulo para a função do menu.
  draw_rectangle(window, 10, 30 + i * 20, 100, 50);

  // Desenha o texto da função do menu.
  TextOut(window->hdc, 15, 35 + i * 20, name, strlen(name));

  // Armazena a função do menu.
  window->menu_functions[i] = function;

  // Finaliza a pintura da janela.
  EndPaint(window->handle);
}

void move_player(struct player *player, struct window *window) {
  // Obtém o contexto de entrada da janela.
  INPUT_RECORD input_record;
  DWORD num_events;

  // Lê um evento de entrada.
  ReadConsoleInput(window->handle, &input_record, 1, &num_events);

  // Verifica se o evento é uma tecla pressionada.
  if (input_record.EventType == KEY_EVENT) {
    // Obtém o código da tecla pressionada.
    int key_code = input_record.Event.KeyEvent.wVirtualKeyCode;

    // Verifica se a tecla pressionada é uma tecla de movimento.
    switch (key_code) {
      case VK_UP:
        player->y -= PLAYER_SPEED;
        break;
      case VK_DOWN:
        player->y += PLAYER_SPEED;
        break;
      case VK_LEFT:
        player->x -= PLAYER_SPEED;
        break;
      case VK_RIGHT:
        player->x += PLAYER_SPEED;
        break;
    }

    // Verifica se o jogador saiu da tela.
    if (player->x < 0) {
      player->x = 0;
    } else if (player->x >= window->width) {
      player->x = window->width - 1;
    }

    if (player->y < 0) {
      player->y = 0;
    } else if (player->y >= window->height) {
      player->y = window->height - 1;
    }
  }
}

int rand_range(int min, int max);

#endif