/// \file
#ifndef LER_H
#define LER_H
#define _GNU_SOURCE

#include "glibWarningAvoid.h"
#include "sgr.h"

/**
 * @brief Lê o ficheiro das reviews
 * 
 * @param file ficheiro que vai ser lido
 * @param rc coleção de reviews                                                                                       
 * @param bc coleção de business
 * @param uc coleção de users
 */
void r_read_file(char *file, REVIEWS_C rc, BUSINESS_C bc, USERS_C uc);

/**
 * @brief Lê o ficheiro dos business
 * 
 * @param file ficheiro dos business
 * @param bc coleção de business
 */
void b_read_file(char *file, BUSINESS_C bc);

/**
 * @brief Lê o ficheiro dos users
 * 
 * @param file ficheiro de users
 * @param uc coleção de users
 */
void u_read_file(char *file, USERS_C uc);

#endif