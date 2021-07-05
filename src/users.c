#include "users.h"

struct users
{
    char *user_id;
    char *name;
    char *friends;
    GSList *business_review;
};


USERS u_initUser(char *u, char *n, char *f)
{
    USERS aux = malloc(sizeof(struct users));
    aux->user_id = strdup(u);
    aux->name = strdup(n);
    aux->friends = strdup(f);
    aux->business_review = NULL;
    return aux;
}


USERS u_initUserFromFileLine(char *fileLine, char *fieldSeparator)
{   int key = 0;
    char *user_id = strsep(&fileLine, fieldSeparator);
    char *name = strsep(&fileLine, fieldSeparator);
    if (*user_id && user_id != NULL &&
        *name && name != NULL) key = 1;

    if (fileLine == NULL)
        return NULL;
    char *friends = strsep(&fileLine, fieldSeparator);
   /* if (fileLine != NULL)
        return NULL;
    */ // retirei isto pois acho que esta condição não é necessaria 4-5-2021
    if (key == 1) return u_initUser(user_id, name, friends);
    else return NULL;
}


char *u_getUser_id(USERS u)
{
    return strdup(u->user_id);
}


char *u_getName(USERS u)
{
    return strdup(u->name);
}


char *u_getFriends(USERS u)
{
    return strdup(u->friends);
}


char *u_getUserInfo(void *x)
{
    USERS u = (USERS)x; //Importante decidir maneira mais eficaz de calcular tamanho
    int size = (int)strlen(u->user_id) + (int)strlen(u->name) + (int)strlen(u->friends) + 100;
    char info[size];
    //FAZER ISTO FUNCIONAR SEM PERDA DE INFORMACAO
    snprintf(info, size, "User ID: %s | Name: %s | Friends: %s", u->user_id, u->name,
             u->friends);

    return strdup(info);
}


USERS u_cloneUser(USERS u)
{
    USERS novo = malloc(sizeof(struct users));
    novo->user_id = strdup(u->user_id);
    novo->name = strdup(u->name);
    novo->friends = strdup(u->friends);
    return novo;
}


void u_freeUser(gpointer x)
{
    USERS u = (USERS)x;
    free(u->user_id);
    free(u->name);
    free(u->friends);
    g_slist_free_full(g_steal_pointer(&(u->business_review)), g_free);
    free(u);
}


GSList *u_getListReviews(USERS u)
{
    return u->business_review;
}


void u_updateStatus(USERS c, char *business_id)
{
    c->business_review = g_slist_prepend(c->business_review, business_id);
}
