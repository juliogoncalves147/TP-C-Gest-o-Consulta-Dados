#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Reviews.h"

struct reviews
{
    char *review_id;
    char *user_id;
    char *business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char *date; //(YYYY-MM-DD HH:MM:SS)
    char *text;
};


REVIEWS r_initReviews(char *review_id, char *user_id, char *business_id, float stars, int useful, int funny, int cool, char *date, char *text)
{
    REVIEWS r = malloc(sizeof(struct reviews));
    r->review_id = strdup(review_id);
    r->user_id = strdup(user_id);
    r->business_id = strdup(business_id);
    r->stars = stars;
    r->useful = useful;
    r->funny = funny;
    r->cool = cool;
    r->date = strdup(date);
    r->text = strdup(text);
    return r;
}


REVIEWS r_initReviewsFromFileLine(char *fileline, char *fieldSeparator)
{   int key = 0;
    char *review_ID = strsep(&fileline, fieldSeparator);
    char *user_ID = strsep(&fileline, fieldSeparator);
    char *business_ID = strsep(&fileline, fieldSeparator);
    char *stars2 = strsep(&fileline, fieldSeparator);        
    char *useful2 = strsep(&fileline, fieldSeparator);
    char *funny2 = strsep(&fileline, fieldSeparator);
    char *cool2 = strsep(&fileline, fieldSeparator);
    char *date = strsep(&fileline, fieldSeparator);
    
    if (review_ID != NULL && *review_ID && user_ID != NULL && *user_ID 
        && *business_ID && business_ID != NULL && stars2 != NULL  && *stars2 
        &&  useful2 != NULL && *useful2 && funny2 != NULL && *funny2 
        &&  cool2 != NULL && *cool2 && date != NULL && *date) key = 1;
    
    if (fileline == NULL)
        return NULL;
    char *text = strsep(&fileline, "\n");

    if (key == 1){
    float stars = atof(stars2);
    int useful = atoi(useful2);
    int funny = atoi(funny2);
    int cool = atoi(cool2);

    return r_initReviews(review_ID, user_ID, business_ID,
                         stars, useful, funny, cool, date, text);
    }
    else return NULL;
}


char *r_getReview_ID(REVIEWS r)
{
    return strdup(r->review_id);
}


char *r_getUser_ID(REVIEWS r)
{
    return strdup(r->user_id);
}


char *r_getBusiness_ID(REVIEWS r)
{
    return strdup(r->business_id);
}


float r_getStars(REVIEWS r)
{
    return r->stars;
}


int r_getUseful(REVIEWS r)
{
    return r->useful;
}


int r_getFunny(REVIEWS r)
{
    return r->funny;
}


int r_getCool(REVIEWS r)
{
    return r->cool;
}


char *r_getDate(REVIEWS r)
{
    return strdup(r->date);
}


char *r_getTest(REVIEWS r)
{
    return strdup(r->text);
}


char *r_getReviewsInfo(void *x)
{
    REVIEWS r = (REVIEWS)x;
    int size = strlen(r->text) + 200;
    char info[size]; //ATENCAO ATENCAO
    sprintf(info, "Review_ID: %s | User_ID: %s | Business_ID: %s | Stars: %f | Useful: %d | Funny: %d | Cool: %d | Date: %s | Text: %s \n\n",
            r->review_id, r->user_id, r->business_id, r->stars, r->useful, r->funny, r->cool, r->date, r->text);
    return strdup(info);
}


REVIEWS r_cloneReviews(REVIEWS r)
{
    REVIEWS new_r = malloc(sizeof(struct reviews));
    new_r->review_id = strdup(r->review_id);
    new_r->user_id = strdup(r->user_id);
    new_r->business_id = strdup(r->business_id);
    new_r->stars = r->stars;
    new_r->useful = r->useful;
    new_r->funny = r->funny;
    new_r->cool = r->cool;
    new_r->date = strdup(r->date);
    new_r->text = strdup(r->text);
    return new_r;
}


void r_freeReviews(void *x)
{
    REVIEWS r = (REVIEWS)x;
    free(r->review_id);
    free(r->user_id);
    free(r->business_id);
    free(r->date);
    free(r->text);
    free(r);
}


void remove_punct_and_make_lower_case(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
        if (ispunct((unsigned char)*src))
        {
            /* Skip this character */
            src++;
        }
        else if (isupper((unsigned char)*src))
        {
            /* Make it lowercase */
            *dst++ = tolower((unsigned char)*src);
            src++;
        }
        else if (src == dst)
        {
            /* Increment both pointers without copying */
            src++;
            dst++;
        }
        else
        {
            /* Copy character */
            *dst++ = *src++;
        }
    }
    *dst = 0;
}


int r_textHasWord(REVIEWS r, char *word)
{
    int keytest = 0;
    char *review_text = r_getTest(r);
    char *aux = review_text;
    remove_punct_and_make_lower_case(review_text);
    while ((review_text) && (keytest == 0))
    {
        char *keyword = strsep(&review_text, " ");
        if (strcmp(keyword, word) == 0)
            keytest = 1;
    }
    g_free(aux);
    return keytest;
}

