/// \file
#ifndef _BUSINESS_H
#define _BUSINESS_H
#define _GNU_SOURCE

#include "glibWarningAvoid.h"
/**
 * @brief Estrutura dos businesses
 * 
 */
typedef struct business *BUSINESS;

/**
 * @brief Inicialização do business
 * 
 * @param business_id id do business
 * @param name nome do business
 * @param city cidade do business
 * @param state estado do business
 * @param categories categorias do business
 * @return BUSINESS business inicializado
 */
BUSINESS b_initBusiness(char *business_id, char *name, char *city, char *state, char *categories);

/**
 * @brief Inicialização do business a partir de uma linha de um ficheiro
 * 
 * @param fileline linha do ficheiro
 * @param fieldSeparator separador das linhas
 * @return BUSINESS business inicializado
 */
BUSINESS b_initBusinessFromFileLine(char *fileline, char *fieldSeparator);

/**
 * @brief obtém as estrelas de um business
 * 
 * @param x business de onde vamos obter as stars
 * @return int número de estrelas
 */
int b_getStars(BUSINESS x);

/**
 * @brief obtém o número de reviews de um business
 * 
 * @param x business de onde vamos obter o número de reviews
 * @return int número de reviews
 */
int b_getnumReviews(BUSINESS x);

/**
 * @brief obtém o ID de um business
 * 
 * @param x business de onde vamos obter o ID
 * @return char* business_id
 */
char *b_getBusiness_Id(BUSINESS x);

/**
 * @brief obtém o nome de um business
 * 
 * @param x business de onde vamos obter o nome
 * @return char* nome
 */
char *b_getName(BUSINESS x);

/**
 * @brief obtém a cidade do business
 * 
 * @param x business de onde vamos obter a cidade
 * @return char* cidade
 */
char *b_getCity(BUSINESS x);

/**
 * @brief obtém o estado de um business
 * 
 * @param x business de onde vamos obter o estado
 * @return char* estado
 */
char *b_getState(BUSINESS x);

/**
 * @brief obtém a categoria de um business
 * 
 * @param x business de onde vamos obter a categoria
 * @return char* categoria
 */
char *b_getCategories(BUSINESS x);

/**
 * @brief obtém o número médio de estrelas
 * 
 * @param x business de onde vamos obter o número médio de estrelas
 * @return float número médio de estrelas
 */
float b_getStarsMedia(BUSINESS x);

/**
 * @brief obtém toda a informação da struct business 
 * 
 * @param b business de onde vamos tirar toda a informação
 * @return char* informação do business
 */
char *b_getBusinessInfo(void *x);

/**
 * @brief obtém a informação necessária para a query 3
 * 
 * @param b business de onde vamos retirar a informação
 * @return char* informação
 */
char *b_getBusinessInfoQ3(BUSINESS b);

/**
 * @brief dá clone de um business
 * 
 * @param x business para dar clone
 * @return BUSINESS business clonado
 */
BUSINESS b_cloneBusiness(BUSINESS x);

/**
 * @brief dá free de um business
 * 
 * @param b business que vai ser libertado
 */
void b_freeBusiness(void *b);

/**
 * @brief verifica se um business começa por uma letra
 * 
 * @param b business
 * @param c letra pela qual queremos que comece
 * @return int return true or false
 */
int businessStartsWithLetter(BUSINESS b, char c);

/**
 * @brief atualiza a informação de um business útil na leitura de reviews
 * 
 * @param c business a atualizar
 * @param stars stars desse business
 */
void b_updateStatus(BUSINESS c, float stars);

/**
 * @brief verifica se um business pertence a uma cidade
 * 
 * @param b business a ser verificado
 * @param city cidade
 * @return int retorna true or false
 */
int businessBelongCity(BUSINESS b, char *city);

/**
 * @brief verifica se a média de stars de um business é maior que um valor
 * 
 * @param b business a ser verificado
 * @param stars número médio para comparar
 * @return int retorna true or false
 */
int businessHasStars(BUSINESS b, float stars);

/**
 * @brief verifica se um business tem a categoria
 * 
 * @param b business
 * @param needle categoria
 * @return int retorna true or false
 */
int business_has_categorie(BUSINESS b, char *needle);

#endif