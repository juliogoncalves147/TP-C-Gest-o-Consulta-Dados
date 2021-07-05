/// \file
#ifndef TABLE_H
#define TABLE_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "glibWarningAvoid.h"
#include "Business.h"
#include "BusinessCollection.h"
#include "CidadeCollection.h"
#include "Cidade.h"
#include "OrdenacaoEstruturas.h"

/**
 * @brief Estrutura de uma table
 * 
 */
typedef struct table *TABLE;

/**
 * @brief Estrutura auxiliar
 * 
 */
typedef struct citie_bus_col *C_B_COL;

/**
 * @brief Lista de Comandos possiveis para a query "filter"
 * 
 */
typedef enum
{
    LT, //Lower0
    EQ, //Equal1
    GT  //Greater2
} op_elem;

/**
 * @brief Iniciar table
 * 
 * @param hd Header da table
 * @param nl Numero de linhas
 * @param nc Numero de colunas
 * @return TABLE Nova table
 */
TABLE init_table(GString *hd, int nl, int nc);

/**
 * @brief Decide se uma linha deve ser filtrada ou nao
 * 
 * @param linha Linha da table
 * @param coluna Numero de colunas
 * @param value Valor a ser comparado
 * @param operator Operador da comparacao
 * @return int 1 -> Apagar | 0 -> Nao apagar
 */
int filter_string(GString *linha, int coluna, char *value, op_elem operator);

/**
 * @brief Funcao que filta linhas de uma tabela
 * 
 * @param tab Tabela a ser filtrada
 * @param col Coluna a servir argumentos
 * @param value Valor a ser comparado com valores da coluna escolhida
 * @param operator Operador para fazer comparacao
 * @return TABLE 
 */
TABLE filter_table(TABLE tab, int col, char *value, op_elem operator);

/**
 * @brief Obter x colunas de uma so linha
 * 
 * @param line Linha a ser filtrada
 * @param col1 Primeira coluna(esq)
 * @param col2 Segunda coluna(dir)
 * @return GString* Nova linha, ja filtrada
 */
GString *get_line_collums(GString *line, int col1, int col2);

/**
 * @brief Delimita uma tabela pelo numero de colunas
 * 
 * @param tab Tabela a ser filtrada
 * @param col1_a Primeira coluna(esq)
 * @param col2_a Segunda coluna(dir)
 * @return TABLE Nova Tabela
 */
TABLE get_table_collums(TABLE tab, int col1_a, int col2_a);

/**
 * @brief Table da query 2 e query 5
 * 
 * @param lista Lista de user ids
 * @param bc Colecao de negocios
 * @param linhas Numero de linhas da nova table
 * @return TABLE Nova table
 */
TABLE query_2_5_table(GSList *lista, BUSINESS_C bc, int linhas);

/**
 * @brief Constroi tabela da query 3
 * 
 * @param info Info de negocio
 * @return TABLE Nova tabela
 */
TABLE query3_table(char *info);

/**
 * @brief Constroi tabela da query 4
 * 
 * @param list Lista de ids
 * @param linhas Numero de linhas da nova tabela
 * @param bc Colecao de negocios
 * @return TABLE Nova tabela
 */
TABLE query4_table(GSList *list, int linhas, BUSINESS_C bc);

/**
 * @brief Tabela da query 6
 * 
 * @param ccol Colecao de cidades
 * @param bcol Colecao de negocios
 * @return TABLE Nova tabela
 */
TABLE query6_table(CITIES_COL ccol, BUSINESS_C bcol);

/**
 * @brief Lista de users para tabela da query 7
 * 
 * @param lista_u Lista de users
 * @return TABLE Nova tabela
 */
TABLE query7_table(GSList *lista_u);

/**
 * @brief Lista de ids para table
 * 
 * @param lista_b Lista de ids de business
 * @param bc Business collection 
 * @return TABLE Tabela a ser devolvia
 */
TABLE query8_table(GSList *lista_b, BUSINESS_C bc);

/**
 * @brief Lista de ids da query 9 para table
 * 
 * @param lista Lista de ids
 * @return TABLE Tabela construida
 */
TABLE query9_table(GSList *lista);

/**
 * @brief index_table do interpretador
 * 
 * @param t Tabela a ser indexada
 * @param coluna Coluna desejada
 * @param linha Linha desejada
 * @return TABLE Tabela resultante da indexacao
 */
TABLE index_table(TABLE t, int coluna, int linha);

/**
 * @brief Destroi tabela com opçao de destruir conteudo
 * 
 * @param t Tabela a ser destruida
 * @param true Opcao para destruir conteudo
 */
void table_destroy(TABLE t, int true);

/**
 * @brief Destroi tabela sem opçao de destruir conteudo
 * 
 * @param x Pointer tabela
 */
void table_destroy2(void *x);

/**
 * @brief Imprime a tabela
 * 
 * @param t Tabela
 */
void print_table(TABLE t);

void print_table_aux(gpointer data, gpointer user_data);

/**
 * @brief Funcao auxiliar para mudar os delimitadores ';' para delim
 * 
 * @param frase Frase a ser atualizada
 * @param delim Novo delimitador
 * @return char* Nova frase com o novo delimitador
 */
char *g_string_to_string(GString *frase, char delim);

/**
 * @brief Table to ficheiro csv do interpretador
 * 
 * @param tabela Tabela a ser transferida para ficheiro
 * @param delim Delimitador a ser usado no ficheiro
 * @param file_path Destino do ficheiro
 * @return int Sucesso/Nao sucesso
 */
int table_to_csv(TABLE tabela, char delim, char *file_path);

/**
 * @brief Interpretador cvs to table
 * 
 * @param file_path Ficheiro cvs a converter em table
 * @param delim Delimitador no ficheiro que separa os campos
 * @return TABLE Table originaria do ficheiro
 */
TABLE csv_to_table(char *file_path, char delim);

/**
 * @brief Calcula tamanho de todos os campos dado uma linha de uma table
 * 
 * @param linha Linha a ser analisada
 * @param colunas Numero de colunas da table
 * @return int* Tamanho dos campos desta linha
 */
int *sizes_per_collum(char *linha, int colunas);

/**
 * @brief Calcula maior palavra em cada coluna da tabela
 * 
 * @param t Tabela a analisar
 * @return int* Lista de tamanhos de cada coluna
 */
int *biggest_sizes_per_collum(TABLE t);

/**
 * @brief Recebe uma linha da table e formata para imprimir
 * 
 * @param matriz Palavras que constituem a linha a imprimir
 * @param sizess Tamanhos da maior palavra para cada coluna
 * @param colunas Numero de colunas da table
 * @return char* Linha com formato pronto a ser imprimido
 */
char *show_line(char **matriz, int *sizess, int colunas);

/**
 * @brief Funcao que imprime tabela dada uma linha
 * 
 * @param tabela Tabela a imprimir
 * @param linha Linha de onde começa a imprimir
 */
void show_table(TABLE tabela, int linha);

/**
 * @brief Get the Table lines lenght object
 * 
 * @param tabela 
 * @return ** int Numero de linhas 
 */
int getTable_lines_lenght(TABLE tabela);

/**
 * @brief Destoi estrutura auxiliar C_B_COL 
 * 
 * @param cbcol Estrutura a ser destruida
 */
void cbcol_destroy(C_B_COL cbcol);

/**
 * @brief Funcao auxiliar para iterar colecao cidade e preencher tabela
 * 
 * @param key Key da cidade
 * @param value Cidade
 * @param data Estrutura auxilia C_B_COL
 */
void iterate_citie_coll(gpointer key, gpointer value, gpointer data);

#endif