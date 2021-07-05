#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Ler.h"

void r_read_file(char *file, REVIEWS_C rc, BUSINESS_C bc, USERS_C uc)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("error: unable to open file\n");
        return;
    }

    char buff[512];

    size_t len = sizeof(buff);
    char *line = malloc(len);
    if (line == NULL)
    {
        printf("error: unable to allocate memory\n");
        return;
    }
    if (fgets(buff, sizeof(buff), fp) == NULL)
        return;
    line[0] = '\0';

    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        //Realoca espaço se necessario
        if (len - strlen(line) < sizeof(buff))
        {
            len *= 2;
            if ((line = realloc(line, len)) == NULL)
            {
                printf("error: unable to reallocate memory\n");
                free(line);
                return;
            }
        }
        //Append buffer
        strcat(line, buff);
        //Se linha contem '\n' aplica alguma funçao
        if (line[strlen(line) - 1] == '\n')
        {
            //  printf("%s\n",line);
            REVIEWS new = r_initReviewsFromFileLine(line, ";");
            if (new)
            {
                char *bid = r_getBusiness_ID(new);
                char *uid = r_getUser_ID(new);
                BUSINESS b = getBusiness(bc, bid);
                USERS u = getUsers(uc, uid);

                if (b != NULL && u != NULL)
                {
                    b_updateStatus(b, r_getStars(new));
                    u_updateStatus(u, bid);
                    addReviewToCollection(rc, new);
                }
                else
                {
                    r_freeReviews(new);
                    free(bid);
                }

                free(uid);
            }
            line[0] = '\0';
        }
    }
    printf("--| Ficheiro Reviews Done!\n");
    fclose(fp);
    free(line);
}

void b_read_file(char *file, BUSINESS_C bc)
{
    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        printf("error: unable to open file\n");
        return;
    }

    char buff[1024];

    size_t len = sizeof(buff);
    char *line = malloc(len);
    if (line == NULL)
    {
        printf("error: unable to allocate memory\n");
        return;
    }
    if (fgets(buff, sizeof(buff), fp) == NULL)
        return;
    line[0] = '\0';

    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        //Realoca espaço se necessario
        if (len - strlen(line) < sizeof(buff))
        {
            len *= 2;
            if ((line = realloc(line, len)) == NULL)
            {
                printf("error: unable to reallocate memory\n");
                free(line);
                return;
            }
        }
        //Append buffer
        strcat(line, buff);
        //Se linha contem '\n' aplica alguma funçao
        if (line[strlen(line) - 1] == '\n')
        {
            //    printf("%s\n",line);
            BUSINESS new = b_initBusinessFromFileLine(line, ";");
            if (new)
                addBusinessToCollection(bc, new);
            line[0] = '\0';
        }
    }
    printf("--| Ficheiro Businesses Done!\n");
    fclose(fp);
    free(line);
}

void u_read_file(char *file, USERS_C uc)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("error: unable to open file\n");
        return;
    }

    char buff[16384];

    size_t len = sizeof(buff);
    char *line = malloc(len);
    if (line == NULL)
    {
        printf("error: unable to allocate memory\n");
        return;
    }
    if (fgets(buff, sizeof(buff), fp) == NULL)
        return;
    line[0] = '\0';

    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        //Realoca espaço se necessario
        if (len - strlen(line) < sizeof(buff))
        {
            len *= 2;
            if ((line = realloc(line, len)) == NULL)
            {
                printf("error: unable to reallocate memory\n");
                free(line);
                return;
            }
        }
        //Append buffer
        strcat(line, buff);
        //Se linha contem '\n' aplica alguma funçao
        if (line[strlen(line) - 1] == '\n')
        {
            //printf("%s\n", line);
            USERS new = u_initUserFromFileLine(line, ";");
            if (new)
                addUsersToCollection(uc, new);
            line[0] = '\0';
        }
    }
    printf("--| Ficheiro Users Done!\n");
    fclose(fp);
    free(line);
}