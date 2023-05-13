#include "structures.h"
#include "checker.h"
#include <ncurses.h>    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#define DATABASE_PATH "database/" // Path to the database directory
#define FILENAME_LENGTH 100 // Maximum length of the file name

student students[MAX_STUDENTS];

void studentInput(student *e) {
    char filename[100];

    printw("Enter Student id (layout: yyyy[bac_id]): ");
    scanw("%llu", &(e->id));

    printw("Enter Student's first name : ");
    scanw("%s", e->nom);

    printw("Enter Student's last name : ");
    scanw("%s", e->prenom);

    printw("Enter Student's home adress: ");
    scanw(" %[^\n]", e->adresse);

    CHECKPOINT1:
    printw("Enter Student's Email: ");
    scanw("%s", e->email);
    if(!check(isEmail, e->email)){
        printw("\nInvalid email !\n");
        goto CHECKPOINT1;
    }

    CHECKPOINT2:
    printw("Enter Student's age: ");
    scanw("%d", &(e->age));
    if(!check(age, e->age)){
        printw("\nInvalid age value !\n");
        goto CHECKPOINT2;
    }
}


void addStudent() {
    clear();
    int nb_students = 0;
    printw("How many students to add: ");
    scanw("%d", &nb_students);
    char directory[] = "database/";
    char filename[500];

    //TODO: Check if the database directory exists, and create it if it doesn't
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        mkdir(directory, 0700);
    }

    for (int i = 0; i < nb_students; i++){
        printw("Enter student n° %d data: \n", i+1);
        studentInput(&students[i]);

        sprintf(filename, "%s%s_%s.txt", directory, students[i].nom, students[i].prenom);

        FILE* fp = fopen(filename, "w");
        if(fp == NULL) {
            printw("Error: could not create file for %s\n", students[i].nom);
            continue;
        }
        fprintf(fp, "| ID: %llu\n", students[i].id);
        fprintf(fp, "| First Name: %s\n", students[i].nom);
        fprintf(fp, "| Last Name: %s\n", students[i].prenom);
        fprintf(fp, "| Address: %s\n", students[i].adresse);
        fprintf(fp, "| Email: %s\n", students[i].email);
        fprintf(fp, "| Age: %d\n", students[i].age);
        fclose(fp);
        printw("Student data saved in %s\n", filename);
    }
}

void displayStudent();


void search_database(char* name_or_lastname) {
    DIR *dir;
    struct dirent *ent;
    char *prefix = "database/";
    char filename[100];
    FILE *file;

    if ((dir = opendir("database")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, name_or_lastname) != NULL) {
                strcpy(filename, prefix);
                strcat(filename, ent->d_name);
                file = fopen(filename, "r");
                if (file) {
                    printw("File %s:\n", filename);
                    char line[256];
                    while (fgets(line, sizeof(line), file)) {
                        printw("%s", line);
                    }
                    fclose(file);
                } else {
                    printw("Error opening file %s\n", filename);
                }
            }
        }
        closedir(dir);
    } else {
        printw("Error opening database directory\n");
    }
}

void searchStudent() {
    clear();
    char target[200];
    printw("Enter Student's name or lastname: ");
    scanw(" %[^\n]", target);
    printw("\n\n");
    search_database(target);
    refresh();
};

void updateStudent();
void deleteStudent();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_PATH "database/" // Path to the database directory
#define FILENAME_LENGTH 100 // Maximum length of the file name

// Function to calculate the student's average
float average(float total, int count) {
    if (count == 0)
        return 0.0;
    return total / count;
}

void calculateAverage() {
    clear();
    char studentName[FILENAME_LENGTH];
    student etu;

    printw("Enter student name: ");
    refresh();
    getstr(studentName);

    // Create file path using student name
    char filePath[FILENAME_LENGTH + sizeof(DATABASE_PATH)];
    strcpy(filePath, DATABASE_PATH);
    strcat(filePath, studentName);
    strcat(filePath, ".txt");

    // Open the file for reading and writing
    FILE *file = fopen(filePath, "a+");

    if (file == NULL) {
        printw("Unable to open the file.\n");
        refresh();
        endwin(); // End ncurses
        return;
    }

    // Calculate average and gather module information
    float total = 0.0;
    int coefSum = 0;
    printw("Enter the number of modules: ");
    refresh();
    scanw("%d", &etu.nb_modules);
    clear();

    // Write average and module information to the file
    fprintf(file, "\n| Modules info:\n\n");
    for (int i = 1; i <= etu.nb_modules; i++) {

        printw("Enter module %d name: ", i);
        refresh();
        getstr(etu.modules->nom_module);

        printw("Enter coefficient for module %d: ", i);
        refresh();
        scanw("%d", &etu.modules->coefficient);
        clear();

        printw("Enter note for module %d: ", i);
        refresh();
        scanw("%f", &etu.modules->note);
        clear();
        total += (etu.modules->coefficient * etu.modules->note);
        coefSum += etu.modules->coefficient;
        // Write module information to the file
        fprintf(file, "\t| %s:\n", etu.modules->nom_module);
        fprintf(file, "\t| Coefficient: %d\n", etu.modules->coefficient);
        fprintf(file, "\t| Note: %.2f\n\n", etu.modules->note);
    }
    fprintf(file, "|Moyenne: %.2f\n", average(total, coefSum));
    fclose(file);
    printw("Moyenne: %.2f\n\n\n", average(total, coefSum));
    printw("Student average and module information have been updated successfully.\n");
    refresh();
}
