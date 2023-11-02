#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_TEXT_LENGTH 1024



/*
Sletter indeholde af den givet fil
Input: pointer til filstruktur
Output:
	0: den har ikke adgang til at slette
	1: filen er allerede slettede eller eksisterer ikke
	2: alt vel
*/
void deleteFile(char *filename){
    if (remove(filename) == 0) {
        printf("%s fil slettet:\n", filename);
    } else {
        perror("Kunne ikke slette filen");
    }
}

/*
Viser filen
Input: pointer til filstruktur
Output:
	0: filen eksisterer ikke
	1: af en eller anden grund kunne filen ikke blive vist
	2: alt vel
*/
void displayFileContents(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Kunne ikke aabne filen '%s'\n", filename);
        return;
    }

    char line[MAX_TEXT_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}


/*
Lader dig redigere i filen med det givet navn
Input: pointer til filstruktur
Output:
	0: filen eksisterer ikke
	1: af en eller anden grund kunne filen ikke redigeres
	2: alt vel
*/
void editFileContents(char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Kunne ikke aabne filen '%s'\n", filename);
        return;
    }

    char newContents[MAX_TEXT_LENGTH];
    printf("Indtast den nye tekst (afslut med Ctrl+D i Unix eller Ctrl+Z i Windows):\n");

    while (fgets(newContents, sizeof(newContents), stdin) != NULL) {
        size_t len = strlen(newContents);
        if (len > 0 && newContents[len - 1] == '\n') {
            newContents[len - 1] = '\0';
        }
        fprintf(file, "%s\n", newContents);
    }

    fclose(file);
}



/*
Opretter en fil
Input: pointer til filstruktur
Output:
	0: filen eksisterer allerede
	1: af en eller anden grund kunne filen ikke oprettes
	2: alt vel
*/
int createNewFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        printf("Filen eksisterer allerede\n");
        fclose(file);
        return 0; //ud af createFile
     }
    else {
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Kunne ikke oprette filen '%s'\n", filename);
            return 1; //ud af createFile
        }
        fclose(file);
    }
    editFileContents(filename);
    return 2;
}


/*
vælger mellem de forskellige cases og tag den du vælger og køre koden der passer til casen
input: case 1-5
output:
        0: case eksisterer ikke
        1: af en eller anden grund kunne casen ikke blive valgt
        2: alt vel
*/
int main() {

/*
giver teksten en farve
*/
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);



    char filename[MAX_FILENAME_LENGTH];
    printf("Indtast filnavn at arbejde paa\n");
    scanf("%s", filename);

    int choice;

    while (1){
        printf("\nMenu:\n");
        printf("1. Vis fil\n");
        printf("2. Rediger fil\n");
        printf("3. Opret fil\n");
        printf("4. Afslut\n");
        printf("5. Slet fil\n");
        printf("Valg: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayFileContents(filename);
                break;
            case 2:
                editFileContents(filename);
                break;
            case 3:
                createNewFile(filename);
                break;
            case 4:
                printf("Afslutter...\n");
                return 0;  //ud af main()
            case 5:
                deleteFile(filename);
                break;
            default:
                printf("Ugyldigt valg. Proev igen.\n");
        }
    }
}
