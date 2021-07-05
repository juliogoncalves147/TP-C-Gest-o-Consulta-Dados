#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ReviewsCollection.h"

struct reviewsCollection
{
    GHashTable *reviewsTable;
};

struct WordStruct
{
    GSList *lista_Ids;
    char *word;
};

REVIEWS_C initReviewsCollection()
{
    REVIEWS_C r = malloc(sizeof(struct reviewsCollection));
    r->reviewsTable = g_hash_table_new_full(g_str_hash,
                                            g_str_equal,
                                            (GDestroyNotify)g_free,
                                            (GDestroyNotify)r_freeReviews);
    return r;
}

STRUCTWORD initWordStruct(GSList *lista, char *word)
{
    STRUCTWORD new = malloc(sizeof(struct WordStruct));

    new->lista_Ids = lista;
    new->word = word;

    return new;
}

void addReviewToCollection(REVIEWS_C rc, REVIEWS r)
{
    g_hash_table_insert(rc->reviewsTable, r_getReview_ID(r), r);
}

int reviewsCollectionSize(REVIEWS_C rc)
{
    return (g_hash_table_size(rc->reviewsTable));
}

void destroyReviewsCollection(REVIEWS_C r)
{
    g_hash_table_destroy(r->reviewsTable);
    free(r);
}
void filterReviewWord(gpointer key, gpointer value, gpointer data)
{
    STRUCTWORD auxiliar = (STRUCTWORD)data;
    REVIEWS r = (REVIEWS)value;
    char *needle = strdup(auxiliar->word);
    remove_punct_and_make_lower_case(needle);   //Needle para lower case e sem pontuacao

    if (r_textHasWord(r, needle))   //Verifica se texto de review tem needle
    {
        auxiliar->lista_Ids = g_slist_prepend(auxiliar->lista_Ids, r_getReview_ID(r));  //Adiciona a lista
    }
}
GSList *get_reviews_with_n_word(REVIEWS_C rcol, char *word)
{
    GSList *final = NULL;   //Lista de IDs a devolver
    STRUCTWORD auxiliar = initWordStruct(final, word);  //Estrutura auxiliar para foreach

    g_hash_table_foreach(rcol->reviewsTable, filterReviewWord, auxiliar);

    final = auxiliar->lista_Ids;

    g_free(auxiliar);

    return final;
}