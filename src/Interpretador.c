#define _GNU_SOURCE
#include "Interpretador.h"
#include "InterpretadorView.h"

struct Variable
{
    gpointer *dados;
    int tipo; // Tipos // SGR-> 0;
                       // TABLE-> 1;
                       // outro-> 2;
};

char **inputDivide(char *input)
{
    char **stdi = (char **)malloc(10 * sizeof(char *)); // aloca memória para um array de apontadores para Strings.
    for (int j = 0; j < 10; j++)
        stdi[j] = NULL; // inicia todos os apontadores a NULL.

    int i = 0;
    while (input)
    {
        char *aux = strsep(&input, "\t\n= (,)[]"); // ;  // divide a String dada segundo os delimitadores dados.
        if (aux && aux[0])
            stdi[i++] = strdup(aux); // aloca espaço e copia a String.
    }

    return stdi; // retorna o Array de apontadores para Strings
}

VARIABLE initVariable(gpointer x, int y)
{
    VARIABLE new = malloc(sizeof(struct Variable));
    new->dados = x; // Faz um apontador para o Data passado.
    new->tipo = y;  // Atribui o inteiro identificador do tipo de Data

    return new;
}

void destroyVariable(void *v)
{
    VARIABLE x = (VARIABLE) v;
    if (x->tipo == 0)
        free_sgr((SGR)x->dados); // Se a data for do tipo SGR
    else
        table_destroy2((TABLE)x->dados); // Se a data for do tipo TABLE

    free(x);
}

int next_comand(TABLE x, int i)
{
    int max = getTable_lines_lenght(x);
    i += 25;
    if (i > max)
        i = max;         // Atualiza a linha da Table
    cleanOutput();       // Dá clean ao stdout para uma melhor interface
    show_table(x, i);    // Visualização da Table em questão
    paginacao_comands(); // Comandos Utilitários

    return i; // Retorna a Primeira linha após o comando next.
}

int final_comand(TABLE x){
    int i = getTable_lines_lenght(x) - 25;
    cleanOutput();
    show_table(x, i);
    paginacao_comands();
    return i;
}

int inicio_comand(TABLE x){
    int i = 0;
    cleanOutput();
    show_table(x, i);
    paginacao_comands();
    return i;
}

int back_comand(TABLE x, int i)
{
    i -= 25; // Atualiza a linha da Table
    if (i < 0)
        i = 0;
    cleanOutput();       // Dá clean ao stdout para uma melhor interface
    show_table(x, i);    // Visualização da Table em questão
    paginacao_comands(); // Comandos Utilitários

    return i; // Retorna a Primeira linha após o comando back.
}

int up_comand(TABLE x, int i)
{
    i -= 1; // Atualiza a linha da Table
    if (i < 0)
        i = 0;
    cleanOutput();       // Dá clean ao stdout para uma melhor interface
    show_table(x, i);    // Visualização da Table em questão
    paginacao_comands(); // Comandos Utilitários

    return i; // Retorna a Primeira linha após o comando back.
}

int down_comand(TABLE x, int i)
{
    i += 1;              // Atualiza a linha da Table
    cleanOutput();       // Dá clean ao stdout para uma melhor interface
    show_table(x, i);    // Visualização da Table em questão
    paginacao_comands(); // Comandos Utilitários

    return i; // Retorna a Primeira linha após o comando back.
}

int getNext(char *string)
{
    return g_str_equal(string, "next\n");
}

int getBack(char *string)
{
    return g_str_equal(string, "back\n");
}

int getUp(char *string)
{
    return g_str_equal(string, "up\n");
}

int getDown(char *string)
{
    return g_str_equal(string, "down\n");
}

int getFinal(char *string){
    return g_str_equal(string, "final\n");
}

int getInicio(char *string){
    return g_str_equal(string, "inicio\n");
}

void comando_show(TABLE x)
{
    size_t bufsize = 1024;
    char *buffer = malloc(bufsize); // Aloca espaço para o buffer que vai ser usado para ler do stdin
    buffer = NULL;

    int bytes_read;
    int i = 0;
    int ctest = 0;

    cleanOutput();       // Dá clean ao stdout para uma melhor interface
    show_table(x, i);    // Inicia a visualização da Table
    paginacao_comands(); // Comandos Utilitários

    while (ctest == 0)
    {
        if ((bytes_read = getline(&buffer, &bufsize, stdin)) == -1) // Lê os comandos passados no stdin
        {
            memory_error(); // No caso de dar erro ao ler
        }
        else if (getNext(buffer))  // Comando "next"
            i = next_comand(x, i); // Executa o comando "next" e atualiza o número da primeira linha visualizada

        else if (getBack(buffer))  // Comando "back"
            i = back_comand(x, i); // Executa o comando "back" e atualiza o número da primeira linha visualizada

        else if (getUp(buffer))  // Comando "up"
            i = up_comand(x, i); // Executa o comando "up" e atualiza o número da primeira linha visualizada

        else if (getDown(buffer))  // Comando "down"
            i = down_comand(x, i); // Executa o comando "down" e atualiza o número da primeira linha visualizada

        else if (getFinal(buffer))
            i = final_comand(x);

        else if (getInicio(buffer))
            i = inicio_comand(x);

        else if (strcmp(buffer, "quit\n") == 0) // Comando "quit"
        {
            leaving(); // Sai da visualização do tipo Table
            ctest = 1;
        }
        else // Caso o comando inserido não seja reconhecido.
            printf("Comando não reconhecido\n");
    }
    free(buffer); // Liberta memória utilizada.
}

int getLoad_sgr(char *string)
{
    return g_str_equal(string, "load_sgr");
}

int getBusinesses_started_by_letter(char *string)
{
    return g_str_equal(string, "businesses_started_by_letter");
}

int getBusiness_info(char *string)
{
    return g_str_equal(string, "business_info");
}

int getBusinesses_reviewed(char *string)
{
    return g_str_equal(string, "businesses_reviewed");
}

int getBusinesses_with_stars_and_city(char *string)
{
    return g_str_equal(string, "businesses_with_stars_and_city");
}

int getTop_businesses_by_city(char *string)
{
    return g_str_equal(string, "top_businesses_by_city");
}

int getInternational_users(char *string)
{
    return g_str_equal(string, "international_users");
}

int getTop_businesses_with_category(char *string)
{
    return g_str_equal(string, "top_businesses_with_category");
}

int getReviews_with_word(char *string)
{
    return g_str_equal(string, "reviews_with_word");
}

int getFromCSV(char *string)
{
    return g_str_equal(string, "fromCSV");
}

int getFilter(char *string)
{
    return g_str_equal(string, "filter");
}

int getProj(char *string)
{
    return g_str_equal(string, "proj");
}

int getShow(char *string)
{
    return g_str_equal(string, "show");
}

int getToCSV(char *string)
{
    return g_str_equal(string, "toCSV");
}

int getIndex(char **input, GHashTable *tableHash)
{   

    VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[1]); // Vai buscar a variável passada

    if (x->tipo == 1 && (atoi(input[2]) != 0) && (atoi(input[3]) != 0))
        return 1; // Testa se a variável é do tipo TABLE

    return 0;
}

int getCount(char *string)
{
    return g_str_equal(string, "count");
}

void setLoad_sgr(char **input, GHashTable *tableHash)
{

    int cond = 0;
    if (input == NULL) // Verificação do char** passado como argumento
        cond = memory_error();

    if (cond != 1)
    {
        SGR y = load_sgr(input[2], input[3], input[4]); // Invocação da query
        if (y == NULL)                                  // Verificação do conteúdo da variável
        {
            undefinedVariable();
            return;
        }

        VARIABLE x = initVariable(y, 0);             // Iniciasse uma struct do tipo VARIABLE, inserindo o SGR e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], x); // Inserção da struct definida anteriormente na HashTable
    }
}

void setDefaut_Load(GHashTable *tableHash){
    SGR y = load_sgr("input/users_full.csv", "input/business_full.csv", "input/reviews_1M.csv");
    char *aux = strdup("x");
    if (y == NULL)                                  // Verificação do conteúdo da variável
    {
            undefinedVariable();
            return;
    }
    VARIABLE z = initVariable(y, 0);    
    g_hash_table_insert(tableHash, aux , z);
}

void setBusinesses_started_by_letter(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        if (input[3] == NULL) // Condição de Testagem
        {
            undefinedVariable();
            return;
        }

        TABLE t = businesses_started_by_letter((SGR)x->dados, (*input[3])); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                    // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                        // Inserção da struct definida anteriormente na HashTable
    }
}

void setBusiness_info(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = business_info((SGR)x->dados, input[3]); // Invocação da query
        VARIABLE y = initVariable(t, 1);                  // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);      // Inserção da struct definida anteriormente na HashTable
    }
}

void setBusiness_reviewed(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = businesses_reviewed((SGR)x->dados, input[3]); // Invocação da query
        VARIABLE y = initVariable(t, 1);                        // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);            // Inserção da struct definida anteriormente na HashTable
    }
}

void setBusinesses_with_stars_and_city(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = businesses_with_stars_and_city((SGR)x->dados, atof(input[3]), input[4]); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                                   // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                                       // Inserção da struct definida anteriormente na HashTable
    }
}

void setTop_businesses_by_city(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = top_businesses_by_city((SGR)x->dados, atoi(input[3])); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                 // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                     // Inserção da struct definida anteriormente na HashTable
    }
}

void setInternational_users(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = international_users((SGR)x->dados); // Invocação da query
        VARIABLE y = initVariable(t, 1);              // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);  // Inserção da struct definida anteriormente na HashTable
    }
}

void setTop_businesses_with_category(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = top_businesses_with_category((SGR)x->dados, atoi(input[3]), input[4]); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                                 // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                                     // Inserção da struct definida anteriormente na HashTable
    }
}

void setReviews_with_word(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 1 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo SGR
        {
            undefinedVariable();
            return;
        }

        TABLE t = reviews_with_word((SGR)x->dados, input[3]); // Invocação da query
        VARIABLE y = initVariable(t, 1);                      // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);          // Inserção da struct definida anteriormente na HashTable
    }
}

void setFromCSV(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        TABLE t = csv_to_table(input[2], input[3][0]); // Invocação da query
        VARIABLE x = initVariable(t, 1);               // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], x);   // Inserção da struct definida anteriormente na HashTable
    }
}

void setFilter(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {

        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }

        TABLE t = filter_table((TABLE)x->dados, atoi(input[3]), input[4], atoi(input[5])); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                                   // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                                       // Inserção da struct definida anteriormente na HashTable
    }
}

void setProj(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {

        VARIABLE x = g_hash_table_lookup(tableHash, input[2]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }

        TABLE t = get_table_collums((TABLE)x->dados, atoi(input[3]), atoi(input[4])); // Invocação da query
        VARIABLE y = initVariable(t, 1);                                              // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], y);                                  // Inserção da struct definida anteriormente na HashTable
    }
}

void setShow(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[1]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }
        comando_show((TABLE)x->dados); // Função de execução do comando show
    }
}

void setCount(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {
        VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[1]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }
        TABLE y = (TABLE)x->dados; // Função de execução do comando show
        int lenght = getTable_lines_lenght(y);

        printf("--| Tamanho do Input: %d linhas\n", lenght);
    }
}

void setToCSV(char **input, GHashTable *tableHash)
{
    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {

        VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[1]); // lookup do tipo de dados passado como argumento na HashTable

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }

        table_to_csv((TABLE)x->dados, input[2][0], input[3]); // Função de execução do comando show
    }
}

void setIndex(char **input, GHashTable *tableHash)
{

    int cond = 0;
    if (input == NULL)
        cond = memory_error(); // Verificação do char** passado como argumento

    if (cond != 1)
    {

        VARIABLE x = (VARIABLE)g_hash_table_lookup(tableHash, input[1]); // lookup do tipo de dados passado como argumento na HashTable

        int coluna = atoi(input[3]); // atribuição do numero da coluna
        int linha = atoi(input[2]);  // atribuição do numero da linha

        if (x == NULL || x->tipo == 0 || x->tipo == 2) // Verificação se a data dentro da Struct Variable é do tipo TABLE
        {
            undefinedVariable();
            return;
        }

        TABLE y = index_table((TABLE)x->dados, coluna, linha); // Invocação da query
        VARIABLE t = initVariable(y, 1);                       // Iniciasse uma struct do tipo VARIABLE, inserindo a TABLE e identificando o seu tipo de dados.
        g_hash_table_insert(tableHash, input[0], t);           // Inserção da struct definida anteriormente na HashTable
    }
}

void getQuery(char **input, GHashTable *tableHash)
{ // Testa o input passado pelo stdin com as possiveis querys e sua chamada

    if (input[1] != NULL && getLoad_sgr(input[1]))
        setLoad_sgr(input, tableHash);
    else if (input[1] != NULL && getBusinesses_started_by_letter(input[1]))
        setBusinesses_started_by_letter(input, tableHash);

    else if (input[1] != NULL && getBusiness_info(input[1]))
        setBusiness_info(input, tableHash);

    else if (input[1] != NULL && getBusinesses_reviewed(input[1]))
        setBusiness_reviewed(input, tableHash);

    else if (input[1] != NULL && getBusinesses_with_stars_and_city(input[1]))
        setBusinesses_with_stars_and_city(input, tableHash);

    else if (input[1] != NULL && getTop_businesses_by_city(input[1]))
        setTop_businesses_by_city(input, tableHash);

    else if (input[1] != NULL && getInternational_users(input[1]))
        setInternational_users(input, tableHash);

    else if (input[1] != NULL && getTop_businesses_with_category(input[1]))
        setTop_businesses_with_category(input, tableHash);

    else if (input[1] != NULL && getReviews_with_word(input[1]))
        setReviews_with_word(input, tableHash);

    else if (input[1] != NULL && getFromCSV(input[1]))
        setFromCSV(input, tableHash);

    else if (input[1] != NULL && getFilter(input[1]))
        setFilter(input, tableHash);

    else if (input[1] != NULL && getProj(input[1]))
        setProj(input, tableHash);

    else if (input[0] != NULL && getShow(input[0]))
        setShow(input, tableHash);

    else if (input[0] != NULL && getToCSV(input[0]))
        setToCSV(input, tableHash);

    else if (input[0] != NULL && getCount(input[0]))
        setCount(input, tableHash);

    else if (input[1] != NULL && getIndex(input, tableHash))
        setIndex(input, tableHash);

    else
        invalidComand();
}

void strsepAlterada(char** text, char** out) {
    int i = 0;
    char ant = '\0';
    for (i = 0; (*text)[i]; i++) {
        if ((*text)[i] == ';' && (ant == ')' || ant == ']')) break;
        if ((*text)[i] == '\n') break;
        ant=(*text)[i];
    }
    char lst = (*text)[i];
    (*text)[i] = '\0';
    *out = strdup(*text);
    if (lst == '\0' || lst == '\n') (*text) = NULL;
    else *text = &((*text)[i + 1]);
}

void interpretador()
{
    size_t bufsize = 1024; // aloca memória para um array de apontadores para Strings.
    char *buffer = malloc(bufsize);
    buffer = NULL; // inicia o Buffer a NULL.

    int ctest = 0;
    int bytes_read;
    // criamos a HashTable que vai ser utilizada para guardar variáveis e possiveis invocações destas.
    GHashTable *tableHash = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)g_free, (GDestroyNotify)destroyVariable);

    printf("--| Programa Iniciando...\n");

    int load;
    if ((load = default_getLoad())) setDefaut_Load(tableHash);
    
    
    while (ctest == 0)
    { // Ciclo de execução e leitura de comandos do stdout e stdin respetivamente
        printf("--| Introduza um novo comando!\n");
        if ((bytes_read = getline(&buffer, &bufsize, stdin)) == -1) // Utilização do getline pelo facto de reallocar memória sozinho
            printf("--| Erro ao ler sobre o stdin!\n");

        else if (strcmp(buffer, "quit\n") == 0)
        {
            printf("--| Terminando o Programa...\n");
            break;
        }

        else if (strcmp(buffer, "help\n") == 0)
            show_comands();

        else
        {
            while (buffer)
            {   // Ciclo de divisão de comandos e respetivas execuções
                //char *aux = strdup(strsep(&buffer, ";\n"));
                char* aux = malloc(1024);
                strsepAlterada(&buffer, &aux);
                if (!aux || !aux[0])
                    break;
                char **lista = inputDivide(aux);
                getQuery(lista, tableHash);
                free(aux);
                free(lista);
            }
        }     
    }

    g_hash_table_destroy(tableHash); // Liberta-se a memória alocada para a HashTable e todas as Structs inseridas
    printf("--| Programa Terminado!\n");
}
