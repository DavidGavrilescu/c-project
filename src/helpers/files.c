char *readFile(const char *filename, long *fileSize)
{
    FILE *file = fopen(filename, "rb"); // Deschidere în mod binar

    if (file == NULL)
    {
        perror("Eroare la deschiderea fisierului");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (size == 0)
    {
        fclose(file);
        *fileSize = 0;
        return strdup(""); // returnare șir gol pentru fișier gol
    }

    char *buffer = (char *)malloc(size + 1); // +1 pentru terminatorul de șir
    if (buffer == NULL)
    {
        perror("Eroare la alocarea memoriei");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    fclose(file);

    if (bytesRead != (size_t)size)
    {
        perror("Eroare la citirea fisierului");
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0'; // terminare șir
    *fileSize = size;
    return buffer;
}

char *read_file_to_string(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Eroare! Nu se poate citi fisierul.");
        return NULL; // sau un șir gol ""
    }

    // Află dimensiunea fișierului
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alocă memorie pentru șir + terminatorul nul
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL)
    {
        fclose(file);
        perror("Eroare alocare memorie!");
        return NULL;
    }

    // Citește fișierul în buffer
    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != (size_t)file_size)
    {
        fclose(file);
        free(buffer); // Eliberează memoria în caz de eroare
        perror("Eroare la citirea fisierului!");
        return NULL;
    }

    // Adaugă terminatorul nul
    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}
