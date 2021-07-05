#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sgr.h"

struct sgrSt
{
    USERS_C users;
    BUSINESS_C bus;
    REVIEWS_C revs;
};

SGR init_sgr()
{
    SGR sgrMain = malloc(sizeof(struct sgrSt));
    sgrMain->revs = initReviewsCollection();
    sgrMain->bus = initBusinessCollection();
    sgrMain->users = initUsersCollection();

    return sgrMain;
}

void free_sgr(SGR sgr)
{
    destroyReviewsCollection(sgr->revs);
    destroyBusinessCollection(sgr->bus);
    destroyUsersCollection(sgr->users);
    free(sgr);
}
/* query 1 */
SGR load_sgr(char *users, char *businesses, char *reviews)
{
    SGR new = init_sgr();
    u_read_file(users, new->users);
    b_read_file(businesses, new->bus);
    r_read_file(reviews, new->revs, new->bus, new->users);

    return new;
}

/* query 2 */
TABLE businesses_started_by_letter(SGR sgr, char letter)
{
    GSList *result_ids = filterBusinessCollectionLetterX(sgr->bus, letter);
    TABLE new = query_2_5_table(result_ids, sgr->bus, (int)g_slist_length(result_ids));

    g_slist_free_full(result_ids, (GDestroyNotify)g_free);

    return new;
}

/* query 3 */
TABLE business_info(SGR sgr, char *business_id)
{
    BUSINESS b = getBusiness(sgr->bus, business_id);
    if (b == NULL)
    {
        GString *hd = g_string_new("NAME;CITY;STATE;STARS;N_REVIEWS;");
        TABLE new_error = init_table(hd, 0, 5);
        return new_error;
    }

    char *info = b_getBusinessInfoQ3(b);

    TABLE new = query3_table(info);

    free(info);

    return new;
}
/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id)
{
    USERS u = getUsers(sgr->users, user_id);
    if (u == NULL)
    {
        GString *hd = g_string_new("BUSINESS_ID;NAME;");
        TABLE new_error = init_table(hd, 0, 2);
        return new_error;
    }
    GSList *br = u_getListReviews(u);
    TABLE new = query4_table(br, (int)g_slist_length(br), sgr->bus);

    return new;
}
/* query 5 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city)
{
    GSList *result_ids = filterBusinessCollectionCityandStars(sgr->bus, stars, city);

    TABLE new = query_2_5_table(result_ids, sgr->bus, (int)g_slist_length(result_ids));

    g_slist_free_full(result_ids, g_free);

    return new;
}
/* query 6 */
TABLE top_businesses_by_city(SGR sgr, int top)
{
    GHashTable *aux = getHashTableB(sgr->bus);
    CITIES_COL new = group_per_city_ord(aux, top);
    TABLE t = query6_table(new, sgr->bus);
    destroyCitiesCollection(new);
    g_hash_table_destroy(aux);

    return t;
}
/* query 7 */ // Corona fez
TABLE international_users(SGR sgr)
{
    GSList *result_ids = u_filterStatesVisiter(sgr->users, sgr->bus);

    TABLE t = query7_table(result_ids);

    g_slist_free_full(result_ids, (GDestroyNotify)g_free);

    return t;
}
/* query 8 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category)
{
    GHashTable *aux = getHashTableB(sgr->bus);

    GSList *result_ids = business_with_category(aux, top, category);

    TABLE new = query8_table(result_ids, sgr->bus);

    g_hash_table_destroy(aux);

    g_slist_free_full(result_ids, (GDestroyNotify)free_busstars_aux);

    return new;
}
/* query 9 */
TABLE reviews_with_word(SGR sgr, char *word)
{
    GSList *result_ids = get_reviews_with_n_word(sgr->revs, word);

    TABLE t = query9_table(result_ids);

    g_slist_free_full(result_ids, (GDestroyNotify)g_free);

    return t;
}