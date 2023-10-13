#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 2
#define MAX_MONSTERS 100

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

// Tabela de itens

struct item {
  char *name;
  char *type;
  int attack_bonus;
  int defense_bonus;
  int health_bonus;
};

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
    void print_menu()
    {
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
        default:
          printf("Opção inválida.\n");
           }
    }
    // Passa para o próximo jogador
    player_index = (player_index + 1) % MAX_PLAYERS;
  }
  return 0;
}

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
      "nariz de nandinho",
      "mini nariz",
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

void battle(struct player *player, struct monster *monster)
{
  // Imprime os status do jogador e do monstro
  printf("** Batalha **\n");
  print_stats_player(player);
  print_stats_monster(monster);

  // O jogador ataca primeiro
  int player_damage = player->attack - monster->defense;

  // O jogador escolhe um ataque
  int attack_index;
  printf("Escolha um ataque (0-4): ");
  scanf("%d", &attack_index);

  // Aplica o ataque escolhido
  player_damage += player->attacks[attack_index];

  // O monstro recebe o dano
  monster->health -= player_damage;

  // Se o monstro morrer, o jogador ganha
  if (monster->health <= 0)
  {
    printf("Você derrotou o monstro!\n");
    return;
  }

  // O monstro ataca o jogador
  int monster_damage = monster->attack - player->defense;

  // O jogador defende
  int damage_reduction = rand() % 10 + 1;
  monster_damage -= damage_reduction;

  // O jogador recebe o dano
  player->health -= monster_damage;

  // Se o jogador morrer, o jogo termina
  if (player->health <= 0)
  {
    printf("Você foi derrotado!\n");
    exit(0);
  }
}
