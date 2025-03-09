#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Definirea macro-ului pentru a sterge ecranul in functie de sistemul de operare
#ifdef _WIN32
#define CLEAR_SCREEN "cls" // pentru windows
#else
#define CLEAR_SCREEN "clear" // pentru celelalte sisteme de operare
#endif

typedef struct
{
    char *text;
    int (*action)(void);
    struct Menu *submenu;
} MenuItem;

typedef struct Menu
{
    char *title;
    MenuItem *items;
    int itemCount;
    char *footer;
} Menu;

void pauza()
{
    printf("Apasa o tasta pentru a continua...");
    getchar(); // curata bufferul de intrare
    getchar(); // asteapta apasarea unei taste
}

int action1()
{
    printf("facem tranzactie? ok... \n");
    pauza();
    return 0;
}

int action2()
{
    printf("Actiunea 2 executata\n");
    getchar();
    getchar();
    return 0;
}

Menu submenu1 = {
    "Afisare conturi/clienti",
    (MenuItem[]){
        {"Inapoi", NULL, NULL}},
    1};

Menu mainMenu = {
    "Meniu Principal",
    (MenuItem[]){
        {"Afisare conturi/clienti", NULL, &submenu1},
        {"Management conturi", NULL, &submenu1},
        {"Tranzactie noua", action1, NULL},
        {"Cautare", action2, NULL},
        {"Iesire", NULL, NULL}},
    3};

void displayHeader(Menu **menuStack, int stackTop)
{
    printf("==============================================================================\n");
    printf("Cale: ");
    for (int i = 0; i <= stackTop; i++)
    {
        printf("%s ", menuStack[i]->title);
        if (i < stackTop)
        {
            printf("-> ");
        }
    }
    printf("\n==============================================================================\n");
}
// Funcție pentru afișarea unei pagini de meniu
void displayPage(Menu *menu)
{
    // printf("%s:\n", menu->title);
    for (int i = 0; i < menu->itemCount; i++)
    {
        printf("%d. %s\n", i + 1, menu->items[i].text);
    }
    printf("0. Iesire\n");
}
char* readFile(const char *filename, long *fileSize) {
    FILE *file = fopen(filename, "rb"); // Deschidere în mod binar

    if (file == NULL) {
        perror("Eroare la deschiderea fisierului");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (size == 0) {
        fclose(file);
        *fileSize = 0;
        return strdup(""); // Returnare șir gol pentru fișier gol
    }

    char *buffer = (char*)malloc(size + 1); // +1 pentru terminatorul de șir
    if (buffer == NULL) {
        perror("Eroare la alocarea memoriei");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    fclose(file);

    if (bytesRead != (size_t)size) {
        perror("Eroare la citirea fisierului");
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0'; // Terminare șir
    *fileSize = size;
    return buffer;
}

int main()
{
    Menu *currentMenu = &mainMenu;
    Menu *menuStack[10];
    menuStack[0] = &mainMenu;
    int stackTop = 0;
    int choice;
    int frame = 0;
    long size;
    char *content = readFile("data/clienti.json", &size);

    if (content != NULL) {
        printf("Dimensiune fisier: %ld bytes\n", size);
        // printf("Continut:\n%s\n", content);

        cJSON *json = cJSON_Parse(content);

        if (json == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            if (error_ptr != NULL) {
                fprintf(stderr, "Eroare la parsarea JSON: %s\n", error_ptr);
            }
            cJSON_Delete(json);
            return 1;
        }

        cJSON *items = cJSON_GetObjectItem(json, "clienti");

        if (cJSON_IsArray(items)) {
            int array_size = cJSON_GetArraySize(items);
    
            printf("Array size: %d\n", array_size);
    
            for (int i = 0; i < array_size; i++) {
                cJSON *item = cJSON_GetArrayItem(items, i);
    
                // if (cJSON_IsString(item)) {
                    printf("Item %d: %s\n", i, item->valuestring);
                // }
            }
        }

        cJSON_Delete(json);

        free(content);
    }

    // while (1)
    // {
    //     printf("Frame: %d\n", frame++);
    //     system(CLEAR_SCREEN);
    //     displayHeader(menuStack, stackTop);
    //     displayPage(currentMenu); // Afișează pagina curentă

    //     scanf("%d", &choice);

    //     if (choice == 0)
    //     {
    //         if (stackTop == 0)
    //         {
    //             break;
    //         }
    //         else
    //         {
    //             currentMenu = menuStack[--stackTop];
    //         }
    //     }
    //     else if (choice > 0 && choice <= currentMenu->itemCount)
    //     {
    //         MenuItem selectedItem = currentMenu->items[choice - 1];

    //         if (selectedItem.submenu != NULL)
    //         {
    //             menuStack[++stackTop] = selectedItem.submenu;
    //             currentMenu = selectedItem.submenu;
    //         }
    //         else if (selectedItem.action != NULL)
    //         {
    //             selectedItem.action();
    //         }
    //         else
    //         {
    //             currentMenu = menuStack[--stackTop];
    //         }
    //     }
    //     else
    //     {
    //         printf("Optiune invalida\n");
    //         char userInput[100];
    //         printf("Introduceti textul: ");
    //         getchar();
    //         getchar();
    //     }
    // }

    return 0;
}

// #include <stdio.h>

// int main(int argc, const char * argv[]) {

//     printf("Numar argumente: %d\n", argc);

//     if(argc > 1) {
//         for(int i = 0; i < argc; i++) {
//             printf("Argumentul %d este: %s\n", i, argv[i]);
//         }
//     }
//     return 0;
// }
