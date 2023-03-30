/*
  Disciplina: [Sistemas Operacionais]
  Professora: Prof. Eduardo Ferreira dos Santos
  Descrição: Resolução do problema de Edsger Dijkstra, "O Jantar dos Filósofos".
  Autor: Daniel Kabadayan Dias
  TIA: 42110637 - Turma: 04N11
  Data atual: 28/03/2023
*/

/* Inclusão de bibliotecas. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // SYSCALLS
#include <sys/wait.h> // Controle de processos

/* Define número de filósofos, estado "pensando", estado "faminto" e
estado "comendo". */
#define FILOSOFOS 5
#define PENSANDO 0
#define FAMINTO 1
#define COMENDO 2

/* Cria um vetor "status" para armazenar o estado de cada filósofo, e
também os pipes para comunicação entre filósofos. */
int status[FILOSOFOS];
int pipes[FILOSOFOS][2];

/* Declara as funções que será utilizadas no decorrer do programa. */
void pensando(int id);
void faminto(int id);
void devolverGarfos(int id);
void filosofo(int id);

/* MAIN */
int main() {
    pid_t pid;
    
    /* Inicialização dos pipes. */
    for (int i = 0; i < FILOSOFOS; i++)
    {
      if (pipe(pipes[i]) == -1)
      {
        printf("Erro na inicialização dos pipes.");
        exit(1);
      }
    }
    
    /* Inicialização dos processos. */
    for (int i = 0; i < FILOSOFOS; i++)
    {
      pid = fork();
      if (pid < 0)
      {
        printf("Erro na criação dos processos.");
        exit(1);
      }
      else if (pid == 0)
      {
        filosofo(i);
        exit(1);
      }
    }

  /* Loop para funcionamento dos processos filosóficos. */
  while (true)
  {
    pid = wait(NULL);
    if (pid < 0)
    {
      printf("Erro na finalização do processo.");
      exit(1);
    }
    else if (pid > 0)
      printf("\n%s terminou.\n", pid == 0  ? "Sócrates" : pid == 1 ? "Pitágoras" : pid == 2 ? "Heráclito" : pid == 3 ? "Demócrito" : "Aristóteles");
    else
      /* Se os processos filosóficos terminarem. */
      break;
  }
  
  /* Fechando os pipes. */
  for (int i = 0; i < FILOSOFOS; i++)
  {
    close(pipes[i][0]);
    close(pipes[i][1]);
  }
  
  return 0;
}

/* FUNÇÕES */

/**
 * @brief Simula o filósofo pensando por um período de tempo aleatório.
 * @param id Identificador do filósofo.
 **/
void pensando(int id)
{
  printf("\n%s está pensando.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
  /* Muda status do filosófo para "PENSANDO". */
  status[id] = PENSANDO;
  sleep(rand() % 5);
}

/**
 * @brief Simula o filósofo tentando pegar os garfos para comer.
 * @param id Identificador do filósofo.
 **/
void faminto(int id)
{
  /* As seguintes variáveis armazenam os filósofos a esquerda e a direita
  do filósofo atual. */
  int esquerda = id;
  int direita = (id + 1) % FILOSOFOS;
  /* A variável "msg" armazena mensagem recebida pelos pipes. */
  int msg;
  
  printf("\n%s está com fome.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
  status[id] = FAMINTO;
  /* Utiliza a função "write()" para enviar o estado para o filósofo a esquerda. */
  write(pipes[esquerda][1], &status[id], sizeof(int));
  /* Utiliza a função "read()" para aguardar o recebimento da resposta do filosófo a direita. */
  read(pipes[id][0], &msg, sizeof(int));
  if (msg != COMENDO)
  {
    printf("\n%s falhou em pegar o garfo da direita.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
    return;
  }
  /* Utiliza a função "read()" para aguardar o recebimento da resposta do filosófo a esquerda. */
  read(pipes[esquerda][0], &msg, sizeof(int));
  if (msg != COMENDO)
  {
    printf("\n%s falhou em pegar o garfo da esquerda.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
    /* Envia a mensagem de liberação do garfo para o filósofo à direita. */
    write(pipes[id][1], &status[direita], sizeof(int));
  return;
  } 
  printf("\n%s está comendo.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
  status[id] = COMENDO;
  sleep(rand() % 5);
}

/**
 * @brief Simula o filósofo devolvendo os garfos após terminar de comer.
 * @param id Identificador do filósofo.
 **/
void devolverGarfos(int id)
{
  /* As seguintes variáveis armazenam os filósofos a esquerda e a direita
  do filósofo atual. */
  int esquerda = id;
  int direita = (id + 1) % FILOSOFOS;
  
  printf("\n%s terminou de comer e libera os garfos.\n", id == 0  ? "Sócrates" : id == 1 ? "Pitágoras" : id == 2 ? "Heráclito" : id == 3 ? "Demócrito" : "Aristóteles");
  /* Envia a mensagem de liberação do garfo para o filósofo à direita. */
  write(pipes[id][1], &status[direita], sizeof(int));
  /* Envia a mensagem de liberação do garfo para o filósofo à esquerda. */
  write(pipes[esquerda][1], &status[esquerda], sizeof(int));
}

/**
 * @brief Função principal que implementa o comportamento de um filósofo.
 * @param id Identificador do filósofo.
 **/
void filosofo(int id)
{
  while (true)
  {
    pensando(id);
    faminto(id);
    devolverGarfos(id);
  }
}