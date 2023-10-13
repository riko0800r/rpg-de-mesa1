#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 2
#define MAX_MONSTERS 100
struct item {
  char *name;
  char *type;
  int attack_bonus;
  int defense_bonus;
  int health_bonus;
  int chance;
};
// Estruturas de dados
struct player
{
  char name[100];
  int health;
  int attack;
  int defense;
  int experience;
  int level;
  int attacks[5];
  int  items[];
};

struct monster
{
  char name[100];
  int health;
  int attack;
  int defense;
  int level;
  struct item *drop;
};

// Funções
void generate_players(struct player *players, int num_players);
void generate_monsters(struct monster *monsters, int num_monsters);
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

// Função para gerar um drop para um monstro

struct item *generate_monster_drop(struct monster *monster)
{
  // Gera um número aleatório entre 0 e 100
  int chance = rand() % 100;

  // Verifica se o monstro tem um drop
  if (monster->drop == NULL)
  {
    return NULL;
  }

  // Verifica se o monstro dropa um item
  if (chance < monster->drop->chance)
  {
    return monster->drop;
  }

  // Retorna NULL
  return NULL;
}
// Tabela de itens



// Tabela de itens

struct item items[] = {
  { "Espada","ataque", 10, 0, 0 },
  { "Armaduras","Defesa", 0, 10, 0 },
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
// declaraçao
void print_menu();

// Função `drop_item()`
void drop_item(struct player *player, struct item *item) {
  // Libera a memória do item
  free(item);
}

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

void print_stats_monster(struct monster *monster)
{
  // Imprime um título para o monstro
  printf("** Monstro %s **\n", monster->name);

  // Imprime as estatísticas do monstro
  printf("Nome: %-10s\n", monster->name);
  printf("Saúde: %d \n", monster->health);
  printf("Ataque: %d\n", monster->attack);
  printf("Defesa: %d\n", monster->defense);
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

// tipos de ataque

enum attack_type {
  ATTACK_TYPE_PHYSICAL,
  ATTACK_TYPE_FIRE,
  ATTACK_TYPE_ICE,
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
void generate_monsters(struct monster *monsters, int num_monsters)
{
  // Inicializa o array de nomes de monstros
  char *monster_names[] = {
      "Orc",
      "Goblin",
      "Troll",
      "Dragão",
      "gnomo de jardim",
      "lobo feroz"
      
      };

  // Gera os monstros
  for (int i = 0; i < num_monsters; i++)
  {
    // Seleciona um nome de monstro aleatório
    int name_index = rand() % (sizeof(monster_names) / sizeof(char *));

    // Inicializa o monstro
    strcpy(monsters[i].name, monster_names[name_index]);
    monsters[i].health = rand() % 100 + 1;
    monsters[i].attack = rand() % 10 + 1;
    monsters[i].defense = rand() % 10 + 1;
  }
}

struct terrain {
  char *name;
  int attack_bonus;
  int defense_bonus;
};

// Função para gerar um **microambiente** aleatório
struct terrain *generate_terrain()
{
  // Gera um número aleatório entre 0 e 2
  int terrain_type = rand() % 3;

  // Retorna o **microambiente**
  switch (terrain_type)
  {
    case 0: return generate_grass();
    case 1: return generate_water();
    case 2: return generate_mountain();
  }
}

// Função para calcular o dano causado por um ataque
int calculate_damage(struct player *player, struct monster *monster, struct attack *attack)
{
  // Calcula o dano base
  int damage = attack->damage;

  // Aplica o bônus de ataque do jogador
  damage += player->attack;

  // Aplica o bônus de defesa do monstro
  damage -= monster->defense;

  // Aplica o bônus de **microambiente**
  damage += terrain->attack_bonus;
  damage -= terrain->defense_bonus;

  return damage;
}


void battle(struct player *player, struct monster *monster)
{
  // Imprime os status do jogador e do monstro
  printf("** Batalha **\n");
  print_stats_player(player);
  print_stats_monster(monster);

  // Gera o **microambiente** da batalha
  struct terrain *terrain = generate_terrain();
  
  // Calcula o dano causado por cada ataque
  int player_damage = calculate_damage(player, monster, player->attacks[attack_index]);
  
  int monster_damage = calculate_damage(monster, player, monster->attacks[rand() % monster->attacks_count]);
  
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
