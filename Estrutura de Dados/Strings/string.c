//retorna texto do arquivo em uma string
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


//retorna a string minuscula
char *stolower(char string[]){
    //codigo simples para comentarios
    char *ret = malloc(sizeof(char)*strlen(string)+1);

    for(int i = 0; i<strlen(string); i++)
    ret[i] = tolower(string[i]);


    ret[strlen(string)] = '\0';

    return ret;
}


int find_Char(char string[], char c){
  //codigo simples para comentarios
  for(int i = 0; i<strlen(string); i++){
    if(string[i] == c)
        return i;
  }

  return -1;

}


//retorna a string recortada nas posicoes iniciais e finais estabelecidas
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
