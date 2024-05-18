#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int filas, columnas;
  for (filas = 0; filas < 9; filas++) {
    bool estaNum[9] = {false};
    for (columnas = 0; columnas < 9; columnas++) {
      int num = n->sudo[filas][columnas];
      if (num != 0) {
        if (estaNum[num - 1]) {
          return 0;
        }
        estaNum[num - 1] = true;
      }
    }
  }

  for (columnas = 0; columnas < 9; columnas++) {
    bool estaNum[9] = {false};
    for (filas = 0; filas < 9; filas++) {
      int num = n->sudo[filas][columnas];
      if (num != 0) {
        if (estaNum[num - 1]) {
          return 0;
        }
        estaNum[num - 1] = true;
      }
    }
  }

  for (int comienzoFil = 0; comienzoFil < 9; comienzoFil += 3) {
    for (int comienzoCol = 0; comienzoCol < 9; comienzoCol += 3) {
      bool estaNum[9] = {false};
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          int num = n->sudo[comienzoFil + i][comienzoCol + j];
          if (num != 0) {
            if (estaNum[num - 1]) {
              return 0;
            }
            estaNum[num - 1] = true;
          }
        }
      }
    }
  }

  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();
  int filas, columnas;
  for (filas = 0; filas < 9; filas++) {
    bool estaNum[9] = {false};
    for (columnas = 0; columnas < 9; columnas++) {
      int numero = n->sudo[filas][columnas];
      if (numero == 0) {
        for (int i = 0; i < 9; i++) {
          if (!estaNum[i]) {
            Node *adj = copy(n);
            adj->sudo[filas][columnas] = i + 1;
            pushBack(list, adj);
          }
        }
      }
    }
  }

  return list;
}

List *get_adj_nodesIsValid(Node *n) {
  List *list = createList();
  int filas, columnas;
  for (filas = 0; filas < 9; filas++) {
    bool estaNum[9] = {false};
    for (columnas = 0; columnas < 9; columnas++) {
      int numero = n->sudo[filas][columnas];
      if (numero == 0) {
        for (int i = 0; i < 9; i++) {
          if (!estaNum[i]) {
            Node *adj = copy(n);
            adj->sudo[filas][columnas] = i + 1;
            if (is_valid(adj->sudo[filas][columnas]))
            pushBack(list, adj);
          }
        }
      }
    }
  }

  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/