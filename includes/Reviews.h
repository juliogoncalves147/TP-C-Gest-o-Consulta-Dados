/// \file
#ifndef REVIEWS_H
#define REVIEWS_H
#define _GNU_SOURCE
#include "glibWarningAvoid.h"

/**
 * @brief Estrutura das reviews
 * 
 */
typedef struct reviews *REVIEWS;

/**
 * @brief Inicialização das reviews
 * 
 * @param review_id ID da review
 * @param user_id ID do user
 * @param business_id ID do business
 * @param stars estrelas
 * @param useful útil
 * @param funny engraçado
 * @param cool fixe
 * @param date data
 * @param text texto
 * @return REVIEWS reviews inicializada
 */
REVIEWS r_initReviews(char *review_id, char *user_id, char *business_id, float stars, int useful, int funny, int cool, char *date, char *text);

/**
 * @brief Inicializa as reviews a partir da linha de um ficheiro
 * 
 * @param fileline ficheiro
 * @param fieldSeparator separador
 * @return REVIEWS reviews inicializadas
 */
REVIEWS r_initReviewsFromFileLine(char *fileline, char *fieldSeparator);

/**
 * @brief Obtém o ID de uma review
 * 
 * @param r reviews de onde vamos obter o review ID
 * @return char* ID da review 
 */
char *r_getReview_ID(REVIEWS r);

/**
 * @brief Obtém o user ID de uma review
 * 
 * @param r reviews de onde vamos obter o user ID
 * @return char* User ID da review
 */
char *r_getUser_ID(REVIEWS r);

/**
 * @brief Obtém o business ID de uma review
 * 
 * @param r reviews de onde vamos obter o business ID
 * @return char* Business ID da review
 */
char *r_getBusiness_ID(REVIEWS r);

/**
 * @brief Obtém as stars de uma review
 * 
 * @param r review de onde vamos obter as stars
 * @return float Stars da review
 */
float r_getStars(REVIEWS r);

/**
 * @brief Obtém o useful de uma review
 * 
 * @param r review de onde vamos obter o useful
 * @return int Useful de uma review
 */
int r_getUseful(REVIEWS r);

/**
 * @brief Obtém o funny de uma review
 * 
 * @param r Review de onde vamos obter o funny
 * @return int Funny de uma review
 */
int r_getFunny(REVIEWS r);

/**
 * @brief Obtém o cool de uma review
 * 
 * @param r review de onde vamos obter um cool
 * @return int Cool de uma review
 */
int r_getCool(REVIEWS r);
/**
 * @brief Obtém a data de uma review
 * 
 * @param r review de onde vamos obter a data
 * @return char* Data da review
 */
char *r_getDate(REVIEWS r);

/**
 * @brief Obtém o text de uma review
 * 
 * @param r Review de onde vamos obter o text
 * @return char* text da review
 */
char *r_getTest(REVIEWS r);

/**
 * @brief Obtém toda a informação de uma review
 * 
 * @param x Review de onde vamos obter toda a informação
 * @return char* Informação da review
 */
char *r_getReviewsInfo(void *x);

/**
 * @brief Clona uma review
 * 
 * @param r review que vai ser clonada
 * @return REVIEWS Clone da review
 */
REVIEWS r_cloneReviews(REVIEWS r);

/**
 * @brief Libertação de uma review
 * 
 * @param x review a ser libertada
 */
void r_freeReviews(void *x);

/**
 * @brief Remove a pontuação e substitui maiúsculas por minúsculas
 * 
 * @param p String a ser alterada
 */
void remove_punct_and_make_lower_case(char *p);

/**
 * @brief Verifica se o texto de uma review tem uma palavra
 * 
 * @param r review com texto a ser comparado
 * @param word palavra a ser comparada
 * @return int Retorna true or false
 */
int r_textHasWord(REVIEWS r, char *word);

#endif