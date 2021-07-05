/// \file
#ifndef USERS_COLLECTION_H
#define USERS_COLLECTION_H
#define _GNU_SOURCE

#include "users.h"
#include "glibWarningAvoid.h"

/**
 * @brief Coleção dos users
 * 
 */
typedef struct usersCollection *USERS_C;

/**
 * @brief Estrutura auxiliar
 * 
 */
typedef struct usersAndBusinessCollection *USER_AND_BUS_C;

/**
 * @brief Inicialização da coleção dos users
 * 
 * @return USERS_C Coleção de users
 */
USERS_C initUsersCollection();

/**
 * @brief Adiciona um User à coleção
 * 
 * @param uc Coleção de users
 * @param u User a adicionar
 */
void addUsersToCollection(USERS_C uc, USERS u);

/**
 * @brief Número de users guardado na coleção
 * 
 * @param uc Coleção de users
 * @return int Número de users
 */
int usersCollectionSize(USERS_C uc);

/**
 * @brief Destroi a coleção de users
 * 
 * @param u Coleção a destruir
 */
void destroyUsersCollection(USERS_C u);

/**
 * @brief Obtém um user da coleção
 * 
 * @param bs Coleção de users
 * @param key Chave para o user
 * @return USERS User obtido
 */
USERS getUsers(USERS_C bs, char *key);

/**
 * @brief Compara se um User foi a dois estados diferentes
 * 
 * @param u User
 * @param str Estrutura com as coleções de users e business
 * @return int retorna true or false
 */
int userVisited(USERS u, USER_AND_BUS_C str);

/**
 * @brief Adiciona um user ID a lista de ids no caso de ter visitado dois estados diferentes
 * 
 * @param key User ID a adicionar
 * @param value User 
 * @param data Estrutura para comparar com User
 */
void filterAndAddVisitedUser(gpointer key, gpointer value, gpointer data);

/**
 * @brief Função que verifica se os users são internacionais
 * 
 * @param ucol coleção dos users
 * @param bcol coleção dos businesses
 * @return GSList* Lista de users internacionais
 */
GSList *u_filterStatesVisiter(USERS_C ucol, BUSINESS_C bcol);

#endif