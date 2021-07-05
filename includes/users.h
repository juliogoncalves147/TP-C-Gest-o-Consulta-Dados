/// \file
#ifndef USERS_H
#define USERS_H
#define _GNU_SOURCE

#include "glibWarningAvoid.h"
#include "BusinessCollection.h"
#include "ReviewsCollection.h"

/**
 * @brief Estrutura dos users
 * 
 */
typedef struct users *USERS;

/**
 * @brief Inicialização de um user
 * 
 * @param u User ID
 * @param n Nome
 * @param f Friends
 * @return USERS user inicializado
 */
USERS u_initUser(char *u, char *n, char *f);

/**
 * @brief Inicialização de um user através da linha de um ficheiro
 * 
 * @param fileLine Linha do ficheiro
 * @param fieldSeparator separador
 * @return USERS user inicializado
 */
USERS u_initUserFromFileLine(char *fileLine, char *fieldSeparator);

/**
 * @brief Obtém o ID de um user
 * 
 * @param u User de onde obtemos o ID
 * @return char* ID do user
 */
char *u_getUser_id(USERS u);

/**
 * @brief Obtém o nome do user
 * 
 * @param u User de onde vamos obter o nome
 * @return char* Nome do user
 */
char *u_getName(USERS u);

/**
 * @brief Obtém os amigos de um user
 * 
 * @param u User de onde se obtém os amigos
 * @return char* amigos do user
 */
char *u_getFriends(USERS u);

/**
 * @brief Obtém toda a informação de um user
 * 
 * @param x User do qual vamos obter informação
 * @return char* Informação do user
 */
char *u_getUserInfo(void *x);

/**
 * @brief Clone do User
 * 
 * @param u User clonado
 * @return USERS Clone do user
 */
USERS u_cloneUser(USERS u);

/**
 * @brief Libertação do user
 * 
 * @param x User libertado
 */
void u_freeUser(void *x);

/**
 * @brief Obtém todos os business onde o user fez review
 * 
 * @param u User de onde se obtem a informação
 * @return GSList* Lista de todos os business onde o user fez review
 */
GSList *u_getListReviews(USERS u);

/**
 * @brief Adiciona um business a lista de business cujo o user fez review
 * 
 * @param c User onde se adiciona a informação
 * @param business_id business a ser adicionado
 */
void u_updateStatus(USERS c, char *business_id);

#endif