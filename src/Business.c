#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Business.h"


struct business
{
    char *business_id;
    char *name;
    char *city;
    char *state;
    char *categories;
    float totalStars;
    int numReviews;
};

BUSINESS b_initBusiness(char *business_id, char *name, char *city, char *state, char *categories)
{
    BUSINESS x = malloc(sizeof(struct business));
    x->business_id = strdup(business_id);
    x->name = strdup(name);
    x->city = strdup(city);
    x->state = strdup(state);
    x->categories = strdup(categories);
    x->totalStars = 0;
    x->numReviews = 0;
    return x;
}


BUSINESS b_initBusinessFromFileLine(char *fileline, char *fieldSeparator)
{
    int key = 0;
    char *business_id = strsep(&fileline, fieldSeparator);
    char *name = strsep(&fileline, fieldSeparator);
    char *city = strsep(&fileline, fieldSeparator);
    char *state = strsep(&fileline, fieldSeparator);
    if (fileline == NULL)
        return NULL;
    char *categories = strsep(&fileline, fieldSeparator);

    if (*business_id && business_id != NULL &&
        *name && name != NULL &&
        *city && city != NULL &&
        *state && state != NULL &&
        *state && state != NULL)
        key = 1;

    if (key == 1)
        return b_initBusiness(business_id, name, city, state, categories);
    else
        return NULL;
}


int b_getStars(BUSINESS x)
{
    return x->totalStars;
}


int b_getnumReviews(BUSINESS x)
{
    return x->numReviews;
}


char *b_getBusiness_Id(BUSINESS x)
{
    return strdup(x->business_id);
}


char *b_getName(BUSINESS x)
{
    return strdup(x->name);
}


char *b_getCity(BUSINESS x)
{
    return strdup(x->city);
}


char *b_getState(BUSINESS x)
{
    return strdup(x->state);
}


char *b_getCategories(BUSINESS x)
{
    return strdup(x->categories);
}


float b_getStarsMedia(BUSINESS x)
{
    if (x->numReviews == 0 || x->totalStars == 0)
        return 0.0;
    else
        return (x->totalStars / x->numReviews);
}


char *b_getBusinessInfo(void *b)
{
    BUSINESS x = (BUSINESS)b;
    char info[7000]; // ter atençao a isto
    sprintf(info, "Business ID: %s | Name: %s | City: %s | State: %s | Categories: %s | Stars: %f | Nº Reviews: %d\n",
            x->business_id,
            x->name,
            x->city,
            x->state,
            x->categories,
            b_getStarsMedia(x),
            x->numReviews);

    return strdup(info);
}


char *b_getBusinessInfoQ3(BUSINESS b)
{
    //USAR C SIMPLES | ESTA MUITO LENTO
    GString *aux = g_string_new("");
    g_string_append(aux, b->name);
    g_string_append(aux, ";");
    g_string_append(aux, b->city);
    g_string_append(aux, ";");
    g_string_append(aux, b->state);
    g_string_append(aux, ";");
    char stars[10];
    sprintf(stars, "%.3f;", b_getStarsMedia(b));
    g_string_append(aux, stars);
    char n_reviews[10];
    sprintf(n_reviews, "%d", b->numReviews);
    g_string_append(aux, n_reviews);

    return (char *)aux->str;
}


BUSINESS b_cloneBusiness(BUSINESS x)
{
    BUSINESS new = malloc(sizeof(struct business));
    new->business_id = strdup(x->business_id);
    new->name = strdup(x->name);
    new->city = strdup(x->city);
    new->state = strdup(x->state);
    new->categories = strdup(x->categories);
    new->numReviews = x->numReviews;
    new->totalStars = x->totalStars;
    return new;
}


void b_freeBusiness(void *b)
{
    BUSINESS x = (BUSINESS)b;
    free(x->business_id);
    free(x->name);
    free(x->city);
    free(x->state);
    free(x->categories);
    free(x);
}


int businessStartsWithLetter(BUSINESS b, char c)
{
    return (b->name[0] == c);
}


void b_updateStatus(BUSINESS c, float stars)
{
    c->numReviews++;
    c->totalStars += stars;
}


int businessBelongCity(BUSINESS b, char *city)
{
    return (strcmp(b->city, city) == 0);
}


int businessHasStars(BUSINESS b, float stars)
{
    //if(b->numReviews == 0) return 0;
    return ((b->totalStars / b->numReviews) >= stars);
}

int business_has_categorie(BUSINESS b, char *needle)
{
    int found = 0;
    char *categories = b_getCategories(b);
    char *aux = categories;
    while (categories && !found)
    {
        char *buf = strsep(&categories, ",");
        if (strcmp(buf, needle) == 0)
            found = 1;
    }
    free(aux);
    return found;
}