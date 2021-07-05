#define _GNU_SOURCE
#include "InterpretadorView.h"


void show_comands()
{
    printf("--| Lista de Comandos\n");
    printf("--| x = load_sgr (char *users, char *businesses, char *reviews);\n");
    printf("--| x = businesses_started_by_letter (SGR sgr, char letter);\n");
    printf("--| x = business_info (SGR sgr, char *business_id);\n");
    printf("--| x = businesses_reviewed (SGR sgr, char *user_id);\n");
    printf("--| x = businesses_with_stars_and_city (SGR sgr, float stars, char *city);\n");
    printf("--| x = top_businesses_by_city (SGR sgr, int top);\n");
    printf("--| x = international_users (SGR sgr)\n");
    printf("--| x = top_businesses_with_category (SGR sgr, int top, char *category);\n");
    printf("--| x = reviews_with_word (SGR sgr, char *word);\n");
    printf("--| x = fromCSV (char *file_path, char delim);\n");
    printf("--| x = filter (TABLE tab, int col, char *value, op_elem operator);\n");
    printf("--| x = proj (TABLE tab, int col1_a, int col2_a);\n");
    printf("--| x = y[int][int];\n");
    printf("--| toCSV(TABLE tab, char delimiter, char* file_path);\n");
    printf("--| show(TABLE x);\n");
    printf("--| count(TABLE x);\n");
}


void paginacao_comands()
{
    printf("--| next -> Próxima Página        ::  back -> Página Anterior \n");
    printf("--| down -> Próxima Linha         ::  up -> Linha Anterior \n");
    printf("--| inicio -> Inicio do Ficheiro  ::  final -> Final do Ficheiro \n");
}   


void erro_stdin(){
    printf("--| Erro ao ler sobre o stdin!\n");
}


void leaving(){
    printf("Leaving...\n");
}


int memory_error()
{
    printf("--| Erro de memória derivado do input\n--| Volte a introduzir um novo comando\n");
    return 1;
}


void cleanOutput()
{
    printf("\033[2J");
    printf("\033[0;0H");
}


void undefinedVariable(){
    printf("Variavel não definida\n");
}


void invalidComand(){
    printf("--| ERROR: O comando inserido não é valido!\n");
}


int default_getLoad(){

    printf("--| Deseja usar os ficheiros pré-definidos como base de dados?\n");
    printf("--| .: sim || não\n");

    size_t bufsize = 1024; // aloca memória para um array de apontadores para Strings.
    char *buffer = malloc(bufsize);
    buffer = NULL;
    int bytes_read;

    if ((bytes_read = getline(&buffer, &bufsize, stdin)) == -1) // Utilização do getline pelo facto de reallocar memória sozinho
            printf("--| Erro ao ler sobre o stdin!\n");
    
    if (strcmp(buffer, "sim\n") == 0) {
         printf("--| Dados do Tipo SGR serão carregados automaticamente na variável 'x'\n");
         printf("--| Aguarde uns instantes...\n");
         free(buffer);
         return 1;
    }
    else return 0;
}