/// \file
#ifndef BUSINESS_COLLECTION_H
#define BUSINESS_COLLECTION_H
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glibWarningAvoid.h"
#include "Business.h"

/**
 * @brief Estrutura auxiliar com lista de ids e char por que respetivo nome comeca
 * 
 */
typedef struct listAndChar *LIST_AND_CHAR;

/**
 * @brief Estrutura auxiliar com lista de negocios, sua cidade e media de estrelas
 * 
 */
typedef struct listCityStar *LIST_CITY_STAR;

/**
 * @brief Estrutura auxiliar com lista de ids, e categoria dos negocios
 * 
 */
typedef struct citiesAndCategory *CITIES_AND_CATEGORY;

/**
 * @brief Colecao de Business
 * 
 */
typedef struct businessCollection *BUSINESS_C;

/**
 * @brief Criacao de estrutura de colecao de negocios
 * 
 * @return BUSINESS_C 
 */
BUSINESS_C initBusinessCollection();

/**
 * @brief Recebe negocio e verifica se comeca por letra desejada
 * 
 * @param key BUSINESS ID
 * @param value BUSINESS
 * @param data Chars de letras a verificar e lista onde adicionar ID
 */
void filterAndAddList(gpointer key, gpointer value, gpointer data);

/**
 * @brief Filtra colecao de negocios por aqueles que comecam com letra desejada
 * 
 * @param bcol Colecao a filtrar
 * @param c Char a procurar
 * @return GSList* Lista de IDs de negocios com os requisitos
 */
GSList *filterBusinessCollectionLetterX(BUSINESS_C bc, char c);

/**
 * @brief Verifica se negocio pertence a x cidade e tem no minimo y estrelas
 * 
 * @param key BUSINESS ID
 * @param value BUSINESS
 * @param data estrutura auxiliar com estrelas e cidade
 */
void filterAndAddListBusiness(gpointer key, gpointer value, gpointer data);

/**
 * @brief Filtra colecao de negocios por aqueles que pertencem a cidade desejada e teem minimo de estrelas
 * 
 * @param bcol Colecao a filtrar
 * @param stars Minimo de estrelas
 * @param city Cidade a que pertencem
 * @return GSList* Lista de IDs resultante
 */
GSList *filterBusinessCollectionCityandStars(BUSINESS_C bcol, float stars, char *city);

/**
 * @brief Adiciona negocio a colecao
 * 
 * @param bc Colecao de negocios
 * @param b Negocio a ser adicionado
 */
void addBusinessToCollection(BUSINESS_C bc, BUSINESS b);

/**
 * @brief Numero de Negocios na Colecao
 * 
 * @param bc Colecao de negocios
 * @return int Tamanho final
 */
int businessCollectionSize(BUSINESS_C bc);

/**
 * @brief Liberta espaco ocupado por colecao de negocios
 * 
 * @param bc Colecao a ser destruida
 */
void destroyBusinessCollection(BUSINESS_C bc);

/**
 * @brief Get Negocio dado ID
 * 
 * @param bs Colecao de negocios
 * @param key ID de negocio a procurar
 * @return BUSINESS Negocio resultante da procura
 */
BUSINESS getBusiness(BUSINESS_C bs, char *key);

void temp(BUSINESS_C bc, char *needle);

/**
 * @brief Get HashTable da Colecao de negocios
 * 
 * @param bcol Colecao ne negocios
 * @return GHashTable* Table que guarda negocios
 */
GHashTable *getHashTableB(BUSINESS_C bcol);

#endif