#include <stdio.h>
#include <stdlib.h>

typedef struct elemento* Pilha;

struct elemento{
  int current;
  struct elemento *prox;
};
typedef struct elemento Elem;



int insere_pilha(Pilha* pi, int cur){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->current = cur;
    no->prox = (*pi);
    *pi = no;
    return 1;
}


int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

Pilha* cria_pilha(){
  Pilha *pi;
  pi = (Pilha*) malloc(sizeof(Pilha));
  if(pi!=NULL)
    *pi = NULL;
  return pi;
}

void ShapleGaley(int M[4][4], int W[4][4]){
 int married[1][4];
 Pilha *pi = cria_pilha();
 

 for (int i = 0; i < 4; i++) {
  married[0][i] = -1;
  insere_pilha(pi, 3 - i);
 }



 Elem* no = *pi;
 while (no != NULL) {
  for (int i = 0; i < 4; i++) {
    int pretendente = M[no->current][i];
    if(married[0][pretendente] == -1){
      married[0][pretendente] = no->current;
      remove_Pilha(&no);
      break;
    }
    else {
        int actLov = 0;
        while(W[pretendente][actLov] != married[0][pretendente]){
         actLov++;   
        }
        
        int compet = 0;
        while(W[pretendente][compet] != no->current){
         compet++;   
        } 
        
        if (compet < actLov) {
          married[0][pretendente] = no->current;
          remove_Pilha(&no);
          insere_pilha(&no, W[pretendente][actLov]);
          break;
        }
    }


  } 
      if(no == NULL){
        printf("Esquema finalizado!\n");
       for (int i = 0; i < 4; i++) {
            printf("Mulher %d casada com %d\n", i, married[0][i]);
           }
        return;
    }
   }
}

int main(){
  printf("Starting\n");
  int M[4][4] =  {{0,1,2,3},
                  {0,3,2,1},
                  {0,2,1,3},
                  {0,3,1,2}};
  
  int W[4][4] =  {{3,0,1,2},
                  {0,3,2,1},
                  {2,3,1,0},
                  {0,2,3,1}};
  ShapleGaley(M, W);
}
