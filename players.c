#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 2

struct player
{
  char name[100];
  int  health;
  int  attack;
  int  defense;
  int  experience;
  int  level;
  int  attacks[5];
  int  typeOfAttacks;
  int  items[];
};

// Funções auxiliares
void generate_players(struct player *players, int num_players)
{
  // Gera um nome aleatório para cada jogador
  for (int i = 0; i < num_players; i++)
  {
    char name[100];
    sprintf(name, "Jogador %d", i + 1);
    strcpy(players[i].name, name);

    // Gera estatísticas aleatórias para cada jogador
    players[i].health = rand() % 100 + 1;
    players[i].attack = rand() % 10 + 1;
    players[i].defense = rand() % 10 + 1;
    players[i].experience = 0;
    players[i].level = 1;
    // Gera um array de ataques para cada jogador
    for (int j = 0; j < 5; j++)
    {
      players[i].attacks[j] = rand() % 10 + 1;
    }
  }
}
// Função para bloquear um ataque
void block_attack(struct player *player)
{
  // Calcula a chance de bloqueio
  int block_chance = player->defense / 2;

  // Gera um número aleatório
  int random_number = rand() % 100;

  // Verifica se o ataque foi bloqueado
  if (random_number < block_chance)
  {
    // O ataque foi bloqueado
    printf("Você bloqueou o ataque!\n");
  }
  else
  {
    // O ataque não foi bloqueado
    printf("Você não conseguiu bloquear o ataque!\n");
  }
}

void print_stats_player(struct player *player)
{
  // Imprime um título para o jogador
  printf("** Jogador %s **\n", player->name);

  // Imprime as estatísticas do jogador
  printf("Nome: %-10s\n", player->name);
  printf("Saúde: %d\n", player->health);
  printf("Ataque: %d\n", player->attack);
  printf("Defesa: %d\n", player->defense);
  printf("Nível: %d\n", player->level);
  printf("Experiência: %d\n", player->experience);
}


void generate_players(struct player *players, int num_players);