/// \file
#include "Table.h"

struct table
{
    GString *header;
    GPtrArray *linhas;
    int n_linhas;
    int n_coluna;
};

struct citie_bus_col
{
    GPtrArray *linhas;
    BUSINESS_C bc;
};

TABLE init_table(GString *hd, int nl, int nc)
{
    TABLE new = malloc(sizeof(struct table));

    new->header = hd;
    new->n_linhas = nl;
    new->n_coluna = nc;
    new->linhas = g_ptr_array_new_with_free_func((GDestroyNotify)g_string_free);

    return new;
}

int filter_string(GString *linha, int coluna, char *value, op_elem operator)
{
    char *linha_char_p = (char *)linha->str;
    char *value_to_compare;
    //Divide a linha por palavras e obtem a palavra a comparar dado numero da coluna
    char **linha_dividida = g_strsplit(linha_char_p, ";", coluna);
    value_to_compare = linha_dividida[coluna - 1];
    //Comprar o valor das strings
    int comparation = g_strcmp0(g_ascii_strdown(value, -1), g_ascii_strdown(value_to_compare, -1));

    //RETORNA 1 SE FOR SUPOSTO REMOVER
    if (operator== 0)
    { //COMPARATION > 0 -> VALUE > VALUE_TO_COMPARE
        return (comparation > 0) ? 1 : 0;
    }
    else if (operator== 1)
    { //COMPARATION = 0 -> VALUE = VALUE_TO_COMPARE
        return (comparation == 0) ? 1 : 0;
    }
    else if (operator== 2)
    { //COMPARATION < 0 -> VALUE < VALUE_TO_COMPARE
        return (comparation < 0) ? 1 : 0;
    }
    else
        return 0;
}

TABLE filter_table(TABLE tab, int col, char *value, op_elem operator)
{
    int n_colunas_table = tab->n_coluna;
    //Controlo de logica de argumentos
    if (n_colunas_table < col || (col == 0))
        return tab;
    //Linha a linha decide se filtra ou nao
    for (int i = 0; i < (tab->n_linhas); i++)
    {
        GString *linha = (GString *)g_ptr_array_index(tab->linhas, i);
        GString *aux = g_string_new((char *)linha->str);
        if (filter_string(aux, col, value, operator))
        {
            //Caso seja decidido eliminar elemento removese a linha das lista de linhas
            g_ptr_array_remove_index(tab->linhas, i);
            i--;
            tab->n_linhas--;
        }
        g_string_free(aux, TRUE);
    }
    return tab;
}

GString *get_line_collums(GString *line, int col1, int col2)
{
    //Divisao da linha por palavras
    char *linha_c = strdup((char *)line->str);
    char **divisao = g_strsplit(linha_c, ";", -1);

    GString *new = g_string_new("");
    //Adiciona a linha final apenas as palavras que pertencem a dadas colunas
    for (int i = col1 - 1; divisao[i] && i < col2; i++)
    {
        g_string_append(new, divisao[i]);
        g_string_append(new, ";");
    }
    //Frees de informacao desnecessaria
    free(linha_c);
    g_strfreev(divisao);

    return new;
}

TABLE get_table_collums(TABLE tab, int col1_a, int col2_a)
{
    //Controlo de logica de colunas pedidas
    if (col2_a < col1_a)
        return tab;

    int col2 = col2_a;
    int col1 = col1_a;

    if (col2_a > tab->n_coluna)
        col2 = tab->n_coluna;

    if (col1_a < 1)
        col1 = 1;
    //Delimita header
    GString *new_header = get_line_collums(tab->header, col1, col2);

    TABLE new = init_table(new_header, 0, col2 - col1 + 1);
    //Delimita linhas
    for (int i = 0; i < tab->n_linhas; i++)
    {
        GString *linha = (GString *)g_ptr_array_index(tab->linhas, i);
        g_ptr_array_add(new->linhas, (gpointer)(get_line_collums(linha, col1, col2)));
        new->n_linhas++;
    }
    return new;
}

TABLE query_2_5_table(GSList *lista, BUSINESS_C bc, int linhas)
{
    GString *hd = g_string_new("USER ID;NAME;");
    TABLE new = init_table(hd, linhas, 2);

    GSList *iterator = NULL;

    for (iterator = lista; iterator; iterator = iterator->next)
    {
        char *b_id = (char *)(iterator->data);
        //Obtem nome do User
        char *name = b_getName(getBusiness(bc, b_id));
        GString *linha1 = g_string_new(b_id);
        g_string_append(linha1, ";");
        g_string_append(linha1, name);
        g_string_append(linha1, ";");
        g_ptr_array_add(new->linhas, (gpointer)linha1);
        g_free(name);
    }
    return new;
}

TABLE query3_table(char *info)
{
    //Prepara header
    GString *hd = g_string_new("NAME;CITY;STATE;STARS;N_REVIEWS;");
    TABLE new = init_table(hd, 1, 5);
    //Constro string e adiciona a table
    GString *linha = g_string_new(info);
    g_string_append(linha, ";");
    g_ptr_array_add(new->linhas, (gpointer)linha);
    return new;
}

TABLE query4_table(GSList *list, int linhas, BUSINESS_C bc)
{
    //Prepara header
    GString *hd = g_string_new("BUSINESS_ID;NAME;");
    TABLE new = init_table(hd, linhas, 2);

    GSList *iterator = NULL;
    //Adiciona linhas
    for (iterator = list; iterator; iterator = iterator->next)
    {
        char *b_id = (char *)(iterator->data);
        char *name = b_getName(getBusiness(bc, b_id));
        GString *linha1 = g_string_new(b_id);
        g_string_append(linha1, ";");
        g_string_append(linha1, name);
        g_string_append(linha1, ";");
        g_ptr_array_add(new->linhas, (gpointer)linha1);
        g_free(name);
    }
    return new;
}

void cbcol_destroy(C_B_COL cbcol)
{
    g_free(cbcol);
}

void iterate_citie_coll(gpointer key, gpointer value, gpointer data)
{
    CIDADE_ORD c = (CIDADE_ORD)value;
    C_B_COL pt = (C_B_COL)data;
    c_fill_table(c, pt->linhas, pt->bc);
}

TABLE query6_table(CITIES_COL ccol, BUSINESS_C bcol)
{
    //Prepara header
    GString *hd = g_string_new("ID;NAME;STARS;CITY;");
    int line_number = cc_num_of_bus(ccol);
    TABLE new = init_table(hd, line_number, 4);

    C_B_COL cbcol = malloc(sizeof(struct citie_bus_col));
    cbcol->bc = bcol;
    cbcol->linhas = new->linhas;
    //Itera colecao de cidades e preenche estutura auxiliar C_B_COL
    g_hash_table_foreach(c_getTable(ccol), iterate_citie_coll, cbcol);
    //Destroi informacao desnecessaria
    cbcol_destroy(cbcol);

    return new;
}

TABLE query7_table(GSList *lista_u)
{
    int number_of_users = g_slist_length(lista_u);
    char number_of_users_s[10];
    sprintf(number_of_users_s, "%d", number_of_users);

    //Prepara header
    GString *hd = g_string_new("ID;");
    TABLE new = init_table(hd, number_of_users + 1, 1);

    GSList *iterator = NULL;
    //Adiciona linhas
    for (iterator = lista_u; iterator; iterator = iterator->next)
    {
        char *u_id = (char *)(iterator->data);
        GString *linha1 = g_string_new(u_id);
        g_string_append(linha1, ";");
        g_ptr_array_add(new->linhas, (gpointer)linha1);
    }
    //Informacao de numero de users Internacionais adicionada Table
    GString *n_users = g_string_new("Numero de users internacionais: ");
    g_string_append(n_users, number_of_users_s);
    g_string_append(n_users, ";");
    g_ptr_array_add(new->linhas, (gpointer)n_users);

    return new;
}

TABLE query8_table(GSList *lista_b, BUSINESS_C bc)
{
    //Prepara header
    GString *hd = g_string_new("ID;NAME;STARS;");
    int line_number = g_slist_length(lista_b);
    TABLE new = init_table(hd, line_number, 3);

    GSList *iterator = NULL;

    for (iterator = lista_b; iterator; iterator = iterator->next)
    {
        //Campos da tabela como id  e stars
        char *b_id = get_id_busstars_aux((STRUCTBUSSTARS)(iterator->data));
        float stars = get_media_stars_busstars_aux((STRUCTBUSSTARS)(iterator->data));
        BUSINESS aux = getBusiness(bc, b_id);

        if (aux != NULL)
        {
            //Nome do negocio
            char *name_s = b_getName(aux);
            //Float stars to string
            char stars_s[10];
            sprintf(stars_s, "%.3f", stars);
            //Constroi linha
            GString *linha1 = g_string_new(b_id); //ID
            g_string_append(linha1, ";");
            g_string_append(linha1, name_s); //NAME
            g_string_append(linha1, ";");
            g_string_append(linha1, stars_s); //STARS
            g_string_append(linha1, ";");
            g_ptr_array_add(new->linhas, (gpointer)linha1);

            free(name_s);
        }
        free(b_id);
    }
    return new;
}

TABLE query9_table(GSList *lista)
{
    GString *hd = g_string_new("ID;");
    int line_number = g_slist_length(lista);
    TABLE new = init_table(hd, line_number, 1);

    GSList *iterator = NULL;

    for (iterator = lista; iterator; iterator = iterator->next)
    {
        char *r_id = (char *)(iterator->data);
        GString *linha1 = g_string_new(r_id);
        g_string_append(linha1, ";");
        g_ptr_array_add(new->linhas, (gpointer)linha1);
    }

    return new;
}

void print_table_aux(gpointer data, gpointer user_data)
{
    GString *new = (GString *)data;
    printf("%s\n", (char *)new->str);
}
void print_table(TABLE t)
{
    printf("%s\n", (char *)t->header->str);
    g_ptr_array_foreach(t->linhas, print_table_aux, NULL);
}

void table_destroy(TABLE t, int true)
{
    g_string_free(t->header, TRUE);
    if (true)
        g_ptr_array_free(t->linhas, TRUE);
    else
        g_ptr_array_free(t->linhas, FALSE);
    free(t);
}

void table_destroy2(void *x)
{
    TABLE t = (TABLE)x;
    g_string_free(t->header, TRUE);
    g_ptr_array_free(t->linhas, TRUE);

    free(t);
}

TABLE index_table(TABLE t, int coluna, int linha)
{
    //Verifica se celula existe na tabela
    if (!(coluna > 0 && linha > 0 && coluna <= t->n_coluna && linha <= t->n_linhas))
    {
        printf("ERROR");
        return t;
    }
    //Prepara novo header
    GString *new_hd = get_line_collums(t->header, coluna, coluna);
    TABLE new = init_table(new_hd, 1, 1);
    //Prepara nova linha
    GString *line = (GString *)g_ptr_array_index(t->linhas, linha - 1);
    g_ptr_array_add(new->linhas, get_line_collums(line, coluna, coluna));
    return new;
}

char *g_string_to_string(GString *frase, char delim)
{
    char *new_frase = strdup(frase->str);
    g_strdelimit(new_frase, ";", delim);
    return new_frase;
}

int table_to_csv(TABLE tabela, char delim, char *file_path)
{
    FILE *fp = fopen(file_path, "w");

    if (fp == NULL)
    {
        printf("error: unable to open file\n");
        return 1;
    }
    char *new_header = g_string_to_string(tabela->header, delim);
    fprintf(fp, "%s\n", new_header);
    free(new_header);

    for (int i = 0; i < tabela->n_linhas; i++)
    {
        char *new_linha = g_string_to_string((GString *)g_ptr_array_index(tabela->linhas, i), delim);
        fprintf(fp, "%s\n", new_linha);
        free(new_linha);
    }
    fclose(fp);
    return 0;
}

TABLE csv_to_table(char *file_path, char delim)
{
    //Abre ficheiro e prepara buffers
    FILE *fp = fopen(file_path, "r");
    char *buf = malloc(256);
    size_t size = 256;
    char *delims = g_strnfill(1, delim);
    int colunas = 0;

    if (fp == NULL)
    {
        printf("error: unable to open file\n");
        return NULL;
    }
    //Carrega header
    if (getline(&buf, &size, fp) < 0)
        return NULL;
    char *aux_hd = strdup(buf);
    g_strdelimit(aux_hd, delims, ';');
    GString *new_hd = g_string_new(aux_hd);

    for (int j = 0; aux_hd[j]; j++)
    {
        if (';' == aux_hd[j])
        {
            colunas++;
        }
    }
    free(aux_hd);
    //Inicia a table ja com o header
    TABLE new = init_table(new_hd, 0, colunas);
    //Carrega linhas do ficheiro para a table
    while ((getline(&buf, &size, fp)) > 0)
    {
        char *aux_line = strdup(buf);
        g_strdelimit(aux_line, delims, ';');
        GString *new_line = g_string_new(aux_line);
        new->n_linhas++;
        g_ptr_array_add(new->linhas, (gpointer)new_line);
        free(aux_line);
    }
    return new;
}

int *sizes_per_collum(char *linha, int colunas)
{
    //Divide linha numa lista de palavras
    char **aux = g_strsplit(linha, ";", -1);
    int *resultado = malloc(sizeof(int) * colunas);
    //Guarda comprimento das palavras numa lista para ser devolvida
    for (int i = 0; i < colunas; i++)
        resultado[i] = (int)strlen(aux[i]);

    g_strfreev(aux);
    return resultado;
}

int *biggest_sizes_per_collum(TABLE t)
{
    int numero_colunas = t->n_coluna;

    int *resultado = malloc(sizeof(int) * numero_colunas);
    //Inicializa a 0
    for (int i = 0; i < numero_colunas; i++)
        resultado[i] = 0;
    //Preenche lista
    for (int i = 0; i < t->n_linhas; i++)
    {
        char *linha = strdup(((GString *)g_ptr_array_index(t->linhas, i))->str);
        int *aux = sizes_per_collum(linha, numero_colunas);
        free(linha);
        for (int j = 0; j < numero_colunas; j++)
        {
            //Se linha a ser analisada tiver algum campo maior atualiza-se resultado
            if (aux[j] > resultado[j])
                resultado[j] = aux[j];
        }
        g_free(aux);
    }
    return resultado;
}

char *show_line(char **matriz, int *sizess, int colunas)
{
    GString *frase = g_string_sized_new(120);
    for (int i = 0; i < colunas; i++)
    {
        //Obtem comprimento da palavra em coluna 'i'
        int word_length = g_utf8_strlen(matriz[i], 80);
        //Da um pouco de espaco para palavra nao ficar encostada a coluna
        int biggest_space = sizess[i] + 2;
        //Calcula numero de espaços para alinhar a palavra no centro da coluna
        int padlen = (biggest_space - word_length) / 2;
        //Ajusta a palavra dependendo do seu comprimento e do numero de casas na coluna
        if (i == 0)
            g_string_append(frase, "|");
        if ((biggest_space % 2 == 0) && (word_length % 2 == 1))
        {
            g_string_append_printf(frase, "%*s%s%*s|", padlen + 1, "", matriz[i], padlen, "");
        }
        else if ((biggest_space % 2 == 1) && (word_length % 2 == 0))
        {
            g_string_append_printf(frase, "%*s%s%*s|", padlen, "", matriz[i], padlen + 1, "");
        }
        else
        {
            g_string_append_printf(frase, "%*s%s%*s|", padlen, "", matriz[i], padlen, "");
        }
    }
    g_string_append(frase, "\n");
    return strdup(frase->str);
}

void show_table(TABLE tabela, int linha)
{
    //Obtem maior palavra em cada coluna para conseguir alinhar
    int *tamanhos_por_coluna = biggest_sizes_per_collum(tabela);
    //Imprime Header
    char **header_m = g_strsplit((tabela->header)->str, ";", -1);
    char *frase = show_line(header_m, tamanhos_por_coluna, tabela->n_coluna);
    printf(" LINHA %s", frase);
    free(frase);
    //Imprime linhas
    for (int i = linha; i < linha + 25 && i < tabela->n_linhas; i++)
    {
        char *linha = (((GString *)g_ptr_array_index(tabela->linhas, i))->str);
        char **frase_m = g_strsplit(linha, ";", -1);
        char *new_line = show_line(frase_m, tamanhos_por_coluna, tabela->n_coluna);
        //Imprime linha
        printf("%7d%s", i + 1, new_line);
        free(new_line);
    }
    g_free(tamanhos_por_coluna);
}

int getTable_lines_lenght(TABLE tabela)
{
    return tabela->n_linhas;
}
