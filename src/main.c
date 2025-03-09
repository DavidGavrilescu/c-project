#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "helpers/files.c"
#include "helpers/json.c"
#include "helpers/cli_pages.c"

int main()
{
    Menu *currentMenu = &mainMenu;
    Menu *menuStack[10];
    menuStack[0] = &mainMenu;
    int stackTop = 0;
    int choice;
    Menu *meniulAnterior;
    while (1)
    {
        system(CLEAR_SCREEN);
        arataHeader(menuStack, stackTop);
        arataPagina(currentMenu); // Afisează pagina curenta

        scanf("%d", &choice);

        if (choice == 0)
        {
            curatareEcran();
            goto exit;
        }
        else if (choice > 0 && choice <= currentMenu->itemCount)
        {
            MenuItem selectedItem = currentMenu->items[choice - 1];

            if (selectedItem.submenu != NULL)
            {
                menuStack[++stackTop] = selectedItem.submenu;
                currentMenu = selectedItem.submenu;
            }
            else if (selectedItem.action != NULL)
            {
                selectedItem.action();
            }
            else
            {
                currentMenu = menuStack[--stackTop];
            }
        }
        else if (choice == currentMenu->itemCount + 1)
        {
            currentMenu = menuStack[--stackTop];
        }
        else
        {
            printf("Optiune invalida\n");
            char userInput[100];
            printf("Introduceti textul: ");
            pauza();
        }
    }

exit:
    return 0;
}
