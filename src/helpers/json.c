char *generateClientsList(cJSON *json)
{
    cJSON *clienti = cJSON_GetObjectItemCaseSensitive(json, "clienti");
    if (!cJSON_IsArray(clienti))
    {
        fprintf(stderr, "Eroare: 'clienti' nu este un array.\n");
        return NULL;
    }

    char *lista = NULL;
    size_t lista_size = 0;
    cJSON *client;

    // Adauga antetul tabelului
    char antet[] = "Nr. Cont | Nume          | Prenume       | Cont curent\n"
                   "---------|---------------|---------------|-------------\n";
    size_t antet_len = strlen(antet);
    lista = (char *)malloc(antet_len + 1);
    if (lista == NULL)
    {
        fprintf(stderr, "Eroare la alocarea memoriei.\n");
        return NULL;
    }
    strcpy(lista, antet);
    lista_size = antet_len;

    cJSON_ArrayForEach(client, clienti)
    {
        cJSON *nume = cJSON_GetObjectItemCaseSensitive(client, "nume");
        cJSON *prenume = cJSON_GetObjectItemCaseSensitive(client, "prenume");
        cJSON *numar_cont = cJSON_GetObjectItemCaseSensitive(client, "numarCont");
        cJSON *cont_curent = cJSON_GetObjectItemCaseSensitive(client, "contCurent");

        if (cJSON_IsString(nume) && cJSON_IsString(prenume) && cJSON_IsNumber(numar_cont) && cJSON_IsNumber(cont_curent))
        {
            char buffer[256];
            int len = snprintf(buffer, sizeof(buffer), "%-9d| %-14s| %-14s| %-13.2f\n",
            numar_cont->valueint, nume->valuestring, prenume->valuestring, cont_curent->valuedouble);

            if (len < 0)
            {
                fprintf(stderr, "Eroare la formatarea șirului.\n");
                free(lista);
                return NULL;
            }

            char *new_lista = (char *)realloc(lista, lista_size + len + 1);
            if (new_lista == NULL)
            {
                fprintf(stderr, "Eroare la alocarea memoriei.\n");
                free(lista);
                return NULL;
            }
            lista = new_lista;

            strcpy(lista + lista_size, buffer);
            lista_size += len;
        }
        else
        {
            fprintf(stderr, "Eroare: Tipuri de date incorecte pentru client.\n");
            free(lista);
            return NULL;
        }
    }

    return lista;
}

int afisareClienti()
{
    char *clienti = read_file_to_string("data/clienti.json");
    if (clienti != NULL)
    {
        cJSON *json = cJSON_Parse(clienti);
        printf("%s", generateClientsList(json));
        free(clienti);
    }
    return 0;
}