#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//#####################PILHA DINAMICA ALL ESTRUTURAS#######################
//Nó de Pilha
  //int chave
  //*nóPilha
typedef struct NoPilha* PtNoPilha;

typedef struct NoPilha {

  int chave; //onde os dados serão armazenados
  PtNoPilha proximo;//ponteiro que aponta para esta mesma estrutura, no proximo elemento

}NoPilha;//

//ESTRUTURA DA PILHA DINAMICA

typedef struct{
  PtNoPilha topo;
  int qtd;

}Pilha_Dinamica;

//#####################PILHA DINAMICA ALL ESTRUTURAS#######################


///////////////////METODOS QUE ALTERAM A ESTRUTURA /////////////////

//INICIALIZAR  A ESTRUTURA
void iniciar_D(Pilha_Dinamica *Pilha){
  //Topo deve apontar para NULL
  Pilha->topo = NULL; //topo é um nó de pilha
  //quantidade deve receber zero
  Pilha->qtd = 0;


}//iniciar_D

// Inserir
void Inserir(Pilha_Dinamica *Pilha, int Valor){

  //Um novo nó é criado
  PtNoPilha aux;
  //A memoria para o novo nó é alocada
  aux = malloc(sizeof(NoPilha));

  //novo nó recebe o dado/Valor
  aux->chave = Valor;

  //"proximo" de aux, aponta para onde o topo apontava
  aux->proximo = Pilha->topo;

  //topo aponta para o novo nó
  Pilha->topo = aux;

  //quantidade recebe +=1;
  Pilha->qtd++;


}//Inserir

//Remover
//esta_vazia
bool esta_vazia(Pilha_Dinamica *Pilha){
  return Pilha->topo == NULL;
}//esta_vazia

void Remover(Pilha_Dinamica *Pilha){

  if(esta_vazia(Pilha)==false)
    Pilha->topo = Pilha->topo->proximo;
  else
    printf("Pilha Vazia!\n");

}//remover


//Iniciar

//Pesquisar (consulta o topo)

//Imprimir

void Imprimir(Pilha_Dinamica *Pilha){


PtNoPilha percorre;
printf("Pilha = { ");
for(percorre = Pilha->topo; percorre!=NULL; percorre = percorre->proximo){
  printf("%i,",percorre->chave);
}
printf(" }\n");

}//Imprimir

//Tamanho (quantidade de elementos da pilha)
int tamanho(Pilha_Dinamica *Pilha){
  return Pilha->qtd;
}//tamanho

//esta_cheia



//Destruir Pilha

int main(){

  Pilha_Dinamica Pilha;
  iniciar_D(&Pilha);

  Inserir(&Pilha, 1);
  Imprimir(&Pilha);
  Inserir(&Pilha, 2);
  Imprimir(&Pilha);
  Inserir(&Pilha, 3);
  Imprimir(&Pilha);
  Inserir(&Pilha, 4);
  Imprimir(&Pilha);
  Inserir(&Pilha, 5);
  Imprimir(&Pilha);

  printf("CONTROELE///////////////////\n");

  Remover(&Pilha);
  Imprimir(&Pilha);
  Remover(&Pilha);
  Imprimir(&Pilha);
  Remover(&Pilha);
  Imprimir(&Pilha);
  Remover(&Pilha);
  Imprimir(&Pilha);
  Remover(&Pilha);
  Imprimir(&Pilha);
  Remover(&Pilha);
  Imprimir(&Pilha);
  return 0;
}//return int main()
