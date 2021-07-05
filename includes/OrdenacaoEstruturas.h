/// \file
#ifndef ORDENATED_STRUCTS_H
#define ORDENATED_STRUCTS_H
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glibWarningAvoid.h"
#include "BusinessCollection.h"
#include "ReviewsCollection.h"

/**
 * @brief Estrutura de ordenação de businesses por estrelas
 * 
 */
typedef struct OrdStruct *STRUCTORD;

/**
 * @brief Estrutura com business ID e respetiva média de estrelas
 * 
 */
typedef struct businessAndStarsAux *STRUCTBUSSTARS;

/**
 * @brief Inicialização da esturtura
 * 
 * @param list lista de ID's
 * @param top top de business
 * @param category categoria
 * @return STRUCTORD 
 */
STRUCTORD initOrdStruct(GSList *list, int top, char *category);

/**
 * @brief Inicialização da estrutura
 * 
 * @param id Business ID
 * @param stars Média de stars
 * @return STRUCTBUSSTARS struct inicializada
 */
STRUCTBUSSTARS init_business_and_stars_aux(char *id, float stars);

/**
 * @brief Libertação da estrutura STRUCTORD
 * 
 * @param b Estrutura a ser libertada
 */
void free_OrdStruct(void *b);

/**
 * @brief Libertação da estrutura STRUCTBUSSSTARS
 * 
 * @param pt Estrutura a ser libertada
 */
void free_bus_stars(void *pt);

/**
 * @brief Compara a média de estrelas entre dois business
 * 
 * @param as apontador para uma struct STRUCTBUSSTARS
 * @param bs apontador para uma struct STRUCTBUSSTARS
 * @return gint ------------------------------------------------------------------------- 
 */
gint comparatedBusiness(gconstpointer as, gconstpointer bs);

/**
 * @brief 
 * 
 * @param key 
 * @param value 
 * @param data 
 */
void filterBusinessCategory(gpointer key, gpointer value, gpointer data);

/**
 * @brief Obtém os businesses com a respetiva categoria
 * 
 * @param bcol coleção de businesses
 * @param top o top de stars
 * @param category a categoria procurada
 * @return GSList* businesses com a respteiva categoria
 */
GSList *business_with_category(GHashTable *tabela, int top, char *category);

/**
 * @brief Obtém o ID da estrutura
 * 
 * @param x estrutura
 * @return char* Business ID
 */
char *get_id_busstars_aux(STRUCTBUSSTARS x);

/**
 * @brief Obtém a média estrelas
 * 
 * @param x estrutura
 * @return float média de estrelas do business
 */
float get_media_stars_busstars_aux(STRUCTBUSSTARS x);

/**
 * @brief Liberta a estrutura
 * 
 * @param x estrutura
 */
void free_busstars_aux(STRUCTBUSSTARS x);

#endif
