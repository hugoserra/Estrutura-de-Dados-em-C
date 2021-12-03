#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////OPERAÇÕES RELACIONADAS A ESTRUTURA DE DADOS (LISTA)////////////////////////
typedef struct NoLista* PtrNoLista;

typedef struct NoLista{

  int chave;
  char nome[20];
  char sexo_mf;
  int peso_kg;
  int altura_cm;
  PtrNoLista proximo;
  PtrNoLista anterior; //duplamente encadeada

}NoLista;

//Lista Ordenada
typedef struct {

  PtrNoLista inicio;

  int qtdeElementos;

}ListaOrdenada;

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

void inserirListaOrdenada(ListaOrdenada *lista,int valor){
  //situações de inserção

  //situações que sempre ocorrem

    //criar um novo no
    PtrNoLista NovoNo = malloc(sizeof(NoLista));
    //copiar o valor a ser inserido no novo no
    NovoNo->chave = valor;

  ////////situação 1 é  NÃO É IGUAL A situação 2 NEM A 3

  //1 lista ta vazia
  if(estaVaziaListaOrdenada(lista)){
    //proximo de novo nó aponta para inicio (NULL)
    NovoNo->proximo = lista->inicio;
    //anterior de novo nó aponta para inicio (NULL)
    NovoNo->anterior = lista->inicio;
    //inicio recebe novo nó
    lista->inicio = NovoNo;

  }//if(vazia) ou if(menor)

  //2 Valor menor que o contido no inicio
  else if(valor<lista->inicio->chave){
    //proximo do novo nó aponta para inicio
    NovoNo->proximo = lista->inicio;
    //anterior novo nó, aponta para anterior do inicio (NULL)
    NovoNo->anterior = lista->inicio->anterior;
    //Anterior de inicio aponta para novo nó
    lista->inicio->anterior = NovoNo;
    //inicio recebe novo nó
    lista->inicio = NovoNo;

  }else{
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
      //Anterior de novo nó recebe Auxiliar
      NovoNo->anterior = Aux;
      //Aux->proximo = proximo do elemento anterior ao elemento maior que o valor a ser inserido
      //Aux->proximo aponta para novoNo
      Aux->proximo = NovoNo;
  }

  //situação que sempre ocorre
  lista->qtdeElementos++;
}//inserirListaOrdenada

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

void destruirListaOrdenada(ListaOrdenada *lista){

  while(lista->inicio != NULL){
    //remove sempre o primerio elemento, evitando de executar a função de remoção inteira
    removerListaOrdenada(lista,lista->inicio->chave);
  }
}//destruirListaOrdenada

void imprimirListaOrdenada(ListaOrdenada *lista, char Sentido){



  if(estaVaziaListaOrdenada(lista)==false){

    PtrNoLista Aux;
    Aux = lista->inicio;

    printf("Lista = {");

    if(Sentido == 'C'){//Se sentido == C, imprime em ordem crescente

      while(Aux != NULL){
        printf(" %i, ",Aux->chave);
        Aux = Aux->proximo;
      }

    }else{// senão em ordem decrescente

      //Aux percorre até o ultimo elemento
      while(Aux->proximo != NULL){
        Aux = Aux->proximo;
      }

      while(Aux != NULL){//Aux percorre do ultimo ao primeiro, imprimindo
        printf(" %i, ",Aux->chave);
        Aux = Aux->anterior;
      }//while
    }//else

  printf("}\n");
  }else{
    printf("Lista = {}\n");
  }
}//imprimirListaOrdenada

//retorna por referencia o ponteiro que armazena as informações do elemento encontrado
bool consultaListaOrdenada(ListaOrdenada *lista, int valor_chave, PtrNoLista *elemento){

  PtrNoLista Aux = lista->inicio;

  //enquanto proximo de aux for != de NULL, e chave de aux for diferente da procutada, aux = aux->proximo
  while(Aux->proximo != NULL && Aux->chave != valor_chave){
    Aux = Aux->proximo;
  }

  //se aux == NULL o elemento não foi encontrado, então retorna false
  if(Aux==NULL)
    return false;
  else{//senão, foi encontrado, retorna Aux por referencia, e return true;
    *elemento = Aux;
    return true;
  }

}//consultaListaOrdenada

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNÇÕES RELACIONADAS A ATIVIDADE//////////////////////////////////

void inserir_ark(FILE *ark){

  while (!feof(ark)) {
    printf("%c\n",fgetc(ark));
  }

}//inserir_ark


int main(){

  ListaOrdenada lista;

  iniciaListaOrdenada(&lista);

  inserirListaOrdenada(&lista, 4);
  inserirListaOrdenada(&lista, 3);
  inserirListaOrdenada(&lista, 2);
  inserirListaOrdenada(&lista, 5);
  inserirListaOrdenada(&lista, 6);
  inserirListaOrdenada(&lista, 1);


  imprimirListaOrdenada(&lista,'C');
  imprimirListaOrdenada(&lista,'s');

  FILE *ark = fopen("entrada01.txt","w");

  inserir_ark(ark);





  return 0;
}//main
