#include <stdio.h>
#include <stdlib.h>


#include "bibliotecas/rikos.h"

// Função para criar uma janela
struct window *create_window(int width, int height, char *title) {
  // Cria uma janela
  HWND handle = CreateWindow(
      "STATIC", title, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);

  // Verifica se a janela foi criada com sucesso
  if (handle == NULL) {
    printf("Falha ao criar a janela.\n");
    return NULL;
  }

  // Obtém o contexto de dispositivo da janela
  HDC hdc = GetDC(handle);
  
  // Retorna a estrutura da janela
  struct window *window = malloc(sizeof(struct window));
  window->handle = handle;
  window->hdc = hdc;

  return window;
}
// Função para desenhar o jogador na janela
void draw_player(struct window *window,struct player *player) {
  // Obtém a posição do jogador
  int player_x = player->x;
  int player_y = player->y;

  // Desenha um retângulo na posição do jogador
  SetTextColor(window->hdc, RGB(255, 0, 0));
  SetBkColor(window->hdc, RGB(255, 255, 255));
  Rectangle(window->hdc, player_x, player_y, player_x + 20, player_y + 20);
}

// Função para desenhar os inimigos na janela
void draw_enemies(struct window *window,struct monster *monster) {
  // Percorre a lista de inimigos
  for (int i = 0; i < MAX_MONSTERS; i++) {
    // Obtém a posição do inimigo
    int enemy_x = monster->x[i];
    int enemy_y = monster->y[i];

    // Desenha um retângulo na posição do inimigo
    SetTextColor(window->hdc, RGB(0, 0, 255));
    SetBkColor(window->hdc, RGB(255, 255, 255));
    Rectangle(window->hdc, enemy_x, enemy_y, enemy_x + 20, enemy_y + 20);
  }
}
// Função para desenhar na janela
void draw_in_window(struct window *window, int x, int y, char *text) {
  // Obtém o contexto de pintura da janela
  PAINTSTRUCT ps;
  BeginPaint(window->handle, &ps);

  // Desenha o texto na janela
  SetTextColor(window->hdc, RGB(0, 0, 0));
  SetBkColor(window->hdc, RGB(255, 255, 255));
  TextOut(window->hdc, x, y, text, strlen(text));

  // Finaliza a pintura da janela
  EndPaint(window->handle, &ps);
}

// Função para exibir a janela
void show_window(struct window *window,struct player *player,struct monster *monster) {
  // Exibe a janela
  ShowWindow(window->handle, SW_SHOW);

   // Aguarda o encerramento da janela.
  while (GetAsyncKeyState(VK_ESCAPE) == 0) {
    // Atualiza a janela.
    UpdateWindow(window->handle);

    // Desenha o jogador na janela.
    draw_player(window,player);

    // Desenha os inimigos na janela.
    draw_enemies(window,monster);
  }

  // Fecha a janela
  DestroyWindow(window->handle);
}
int main(){
  // Cria uma janela.
  struct window *window = create_window(640, 480, "Meu RPG");

  while(1){
    draw_player(window,player);
    
    move_player(player,window);
  }
  return 0;
}