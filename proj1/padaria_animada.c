/*
 * Implementação do algoritmo da padaria.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>


#define N 10        /* Número de threads */
#define N_VEZES 10  /* Número de acessos por thread à região crítica */

#define BLACK 0
#define WHITE 1

#define TRUE  1
#define FALSE 0

#define DELAY 30000

volatile int s = 0;         /* Variável compartilhada */
volatile int num[N];        /* Vetor de senhas */
volatile int escolhendo[N]; /* Vetor que marca quais threads estão escolhendo */
volatile bool color[N];     /* Vetor que marca a cor dos tickets */
volatile bool sharedColor = BLACK;

/* Retorna o valor máximo presente no vetor num[] cuja cor correspondente
 no velor color[] é a mesma cor da entrada */
int max(bool entry_color) {
  int i, m = -1;

  for (i = 0; i < N; i++) 
    if (m < num[i] && color[i] == entry_color) 
      m = num[i];
  
  return m;
}

/* Função executada pelas threads */
void* f_thread(void *v) {
  int thr_id = *(int *)v; 
  int i, j, aux;

  /* Acessa as região crítica N vezes */
  for (i = 0; i < N_VEZES; i++) {
    /* Pega uma senha e uma cor */
    escolhendo[thr_id] = TRUE;

    color[thr_id] = sharedColor;  /* Atribui cor */

    aux = max(color[thr_id]) + 1; /* Calcula senha */
    num[thr_id] = aux;

    /* Ja escolhi meu ticket! */
    escolhendo[thr_id] = FALSE;

    /* Espera chegar a sua vez */
    for (j = 0; j < N; j++) {
      while (escolhendo[j] == TRUE); /* Espera terminar de escolher */

      if (color[j] == color[thr_id])
        /* Mesma cor */
        while(num[j] != 0 && (num[j] < num[thr_id] || (num[j] == num[thr_id] && j < thr_id)) && color[j] == color[thr_id]);
      else 
        /* Cores diferentes */
        while(num[j] != 0 && color[thr_id] == sharedColor && color[j] != color[thr_id] );
    }

    /* Muda a shared color para dar preferência a threads de cores diferentes */
    if (color[thr_id] == BLACK)
      sharedColor = WHITE;
    else
      sharedColor = BLACK;

    /* Escreve na região crítica */
    s = thr_id;

    // printf("Thread %d, s = %d, ticket_color: %d, shared_color: %d \n", thr_id, s, color[thr_id], sharedColor);

    sleep(1);

    num[thr_id] = 0;  /* Marca que saiu da região crítica */
    
    sleep(1);
  }

  return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thr[N];
    int i, id[N];

    initscr();
    noecho();
    curs_set(FALSE);


    for (i = 0; i < N; i++) 
      num[i] = 0;

    for (i = 0; i < N; i++) {
      id[i] = i;
      pthread_create(&thr[i], NULL, f_thread, &id[i]);
    }

    //Animation
    while(1) {
        clear(); // Clear the screen of all
        // previously-printed characters

        // Print all lines (no migue)
        printw("Thread    ");
        
        for(i = 0; i < N; i++)
        {
            printw("| %d |", id[i]);
        }

        printw("\n");
        printw("Color     ");

        for(i = 0; i < N; i++)
        {
            if(color[i] == 0) printw("| B |");
            else printw("| W |");
        }

        printw("\n");
        printw("Ticket    ");

        for(i = 0; i < N; i++)
        {
            printw("| %d |", num[i]);
        }

        printw("\n");

        //mvprintw(y, x, "o"); // Print our "ball" at the current xy position
        refresh();

        usleep(DELAY); // Shorter delay between movements

    }

    endwin();
    
    //for (i = 0; i < N; i++) 
     // pthread_join(thr[i], NULL); 

    return 0;
}