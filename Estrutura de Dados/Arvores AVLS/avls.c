
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//_PTR NO DE Avl
typedef struct NoAvl * PtrNoAvl;

//NO DE Avl
typedef struct NoAvl{

  int chave;
  int altura;
  PtrNoAvl esquerda;
  PtrNoAvl direita;

}NoAvl;


//INICIALIZAR
void iniciaAvl(PtrNoAvl *Avl){
  (*Avl) = NULL;
}

//Captura altura do noavl
int getAlturaAvl(PtrNoAvl NoAvl){

  if(NoAvl == NULL) return 0;
  else  return NoAvl->altura;


}

int attAlturaAvl(PtrNoAvl *NoAvl){

  int Alt_SubArv_Dir = getAlturaAvl((*NoAvl)->direita);
  int Alt_SubArv_Esq = getAlturaAvl((*NoAvl)->esquerda);

  if(Alt_SubArv_Esq > Alt_SubArv_Dir) return(Alt_SubArv_Esq+1);
  else                                return(Alt_SubArv_Dir+1);

}

//ROTACOES
void rotSimplesDir(PtrNoAvl *p){

  PtrNoAvl u = (*p)->esquerda;
  (*p)->esquerda = u->direita;
  u->direita = (*p);

  (*p)->altura = attAlturaAvl(&(*p));
  u->altura = attAlturaAvl(&u);

  (*p) = u;

}

void rotSimplesEsq(PtrNoAvl *p){

  PtrNoAvl u = (*p)->direita;
  (*p)->direita = u->esquerda;
  u->esquerda = (*p);

  (*p)->altura = attAlturaAvl(&(*p));
  u->altura = attAlturaAvl(&u);

  (*p) = u;

}

void rotDuplaEsq(PtrNoAvl *p){

  PtrNoAvl u = (*p)->direita;
  PtrNoAvl v = u->esquerda;

  u->esquerda = v->direita;
  (*p)->direita = v->esquerda;
  v->esquerda = (*p);
  v->direita = u;

  (*p)->altura = attAlturaAvl(&(*p));
  u->altura = attAlturaAvl(&u);
  v->altura = attAlturaAvl(&v);

  (*p) = v;

}

void rotDuplaDir(PtrNoAvl *p){

  PtrNoAvl u = (*p)->esquerda;
  PtrNoAvl v = u->direita;

  u->direita = v->esquerda;
  (*p)->esquerda = v->direita;
  v->direita = (*p);
  v->esquerda = u;

  (*p)->altura = attAlturaAvl(&(*p));
  u->altura = attAlturaAvl(&u);
  v->altura = attAlturaAvl(&v);

  (*p) = v;

}

//APLICAR ROTACOES
void aplicarRotacoes(PtrNoAvl *NoAvl){

  int Alt_SubArv_Dir = getAlturaAvl((*NoAvl)->direita);
  int Alt_SubArv_Esq = getAlturaAvl((*NoAvl)->esquerda);

  int balanco = Alt_SubArv_Dir - Alt_SubArv_Esq;

  if(balanco == 2){//rotacao para a esq
    PtrNoAvl temp = (*NoAvl)->direita;
    int tempAD = getAlturaAvl(temp->direita);
    int tempAE = getAlturaAvl(temp->esquerda);

    printf("balanco 2\n");


    if(tempAE > tempAD){
      rotDuplaEsq(NoAvl);
    }else{
      rotSimplesEsq(NoAvl);
    }
    return;

  }else if(balanco == -2){//rotacao para a dir
    PtrNoAvl temp = (*NoAvl)->esquerda;
    int tempAD = getAlturaAvl(temp->direita);
    int tempAE = getAlturaAvl(temp->esquerda);

    printf("balanco -2\n");

    if(tempAD > tempAE){
      rotDuplaDir(NoAvl);
    }else{
      rotSimplesDir(NoAvl);
    }
    return;
  }

}


//INSERIR
bool inserirAvl(PtrNoAvl *Avl, int x){

  if((*Avl) == NULL){
    (*Avl) = malloc(sizeof(NoAvl));
    (*Avl)->direita = NULL;
    (*Avl)->esquerda = NULL;
    (*Avl)->chave = x;
    (*Avl)->altura =1;
    return true;
  }

  if((*Avl)->chave == x){
    printf("Warning!! Elemento Duplicado\n");
    return false;
  }

  bool insersao;


  if(x > (*Avl)->chave){
    insersao = inserirAvl(&(*Avl)->direita,x);
  }else
  {
    insersao = inserirAvl(&(*Avl)->esquerda,x);
  }

  (*Avl)->altura = attAlturaAvl(&(*Avl));
  aplicarRotacoes(Avl);

  if(insersao == false) return false;




}

//CONSULTAR
bool pesquisaAvl(PtrNoAvl *NoAvl, int x){

  if((*NoAvl) == NULL) return false;

  if( (*NoAvl)->chave == x) return true;

  if(x > (*NoAvl)->chave )
    return (pesquisaAvl(&(*NoAvl)->direita,x));
  else
    return (pesquisaAvl(&(*NoAvl)->esquerda,x));

}

//ESTA VAZIA
bool estaVaziaAvl(PtrNoAvl *Avl){
  return ((*Avl) == NULL );
}

//EMPRESSAO
void imprimeAvl(PtrNoAvl *Avl){
  if((*Avl) == NULL) return;


  printf("%i,",(*Avl)->chave,(*Avl)->altura);
  imprimeAvl(&((*Avl)->esquerda));
  imprimeAvl(&((*Avl)->direita));

}

//DESTRUIR
void destruirAvl(PtrNoAvl *NoAvl){

  if((*NoAvl) != NULL){
    destruirAvl(&(*NoAvl)->direita);
    destruirAvl(&(*NoAvl)->esquerda);
    free((*NoAvl));
    (*NoAvl) = NULL;
  }
}

PtrNoAvl GetMaxArv(PtrNoAvl *NoAvl){
  PtrNoAvl retorno;

  if((*NoAvl)->direita==NULL){
    retorno = (*NoAvl);
    (*NoAvl) = (*NoAvl)->direita;
    return retorno;
  }

  return GetMaxArv(&(*NoAvl)->direita);


}

bool removerArvore(PtrNoAvl *NoAvl, int x){

  //AUX PARA N PERDER A REFERENCIA
  PtrNoAvl Aux = (*NoAvl);

  //SE == NULL, O ELEMENTO NAO EXISTE
  if( (*NoAvl) == NULL) return false;

  //QUANDO O ELEMENTO FOR ENCONTRADO FAZER ESSE TRATAMENTO
  if( (*NoAvl)->chave == x){

    //CASO NoAvl FOR UMA FOLHA
    if((*NoAvl)->esquerda == NULL && (*NoAvl)->direita == NULL){
      (*NoAvl) = NULL;
    }else


    //SE TIVER APENAS A SUBARVORE ESQUERDA
    if((*NoAvl)->esquerda != NULL && (*NoAvl)->direita == NULL){
      (*NoAvl) = (*NoAvl)->esquerda;
    }else


    //SE TIVER APENAS A SUBARVORE DIREITA
    if((*NoAvl)->esquerda == NULL && (*NoAvl)->direita != NULL){
      (*NoAvl) = (*NoAvl)->direita;
    }else

    //SE TIVER 2 SUB_ARVORES
    {

      Aux = GetMaxArv(&(*NoAvl)->esquerda);
      (*NoAvl)->chave = Aux->chave;
    }

    free(Aux);
    return true;
  }

//IF ELSE ABAIXO PERCORRE A ARVOVE, ATÉ ENCONTRAR O ELEMENTO

  bool remove;

  if(x > (*NoAvl)->chave )
    remove = (removerArvore(&(*NoAvl)->direita,x));
  else
    remove = (removerArvore(&(*NoAvl)->esquerda,x));

  (*NoAvl)->altura = attAlturaAvl(NoAvl);
  aplicarRotacoes(NoAvl);

}


int main(){

  PtrNoAvl raiz;

  //inicializando Avl
  iniciaAvl(&raiz);


  inserirAvl(&raiz,40);
  inserirAvl(&raiz,30);
  inserirAvl(&raiz,50);
  inserirAvl(&raiz,29);
  inserirAvl(&raiz,31);
  inserirAvl(&raiz,55);
  inserirAvl(&raiz,32);

  removerArvore(&raiz,55);//nessa remocao acontece uma rotacao dupla pra direita.

  //já testei a rotação dupla pra esquerda e tmb funcionou
  //não encontrei nenhum bug na remoção
  //ambas as rotacoes simples tmb funcionam

  //comparei as impressões pre ordem com o a impressão pre oredem do site: https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
  //comparei em todos os casos possiveis e funcionou sem bugs (pelo menos nao encontrei). (0bs: o site buga com numeros negativos)



  imprimeAvl(&raiz);



return 0;
}
