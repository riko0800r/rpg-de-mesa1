#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "items.c"

#define MAX_MONSTERS 100

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

void generate_monsters(struct monster *monsters, int num_monsters)
{
  // Inicializa o array de nomes de monstros
  char *monster_names[] = {
      "Orc",
      "Goblin",
      "Troll",
      "Dragão",
      "gnomo de jardim",
      "pudim selvagem",
      "mini pudim selvagem",
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

void generate_monsters(struct monster *monsters, int num_monsters);