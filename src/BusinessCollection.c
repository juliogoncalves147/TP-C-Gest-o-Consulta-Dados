#include "BusinessCollection.h"

struct businessCollection
{
    GHashTable *businessTable;
};

struct listAndChar
{
    GSList *lista_IDs;
    char ch;
    char ch2;
};

struct listCityStar
{
    GSList *lista_IDs;
    char *city;
    float stars;
};

struct citiesAndCategory
{
    GSList *lista_IDs;
    int top;
    char *category;
};

BUSINESS_C initBusinessCollection()
{
    BUSINESS_C b = malloc(sizeof(struct businessCollection));
    b->businessTable = g_hash_table_new_full(g_str_hash,
                                             g_str_equal,
                                             (GDestroyNotify)g_free,
                                             (GDestroyNotify)b_freeBusiness);
    return b;
}

void filterAndAddList(gpointer key, gpointer value, gpointer data)
{
    BUSINESS b = ((BUSINESS)value);
    LIST_AND_CHAR lac = (LIST_AND_CHAR)data;

    char firstLetter = lac->ch;
    char secondLetter = lac->ch2;

    if (businessStartsWithLetter(b, firstLetter) || businessStartsWithLetter(b, secondLetter))
    {
        lac->lista_IDs = g_slist_prepend(lac->lista_IDs, strdup(key));
    }
}

GSList *filterBusinessCollectionLetterX(BUSINESS_C bcol, char c)
{
    LIST_AND_CHAR lac = malloc(sizeof(struct listAndChar));

    GSList *lista = NULL;

    lac->lista_IDs = lista;
    lac->ch = c;
    //Nao case-sensitive
    if (c >= 'A' && c <= 'Z')
    {
        lac->ch2 = c + 32;
    }
    else if (c >= 'a' && c <= 'z')
    {
        lac->ch2 = c - 32;
    }
    else
    {
        lac->ch2 = c;
    }
    //Itera hash table e adiciona a estrutura auxiliar
    g_hash_table_foreach(bcol->businessTable, filterAndAddList, lac);

    lista = lac->lista_IDs;

    free(lac);
    return lista;
}

void filterAndAddListBusiness(gpointer key, gpointer value, gpointer data)
{
    BUSINESS b = ((BUSINESS)value);
    LIST_CITY_STAR lista = (LIST_CITY_STAR)data;

    char *city = lista->city;
    float stars = lista->stars;

    if (businessHasStars(b, stars) && businessBelongCity(b, city))
    {
        lista->lista_IDs = g_slist_prepend(lista->lista_IDs, strdup(key));
    }
}

GSList *filterBusinessCollectionCityandStars(BUSINESS_C bcol, float stars, char *city)
{
    LIST_CITY_STAR lcs = malloc(sizeof(struct listCityStar));
    GSList *lista = NULL;

    lcs->lista_IDs = lista;
    lcs->city = city;
    lcs->stars = stars;
    //Itera colecao a procura de negocios e adiciona a lista final na estrutura auxiliar lcs
    g_hash_table_foreach(bcol->businessTable, filterAndAddListBusiness, lcs);

    lista = lcs->lista_IDs;
    free(lcs);
    return lista;
}

void addBusinessToCollection(BUSINESS_C bc, BUSINESS b)
{
    g_hash_table_insert(bc->businessTable, b_getBusiness_Id(b), b);
}

int businessCollectionSize(BUSINESS_C bc)
{
    return (g_hash_table_size(bc->businessTable));
}

void destroyBusinessCollection(BUSINESS_C bc)
{
    g_hash_table_destroy(bc->businessTable);
    free(bc);
}

BUSINESS getBusiness(BUSINESS_C bs, char *key)
{
    return (BUSINESS)g_hash_table_lookup(bs->businessTable, key);
}
void cloneTable(gpointer key, gpointer value, gpointer data)
{
    BUSINESS original = (BUSINESS) value;
    BUSINESS new = b_cloneBusiness(original);
    GHashTable *table = (GHashTable *) data;
    g_hash_table_insert(table, b_getBusiness_Id(new), new);
}
GHashTable *getHashTableB(BUSINESS_C bcol)
{
    GHashTable *table = g_hash_table_new_full(g_str_hash,
                                              g_str_equal,
                                              (GDestroyNotify)g_free,
                                              (GDestroyNotify)b_freeBusiness);

    g_hash_table_foreach(bcol->businessTable, cloneTable, table);

    return table;
}