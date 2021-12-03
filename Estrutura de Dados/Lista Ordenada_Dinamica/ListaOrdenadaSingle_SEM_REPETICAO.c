#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct NoLista* PtrNoLista;

typedef struct NoLista{

  int chave;
  PtrNoLista proximo;
  //PtrNoLista anterior; duplamente encadeada

}NoLista;

//Lista Ordenada
typedef struct {

  PtrNoLista inicio;

  int qtdeElementos;

}ListaOrdenada;


////////////////////////OPERAÇÕES////////////////////////

//iniciar
void iniciaListaOrdenada(ListaOrdenada *lista){
  //iniciar ptr = NULL
  lista->inicio = NULL;
  //contador = 0
  lista->qtdeElementos = 0;

}//iniciaListaOrdenada

bool estaVaziaListaOrdenada(ListaOrdenada *lista){
  return(lista->qtdeElementos==0);//ou ponteiro == null
}//estavazialistaOrdenada

int tamanhoListaOrdenada(ListaOrdenada *lista){
  return lista->qtdeElementos;
}//tamanhoListaOrdenada

//inserir

void inserirListaOrdenada(ListaOrdenada *lista,int valor){
  //situações de inserção

  //situações que sempre ocorrem

    //criar um novo no
    PtrNoLista NovoNo = malloc(sizeof(NoLista));
    //copiar o valor a ser inserido no novo no
    NovoNo->chave = valor;

  //1 lista ta vazia
    //novo nó aponta para inicio (NULL)
    //inicio apontar para novo nó
  //2valor menor que o contido no inicio
    //proximo do novo nó aponta para inicio
    //inicio aponta para novo nó

  ////////situação 1 é igual a situação 2, Logo://///////
  if(estaVaziaListaOrdenada(lista) || valor<lista->inicio->chave){
    //novo nó aponta para inicio (NULL)
    NovoNo->proximo = lista->inicio;
    //inicio apontar para novo nó
    lista->inicio = NovoNo;

  }//if(vazia) ou if(menor)
  else{
    //3 encontrar ponto de inserção
      //novo no Aux criado
      PtrNoLista Aux;
      //Aux aponta para inicio
      Aux = lista->inicio;
      //Aux deve encontrar o ponto de inserção (percorre)
      while(Aux->proximo!=NULL && Aux->proximo->chave < valor)
        Aux = Aux->proximo;
      //Novo nó recebe a posição de Aux, aponta para Aux
      NovoNo->proximo = Aux->proximo;
      //Aux->proximo = proximo do elemento anterior ao elemento maior que o valor a ser inserido
      //Aux->proximo aponta para novoNo
      Aux->proximo = NovoNo;
  }

  //situação que sempre ocorre
  lista->qtdeElementos++;
}//inserirListaOrdenada

//remover
bool removerListaOrdenada(ListaOrdenada *lista, int valor){

  //situações de remoção

    //se a lista estiver vazia ou o numero a ser removido for menor que o primeiro elemento
  if(estaVaziaListaOrdenada(lista) || valor < lista->inicio->chave){
    printf("Warning! Elemento inexistente ou lista vazia\n");
    return false;
  }//if(estavazia)

    //se o elemento a ser removido for o primeiro elemento da lista
  if(valor == lista->inicio->chave){

      //Aux aponta para inicio
      PtrNoLista Aux = lista->inicio;
      //incio aponta para proximo
      lista->inicio = lista->inicio->proximo;
      //desaloca memoria de aux (antigo inicio)
      free(Aux);
      //decrementa a quantidade de elementos
      lista->qtdeElementos--;

    return true;
  }//if(valor==inicio)

  //se o elemento a ser removido não for o primeiro elemento da lista

  //novo no percorre criado
  PtrNoLista percorre;
  //percorre aponta para inicio
  percorre = lista->inicio;
  //percorre deve encontrar o ponto de inserção (percorre)
  while(percorre->proximo!=NULL && percorre->proximo->chave < valor)
    percorre = percorre->proximo;

  //se percorre proximo for igual a NULL e sua chave < valor, o elemento não foi encontrado
  if(percorre->proximo == NULL || percorre->proximo->chave < valor){
    printf("Warning! Elemento inexistente\n");
    return false;
  }



  if(percorre->proximo->chave==valor){
    //novo Aux criado
    PtrNoLista Aux;
    //Aux recebe percorre->proximo
    Aux = percorre->proximo;
    //percorre proximo recebe percorre proximo proximo
    percorre->proximo = percorre->proximo->proximo;
    //desalocar memoria de Aux
    free(Aux);
    //decrementar qtdelementos
    lista->qtdeElementos--;

    return true;
  }

}//removerListaOrdenada

//destruir
void destruirListaOrdenada(ListaOrdenada *lista){

  while(lista->inicio != NULL){
    //remove sempre o primerio elemento, evitando de executar a função de remoção inteira
    removerListaOrdenada(lista,lista->inicio->chave);
  }
}//destruirListaOrdenada

//impressão
void imprimirListaOrdenada(ListaOrdenada *lista){

  if(estaVaziaListaOrdenada(lista)==false){

    PtrNoLista Aux;
    Aux = lista->inicio;

    printf("Lista = {");
    while(Aux != NULL){
      printf(" %i, ",Aux->chave);
      Aux = Aux->proximo;
    }
    printf("}\n");

  }else{
    printf("Lista = {}\n");
  }
}//imprimirListaOrdenada



int main(){

  ListaOrdenada lista;

  iniciaListaOrdenada(&lista);

  inserirListaOrdenada(&lista,5);
  inserirListaOrdenada(&lista,8);
  inserirListaOrdenada(&lista,3);
  inserirListaOrdenada(&lista,1);

  imprimirListaOrdenada(&lista);




  return 0;
}//main
