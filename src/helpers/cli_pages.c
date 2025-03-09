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
    char *continut;
    int isMainMenu;
} Menu;

void pauza()
{
    printf("Apasa o tasta pentru a continua...");
    getchar(); // curata bufferul de intrare
    getchar(); // asteapta apasarea unei taste
}

void curatareEcran()
{
    system(CLEAR_SCREEN);
}
int action1()
{
    curatareEcran();
    afisareClienti();
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
    "Management conturi",
    (MenuItem[]){
        {"Sterge cont", action2, NULL},
        {"Adauga cont", action2, NULL}},
    2,   "", 0};

Menu mainMenu = {
    "Meniu Principal",
    (MenuItem[]){
        {"Afisare conturi/clienti", action1, NULL},
        {"Management conturi", NULL, &submenu1,},
        {"Tranzactie noua", action1, NULL},
        {"Cautare", action2, NULL}},
    4,
        "",
        1
};



void arataHeader(Menu **menuStack, int stackTop)
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

void arataPagina(Menu *menu)
{
    // printf("%s:\n", menu->title);
    for (int i = 0; i < menu->itemCount; i++)
    {
        
        printf("%d. %s\n", i + 1, menu->items[i].text);
    }
    if(!menu->isMainMenu){
        printf("%d. Inapoi\n",menu->itemCount+1);
    }
    printf("0. Iesire\n");
    
    if (menu->continut)
    {
        printf("----------------");
        printf("%s\n", menu->continut);
    }
}