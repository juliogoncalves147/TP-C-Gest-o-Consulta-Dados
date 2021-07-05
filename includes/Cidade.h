/// \file
#ifndef CIDADE_H
#define CIDADE_H
#define _GNU_SOURCE
#include <stdio.h>

#include "glibWarningAvoid.h"
#include "BusinessCollection.h"

/**
 * @brief Estrutura de uma cidade ordenada por estrelas
 * 
 */
typedef struct cidadeOrdenada *CIDADE_ORD;

/**
 * @brief Estrutura auxiliar com id de business e media do mesmo
 * 
 */
typedef struct businessAndStars *BUS_STARS;

/**
 * @brief Inicializa uma cidade
 * 
 * @param size Tamanho da cidade
 * @param city Nome da cidade
 * @return CIDADE_ORD Nova Cidade ordenada
 */
CIDADE_ORD initCidadeOrdenada(int size, char *city);

/**
 * @brief Inicializa estrutura auxiliar
 * 
 * @param id Id de business
 * @param stars Stars do mesmo
 * @return BUS_STARS Retorna nova estrutura auxiliar
 */
BUS_STARS init_business_and_stars(char *id, float stars);

/**
 * @brief Funcao que ordena businesses por media de stars
 * 
 * @param as pointer para business 1
 * @param bs pointer para business 2
 * @return gint resultado da comparacao
 */
gint compareBusiness(gconstpointer as, gconstpointer bs);

/**
 * @brief Funcao que insere um negocio numa cidade
 * 
 * @param cidade Cidade onde vai ser inserido
 * @param bus Negocio a ser inserido
 */
void insert_business_in_city(CIDADE_ORD cidade, BUSINESS bus);

/**
 * @brief Liberta espaco ocupado por estrutura auxiliar de cidade ordenada
 * 
 * @param b Apontador para estrutura a ser destruida
 */
void c_free_cidade_ord(void *b);

/**
 * @brief Liberta Cidade Ordenada
 * 
 * @param b Apontador para Cidade a ser Destruida 
 */
void c_free_cidade(void *b);

/**
 * @brief Preenche linhas de uma table com informacao de uma cidade
 * 
 * @param c Cidade de onde se vai retirar informacao
 * @param pt Lista de linhas da table
 * @param bc Colecao de negocios
 */
void c_fill_table(CIDADE_ORD c, GPtrArray *pt, BUSINESS_C bc);

/**
 * @brief Funcao auxiliar que calcula numero de negocios numa so cidade(nem todas as cidades enchem top x)
 * 
 * @param key Key da cidade
 * @param value Cidade em si
 * @param data Acumulador de funcao chamadora
 */
void c_num_of_bus(gpointer key, gpointer value, gpointer data);

#endif