<<<<<<< HEAD
#include "includes.h" //? The file wchich includes all required libraries to work.
=======
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
>>>>>>> 5e3ce1aff47bf4c2db394f23b1540ef6d37fcd61
#include "structures.h"

void load(const char* name, student *e) {
    char filename[100];
    sprintf(filename, "database/%s.txt", name);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char line[100];
    char *token;
    int moduleCount = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "| ID:") != NULL) {
            sscanf(line, "| ID: %lld", &(e->id));
        }
        else if (strstr(line, "| First Name:") != NULL) {
            token = strtok(line, ":");
            token = strtok(NULL, ":");
            strcpy(e->nom, token+1);
        }
        else if (strstr(line, "| Last Name:") != NULL) {
            token = strtok(line, ":");
            token = strtok(NULL, ":");
            strcpy(e->prenom, token+1);
        }
        else if (strstr(line, "| Address:") != NULL) {
            token = strtok(line, ":");
            token = strtok(NULL, ":");
            strcpy(e->adresse, token+1);
        }
        else if (strstr(line, "| Email:") != NULL) {
            token = strtok(line, ":");
            token = strtok(NULL, ":");
            strcpy(e->email, token+1);
        }
        else if (strstr(line, "| Age:") != NULL) {
            sscanf(line, "| Age: %d", &(e->age));
        }
        else if (strstr(line, "|Total Modules:") != NULL) {
            sscanf(line, "|Total Modules: %d", &(e->nb_modules));
        }
        else if (strstr(line, "|Moyenne:") != NULL) {
            sscanf(line, "|Moyenne: %f", &(e->moyenne));
        }
        else if (strstr(line, "| Modules info:") != NULL) {
            moduleCount = 0;

            while (fgets(line, sizeof(line), file) != NULL) {
                if (line[0] == '|') {
                    module* m = &(e->modules[moduleCount]);

                    fgets(line, sizeof(line), file); // Read module name line
                    strtok(line, ":");
                    strcpy(m->nom_module, strtok(NULL, ":"));

                    fgets(line, sizeof(line), file); // Read coefficient line
                    strtok(line, ":");
                    sscanf(strtok(NULL, ":"), "%f", &(m->coefficient));

                    fgets(line, sizeof(line), file); // Read note line
                    strtok(line, ":");
                    sscanf(strtok(NULL, ":"), "%f", &(m->note));

                    moduleCount++;
                }
                else if (strstr(line, "|Total Modules:") != NULL) {
                    sscanf(line, "|Total Modules: %d", &(e->nb_modules));
                    break; // Exit the module information section
                }
            }
        }
    }
    fclose(file);
}