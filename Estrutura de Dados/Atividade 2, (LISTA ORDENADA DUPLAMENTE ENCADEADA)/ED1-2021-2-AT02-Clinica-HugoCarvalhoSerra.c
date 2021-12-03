#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>


///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////OPERAÇÕES RELACIONADAS A ESTRUTURA DE DADOS (LISTA)////////////////////////
typedef struct NoLista* PtrNoLista;

typedef struct NoLista{

  int chave;
  char nome[28];
  char sexo_mf[2];
  float peso_kg;
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

bool imprimir_gravar_ListaOrdenada(ListaOrdenada *lista, int Sentido,FILE *ark,char gravar_ou_imprimir){

  if(estaVaziaListaOrdenada(lista)==false){

    PtrNoLista Aux;
    Aux = lista->inicio;

    if(Sentido == 1){//Se sentido == 1, imprime em ordem crescente

      while(Aux != NULL){//percore a lista, imprimindo ou gravando no arquivo, sentido CRESCENTE

        if(gravar_ou_imprimir=='i')
          printf("{%i,%s,%s,%.1f,%i}\n",Aux->chave,Aux->nome,Aux->sexo_mf,Aux->peso_kg,Aux->altura_cm);
        else
          fprintf(ark,"{%i,%s,%s,%.1f,%i}\n",Aux->chave,Aux->nome,Aux->sexo_mf,Aux->peso_kg,Aux->altura_cm);

        Aux = Aux->proximo;
      }

    }else if(Sentido = 2){// se == 2, em ordem decrescente

      //Aux percorre até o ultimo elemento
      while(Aux->proximo != NULL){
        Aux = Aux->proximo;
      }

      while(Aux != NULL){////percore a lista, imprimindo ou gravando no arquivo, sentido DECRESCENTE
        if(gravar_ou_imprimir=='i')
          printf("{%i,%s,%s,%.1f,%i}\n",Aux->chave,Aux->nome,Aux->sexo_mf,Aux->peso_kg,Aux->altura_cm);
        else
          fprintf(ark,"{%i,%s,%s,%.1f,%i}\n",Aux->chave,Aux->nome,Aux->sexo_mf,Aux->peso_kg,Aux->altura_cm);

        Aux = Aux->anterior;
      }//while
    }//else
    return true;
  }else{
    printf("Warning! Lista = {}\n");
    return false;
  }
}//imprimirListaOrdenada



//retorna por referencia o ponteiro que armazena as informações do elemento encontrado
bool consultaListaOrdenada(ListaOrdenada *lista, int valor_chave, PtrNoLista *elemento){

  PtrNoLista Aux = lista->inicio;

  //enquanto aux for != de NULL, e chave de aux for diferente da procurada, aux = aux->proximo
  while(Aux != NULL && Aux->chave != valor_chave){
    Aux = Aux->proximo;
  }

  //se aux == NULL o elemento não foi encontrado, então retorna false
  if(Aux==NULL){
    return false;
  }
  else{//senão, foi encontrado, retorna Aux por referencia, e return true;
    *elemento = Aux;
    return true;
  }

}//consultaListaOrdenada

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNÇÕES RELACIONADAS A ATIVIDADE//////////////////////////////////

//Nesta função foram inseridas as linhas relacionadas ao tratamento de erros no arquivo
bool inserir_ark_to_list(ListaOrdenada *lista,FILE *ark,int *num_controle){

  int Aux_Tamanho_Char;
  fseek(ark,0,SEEK_END);//aponta para o final do arquivo
  Aux_Tamanho_Char = ftell(ark);//captura a posi��o do ponteiro e armazena em Aux_Tamanho_Char
  fseek(ark,0,SEEK_SET);//retorna o ponteiro para a posi��o zero

  if(Aux_Tamanho_Char<5){
    printf("Arquivo Invalido!\n");
    return false;
  }//para tratamento de erros, se o arquivo for menor q 5 chars, então

  char String[Aux_Tamanho_Char+1];//string com o tamanho do arquivo

  int count_virgulas = 0;
  int count_chars = -1;

  char chave[5];
  char nome[28];
  char sexo[2];
  char peso[7];
  char altura[4];

  int i = -1;
  while(!feof(ark)){//copia o arquivo para String
    i+=1;
    String[i] = fgetc(ark);
    switch (String[i]) {
      case '!':
      case '@':
      case '#':
      case '$':
      case '%':
      case '&':
      case '*':
      case '(':
      case ')':
      case '-':
      case '_':
      case '=':
      case '+':
      case '[':
      case ']':
      case '?':
      case ':':
      case ';':
      case '"':
        printf("\nCaracter invalido no arquivo!\n");
        return false;
      break;
    }
  }
  String[i+1]='\0';//finaliza String


  for(int j = 0; j<i; j++){//for que percorre a String, selecionando as palavras entre as virgulas, das pessoas entre chaves, e as atribuindo as litas

    if(String[j]=='}'){//cada {}, representa dados de uma pessoa diferente, então os valores devem ser zerados
      count_virgulas = 0;
      count_chars = -1;

      //cada execução desse if, representa a mudança das informações de uma pessoa para outra
      //então, devemos armazenar na pilha, antes de ir para a proxima pessoa

      //inserimos o elemento a lista
      inserirListaOrdenada(lista,atoi(chave));

      //pessoa recebe o elemento da lista por referencia
      PtrNoLista pessoa;

      //PtrNoLista pessoa recebe por referencia, o nó correspondente a chave
      consultaListaOrdenada(lista,atoi(chave),&pessoa);

      //alteramos os elementos da struct
      strcpy(pessoa->nome, nome);
      strcpy(pessoa->sexo_mf, sexo);
      pessoa->peso_kg = atof(peso);
      pessoa->altura_cm = atoi(altura);

    }

    if(String[j]!='{' && String[j]!='}' && String[j]!='\n'){//pula os caracteres de controle

      if(String[j]==','){
        count_virgulas +=1;//virgula encontrada, passa para o proximo case  do switch abaixo
        count_chars = -1;//cont char volta para o inicio;
        j+=1;//pula a virgula
      }//if

      count_chars+=1;


      switch (count_virgulas) {
        case 0:
          chave[count_chars]=String[j];
          chave[count_chars+1] = '\0';//finaliza string
          break;
        case 1:
          nome[count_chars]=String[j];
          nome[count_chars+1] = '\0';//finaliza string
          break;
        case 2:
          sexo[count_chars]=String[j];
          sexo[count_chars+1] = '\0';//finaliza string
          break;
        case 3:
          peso[count_chars]=String[j];
          peso[count_chars+1] = '\0';//finaliza string
          break;
        case 4:
          altura[count_chars]=String[j];
          altura[count_chars+1] = '\0';//finaliza string
          break;
      }//switch

    }//if

  }//for

  //caso 1: Se o numero de controle for igual a 1, será retornado por referencia para num_controle;
  //caso 2: Se o numero de controle for igual a 2, será retornado por referencia para num_controle;
  //caso 3: Se o numero de controle for igual a 3, será retornado o valor negativo, da chave da ser consultada;
  //logo, todo valor negativo, é caso 3;


  char Aux_Num_controle[5];
  for(int j = i; j>0; j--){//percorre de tras para frente, e captura o primeiro numero depois da ultima chave
    if(String[j]=='}' && String[j+1] == '\n'){
      Aux_Num_controle[0] = String[j+2];
      Aux_Num_controle[1] = '\0';

      *num_controle = atoi(Aux_Num_controle);
      if(*num_controle == 3){
        //string[j+3] será o '\n' antes do valor a ser buscado então
        for(int k = 0; k<5; k++){
          Aux_Num_controle[k] = String[j+3+k];//percorre a string depois do '3' salvando em Aux_Num_controle
          Aux_Num_controle[k+1] = '\0';
        }
        *num_controle = atoi(Aux_Num_controle)*-1;//retorna o negativo da chave -> caso 3

      }//caso seja igual a 3, retorna o valor negativo da chave inserida na linha de baixo.
      //ao receber um numero negativo, saberemos que se trata do numero de controle '3', e o modulo do valor negativo será a chave
      break;
    }//if
  }//for

  return true;
}//inserir_ark

void inserir_list_to_ark(ListaOrdenada *lista,FILE *ark, int num_controle){

  PtrNoLista Aux = lista->inicio;
  char Aux_Chave[10];

  if(num_controle < 0){//se o numero for negativo, sempre será caso 3. e o modulo do numero negativo é igual ao valor da chave do numero a ser consultado

    PtrNoLista pessoa;

    if(consultaListaOrdenada(lista,(num_controle*-1),&pessoa))
    {
      fprintf(ark,"{%i,%s,%s,%.1f,%i}\n",pessoa->chave,pessoa->nome,pessoa->sexo_mf,pessoa->peso_kg,pessoa->altura_cm);
      printf("\nGravacoes no arquivo finalizadas!\n");
    }
    else
      printf("\nO codigo solicitado nao existe!\n");

  }else if(num_controle<=3 && num_controle>0){//se o numero n�o for negativo, e maior que 1 e 2, significa que � um numero de controle invalido (numeros negativos == caso 3)
    //esta fun��oo j� grava no arquivo. 'g' representa Gravar, e 'i' Imprimir
    imprimir_gravar_ListaOrdenada(lista,num_controle,ark,'g');
    printf("\nGravacoes no arquivo finalizadas!\n");
  }else{
    printf("\nNumero de controle invalido!\n" );
  }

}//inserir_list_to_ark


int main(int argc, const char * argv[]){

  if(argc!= 3) {
    printf("\nQuantidade de parametros invalida!\n");
    return 0;
  }


  ListaOrdenada lista;
  iniciaListaOrdenada(&lista);

  FILE *ark_entrada = fopen(argv[1],"r");
  FILE *ark_saida = fopen(argv[2],"w");
  int num_controle;

  if(inserir_ark_to_list(&lista,ark_entrada,&num_controle))//se tudo der certo no proceso de inserir o arquivo de entrada na lista
    inserir_list_to_ark(&lista,ark_saida,num_controle);//ent�o, ensira a lista no arquvi de saida



  //fechando arquivos e desalocando memoria
  fclose(ark_entrada);
  fclose(ark_saida);
  destruirListaOrdenada(&lista);


  return 0;
}//main
