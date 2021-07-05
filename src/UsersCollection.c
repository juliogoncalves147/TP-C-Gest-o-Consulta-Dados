#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UsersCollection.h"

struct usersCollection
{
    GHashTable *usersTable;
};

struct usersAndBusinessCollection
{
    USERS_C usersTable;
    BUSINESS_C businessTable;
    GSList *lista_IDs;
};

USERS_C initUsersCollection()
{
    USERS_C us = malloc(sizeof(struct usersCollection));
    us->usersTable = g_hash_table_new_full(g_str_hash,
                                           g_str_equal,
                                           (GDestroyNotify)g_free,
                                           (GDestroyNotify)u_freeUser);
    return us;
}


void addUsersToCollection(USERS_C uc, USERS u)
{
    g_hash_table_insert(uc->usersTable, u_getUser_id(u), u);
}


int usersCollectionSize(USERS_C uc)
{
    return (g_hash_table_size(uc->usersTable));
}


void destroyUsersCollection(USERS_C u)
{
    g_hash_table_destroy(u->usersTable);
    free(u);
}


USERS getUsers(USERS_C bs, char *key)
{
    USERS b = (USERS)g_hash_table_lookup(bs->usersTable, key);
    return b;
}


int userVisited(USERS u, USER_AND_BUS_C str)
{ 
    GSList *lista = u_getListReviews(u);
    if (lista == NULL)
        return 0;
    GSList *iterator = NULL;
    iterator = lista;

    BUSINESS b = getBusiness(str->businessTable, (char *)lista->data);

    char *state = b_getState(b);
    iterator = iterator->next;
    int new = 0;
    for (; iterator && !new; iterator = iterator->next)
    {
        BUSINESS aux = getBusiness(str->businessTable, (char *)iterator->data);
        char *state_aux = b_getState(aux);

        if (strcmp(state, state_aux))
            new = 1;
        free(state_aux);
    }
    free(state);
    return new;
}


void filterAndAddVisitedUser(gpointer key, gpointer value, gpointer data)
{
    USERS u = (USERS)value;
    USER_AND_BUS_C str = (USER_AND_BUS_C)data;

    if (userVisited(u, str))
    {
        str->lista_IDs = g_slist_prepend(str->lista_IDs, strdup(key));
    }
}


GSList *u_filterStatesVisiter(USERS_C ucol, BUSINESS_C bcol)
{

    GSList *lista = NULL;

    USER_AND_BUS_C str = malloc(sizeof(struct usersAndBusinessCollection));

    str->lista_IDs = lista;
    str->usersTable = ucol;
    str->businessTable = bcol;

    g_hash_table_foreach(ucol->usersTable, filterAndAddVisitedUser, str);

    lista = str->lista_IDs;
    g_free(str);
    return lista;
}