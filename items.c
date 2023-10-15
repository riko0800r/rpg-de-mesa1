#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "players.c"

struct item {
  char *name;
  char type[20];
  int  attack_bonus;
  int  defense_bonus;
  int  health_bonus;
  int  chance;
};
// Tabela de itens
struct item items[] = {
  { "Espada","ataque", 10, 0, 0 },
  { "Armaduras","Defesa", 0, 10, 0},
  { "Poção de cura","vida", 0, 0, 100 },
};



// Implementação da função

struct item *generate_item()
{
  // Gera um número aleatório entre 0 e o tamanho da tabela de itens
  int index = rand() % (sizeof(items) / sizeof(struct item));

  // Retorna o item no índice especificado
  return &items[index];
}
// Implementação da função

// Função para equipar um item no jogador

void equip_item(struct player *player, struct item *item, int slot)
{
  // Obtém o item atual no slot especificado
  struct item *current_item = player->items[slot];

  // Substitui o item atual pelo novo item
  player->items[slot] = item;

  // Atualiza as estatísticas do jogador
  if (item->type == "ataque")
  {
    player->attack += item->attack_bonus;
  }
  else if (item->type == "defesa")
  {
    player->defense += item->defense_bonus;
  }
  else if (item->type == "vida")
  {
    player->health += item->health_bonus;
  }

  // Libera a memória do item antigo
  if (current_item != NULL)
  {
    free(current_item);
  }
}

void drop_item(struct player *player, struct item *item) {
  // Libera a memória do item
  free(item);
}
