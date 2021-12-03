#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



typedef struct NoFila* PtrNoFila;

typedef struct NoFila {

  int chave; //onde os dados serão armazenados
  PtrNoFila proximo;//ponteiro que aponta para esta mesma estrutura, no proximo elemento

}NoFila;//


typedef struct{
  PtrNoFila inicio;//primeiro elemento da estrutura
  PtrNoFila fim;//ponteiro apara o ultimo eelemento da estrutura
  int quantidade;//quantidade de elemetos na estrutura


}FilaDinamica;

void Iniciar(FilaDinamica *f){

  f->inicio = NULL;
  f->fim = NULL;
  f->quantidade = 0;
}

bool vazia(FilaDinamica *f){
  return((f->quantidade)==0);
}

int tamanho(FilaDinamica *f){
  return(f->quantidade);
}

void enfileirar(FilaDinamica *f, int x){
  PtrNoFila aux = malloc(sizeof(NoFila));

  //aux recebe x
  aux->chave = x;
  //proximo do aux aponta pr aNULL
  aux->proximo = NULL;
  //quantidade +=1


  if(vazia(f)){
    //primeira inserção
    //inicio e fim aponta pra aux
    f-> inicio = f-> fim = aux;


  }else{
    // não é a primeira inserção
    f->fim->proximo = aux;
    f->fim = aux;

  }
  f->quantidade++;

}
void Imprimir(FilaDinamica *f){

  PtrNoFila in;
  printf("Fila {");
  for(in = f->inicio; in!=NULL; in = in->proximo){
    printf("%i,",in->chave);
  }
  printf("}\n");

}

int removerFila(FilaDinamica *f){
  int ret;

  if(!vazia(f)){
    PtrNoFila aux = f->inicio;
    f->inicio = f->inicio->proximo;
    ret = aux->chave;
    free(aux);
  }else{
    printf("Warning!");
  }
return ret;
}

int main(){

  FilaDinamica fila;

  //inicializar
  Iniciar(&fila);


  enfileirar(&fila, 10);                //   enqueue(FILA, 10)
                  //
  enfileirar(&fila, 42);                // * enqueue(FILA, 42)
                  //
  enfileirar(&fila, -4);                // * enqueue(FILA,-4)
                  //
  enfileirar(&fila, 25);                // * enqueue(FILA, 25)
                  //
  enfileirar(&fila, 17);                // * enqueue(FILA, 17)
                  //
  enfileirar(&fila, 3);                // * enqueue(FILA, 3)
                  //
  removerFila(&fila);                // * dequeue(FILA)
                  //
                  // * first(FILA)
                  //
                  // * last(FILA)
                  //
  removerFila(&fila);                 // * dequeue(FILA)
                  //
  removerFila(&fila);                 // * dequeue(FILA)
                  //
  enfileirar(&fila, removerFila(&fila));                 // * enqueue(FILA, dequeue(FILA))
                  //
  enfileirar(&fila, 36);                // * enqueue(FILA, 36)
                  //
  enfileirar(&fila, 67);                // * enqueue(FILA, 67)
                  //
  removerFila(&fila);                 // * dequeue(FILA)
                  //
                  // * last(FILA)
                  //
  removerFila(&fila);                 // * dequeue(FILA)
                  //
  enfileirar(&fila, 90);                // * enqueue(FILA, 90)


  Imprimir(&fila);
  //detruir estrutura
  return 0;
}//main()
