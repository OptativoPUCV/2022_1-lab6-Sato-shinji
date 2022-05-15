#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

void fill_aux_arr (int *arr, int size)
{
  int i;
  for(i = 0; i < size; i++)
  {
    arr[i] = 0;
  }
}

int is_valid(Node* n){
    int i, j, ini_i, ini_j, k, aux_arr[9];

    //Filas
    for(i = 0; i < 9; i++)
    {
      fill_aux_arr(aux_arr, 9);
      for(j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] != 0)
        {
          if(aux_arr[n->sudo[i][j] - 1]) return 0;
          else aux_arr[n->sudo[i][j] - 1] = 1;
        }
      }
    }

    //Columnas
    for(i = 0; i < 9; i++)
    {
      fill_aux_arr(aux_arr, 9);
      for(j = 0; j < 9; j++)
      {
        if(n->sudo[j][i] != 0)
        {
          if(aux_arr[n->sudo[j][i] - 1]) return 0;
          else aux_arr[n->sudo[j][i] - 1] = 1;
        }
      }
    }

    //Submatrices
    ini_i = 0;
    ini_j = 0;
    for(k = 0; k < 9; k++)
    {
      fill_aux_arr(aux_arr, 9);
      for(i = 0; i < 3; i++)
      {
        for(j = 0; j < 3; j++)
        {
          if(n->sudo[ini_i + i][ini_j + j] != 0)
          {
            if(aux_arr[n->sudo[ini_i + i][ini_j + j] - 1]) return 0;
            else aux_arr[n->sudo[ini_i + i][ini_j + j] - 1] = 1;
          }
        }
      }
      if(ini_j < 6) {ini_j +=3;}
      else {ini_j = 0; ini_i += 3;}
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j, num, flag = 0;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for(num = 1; num <= 9; num++)
          {
            Node *adj_n = copy(n);
            adj_n->sudo[i][j] = num;
            if(is_valid(adj_n)) pushBack(list, adj_n);
            else free(adj_n);
          }
          flag = 1;
          break;
        }
      }
      if (flag) break;
    }
    return list;
}


int is_final(Node* n){
    int i, j;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] == 0) return 0;
      }
    }

    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *S = createStack();
  push(S, initial);

  while(get_size(S) > 0)
  {
    Node *n = top(S);
    pop(S);
    if (is_final(n)) return n;

    List *list_adj = get_adj_nodes(n);

    Node *adj_n = first(list_adj);
    while(adj_n)
    {
      push(S, adj_n);
      adj_n = next(list_adj);
    }

    free(n);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/