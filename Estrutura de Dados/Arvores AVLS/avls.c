
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
  //printf("Balanco %i %i\n",(*NoAvl)->chave,balanco);

  if(balanco > 1){//rotacao para a esq
    PtrNoAvl temp = (*NoAvl)->direita;
    int tempAD = getAlturaAvl(temp->direita);
    int tempAE = getAlturaAvl(temp->esquerda);




    if(tempAE > tempAD){
      rotDuplaEsq(NoAvl);
    }else{
      rotSimplesEsq(NoAvl);
    }
    return;

  }else if(balanco < -1){//rotacao para a dir
    PtrNoAvl temp = (*NoAvl)->esquerda;
    int tempAD = getAlturaAvl(temp->direita);
    int tempAE = getAlturaAvl(temp->esquerda);



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
    printf("Warning!! Elemento %i Duplicado\n",x);
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


  printf("%i\n",(*Avl)->chave,(*Avl)->altura);
  imprimeAvl(&((*Avl)->esquerda));
  imprimeAvl(&((*Avl)->direita));

}

void aplicarRotacoes_ALL(PtrNoAvl *NoAvl){
  if((*NoAvl) == NULL) return;



  aplicarRotacoes_ALL(&((*NoAvl)->esquerda));
  aplicarRotacoes_ALL(&((*NoAvl)->direita));

  printf("ROTACAO %i\n",(*NoAvl)->chave);
  (*NoAvl)->altura = attAlturaAvl(NoAvl);
  aplicarRotacoes(NoAvl);

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
    return retorno;
  }

  GetMaxArv(&(*NoAvl)->direita);


}

PtrNoAvl GetMaxArv_PAI(PtrNoAvl *NoAvl){
  PtrNoAvl retorno;

  if((*NoAvl)->direita->direita==NULL){
    retorno = (*NoAvl);
    return retorno;
  }

  GetMaxArv_PAI(&(*NoAvl)->direita);


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



      if((*NoAvl)->esquerda->chave == Aux->chave){
        (*NoAvl)->esquerda = Aux->esquerda;
      }else{
        PtrNoAvl pai = GetMaxArv_PAI(&(*NoAvl)->esquerda);
        pai->direita = Aux->esquerda;

      }
    }

    Aux = NULL;
    free(Aux);

    aplicarRotacoes_ALL(NoAvl);
    return true;
  }

//IF ELSE ABAIXO PERCORRE A ARVOVE, ATÉ ENCONTRAR O ELEMENTO

  bool remove;

  if(x > (*NoAvl)->chave )
    remove = (removerArvore(&(*NoAvl)->direita,x));
  else
    remove = (removerArvore(&(*NoAvl)->esquerda,x));


}


int main(){

  PtrNoAvl raiz;

  //inicializando Avl
  iniciaAvl(&raiz);


  inserirAvl(&raiz,40);
  inserirAvl(&raiz,20);
  inserirAvl(&raiz,26);
  inserirAvl(&raiz,28);
  inserirAvl(&raiz,36);
  inserirAvl(&raiz,42);
  inserirAvl(&raiz,56);
  inserirAvl(&raiz,14);
  inserirAvl(&raiz,18);
  inserirAvl(&raiz,17);
  inserirAvl(&raiz,90);
  inserirAvl(&raiz,70);
  inserirAvl(&raiz,80);
  inserirAvl(&raiz,75);
  inserirAvl(&raiz,5);
  inserirAvl(&raiz,9);
  inserirAvl(&raiz,8);
  inserirAvl(&raiz,23);
  inserirAvl(&raiz,98);
  inserirAvl(&raiz,82);
  inserirAvl(&raiz,71);
  inserirAvl(&raiz,63);
  inserirAvl(&raiz,11);
  inserirAvl(&raiz,19);
  inserirAvl(&raiz,27);
  inserirAvl(&raiz,33);
  inserirAvl(&raiz,85);
  inserirAvl(&raiz,102);
  inserirAvl(&raiz,120);
  inserirAvl(&raiz,111);
  inserirAvl(&raiz,99);
  inserirAvl(&raiz,101);
  inserirAvl(&raiz,118);
  inserirAvl(&raiz,220);
  inserirAvl(&raiz,300);
  inserirAvl(&raiz,289);
  inserirAvl(&raiz,271);
  inserirAvl(&raiz,122);
  inserirAvl(&raiz,132);
  inserirAvl(&raiz,131);
  inserirAvl(&raiz,146);
  inserirAvl(&raiz,0);
  inserirAvl(&raiz,3);



  removerArvore(&raiz,289);
  removerArvore(&raiz,271);
  removerArvore(&raiz,300);


  removerArvore(&raiz,70);
  removerArvore(&raiz,90);
  removerArvore(&raiz,11);
  removerArvore(&raiz,19);
  removerArvore(&raiz,27);
  removerArvore(&raiz,33);
  removerArvore(&raiz,85);






  imprimeAvl(&raiz);



return 0;
}
