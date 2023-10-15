#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "monsters.c"

// Funções


void battle(struct player *player, struct monster *monster);


// Função rand_range()
int rand_range(int min, int max) {
  return rand() % (max - min + 1) + min;
}

// Tipos de ataque
enum attack_type {
  ATTACK_TYPE_PHYSICAL,
  ATTACK_TYPE_FIRE,
  ATTACK_TYPE_ICE,
};

// declaraçao
void print_menu();


// Função `calculate_experience()`

// Tabela de experiência

int experience_table[] = {
  10, 20, 30
};

// Implementação da função

int calculate_experience(struct monster *monster)
{
  // Obtém o nível do monstro
  int level = monster->level;

  // Retorna a experiência do monstro
  return experience_table[level];
}
// Implementação da função

void level_up(struct player *player)
{
  // Obtém a quantidade de experiência necessária para subir de nível
  int experience_needed = player->level * 100;

  // Verifica se o jogador tem experiência suficiente
  if (player->experience >= experience_needed)
  {
    // Aumenta o nível do jogador
    player->level++;

    // Atualiza as estatísticas do jogador
    player->health += 10;
    player->attack += 5;
    player->defense += 5;
  }
}


// Programa principal
int main()
{
  // Inicializa o gerador de números aleatórios
  srand(time(NULL));
  struct player players[MAX_PLAYERS];
  // Cria um array de jogadores
  // Gera os jogadores
  generate_players(players, MAX_PLAYERS);

  // Cria um array de monstros
  struct monster monsters[MAX_MONSTERS];

  // Gera os monstros
  generate_monsters(monsters, MAX_MONSTERS);

  // Inicia o jogo
  int player_index = 0;
  while (1)
  {
    // O jogador escolhe uma ação
    char action[100];
    int monster_index;
    void print_menu() {
      // Imprime uma lista de opções para o jogador escolher
      printf("O que você gostaria de fazer?\n");
      printf("1. Iniciar uma batalha\n");
      printf("2. sair do jogo\n");
       // Lê a escolha do jogador
       int choices;
       scanf("%d",&choices);
       
       // Processa a escolha do jogador
       switch (choices)
        {
        case 1:
          // Iniciar uma batalha
          monster_index = rand() % MAX_MONSTERS;
          // Inicia uma batalha
          battle(&players[player_index], &monsters[monster_index]);
          break;
        case 2:
          // Sair do jogo
          exit(0);
          break;
        }
    // Passa para o próximo jogador
    player_index = (player_index + 1) % MAX_PLAYERS;
    }
  }
}


// Função para imprimir o menu de seleção de ataques
void print_attack_menu(struct player *player)
{
  // Imprime o título do menu
  printf("** Menu de ataques **\n");

  // Imprime os ataques do jogador
  for (int i = 0; i < 5; i++)
  {
    printf("o ataque%d:",player->attacks[i]);
  }
}

// Função para selecionar um ataque
int select_attack(struct player *player)
{
  // Imprime o menu de seleção de ataques
  print_attack_menu(player);

  // Lê a escolha do jogador
  int attack_index;
  scanf("%d", &attack_index);

  // Verifica se a escolha é válida
  if (attack_index < 0 || attack_index >= 5)
  {
    printf("Escolha um ataque válido.\n");
    return -1;
  }

  // Retorna o índice do ataque selecionado
  return attack_index;
}


// Função para calcular o dano causado por um ataque
int calculate_damage_player(struct player *player, struct monster *monster)
{
  // Calcula o dano base
  int damage = 10;

  // Aplica o bônus de ataque do jogador
  damage += player->attack;

  // Aplica o bônus de defesa do monstro
  damage -= monster->defense;

  return damage;
}

// Função para calcular o dano causado por um ataque
int calculate_damage_monster(struct player *player, struct monster *monster)
{
  // Calcula o dano base
  int damage = 10;

  // Aplica o bônus de ataque do jogador
  damage += monster->attack;

  // Aplica o bônus de defesa do monstro
  damage -= player->defense;

  // Aplica a fraqueza ou resistência do monstro

  if (player->typeOfAttacks == monster->weakness)
  {
    damage *= 2;
  }
  else if (player->typeOfAttacks == monster->resistance)
  {
    damage /= 2;
  }

  return damage;
}



// inicia a funçao de batalha
void battle(struct player *player, struct monster *monster)
{
  // Imprime os status do jogador e do monstro
  printf("** Batalha **\n");
  print_stats_player(player);
  print_stats_monster(monster);

  // Imprime o menu de seleção de ataques
  int attack_index = select_attack(player);

  // Calcula o dano causado por cada ataque
  int player_damage = calculate_damage_player(player, monster);
  
  int monster_damage = calculate_damage_monster(player, monster);
  
  // Aplica o dano aos oponentes
  monster->health -= player_damage;
  player->health -= monster_damage;
  
  // Verifica se algum oponente foi derrotado
  if (monster->health <= 0)
  {
    printf("Você derrotou o monstro!\n");
    return;
  }
  if (player->health <= 0)
  {
    printf("Você foi derrotado!\n");
    exit(0);
  }
}
