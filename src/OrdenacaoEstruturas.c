#include "OrdenacaoEstruturas.h"

struct OrdStruct
{
    GSList *lista_IDs;
    char *category;
    int size;
    int inseridos;
    float menor;
};

struct businessAndStarsAux
{
    char *business_id;
    float media_stars;
};

STRUCTORD initOrdStruct(GSList *list, int top, char *category)
{

    STRUCTORD new = malloc(sizeof(struct OrdStruct));

    new->lista_IDs = list;
    new->category = category;
    new->inseridos = 0;
    new->size = top;
    new->menor = 0;

    return new;
}

STRUCTBUSSTARS init_business_and_stars_aux(char *id, float stars)
{
    STRUCTBUSSTARS new = malloc(sizeof(struct businessAndStarsAux));
    new->business_id = id;
    new->media_stars = stars;
    return new;
}

void free_OrdStruct(void *b)
{
    STRUCTORD x = (STRUCTORD)b;
    g_slist_free_full(x->lista_IDs, (GDestroyNotify)free_busstars_aux);
    free(x->category);
    free(x);
}

void free_bus_stars(void *pt)
{
    STRUCTBUSSTARS old = (STRUCTBUSSTARS)pt;
    g_free(old->business_id);
    free(old);
}

gint comparatedBusiness(gconstpointer as, gconstpointer bs)
{
    float a = ((STRUCTBUSSTARS)as)->media_stars;
    float b = ((STRUCTBUSSTARS)bs)->media_stars;
    float result = b - a;
    if (result > 0)
        return 1;
    else if (result < 0)
        return -1;
    else
        return 0;
}

void filterBusinessCategory(gpointer key, gpointer value, gpointer data)
{
    STRUCTORD cc = (STRUCTORD)data;
    BUSINESS b = (BUSINESS)value;

    if (business_has_categorie(b, cc->category))
    {
        float stars = b_getStarsMedia(b);
        int has_space = cc->inseridos < cc->size;

        if (stars > cc->menor || has_space)
        {
            STRUCTBUSSTARS new = init_business_and_stars_aux(b_getBusiness_Id(b), stars);
            if (has_space)
            {
                cc->lista_IDs = g_slist_insert_sorted(cc->lista_IDs, new, (GCompareFunc)comparatedBusiness);
                cc->inseridos++;
                cc->menor = ((STRUCTBUSSTARS)(g_slist_last(cc->lista_IDs)->data))->media_stars;
            }
            else
            {
                cc->lista_IDs = g_slist_prepend(cc->lista_IDs, new);
                cc->lista_IDs = g_slist_sort(cc->lista_IDs, comparatedBusiness);
                GSList *aux = g_slist_last(cc->lista_IDs);
                cc->lista_IDs = g_slist_remove_link(cc->lista_IDs, g_slist_last(cc->lista_IDs));
                free_bus_stars(aux->data);
                g_slist_free1(aux);
                cc->menor = ((STRUCTBUSSTARS)(g_slist_last(cc->lista_IDs)->data))->media_stars;
            }
        }
    }
}

GSList *business_with_category(GHashTable *tabela, int top, char *category)
{
    GSList *lista = NULL;
    STRUCTORD cc = initOrdStruct(lista, top, category);

    g_hash_table_foreach(tabela, filterBusinessCategory, cc);

    lista = cc->lista_IDs;
    g_free(cc);
    return lista;
}
char *get_id_busstars_aux(STRUCTBUSSTARS x)
{
    return strdup(x->business_id);
}

float get_media_stars_busstars_aux(STRUCTBUSSTARS x)
{
    return x->media_stars;
}

void free_busstars_aux(STRUCTBUSSTARS x)
{
    free(x->business_id);
    free(x);
}