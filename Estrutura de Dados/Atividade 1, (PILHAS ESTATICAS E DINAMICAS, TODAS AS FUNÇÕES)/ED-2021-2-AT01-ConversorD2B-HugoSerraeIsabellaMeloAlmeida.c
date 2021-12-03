//Inclui as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////ESTRUTURA DE PILHA DINAMICA ABAIXO//////////////////////////////////////////////////////////


//COMENTARIOS APENAS NAS FUNÇÕES MAIS COMPLEXAS (INSERIR, REMOVER)


typedef struct NoPilha_D* PtNoPilha_D;

typedef struct NoPilha_D {

  int chave; //onde os dados serão armazenados
  PtNoPilha_D proximo;//ponteiro que aponta para esta mesma estrutura, no proximo elemento

}NoPilha_D;

typedef struct{
  PtNoPilha_D topo;
  int qtd;

}Pilha_Dinamica;


void iniciar_Dinamica(Pilha_Dinamica *Pilha){
  //Topo deve apontar para NULL
  Pilha->topo = NULL; //topo é um nó de pilha
  //quantidade deve receber zero
  Pilha->qtd = 0;


}

void Inserir_Dinamica(Pilha_Dinamica *Pilha, int Valor){

  //Um novo nó é criado
  PtNoPilha_D aux;
  //A memoria para o novo nó é alocada
  aux = malloc(sizeof(NoPilha_D));

  //novo nó recebe o dado/Valor
  aux->chave = Valor;

  //"proximo" de aux, aponta para onde o topo apontava
  aux->proximo = Pilha->topo;

  //topo aponta para o novo nó
  Pilha->topo = aux;

  //quantidade recebe +=1;
  Pilha->qtd++;


}

bool esta_vazia_Dinamica(Pilha_Dinamica *Pilha){
  return Pilha->topo == NULL;
}

int Remover_elemento_Dinamica(Pilha_Dinamica *Pilha){
  //valor de controle
  int ret = -99999;

  //so pode remover se não estiver vazia
  if(esta_vazia_Dinamica(Pilha)==false)
  {
    PtNoPilha_D aux;

    //aux aponta para o topo da pilha
    aux = Pilha->topo;

    //ret recebe a chave do elemento que será removido
    ret = aux->chave;

    //topo recebe proximo do topo
    Pilha->topo = Pilha->topo->proximo;

    //libera a memoria de aux
    free(aux);

    //decrementa a quantidade
    Pilha->qtd--;
  }
  else
  {
    printf("Pilha Vazia!\n");
  }

  //retorna o valor removido
  return ret;
}

void Imprimir_Dinamica(Pilha_Dinamica *Pilha){


    PtNoPilha_D percorre;
    printf("Pilha = { ");

    //percorre a pilha printando os valores
    for(percorre = Pilha->topo; percorre!=NULL; percorre = percorre->proximo){
      printf("%i,",percorre->chave);
    }

    printf(" }\n");

}

int tamanho_Dinamica(Pilha_Dinamica *Pilha){
  return Pilha->qtd;
}

void Destruir_dinamica(Pilha_Dinamica *Pilha){

  //remove elementos até que esta_vazia retorne true
  while(esta_vazia_Dinamica(Pilha)==false){
    Remover_elemento_Dinamica(Pilha);
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////ESTRUTURA DE PILHA ESTÁTICA ABAIXO/////////////////////////////////////////////////////////


// A ESTRUTURA DAS PILHAS ESTATICAS ESTÁ BEM SIMPLES DE ENTENDER, POR ISSO POUCOS COMENTARIOS


//Define o tamanho máximo do vetor
#define MAX 10

typedef struct{

  //vetor (onde os dados serão armazenados)
  int vetor[MAX];

  //topo (define onde pode fazer a inserção e a remoção)
  int topo;

}Pilha_Estatica;

void Iniciar_Estatica(Pilha_Estatica *Pilha){
  Pilha->topo = 0;
}

bool esta_Vazia_Estatica(Pilha_Estatica *Pilha){
  return Pilha->topo == 0;
}

bool esta_cheia_Estatica(Pilha_Estatica *Pilha){
  return Pilha->topo == MAX;
}

void Inserir_Estatica(Pilha_Estatica *Pilha, int Valor){

  if(esta_cheia_Estatica(Pilha)==false){
    Pilha->vetor[Pilha->topo] = Valor;
    Pilha->topo++;
  }else{
    printf("A Pilha Esta Cheia!\n");
  }//if(esta_cheia)

}

void Remover_Estatica(Pilha_Estatica *Pilha){

  if(esta_Vazia_Estatica(Pilha)==false)
    Pilha->topo--;
  else
    printf("A Pilha Esta Vazia!\n");

}

void Esvaziar_Estatica(Pilha_Estatica *Pilha){
  Pilha->topo=0;
}

int tamanho_Pilha_Estatica(Pilha_Estatica *Pilha){
  return Pilha->topo;
}

void imprimir_Estatica(Pilha_Estatica *Pilha){

  printf("Pilha = { ");

  for(int i = Pilha->topo-1; i>=0; i--){
    printf("%i,", Pilha->vetor[i]);
  }

  printf(" }\n");

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////FUNÇÕES RELACIONADAS A ATIVIDADE//////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////UTILIZANDO PILHAS DINAMICAS////////////////////////////////////////////

//Faz a conversão de APENAS UM numero DECIMAL para BINARIO.
void conversor_Unidade_Dinamica(Pilha_Dinamica *Pilha, int D){

  //A estrutura da Pilha fará o papel de inverter os digitos binarios

  //Enquanto D!= 1:
  while(D!=1 && D!=0){
    //Para achar o primeiro digito binario
    //Se o resto de D por 2 for > 0, insere '1' na pilha. senão insere 0.
    if(D%2!=0)
    {
      Inserir_Dinamica(Pilha,1);
    }//if
    else{
      Inserir_Dinamica(Pilha,0);
    }//else
    //Divide D por 2, para achar o proximo digito binario
    //D recebe apenas a porção inteira da divisão
    if(D!=0)
      D=D/2;

  }//while

  //Se D==1, o primeiro Digito binario é 1.
  if(D==1){
    Inserir_Dinamica(Pilha,1);
  }//if
  if(D==0){
    Inserir_Dinamica(Pilha,0);
  }//if
}

//Faz a conversão da Pilha com algarismos binarios, para um numero binario em char[]
//retorna o digito
char * Binario_to_String_Dinamica(Pilha_Dinamica *Digitos_Binarios){

  //Vetor char que irá receber todos os digitos binarios
  char *Numero_Binario;
  Numero_Binario = malloc(sizeof(char)*(tamanho_Dinamica(Digitos_Binarios)+1));


  //Contador auxiliar para atribuir os digitos da pilha de Digitos_Binarios ao vetor Char (Numero_Binario)
  int count = 0;

  //Ponteiro auxiliar para percorrer os digitos da pilha de Digitos_Binarios.
  PtNoPilha_D percorre_digitos_b;

  //Estrutura for que percorre a pilha dos Digitos_Binarios
  for(percorre_digitos_b = Digitos_Binarios->topo; percorre_digitos_b!=NULL; percorre_digitos_b = percorre_digitos_b->proximo){
    Numero_Binario[count] = (percorre_digitos_b->chave)+'0';
    count++;
  }//for

  //Finaliza a string com '\0'
  Numero_Binario[tamanho_Dinamica(Digitos_Binarios)] = '\0';

  //Retorna & de Numero_binario
  return Numero_Binario;
}

//Faz a conversão de TODOS os numeros DECIMAIS presentes na Pilha.(para binario)
void conversor_Dinamica(Pilha_Dinamica *Pilha,char nome_ark[]){
  FILE *Ark_saida = fopen(nome_ark,"w");

  Pilha_Dinamica Digitos_Binarios;
  iniciar_Dinamica(&Digitos_Binarios);
  char *String_BINARIOS;

  //Ponteiro auxiliar para percorrer a pilha de numeros decimais
  PtNoPilha_D percorre_decimais;

  //Estrutura for que percorre TODA a pilha dos DECIMAIS.
  for(percorre_decimais = Pilha->topo; percorre_decimais!=NULL; percorre_decimais = percorre_decimais->proximo){

    //D recebe UMA das unidades DECIMAIS da pilha dos decimais.
    int D = percorre_decimais->chave;

    //Converte D para BINARIO, e salva os digitos binarios na pilha de Digitos_Binarios.
    //Cada pilha "Digitos_Binarios" é igual a um numero binario
    conversor_Unidade_Dinamica(&Digitos_Binarios,D);

    //Para poder destruir com free(Numero_Binario) depois.
    char *Numero_Binario = Binario_to_String_Dinamica(&Digitos_Binarios);

    //FUNÇÃO QUE SALVA "Numero_Binario" NO ARQUIVO
    fputs(Numero_Binario,Ark_saida);
    fputc('\n',Ark_saida);
    //FIM DO TRECHO

    //Libera a memoria que a função Binario_to_string alocou
    free(Numero_Binario);

    //Destroi a pilha de Digitos_Binarios, para a proxima conversão no loop for
    Destruir_dinamica(&Digitos_Binarios);

  }//for
  //Fecha o arquivo de saída
  fclose(Ark_saida);
}

//Recebe os dados somente de arquivos para pilhas dinamicas, já tratados no formato que a função aceita sem erros
//Esta função interpreta a string, e salva os numeros decimais em uma pilha dinamica.
void stringDecimal_to_Dinamica(char txt[],Pilha_Dinamica *Decimais){

  char aux[10];//aux
  int count = 0;//contador auxiliar

  //Percorre txt, separando os numeros inteiros e armazenando-os em Decimais
  for(int i = 0; i<strlen(txt); i++){

    //aux recebe tudo que esta entre 2 '\n'
    if(txt[i]!='\n'){//if
      aux[count] = txt[i];
      count++;
    }else{
      count = 0;

      Inserir_Dinamica(Decimais,atoi(aux));

      //exclui todos os valores numericos de aux
      for(int i = 0; i<strlen(aux); i++){
        aux[i]='\n';
      }//for_filho

    }//else

  }//for_pai

}

//Função que será utilizada na MAIN
void Conversor_DecimalToBinario_Dinamico(char string_BN[],char *nome_ark[]){

  Pilha_Dinamica Decimais;
  iniciar_Dinamica(&Decimais);

  //Decimais recebem todos os elementos numericos da string
  stringDecimal_to_Dinamica(string_BN,&Decimais);

  //Imprimir_Dinamica(&Decimais); //LINHA DE DEBUG
  //Converte todos os elementos da pilha Decimais, para binario. tipo char.
  conversor_Dinamica(&Decimais,nome_ark);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////UTILIZANDO PILHAS ESTÁTICAS//////////////////////////////////////////////


//Recebe os dados somente de arquivos para pilhas dinamicas, já tratados no formato que a função aceita sem erros
//Está função interpreta a string, e salva os numeros decimais em uma pilha dinamica.
void stringDecimal_to_Estatica(char txt[],Pilha_Estatica *Decimais){

  char aux[10];//aux
  int count = 0;//contador auxiliar

  //Percorre txt, separando os numeros inteiros e armazenando-os em Decimais
  for(int i = 0; i<strlen(txt); i++){

    //aux recebe tudo que esta entre 2 '\n'
    if(txt[i]!='\n'){//if
      aux[count] = txt[i];
      count++;
    }else{//else
      count = 0;

      Inserir_Estatica(Decimais,atoi(aux));

      //Exclui todos os valores numericos de aux
      for(int i = 0; i<strlen(aux); i++){
        aux[i]='\n';
      }//for_filho

    }//else

  }//for_pai

}

//Faz a conversão da Pilha com algarismos binarios, para um numero binario em char[]
//Retorna o digito
char * Binario_to_String_Estatica(Pilha_Estatica *Digitos_Binarios){

  //Vetor char que ira receber todos os digitos binarios
  char *Numero_Binario;
  Numero_Binario = malloc(sizeof(char)*(tamanho_Pilha_Estatica(Digitos_Binarios)+1));


  //Contador auxiliar para atribuir os digitos da pilha de Digitos_Binarios ao vetor Char (Numero_Binario)
  int count = 0;

  //Estrutura for que percorre a pilha dos Digitos_Binarios
  for(int i = Digitos_Binarios->topo-1; i>=0; i--){
    Numero_Binario[count] = (Digitos_Binarios->vetor[i])+'0';
    count++;
  }//for


  //Finaliza a string com '\0'
  Numero_Binario[tamanho_Pilha_Estatica(Digitos_Binarios)] = '\0';

  //Retorna & de Numero_binario
  return Numero_Binario;
}

//Faz a conversão de APENAS UM numero DECIMAL para BINARIO.
void conversor_Unidade_Estatica(Pilha_Estatica *Pilha, int D){

  //A estrutura da Pilha fará o papel de inverter os digitos binarios

  //Enquanto D!= 1:
  while(D!=1 && D!=0){
    //para achar o primeiro digito binario
    //se o resto de D por 2 for > 0, insere '1' na pilha. senão insere 0.
    if(D%2!=0)
    {//if
      Inserir_Estatica(Pilha,1);
    }else{
      Inserir_Estatica(Pilha,0);
    }//else
    //divide D por 2, para achar o proximo digito binario
    //D recebe apenas a porção inteira da divisão
    if(D!=0);
      D=D/2;

  }//while

  //se D==1, o primeiro Digito binario é 1.
  if(D==1){
    Inserir_Estatica(Pilha,1);
  }//if
  if(D==0){
    Inserir_Estatica(Pilha,0);
  }//if
}

//Faz a conversão de TODOS os numeros DECIMAIS presentes na Pilha.(para binario)
void conversor_Estatica(Pilha_Estatica *Pilha,char nome_ark[]){
  FILE *Ark_saida = fopen(nome_ark,"w");

  Pilha_Estatica Digitos_Binarios;
  Iniciar_Estatica(&Digitos_Binarios);
  char *String_BINARIOS;
  //ponteiro auxiliar para percorrer a pilha de numeros decimais


  //Estrutura for que percorre TODA a pilha dos DECIMAIS.
  for(int i = Pilha->topo-1; i>=0; i--){

    //D recebe UMA das unidades DECIMAIS da pilha dos decimais.
    int D = Pilha->vetor[i];

    //Converte D para BINARIO, e salva os digitos binarios na pilha de Digitos_Binarios.
    //Cada pilha "Digitos_Binarios" é igual a um numero binario
    conversor_Unidade_Estatica(&Digitos_Binarios,D);

    //Para Poder destruir com free(Numero_Binario) depois.
    char *Numero_Binario = Binario_to_String_Estatica(&Digitos_Binarios);

    //APAGAR ESSE PRINTF NO CODIGO FINAL
    //printf("Binario: %s\n", Numero_Binario);

    //FUNÇÃO QUE SALVA "Numero_Binario" NO ARQUIVO
    fputs(Numero_Binario,Ark_saida);
    fputc('\n',Ark_saida);
    //FIM DO TREXO

    //libera a memoria que a função Binario_to_string alocou
    free(Numero_Binario);

    //NÃO É NECESSARIO DESTRUIR UMA PILBHA ESTATICA, mas precisamos esvaziar para o proxmo loop for
    Esvaziar_Estatica(&Digitos_Binarios);

  }//for
  //Fecha o arquivo de saída
  fclose(Ark_saida);
}


//Função que será utilizada na MAIN
void Conversor_DecimalToBinario_Estatico(char string_BN[],char *nome_ark[]){

  Pilha_Estatica Decimais;
  Iniciar_Estatica(&Decimais);

  //Decimais recebe todos os elementos numericos da string
  stringDecimal_to_Estatica(string_BN,&Decimais);

  //imprimir_Estatica(&Decimais); //LINHA DE DEBUG

  //Converte todos os elementos da pilha Decimais, para binario. tipo char.
  conversor_Estatica(&Decimais,nome_ark);
}

char * return_String(char nome_ark[], char *c){

  //Abre o arquivo
  FILE *ark = fopen(nome_ark, "rt");

  //passa o primeiro caractere por referencia ('d' ou 'e')
  *c = fgetc(ark);

  //Pula a primeira linha com as letras 'd' ou  'e'
  fseek(ark,2,SEEK_SET);

  char *string;
  int controle_de_letras = 0;
  int count_malloc = 0;

  char ponteiro;
  while(!feof(ark)){
    count_malloc +=1;
    ponteiro = fgetc(ark);// fgetc faz o ponteiro de leitura do arquivo ler EXATAMENTE a quantidade de caracteres presentes, e salva em count_malloc
  }//while

  //Caso não tiver mais de 1 linha no arquivo, o caracter de controle recebe 'r', que cai no if()else{} da funçaõ main() e retorna arquivo invalido
  if(count_malloc<3)//if
    *c = 'r';

  string = malloc((sizeof(char)*count_malloc)+2);

  //tras o ponteiro de leitura para o inicio do arquivo
  rewind(ark);
  int i = 0;
  //pula a primeira linha
  fseek(ark,2,SEEK_SET);
  int final = 0;


  while(!feof(ark) && controle_de_letras!=1){

    string[i] = fgetc(ark);

    //Tudo que não for digitos de 0 a 9, cai no default
    switch (string[i]) {
      case ('0'):
        controle_de_letras = 0;
      case ('1'):
        controle_de_letras = 0;
      case ('2'):
        controle_de_letras = 0;
      case ('3'):
        controle_de_letras = 0;
      case ('4'):
        controle_de_letras = 0;
      case ('5'):
        controle_de_letras = 0;
      case ('6'):
        controle_de_letras = 0;
      case ('7'):
        controle_de_letras = 0;
      case ('8'):
        controle_de_letras = 0;
      case ('9'):
        controle_de_letras = 0;
      case ('\n'):
        controle_de_letras = 0;
      case (EOF):
        controle_de_letras = 0;
        final = i;
      break;
      default:
        controle_de_letras = 1;
    }//switch

    i++;
  }//while

  //Caso o ultimo digito do arquivo não for '\n', passa a ser
  if(string[final-1] != '\n'){
    string[final] = '\n';
  }//if
  //a string sempre é finalizada na ultima posição de memoria
  string[count_malloc] = '\0';

  //se houver qualquer coisa diferente de numeros inteiros no arquivo, c == 'r', que cai no else da função main() --> arquivo invalido
  if(controle_de_letras==1)
  {
    *c = 'r';
  }//if

  //Retorna a string
  return string;
}

int main(int argc, const char * argv[]){//main

  if(argc!= 3) {
    printf("Quantidade de parametros invalida\n");
    return 0;
  }//if

    char caracter_controle;

    //string recebe os numeros decimais do arquivo
    //caracter_controle recebe por referencia as letras 'd' ou 'e' ou 'r', r para arquivos invalidos
    char *string = return_String(argv[1],&caracter_controle);

    if(caracter_controle=='d'||caracter_controle=='D'){//if

      Conversor_DecimalToBinario_Dinamico(string,argv[2]);

    }else if(caracter_controle=='e'||caracter_controle=='E'){//else if

      Conversor_DecimalToBinario_Estatico(string,argv[2]);

    }else{//caso caracter_controle != de 'd' e 'e', o arquivo é invalido

      FILE *Ark_saida = fopen(argv[2],"w");
      fputs("Arquivo inválido!\n",Ark_saida);
      fclose(Ark_saida);
    }//else

    //Libera e evita vazamento de memória
    free(string);

  return 0;
}//Fim main
