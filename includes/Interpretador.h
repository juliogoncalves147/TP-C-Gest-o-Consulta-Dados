/// \file
#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H
#include "sgr.h"
#include "Table.h"
#include "glibWarningAvoid.h"
#include "InterpretadorView.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * @brief Estrutura que Guarda Dados das Querys e Identifica o seu tipo.
 * 
 */
typedef struct Variable *VARIABLE;

/**
 * @brief Divide a string dada no stdin num array de apontadores para string.
 * 
 * @param input String dada no stdin
 * @return ** char** Array de apontadores para Strings.
 */
char **inputDivide(char *input);

/**
 * @brief Inicia e aloca espaço para uma struct do tipo VARIABLE
 * 
 * @param x Data
 * @param y O Identificador do Data
 * @return ** VARIABLE 
 */
VARIABLE initVariable(gpointer x, int y);

/**
 * @brief Usada para dar free da struct VARIABLE 
 * 
 * @param x Struct VARIABLE
 * @return ** void 
 */
void destroyVariable(void * x);

/**
 * @brief Comando "next" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @param i Numero da primeira linha visualizada aquando da chamada do comando.
 * @return ** int Número da Primeira linha Visualidada
 */
int next_comand(TABLE x, int i);

/**
 * @brief Comando "final" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @return ** int 
 */
int final_comand(TABLE x);

/**
 * @brief Comando "inicio" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @return ** int 
 */
int inicio_comand(TABLE x);

/**
 * @brief Comando "back" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @param i Numero da primeira linha visualizada aquando da chamada do comando.
 * @return ** int  Número da Primeira linha Visualidada
 */
int back_comand(TABLE x, int i);

/**
 * @brief Comando "up" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @param i Numero da primeira linha visualizada aquando da chamada do comando.
 * @return ** int Número da Primeira linha Visualidada
 */
int up_comand(TABLE x, int i);

/**
 * @brief Comando "down" e derivadas funcionalidades resultantes da invocação deste comando
 * 
 * @param x TABLE
 * @param i Numero da primeira linha visualizada aquando da chamada do comando.
 * @return ** int Número da Primeira linha Visualidada
 */
int down_comand(TABLE x, int i);

/**
 * @brief Testa a invocação do Comando "next"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getNext(char *string);

/**
 * @brief Testa a invocação do Comando "back"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBack(char *string);

/**
 * @brief Testa a invocação do Comando "up"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getUp(char *string);

/**
 * @brief Testa a invocação do Comando "down"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getDown(char *string);

/**
 * @brief Testa a invocação do Comando "next"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getNext(char *string);

/**
 * @brief Testa a invocação do Comando "back"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBack(char *string);

/**
 * @brief Testa a invocação do Comando "final"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getFinal(char *string);

/**
 * @brief Testa a invocação do Comando "inicio"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getInicio(char *string);

/**
 * @brief Função que gere as funcionalidades de visualização de um tipo TABLE aquando da chamada do comando "show".
 * 
 * @param x TABLE
 * @return ** void 
 */
void comando_show(TABLE x);

/**
 * @brief Testa a invocação da Query "load_sgr"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getLoad_sgr(char *string);

/**
 * @brief Testa a invocação da Query "businesses_started_by_letter"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBusinesses_started_by_letter(char *string);

/**
 * @brief Testa a invocação da Query "business_info"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBusiness_info(char *string);

/**
 * @brief Testa a invocação da Query "businesses_reviewed"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBusinesses_reviewed(char *string);

/**
 * @brief Testa a invocação da Query "businesses_with_stars_and_city"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getBusinesses_with_stars_and_city(char *string);

/**
 * @brief Testa a invocação da Query "top_businesses_by_city"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getTop_businesses_by_city(char *string);

/**
 * @brief Testa a invocação da Query "international_users"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getInternational_users(char *string);

/**
 * @brief Testa a invocação da Query "top_businesses_with_category"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getTop_businesses_with_category(char *string);

/**
 * @brief Testa a invocação da Query "reviews_with_word"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getReviews_with_word(char *string);

/**
 * @brief Testa a invocação da Query "fromCSV"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getFromCSV(char *string);

/**
 * @brief Testa a invocação da Query "filter"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getFilter(char *string);

/**
 * @brief Testa a invocação da Query "proj"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getProj(char *string);

/**
 * @brief Testa a invocação da Query "show"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getShow(char *string);

/**
 * @brief Testa a invocação da Query "toCSV"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getToCSV(char *string);

/**
 * @brief Testa a invocação da Query "index"
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getIndex(char **input, GHashTable *tableHash);

/**
 * @brief Testa a invocação da Query "count";
 * 
 * @param string Argumento passado no stdin
 * @return ** int  1 - True || 0 - False
 */
int getCount(char *string);

/**
 * @brief Invoca a Query correspondente ao comando "load_sgr"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setLoad_sgr(char **input, GHashTable *tableHash);

/**
 * @brief Carrega os ficheiros pré-definidos do tipo SGR
 * 
 * @param tableHash 
 * @return ** void 
 */
void setDefaut_Load(GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "businesses_started_by_letter"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setBusinesses_started_by_letter(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "business_info"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setBusiness_info(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "business_reviewed"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setBusiness_reviewed(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "businesses_with_stars_and_city"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setBusinesses_with_stars_and_city(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "top_businesses_by_city"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setTop_businesses_by_city(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "international_users"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setInternational_users(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "top_businesses_with_category"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setTop_businesses_with_category(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "reviews_with_word"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setReviews_with_word(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "fromCSV"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setFromCSV(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "filter"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setFilter(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "proj"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setProj(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "show"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setShow(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "count"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setCount(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "toCSV"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setToCSV(char **input, GHashTable *tableHash);

/**
 * @brief Invoca a Query correspondente ao comando "index"
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void setIndex(char **input, GHashTable *tableHash);

/**
 * @brief Função de teste e invocação de Querys
 * 
 * @param input Array de apontadores para strings, comando inserido no stdin
 * @param tableHash HashTable usada para guardar os dados do tipo VARIABLE
 * @return ** void 
 */
void getQuery(char **input, GHashTable *tableHash);

/**
 * @brief Função testa se o delimitador neste caso ';' tem antes um ')'.
 * 
 * @param text buffer
 * @param out string delimitada
 * @return ** void 
 */
void strsepAlterada(char** text, char** out);

/**
 * @brief Função Main da Interface de Gestão e Visualização do Projeto
 * 
 * @return ** void 
 */
void interpretador();
#endif