#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////LISTA ORDENADA SINGLE////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

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


////////////////////////OPERACOES////////////////////////

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

bool consultaListaOrdenada(ListaOrdenada *lista, int valor_chave){

  PtrNoLista Aux = lista->inicio;

  //enquanto proximo de aux for != de NULL, e chave de aux for diferente da procutada, aux = aux->proximo
  while(Aux != NULL && Aux->chave != valor_chave){
    Aux = Aux->proximo;
  }

  //se aux == NULL o elemento nao foi encontrado, entao retorna false
  if(Aux==NULL)
    return false;
  else{//senao: foi encontrado,  return true;
    return true;
  }

}//consultaListaOrdenada

//inserir
void inserirListaOrdenada(ListaOrdenada *lista,int valor){

    //se o elemento já existir, retorna
    if(consultaListaOrdenada(lista,valor)) return;

    PtrNoLista NovoNo = malloc(sizeof(NoLista));
    NovoNo->chave = valor;

  //se estiver vazia ou valor for menor q o primeiro elemento
  if(estaVaziaListaOrdenada(lista) || valor<lista->inicio->chave){

    NovoNo->proximo = lista->inicio;
    lista->inicio = NovoNo;

  }
  else{
      PtrNoLista Aux;
      Aux = lista->inicio;

      while(Aux->proximo!=NULL && Aux->proximo->chave < valor)
        Aux = Aux->proximo;

      NovoNo->proximo = Aux->proximo;
      Aux->proximo = NovoNo;
  }
  lista->qtdeElementos++;
}//inserirListaOrdenada

bool removerListaOrdenada(ListaOrdenada *lista, int valor){

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

  //se o elemento a ser removido nÃ£o for o primeiro elemento da lista

  //novo no percorre criado
  PtrNoLista percorre;
  //percorre aponta para inicio
  percorre = lista->inicio;
  //percorre deve encontrar o ponto de insersao (percorre)
  while(percorre->proximo!=NULL && percorre->proximo->chave < valor)
    percorre = percorre->proximo;

  //se percorre proximo for igual a NULL e sua chave < valor, o elemento nao foi encontrado
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
    //remove sempre o primerio elemento, evitando de executar a funcao de remocao inteira
    removerListaOrdenada(lista,lista->inicio->chave);
  }
}//destruirListaOrdenada

//impressao
void imprimirListaOrdenada(ListaOrdenada *lista){

  if(estaVaziaListaOrdenada(lista)==false){

    PtrNoLista Aux;
    Aux = lista->inicio;

    while(Aux != NULL){
      printf(",%i",Aux->chave);
      Aux = Aux->proximo;
    }

  }else{

  }
}//imprimirListaOrdenada


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ARVORE BINARIA DE STRING////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

//_PTR NO DE ARVORE
typedef struct NoArvore * PtrNoArvore;

//NO DE ARVORE
typedef struct NoArvore{

  char chave[20];
  ListaOrdenada paginas;
  PtrNoArvore esquerda;
  PtrNoArvore direita;

}NoArvore;


//INICIALIZAR
void iniciaArvore(PtrNoArvore *arvore){
  (*arvore) = NULL;
}

//INSERIR
bool inserirArvore(PtrNoArvore *arvore, char x[]){

  //se (*arvore == null) o ponto de inserção foi encontrado. então, iniciamos o no de arvore. alocando memoria, e atribuindo seus valores
  if((*arvore) == NULL){
    (*arvore) = malloc(sizeof(NoArvore));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->chave,x);
    iniciaListaOrdenada(&(*arvore)->paginas);
    return true;
  }


  if(strcmp((*arvore)->chave,x)==0){
    printf("Warning!! Elemento Duplicado\n");
    return false;
  }


  //este bloco de código caminha até o ponto de inserção utilizando recursividade.
  if(strcmp((*arvore)->chave,x)==1){
    return inserirArvore(&(*arvore)->direita,x);
  }else
  {
    return inserirArvore(&(*arvore)->esquerda,x);
  }


}

//CONSULTAR
bool pesquisaArvore(PtrNoArvore *node, char x[], PtrNoArvore *retorno){

  //caso o elemento não exista, retorne false
  if((*node) == NULL) return false;

  //caso o elemento exista, retorne o (*node) deste elemento por referencia, e return true
  if( strcmp((*node)->chave, x)==0){
    (*retorno) = (*node);
    return true;
  }


  //percorre a arvore por recursividade executando as duas funções de analise acima
  //este percurso mantem a propriedade de busca das arvores
  if(strcmp((*node)->chave,x)==1)
    return (pesquisaArvore(&(*node)->direita,x,retorno));
  else
    return (pesquisaArvore(&(*node)->esquerda,x,retorno));
}

//IMPRESSAO
void imprimeArvore(PtrNoArvore *arvore){

  //quando chega em uma folha retorna, para começar a desempilhar a recursividade
  if((*arvore) == NULL) return;

  //percorre para a direita até que o if acima seja true, e comece a desempilhar a recursividade
  imprimeArvore(&((*arvore)->direita));

  //imprime os dados necessarios
  //nesta etapa, a recursividade já está ocorrendo
  printf("%s",(*arvore)->chave);
  imprimirListaOrdenada(&(*arvore)->paginas);
  printf("\n");

  //nesta etapa, a recursividade já está ocorrendo
  imprimeArvore(&((*arvore)->esquerda));

}

//DESTRUIR
void destruirArvore(PtrNoArvore *node){

  //funciona exatamente como a função de imprimir, porem, em vez de printar na tela, desalocamos a memoria.
  if((*node) != NULL){
    destruirArvore(&(*node)->direita);
    destruirArvore(&(*node)->esquerda);
    destruirListaOrdenada(&(*node)->paginas);
    free((*node));
    (*node) = NULL;
  }
}

PtrNoArvore GetMaxArv(PtrNoArvore *node){
  PtrNoArvore retorno;

  //caminha para direita até o maior elemento
  //quando este elemento for encontrado, retorne (*node)
  if((*node)->direita==NULL){
    retorno = (*node);
    (*node) = (*node)->direita;
    return retorno;
  }

  return GetMaxArv(&(*node)->direita);


}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNÇÕES PARA A ATIVIDADE////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

//transforma a string para minusculo
char *stolower(char string[]){
  //codigo simples para comentarios
  char *ret = malloc(sizeof(char)*strlen(string)+1);

  for(int i = 0; i<strlen(string); i++)
  ret[i] = tolower(string[i]);


  ret[strlen(string)] = '\0';

  return ret;

}

//adiciona as palavra da string linha na arvore
void Add_in_arvore(char linha [], PtrNoArvore *raiz){
  //codigo simples para comentarios
  char * palavra;
  palavra = strtok(linha," <>,:");

  while (palavra != NULL)
 {
   palavra = strtok (NULL, " <>,:");
   if(palavra != NULL && palavra != "\n")
      inserirArvore(raiz,stolower(palavra));
 }


  return;
}

//percorre a string procurando pelo char c. caso encontre, retorna a posição do ponteiro na string, senão retorna -1.
int find_Char(char string[], char c){
  //codigo simples para comentarios
  for(int i = 0; i<strlen(string); i++){
    if(string[i] == c)
        return i;
  }

  return -1;

}

//recorta a string nas posicoes iniciais e finais estabelecidas
char *cut_string(char string[], int point_inicial, int point_final){
  //codigo simples para comentarios
  char *new_string = malloc(sizeof(char)*(point_final+1-point_inicial));

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
  palavra = strtok(string," .,(;)\n");
  int pagina = 0;

  //palavra percorre a string assumindo o valor de palavra por palavra
  while (palavra != NULL)
 {
   //caso existe ':' && '>' na palavra, significa que está palavra é a pagina do arquivo  (<page:1>)
   if(find_Char(palavra,':')!=-1  &&  find_Char(palavra,'>')!=-1){
     //pagina_char recebe a string que estiver entre os caracteres ':' && '>'. Exemplo: <page:333> pagina_char = '333'
     //leia a função cut_string e find_char para compreender melhor
     char *pagina_char = cut_string(palavra,find_Char(palavra,':')+1,find_Char(palavra,'>'));
     //int pagina recebe a conversão para inteiro de pagina_char
     pagina = atoi(pagina_char);
   }//até que outra pagina seja encontrada este código não executara, pagina = 1 até que palavra seja = a '<page:1>'


   //verifica se a palavra existe na arvore, se existir PtrNoArvore retorno, recebe por referencia (*node) que tem essa palavra
   if(palavra != NULL && palavra != "\n")
      if(pesquisaArvore(raiz,stolower(palavra),&retorno))
        //a lista ordenada "paginas" contida em retorno, recebe o valor da pagina. esta lista nao permite repeticoes
        inserirListaOrdenada(&retorno->paginas,pagina);

    //para que palavra receba a proxima palavra a cada loop while
   palavra = strtok (NULL, " .;,()\n");

 }//while

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

  if(count_malloc<3)//caso nao tiver mais de 1 linha no arquivo, o caracter de controle recebe 'r', que retorna Arquivo invalido!
    *c = 'r';

  //aloca exatamente a quantidade de caracteres presentes no arquivo
  string = malloc((sizeof(char)*count_malloc)+2);

  //ponteiro de leitura retorna para o inicio do arquivo
  fseek(ark,0,SEEK_SET);
  int final = 0;

  int i = 0;
  //percorre o arquivo copiando-o para string letra por letra, até o final
  while(!feof(ark)){
    string[i] = fgetc(ark);
    i++;

    if(string[i] == EOF){
      //valor armazenado para receber um '\n'
      final = i-1;
    }
  }


    //caso o ultimo digito do arquivo nao for '\n', passa a ser
    if(string[final] != '\n'){
      string[final] = '\n';
    }

    string[count_malloc] = '\0';//a string sempre e finalizada na ultima posisao de memoria

    fclose(ark);
    return string;
  }

//funciona igual a imprimirListaOrdenada, porem em vez de imprimir, salva no arquivo
void Lista_Para_ark(ListaOrdenada *lista, FILE *Ark){

    if(estaVaziaListaOrdenada(lista)==false){

      PtrNoLista Aux;
      Aux = lista->inicio;

      while(Aux != NULL){
        fprintf(Ark,",%i",Aux->chave);
        Aux = Aux->proximo;
      }

    }
  }//imprimirListaOrdenada

//funciona igual a imprimeArvore, porem em vez de imprimir, salva no arquivo
void Arvore_para_Ark(PtrNoArvore *arvore,FILE *Ark){

    if((*arvore) == NULL) return;

    Arvore_para_Ark(&((*arvore)->direita),Ark);

    fprintf(Ark,"%s",(*arvore)->chave);
    Lista_Para_ark(&(*arvore)->paginas,Ark);
    fprintf(Ark,"\n");

    Arvore_para_Ark(&((*arvore)->esquerda),Ark);

}

int main(int argc, const char * argv[]){

  if(argc!= 3) {
    printf("\nQuantidade de parametros invalida!\n\n");
    return 0;
  }

  PtrNoArvore raiz;

  //inicializando arvore
  iniciaArvore(&raiz);

  //string recebe o texto do arquivo c recebe 'r' caso aconteça algum erro na leitura
  char c;
  char *string = return_String(argv[1],&c);

  //Cria arquivo de saída
  FILE *Ark = fopen(argv[2],"w");

  if(c=='r'){
    printf("\nErro na leitura do arquivo!\n\n");
    return 0;
  }

  //termos recebe string, até o primeiro caracter '>'. leia os comentarios da função cut_string e find_Char
  char *termos = cut_string(string,0,find_Char(string,'>'));

  //os termos são adicionados na arvore
  Add_in_arvore(termos,&raiz);

  //string recebe string a partir do primeiro caracter '>' até o final. leia os comentarios da função find_char
  string = cut_string(string,find_Char(string,'>'),strlen(string)-1);

  //verifica se as palavras contidas em string, existem na arvore, se existir o (*node) que contem
  //aquela palavra, recebe a pagina que a palavra está.
  busca_String(&raiz,string);

  //impressao em ordem, já imprime a lista de paginas tambem
  printf("\n");
  imprimeArvore(&raiz);
  printf("\n");

  //Salva no arquivo de saida EXATAMENTE o que é imprimido no prompt
  Arvore_para_Ark(&raiz,Ark);

  //destroi a arvore e a lista dentro dela.
  destruirArvore(&raiz);

  fclose(Ark);
  //o arquivo de entrada é fechado na função return string


return 0;
}
