#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//_PTR NO DE ARVORE
typedef struct NoArvore * PtrNoArvore;

//NO DE ARVORE
typedef struct NoArvore{

  int chave;
  PtrNoArvore esquerda;
  PtrNoArvore direita;

}NoArvore;


//INICIALIZAR
void iniciaArvore(PtrNoArvore *arvore){
  (*arvore) = NULL;
}

//INSERIR
bool inserirArvore(PtrNoArvore *arvore, int x){

  if((*arvore) == NULL){
    (*arvore) = malloc(sizeof(NoArvore));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    (*arvore)->chave = x;
    return true;
  }


  if((*arvore)->chave == x){
    printf("Warning!! Elemento Duplicado\n");
    return false;
  }


  if(x > (*arvore)->chave){
    return inserirArvore(&(*arvore)->direita,x);
  }else
  {
    return inserirArvore(&(*arvore)->esquerda,x);
  }

}

//CONSULTAR
bool pesquisaArvore(PtrNoArvore *node, int x){

  if((*node) == NULL) return false;

  if( (*node)->chave == x) return true;

  if(x > (*node)->chave )
    return (pesquisaArvore(&(*node)->direita,x));
  else
    return (pesquisaArvore(&(*node)->esquerda,x));

}

//ESTA VAZIA
bool estaVaziaArvore(PtrNoArvore *arvore){
  return ((*arvore) == NULL );
}

//EMPRESSAO
void imprimeArvore(PtrNoArvore *arvore){
  if((*arvore) == NULL) return;


  printf("%i,",(*arvore)->chave);
  imprimeArvore(&((*arvore)->esquerda));
  imprimeArvore(&((*arvore)->direita));

}

//DESTRUIR
void destruirArvore(PtrNoArvore *node){

  if((*node) != NULL){
    destruirArvore(&(*node)->direita);
    destruirArvore(&(*node)->esquerda);
    free((*node));
    (*node) = NULL;
  }
}

PtrNoArvore GetMaxArv(PtrNoArvore *node){
  PtrNoArvore retorno;

  if((*node)->direita==NULL){
    retorno = (*node);
    (*node) = (*node)->direita;
    return retorno;
  }

  return GetMaxArv(&(*node)->direita);


}

bool removerArvore(PtrNoArvore *node, int x){

  //AUX PARA N PERDER A REFERENCIA
  PtrNoArvore Aux = (*node);

  //SE == NULL, O ELEMENTO NAO EXISTE
  if( (*node) == NULL) return false;

  //QUANDO O ELEMENTO FOR ENCONTRADO FAZER ESSE TRATAMENTO
  if( (*node)->chave == x){

    //CASO NODE FOR UMA FOLHA
    if((*node)->esquerda == NULL && (*node)->direita == NULL){
      (*node) = NULL;
    }else


    //SE TIVER APENAS A SUBARVORE ESQUERDA
    if((*node)->esquerda != NULL && (*node)->direita == NULL){
      (*node) = (*node)->esquerda;
    }else


    //SE TIVER APENAS A SUBARVORE DIREITA
    if((*node)->esquerda == NULL && (*node)->direita != NULL){
      (*node) = (*node)->direita;
    }else

    //SE TIVER 2 SUB_ARVORES
    {

      Aux = GetMaxArv(&(*node)->esquerda);
      (*node)->chave = Aux->chave;
    }

    free(Aux);
  }

//IF ELSE ABAIXO PERCORRE A ARVOVE, ATÉ ENCONTRAR O ELEMENTO
  if(x > (*node)->chave )
    return (removerArvore(&(*node)->direita,x));
  else
    return (removerArvore(&(*node)->esquerda,x));

}




int main(){

  PtrNoArvore raiz;

  //inicializando arvore
  iniciaArvore(&raiz);


  inserirArvore(&raiz,20);
  inserirArvore(&raiz,30);
  inserirArvore(&raiz,19);
  inserirArvore(&raiz,39);
  inserirArvore(&raiz,25);
  inserirArvore(&raiz,10);
  inserirArvore(&raiz,26);
  inserirArvore(&raiz,22);


  imprimeArvore(&raiz);
  removerArvore(&raiz,30);
  printf("\n");
  imprimeArvore(&raiz);



return 0;
}
