/// \file
#ifndef CIDADE_COLLECTION_H
#define CIDADE_COLLECTION_H
#define _GNU_SOURCE

#include "glibWarningAvoid.h"
#include "Cidade.h"
//#include "Business.h" Necessario

/**
 * @brief Estrutura Colecao Cidades
 * 
 */
typedef struct collectionCidade *CITIES_COL;

/**
 * @brief Estrutura auxiliar CC e top 
 * 
 */
typedef struct citiesColAndTop *CITIES_COL_AND_TOP;

/**
 * @brief Inicializa Estrutura Colecao de Cidades
 * 
 * @return CITIES_COL Nova Colecao de Cidades
 */
CITIES_COL init_cities_collection();

/**
 * @brief Getter de hash table da colecao de cidades
 * 
 * @param cc Colecao de Cidades
 * @return GHashTable* HashTable a retornar
 */
GHashTable *c_getTable(CITIES_COL cc);

/**
 * @brief Adicionar um negocio a uma cidade
 * 
 * @param cc Colecao de cidades
 * @param b Negocio a ser adicionado
 * @param top Top x de negocios
 */
void addBusinessToCity(CITIES_COL cc, BUSINESS b, int top);

/**
 * @brief Destroi Colecao de Cidades
 * 
 * @param c Colecao a destruir
 */
void destroyCitiesCollection(CITIES_COL c);

void addBusToCol(gpointer key, gpointer value, gpointer data);

/**
 * @brief Recebe colecao de negocios e organizaos por cidade e cada cidade ordenada por estrelas
 * 
 * @param bc Colecao de negocios
 * @param top Quantos negocios por cidade
 * @return CITIES_COL CITIES COL nova
 */
CITIES_COL group_per_city_ord(GHashTable *tabela, int top);

/**
 * @brief Funcao que retorna o numero de negocios numa colecao de cidades
 * 
 * @param cc Colecao de cidades
 * @return int Numero de negocios na colecao
 */
int cc_num_of_bus(CITIES_COL cc);

#endif