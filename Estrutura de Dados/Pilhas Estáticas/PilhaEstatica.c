#include <stdio.h>
#include <stdbool.h>

///////////////DEFINIR OS TIPOS DA ESTRUTURA DE DADOS////////////////////////////////////

#define MAX 8

typedef struct{

  //vetor (onde os dados serão armazenados)
  int vetor[MAX];

  //topo (define onde pode fazer a inserção e a remoção)
  int topo;

}Pilha_Estatica;

///////////////METODOS QUE ALTERAM A ESTRUTURA///////////////////////////////////////////


//Iniciar a estrutura

void Iniciar(Pilha_Estatica *Pilha){
  Pilha->topo = 0;
}

//Inserção
//INSERIDA ABAIXO

//Remoção
//INSERIDA ABAIXO

//Pesquiza  / Consulta


////////////SEGUNDO CONJUNTO DE METODOS///////////////////////////////////////////////////
////////////METODOS QUE NÃO ALTERAM A ESTRUTURA (METODOS DE CONSULTA)/////////////////////


//Verifica se esta vazia

bool esta_Vazia(Pilha_Estatica *Pilha){
  return Pilha->topo == 0;
}

//Verifica se esta cheia

bool esta_cheia(Pilha_Estatica *Pilha){
  return Pilha->topo == MAX;
}


void Inserir(Pilha_Estatica *Pilha, int Valor){

  if(esta_cheia(Pilha)==false){
    Pilha->vetor[Pilha->topo] = Valor;
    Pilha->topo++;
  }else{
    printf("A Pilha Esta Cheia!\n");
  }//if(esta_cheia)

}//Inserir

void Remover(Pilha_Estatica *Pilha){

  if(esta_Vazia(Pilha)==false)
    Pilha->topo--;
  else
    printf("A Pilha Esta Vazia!\n");

}//Remover

//Retorna o tamanho da estrutura (quantidade de elememtos)

int tamanho_Pilha(Pilha_Estatica *Pilha){
  return Pilha->topo;
}

//Imprimir a Estrutura

void printp(Pilha_Estatica *Pilha){

  printf("Pilha = { ");

  for(int i = 0; i<Pilha->topo; i++){
    printf("%i,", Pilha->vetor[i]);
  }

  printf(" }\n");

}//printp









int main(){

	Pilha_Estatica Pilha;

  Iniciar(&Pilha);


  printp(&Pilha);
  Inserir(&Pilha, 1);
  printp(&Pilha);
  Inserir(&Pilha, 2);
  printp(&Pilha);
  Inserir(&Pilha, 3);
  printp(&Pilha);
  Inserir(&Pilha, 4);
  printp(&Pilha);
  Inserir(&Pilha, 5);
  printp(&Pilha);
  Inserir(&Pilha, 6);
  printp(&Pilha);
  Inserir(&Pilha, 7);
  printp(&Pilha);
  Inserir(&Pilha, 8);
  printp(&Pilha);
  Inserir(&Pilha, 9);

  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);
  Remover(&Pilha);
  printp(&Pilha);

  return 0;
}//main
