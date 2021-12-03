#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


//_PTR NO DE ARVORE
typedef struct NoArvore * PtrNoArvore;

//NO DE ARVORE
typedef struct NoArvore{

  char chave[20];
  int paginas[10]; //{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};//-1 valor sempre invalido, n�o existem paginas negativas
  PtrNoArvore esquerda;
  PtrNoArvore direita;

}NoArvore;


//INICIALIZAR
void iniciaArvore(PtrNoArvore *arvore){
  (*arvore) = NULL;
}

//INSERIR
bool inserirArvore(PtrNoArvore *arvore, char x[]){

  if((*arvore) == NULL){
    (*arvore) = malloc(sizeof(NoArvore));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->chave,x);
    for(int i =0; i<10; i++){
      (*arvore)->paginas[i] = -1;
    }
    return true;
  }


  if((*arvore)->chave == x){
    printf("Warning!! Elemento Duplicado\n");
    return false;
  }


  if(strcmp((*arvore)->chave,x)==1){
    return inserirArvore(&(*arvore)->direita,x);
  }else
  {
    return inserirArvore(&(*arvore)->esquerda,x);
  }

}

//CONSULTAR
bool pesquisaArvore(PtrNoArvore *node, char x[], PtrNoArvore *retorno){

  if((*node) == NULL) return false;

  if( strcmp((*node)->chave, x)==0){
    (*retorno) = (*node);
    return true;
  }

  if(strcmp((*node)->chave,x)==1)
    return (pesquisaArvore(&(*node)->direita,x,retorno));
  else
    return (pesquisaArvore(&(*node)->esquerda,x,retorno));
}

//ESTA VAZIA
bool estaVaziaArvore(PtrNoArvore *arvore){
  return ((*arvore) == NULL );
}

//EMPRESSAO
void imprimeArvore(PtrNoArvore *arvore){
  if((*arvore) == NULL) return;




  imprimeArvore(&((*arvore)->direita));

  printf("\n%s",(*arvore)->chave);
  for(int i = 0; i<find_Int((*arvore)->paginas,10,-1); i++){
    printf(",%i",(*arvore)->paginas[i]);
  }

  imprimeArvore(&((*arvore)->esquerda));


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

bool removerArvore(PtrNoArvore *node, char x[]){

  //AUX PARA N PERDER A REFERENCIA
  PtrNoArvore Aux = (*node);

  //SE == NULL, O ELEMENTO NAO EXISTE
  if( (*node) == NULL) return false;

  //QUANDO O ELEMENTO FOR ENCONTRADO FAZER ESSE TRATAMENTO
  if(strcmp((*node)->chave,x)==0){

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
      strcpy((*node)->chave,Aux->chave);
    }

    free(Aux);
  }

//IF ELSE ABAIXO PERCORRE A ARVOVE, AT� ENCONTRAR O ELEMENTO
  if(strcmp((*node)->chave,x)==1)
    return (removerArvore(&(*node)->direita,x));
  else
    return (removerArvore(&(*node)->esquerda,x));

}


void Add_in_arvore(char linha [], PtrNoArvore *raiz){

  char * palavra;
  palavra = strtok(linha," <>,:");

  while (palavra != NULL)
 {
   palavra = strtok (NULL, " <>,:");
   if(palavra != NULL && palavra != "\n")
      inserirArvore(raiz,palavra);
 }


  return;
}

int find_Char(char string[], char c){

  for(int i = 0; i<strlen(string); i++){
    if(string[i] == c)
        return i;
  }

  return -1;

}

int find_Int(int vetor[],int len, int x){

  int i = 0;

  for(i = 0; i<len-1; i++){
    if(vetor[i] == x)
        return i;
    if(vetor[i] == -1){
      return i;
    }
  }

}

char *cut_string(char string[], int point_inicial, int point_final){

  char *new_string = malloc(sizeof(char)*(point_final+1));

  int j = 0;
  for(int i = point_inicial; i<point_final; i++){
    new_string[j] = string[i];
    j++;
  }

  new_string[j] = '\0';

  return new_string;
}

void busca_String(PtrNoArvore *raiz, char string[]){

  PtrNoArvore retorno;

  char * palavra;
  char *pagina_char;
  palavra = strtok(string," .,\n()");
  int pagina = 0;

  while (palavra != NULL)
 {
   if(find_Char(palavra,':')!=-1  &&  find_Char(palavra,'>')!=-1){
     char *pagina_char = cut_string(palavra,find_Char(palavra,':')+1,find_Char(palavra,'>'));
     pagina = atoi(pagina_char);
   }

   if(palavra != NULL && palavra != "\n")
      if(pesquisaArvore(raiz,palavra,&retorno)){
        retorno->paginas[find_Int(retorno->paginas,10,pagina)] = pagina;

      }

   //printf(" =%s= id: %i\n",palavra,gerador_ID_UNICO(palavra));
   palavra = strtok (NULL, " .,\n()");

 }






}

char * return_String(char nome_ark[], char *c){


  FILE *ark = fopen(nome_ark, "rt");

  char *string;
  int controle_de_letras = 0;
  int count_malloc = 0;



  char ponteiro;
  while(!feof(ark)){
    count_malloc +=1;
    ponteiro = fgetc(ark);// fgetc faz o ponteiro de leitura do arquivo ler EXATAMENTE a quantidade de caracteres presentes, e salva em count_malloc
  }

  if(count_malloc<3)//caso não tiver mais de 1 linha no arquivo, o caracter de controle recebe 'r', que retorna Arquivo inválido!
    *c = 'r';

  string = malloc((sizeof(char)*count_malloc)+2);

  fseek(ark,0,SEEK_SET);
  int final = 0;

  int i = 0;
  while(!feof(ark)){
    string[i] = fgetc(ark);
    i++;

    if(string[i] == EOF){
      final = i-1;
    }
  }


    //caso o ultimo digito do arquivo não for '\n', passa a ser
    if(string[final] != '\n'){
      string[final] = '\n';
    }

    string[count_malloc] = '\0';//a string sempre é finalizada na ultima posição de memoria


    return string;
  }

int main(){

  PtrNoArvore raiz;

  //inicializando arvore
  iniciaArvore(&raiz);

  



return 0;
}
