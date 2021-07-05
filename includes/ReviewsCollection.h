/// \file
#ifndef REVIEWS_COLLECTION_H
#define REVIEWS_COLLECTION_H
#define _GNU_SOURCE

#include "glibWarningAvoid.h"
#include "Reviews.h"

/**
 * @brief coleção das reviews
 * 
 */
typedef struct reviewsCollection *REVIEWS_C;

/**
 * @brief Estrutura com lista de ids e uma palavra
 * 
 */
typedef struct WordStruct *STRUCTWORD;

/**
 * @brief Inicialização da coleção de reviews
 * 
 * @return REVIEWS_C coleção de reviews
 */
REVIEWS_C initReviewsCollection();

/**
 * @brief Adiciona uma review à coleção
 * 
 * @param rc Coleção de reviews
 * @param r review
 */
void addReviewToCollection(REVIEWS_C rc, REVIEWS r);

/**
 * @brief Obtém o tamanho da coleção
 * 
 * @param rc Coleção de reviews
 * @return int Tamanho
 */
int reviewsCollectionSize(REVIEWS_C rc);

/**
 * @brief Destroi a coleção de reviews
 * 
 * @param r coleção
 */
void destroyReviewsCollection(REVIEWS_C r);

/**
 * @brief Obtém as reviews com uma palavra presente
 * 
 * @param rcol coleção de reviews
 * @param word Palavra que tem de estar presente
 * @return GSList* Reviews que contém a palavra
 */
GSList *get_reviews_with_n_word(REVIEWS_C rcol, char *word);

#endif