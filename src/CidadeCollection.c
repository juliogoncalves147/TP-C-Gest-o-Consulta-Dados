#include "CidadeCollection.h"

struct collectionCidade
{
    GHashTable *citiesTable;
};

struct citiesColAndTop
{
    CITIES_COL cc;
    int top;
};

CITIES_COL init_cities_collection()
{
    CITIES_COL new = malloc(sizeof(struct collectionCidade));
    new->citiesTable = g_hash_table_new_full(g_str_hash,
                                             g_str_equal,
                                             (GDestroyNotify)g_free,
                                             (GDestroyNotify)c_free_cidade);
    return new;
}

GHashTable *c_getTable(CITIES_COL cc)
{
    return cc->citiesTable;
}

void addBusinessToCity(CITIES_COL cc, BUSINESS b, int top)
{
    char *city = b_getCity(b);
    gpointer aux = g_hash_table_lookup(cc->citiesTable, city);

    if (aux != NULL)
    {
        insert_business_in_city((CIDADE_ORD)aux, b);
        free(city); //ADD
    }
    else
    {
        //Se for o primeiro negocio dessa cidade primeiro e preciso
        //criar a mesma na colecao de cidades
        CIDADE_ORD new = initCidadeOrdenada(top, city);
        g_hash_table_insert(cc->citiesTable, city, new);
        insert_business_in_city(new, b);
    }
}

void destroyCitiesCollection(CITIES_COL c)
{
    g_hash_table_destroy(c->citiesTable);
    free(c);
}

void addBusToCol(gpointer key, gpointer value, gpointer data)
{
    BUSINESS b = (BUSINESS)value;
    CITIES_COL_AND_TOP aux = (CITIES_COL_AND_TOP)data;

    addBusinessToCity(aux->cc, b, aux->top);
}
/**
 * @brief Recebe colecao de negocios e organizaos por cidade e cada cidade ordenada por estrelas
 * 
 * @param bc Colecao de negocios
 * @param top Quantos negocios por cidade
 * @return CITIES_COL CITIES COL nova
 */
CITIES_COL group_per_city_ord(GHashTable *tabela, int top)
{
    CITIES_COL new = init_cities_collection();
    CITIES_COL_AND_TOP aux = malloc(sizeof(struct citiesColAndTop));
    aux->cc = new;
    aux->top = top;

    g_hash_table_foreach(tabela, addBusToCol, aux);

    free(aux);
    return new;
}

int cc_num_of_bus(CITIES_COL cc)
{
    int total = 0;

    g_hash_table_foreach(cc->citiesTable, c_num_of_bus, &total);

    return total;
}