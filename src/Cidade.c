#include "Cidade.h"

struct cidadeOrdenada
{
    GSList *listaBusinessID;
    char *city_name;
    int size;
    int inseridos;
    float menor;
};

struct businessAndStars
{
    char *business_id;
    float media_stars;
};

CIDADE_ORD initCidadeOrdenada(int size, char *city)
{
    CIDADE_ORD new = malloc(sizeof(struct cidadeOrdenada));

    GSList *lista = NULL;

    new->listaBusinessID = lista;
    new->city_name = strdup(city);
    new->inseridos = 0;
    new->size = size;
    new->menor = 5.0;

    return new;
}

BUS_STARS init_business_and_stars(char *id, float stars)
{
    BUS_STARS new = malloc(sizeof(struct businessAndStars));
    new->business_id = id;
    new->media_stars = stars;
    return new;
}

gint compareBusiness(gconstpointer as, gconstpointer bs)
{
    //Ordenacao de businesses pela media de estrelas
    float a = ((BUS_STARS)as)->media_stars;
    float b = ((BUS_STARS)bs)->media_stars;
    float result = b - a;
    if (result > 0)
        return 1;
    else if (result < 0)
        return -1;
    else
        return 0;
}

void insert_business_in_city(CIDADE_ORD cidade, BUSINESS bus)
{
    float stars_bus = b_getStarsMedia(bus);
    int has_space = cidade->inseridos < cidade->size;
    //So faz sentido inserir se estrelas de bus > que do menor da lista, ou se ainda nao estiver cheia
    if (stars_bus > cidade->menor || has_space)
    {
        //Inicializa estrutura auxiliar que vai ser inserida na lista
        BUS_STARS new = init_business_and_stars(b_getBusiness_Id(bus), stars_bus);
        if (has_space)
        {
            //Se ainda tiver espaco simplesmente adiciona-se de forma ordenada na lista
            cidade->listaBusinessID = g_slist_insert_sorted(cidade->listaBusinessID, new, compareBusiness);
            cidade->inseridos++;
            //Atualizar o valor do menor na lista visto que houve modificacoes na mesma
            cidade->menor = ((BUS_STARS)(g_slist_last(cidade->listaBusinessID)->data))->media_stars;
        }
        else
        {
            //Se estiver cheia primeiro insere-se
            cidade->listaBusinessID = g_slist_prepend(cidade->listaBusinessID, new);
            //Ordenase a lista (apenas um elemento fora de ordem)
            cidade->listaBusinessID = g_slist_sort(cidade->listaBusinessID, compareBusiness);
            //Trata-se de remover o ultimo da lista e darlhe free
            GSList *aux = g_slist_last(cidade->listaBusinessID);
            cidade->listaBusinessID = g_slist_remove_link(cidade->listaBusinessID, g_slist_last(cidade->listaBusinessID));
            c_free_cidade_ord((void *)aux->data);
            g_slist_free1(aux);
            //Atualizar o valor do menor na lista visto que houve modificacoes na mesma
            cidade->menor = ((BUS_STARS)(g_slist_last(cidade->listaBusinessID)->data))->media_stars;
        }
    }
}

void c_free_cidade_ord(void *b)
{ //FREE ESTRUTURA AUXILIAR DA GList DA CIDADE
    if (b)
    {
        BUS_STARS x = (BUS_STARS)b;
        free(x->business_id);
        free(x);
    }
}
void c_free_cidade(void *b)
{ //FREE DA CIDADE INTEIRA
    if (b)
    {
        CIDADE_ORD x = (CIDADE_ORD)b;
        g_slist_free_full(x->listaBusinessID, (GDestroyNotify)c_free_cidade_ord);
        free(x->city_name);
        free(x);
    }
}

void c_fill_table(CIDADE_ORD c, GPtrArray *pt, BUSINESS_C bc)
{
    GSList *result_ids = c->listaBusinessID;
    GSList *iterator = NULL;
    for (iterator = result_ids; iterator; iterator = iterator->next)
    {
        //Obtencao de dados importante como id, name e stars
        BUS_STARS b = ((BUS_STARS)iterator->data);
        char *id = (b->business_id);
        char *name = b_getName(getBusiness(bc, id));
        char stars[10];
        sprintf(stars, "%.3f", b->media_stars);
        //Criacao de string com informacao pertinente
        GString *linha1 = g_string_new(id);
        g_string_append(linha1, ";");
        g_string_append(linha1, name);
        free(name);
        g_string_append(linha1, ";");
        g_string_append(linha1, stars);
        g_string_append(linha1, ";");
        g_string_append(linha1, c->city_name);
        g_string_append(linha1, ";");
        //Add de string as linhas da table
        g_ptr_array_add(pt, (gpointer)linha1);
    }
}

void c_num_of_bus(gpointer key, gpointer value, gpointer data)
{
    //Devolve numero de negocios numa cidade para agrupar resultados em CidadeCollection
    CIDADE_ORD c = (CIDADE_ORD)value;
    int *x = ((int *)data);
    int new = g_slist_length(c->listaBusinessID);
    *x += new;
}