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

    while (1) // se opreste cand ruleaza pauza() pentru ca asteapta input de la user
    {
        system(CLEAR_SCREEN);
        arataHeader(menuStack, stackTop);
        arataPagina(currentMenu);

        scanf("%d", &choice);

        // 0 inseamna ca iesim din program
        if (choice == 0)
        {
            curatareEcran();
            goto exit; // nu e necesar goto, dar am vrut sa il folosesc
        }
        else if (choice > 0 && choice <= currentMenu->itemCount)
        {
            MenuItem selectedItem = currentMenu->items[choice - 1];

            if (selectedItem.submenu != NULL) // daca avem submeniu, acesta devine meniul curent
            {
                menuStack[++stackTop] = selectedItem.submenu;
                currentMenu = selectedItem.submenu;
            }

            else if (selectedItem.action != NULL) // daca avem actiune, o rulam
            {
                selectedItem.action();
            }

            else // altfel, mergem la meniul anterior din stiva
            {
                currentMenu = menuStack[--stackTop];
            }
        }
        /* daca alegerea userului este cu 1 mai mare decat nr de optiuni din meniu
           mergem inapoi (aceasta optiune este afisata in functia arataPagina) */
        else if (choice == currentMenu->itemCount + 1)
        {
            currentMenu = menuStack[--stackTop];
        }
        else
        {
            printf("Optiune invalida...\n");
            pauza();
        }
    }

exit:
    return 0;
}
