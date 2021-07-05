/// \file
#ifndef INTERPRETADORVIEW_H
#define INTERPRETADORVIEW_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Exibe a lista de comandos possíveis aquando da chamada do comando "help".
 * 
 * @return ** void 
 */
void show_comands();

/**
 * @brief Exibe a lista de comandos possiveis de utilizar aquando da funcao show (Paginação)
 * 
 * @return ** void 
 */
void paginacao_comands();

/**
 * @brief Exibe uma mensagem de erro
 * 
 * @return ** void 
 */
void erro_stdin();

/**
 * @brief Exibe uma mensagem alusiva ao termino do programa
 * 
 * @return ** void 
 */
void leaving();

/**
 * @brief   Função de print de erros de leitura do stdin.
 * 
 * @return ** int 
 */
int memory_error();

/**
 * @brief Dar clean ao stdout usada na Paginação.
 * 
 * @return ** void 
 */
void cleanOutput();

/**
 * @brief Exibe uma mensagem de erro
 * 
 * @return ** void 
 */
void undefinedVariable();

/**
 * @brief Exibe uma mensagem de erro
 * 
 * @return ** void 
 */
void invalidComand();

/**
 * @brief Testa se o utilizador deseja carregar os ficheiros pré-definidos
 * 
 * @return ** int 
 */
int default_getLoad();
#endif

