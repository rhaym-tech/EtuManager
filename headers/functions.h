/*
*
*    EtuManager Project
?    Functions.h : The land of functions
!    Copyright Ghellab Abderrahmane © 2023 All rights reserved
*
*/

/*
*    Functions dictionary: (Guide available at: https://etumanager.rhaym-tech.me/docs/important-functions)

    *0: Helper Functions:
        0.1: findStudent(): Function built to find student's file in database (support's names swapping)
    
    *1: Add Student:
        1.1: studentInput(): the core function of addStudent()
        1.2: addStudent(): the responsible function of adding students to database
    *2: Display Students:
        2.1: displayFileContents(): the core function of displayStudents()
        2.2: displayStudents(): The responsible function of displaying all students whom stored in Database
    *3: Search a Student:
        3.1: search_database: The core function of searchStudent()
        3.2! searchStudent(): The responsible function of searching about a student
    *5: Delete a Student:
        5.1: delete_from_database(): The core function of deleteStudent()
        5.2: deleteStudent: The responsible function of deleting a specified student from database
    *6: Average Calculator:
        6.1: average(avgTotal, modulesNumber): The Core function of  to calculate average
        6.2: calculateAverage(): The responsible function of prompting modules info and calculating average
    *4: Modify a Student:
        4.1: linesCount(): to Count file lines
        4.2: updateStudent: The responsible function of updating a student's states
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//* Including Required Libraries:
#include "includes.h" //? The file wchich includes all required libraries to work.

//* Defining the required macros to use:
#define DATABASE_PATH "database/" // Path to the database directory
#define DEFAULT_BUFFER_SIZE 100 // Maximum length of the file name

//* Global variables
student students[MAX_STUDENTS];


// *0: Helper Function: 

//* 0.1: Find student by his name and returns file name:
char* findStudent(char* nom, char* prenom) {
    char option1[100];
    char option2[100];

    FILE* tmp1;
    FILE* tmp2;

    sprintf(option1, "database/%s_%s.txt", nom, prenom);
    sprintf(option2, "database/%s_%s.txt", prenom, nom);

    tmp1 = fopen(option1, "r");
    tmp2 = fopen(option2, "r");

    if (tmp1 != NULL) {
        fclose(tmp1);
        if (tmp2 != NULL) {
            fclose(tmp2);
        }
        char* result = malloc(strlen(option1) + 1); //* Allocate memory for the result
        strcpy(result, option1); //* Copy option1 to result
        return result;
    } else if (tmp2 != NULL) {
        fclose(tmp2);
        char* result = malloc(strlen(option2) + 1); //* Allocate memory for the result
        strcpy(result, option2); //* Copy option2 to result
        return result;
    }

    return NULL;
}

//* 1: Add Students:

//* 1.1:
void studentInput(student *e) {

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

//* 1.2:
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

//* 2: Display Students:

//* 2.1:
void displayFileContents(WINDOW* win, char* filename, int pageHeight) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        wprintw(win, "Error opening file %s\n", filename);
        return;
    }

    char buffer[100];
    int linesDisplayed = 0;

    while (fgets(buffer, 100, fp) != NULL && linesDisplayed < pageHeight - 1) {
        wprintw(win, "%s", buffer);
        linesDisplayed++;
    }

    fclose(fp);
}

//* 2.2
void displayStudents() {
    initscr();
    cbreak();
    noecho;
    keypad(stdscr, TRUE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int pageHeight = max_y - 4;  // Set page height to leave space for buttons and title

    WINDOW* win = newwin(max_y - 4, max_x, 2, 0);
    refresh();

    DIR* dir = opendir("database");
    struct dirent* entry;
    int currentFile = 0;
    int totalPages = 0;

    if (dir == NULL) {
        printw("Error while opening the database directory or it doesn't exist.\nMake sure you have already added some students.\n");
        refresh();
        getch();
        endwin();
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  // Regular file
            totalPages++;
        }
    }

    if (totalPages == 0) {
        printw("No student files found in the database.\n");
        refresh();
        getch();
        endwin();
        return;
    }

    int ch;
    char filePath[256];

    WINDOW* titleWin = newwin(1, max_x, 0, 0);
    wattron(titleWin, A_BOLD | A_REVERSE);
    mvwprintw(titleWin, 0, (max_x - 12) / 2, " Students List ");
    wattroff(titleWin, A_BOLD | A_REVERSE);
    refresh();
    wrefresh(titleWin);

    WINDOW* buttonWin = newwin(1, max_x, max_y - 2, 0);
    mvwprintw(buttonWin, 0, 2, "Previous: Left Arrow");
    mvwprintw(buttonWin, 0, (max_x - 12) / 2, "Click Q to exit");
    mvwprintw(buttonWin, 0, max_x - 18, "Next: Right Arrow");
    refresh();
    wrefresh(buttonWin);

    while (1) {
        wclear(win);

        if (currentFile >= totalPages)
            currentFile = totalPages - 1;

        if (currentFile < 0)
            currentFile = 0;

        rewinddir(dir);
        int fileCount = 0;

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {  // Regular file
                if (fileCount == currentFile) {
                    snprintf(filePath, sizeof(filePath), "database/%s", entry->d_name);
                    wprintw(win, "  Displaying file: %s\n\n", entry->d_name);
                    displayFileContents(win, filePath, pageHeight);
                    break;
                }
                fileCount++;
            }
        }

        wrefresh(win);

        ch = getch();
        if (ch == 'q' || ch == 'Q'){
            werase(buttonWin);
            wrefresh(buttonWin);
            break;
        }
        else if (ch == KEY_LEFT)
            currentFile--;
        else if (ch == KEY_RIGHT)
            currentFile++;
        else if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, max_y, max_x);
            wresize(win, max_y - 4, max_x);
            mvwin(buttonWin, max_y - 2, 0);
            mvwin(titleWin, 0, (max_x - 12) / 2);
            pageHeight = max_y - 4;
        }
    }

    closedir(dir);
    endwin();
}


//* 3: Searching Students:

//* 3.1:
void search_database(char* name_or_lastname) {
    DIR *dir;
    struct dirent *ent;
    char filename[100];
    FILE *file;

    if ((dir = opendir("database")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, name_or_lastname) != NULL) {
                strcpy(filename, DATABASE_PATH);
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

//* 3.2:
void searchStudent() {
    clear();
    char target[200];
    printw("Enter Student's name or lastname: ");
    scanw("%s", target);
    printw("\n\n");
    search_database(target);
    refresh();
}

// *4: Delete Students:

//* 4.1:
bool delete_from_database(char* nom, char* prenom) {
    char option1[100];
    char option2[100];
    int response;
    sprintf(option1, "database/%s_%s.txt", nom, prenom);
    sprintf(option2, "database/%s_%s.txt", prenom, nom);

    if(remove(option1) == -1)
        if(remove(option2) == -1)
            return false;
    return true;
}

//* 4.2:
void deleteStudent() {
    clear();
    char nom[100];
    char prenom[100];
    init_pair(3, COLOR_RED, COLOR_BLACK);
    printw("Enter Student's First name: ");
    scanw(" %s", nom);
    printw("Enter Student's Last name: ");
    scanw(" %s", prenom);
    clear();
    attron(COLOR_PAIR(3));
    printw("WARNING: ");
    attroff(COLOR_PAIR(3));
    printw("you're going to delete %s %s from database\nClick Any Key to confirm action\nClick Q key to abort!\n", nom, prenom);
    printw("\n\n");
    char ch = getch();
    if(ch == 'Q' || ch == 'q')
        return;
    if(delete_from_database(nom, prenom))
        printw("Student %s %s has been deleted successfully!\n", nom, prenom);
    else
        printw("Something went wrong or student can't be found, aborting...\n");
    refresh();
};


// *5: Calculate average:

//* 5.1:
float average(float total, int count) {
    if (count == 0)
        return 0.0;
    return total / count;
}

//* 5.2:
void calculateAverage() {
    clear();
    char firstName[DEFAULT_BUFFER_SIZE];
    char lastName[DEFAULT_BUFFER_SIZE];
    student etu;

    printw("Enter Student's first name: ");
    refresh();
    scanw("%s", firstName);
    printw("Enter Student's last name: ");
    refresh();
    scanw("%s", lastName);
    printw("\n");

    // Create file path using student name
    char *filePath = findStudent(firstName, lastName);
    // Open the file for reading and writing
    FILE *file = fopen(filePath, "a+");

    if(filePath != NULL) {
        if (file == NULL) {
            printw("Unable to open the file.\n");
            refresh();
            return;
        }
    } else {
        printw("Unable to find student %s %s, make sure you already added him to database!", firstName, lastName);
        free(filePath); free(file);
        refresh();
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

        printw("\nEnter module %d name: ", i);
        refresh();
        getstr(etu.modules->nom_module);

        printw("\nEnter coefficient for module %d: ", i);
        refresh();
        scanw("%d", &etu.modules->coefficient);

        printw("\nEnter note for module %d: ", i);
        refresh();
        scanw("%f", &etu.modules->note);


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

// *6: Modify Students:

//* 6.1:
int linesCount(FILE* file) {
    int lineCount = 1;
    char buffer[DEFAULT_BUFFER_SIZE*2];
    while (fgets(buffer, DEFAULT_BUFFER_SIZE*2, file) != NULL)
        lineCount++;

    return lineCount;
}

//* 6.2:
void updateStudent() {
    clear();
    char nom[DEFAULT_BUFFER_SIZE];
    char prenom[DEFAULT_BUFFER_SIZE];
    student etu;

    printw("Enter the student's last name: ");
    scanw("%s", nom);
    printw("Enter the student's first name: ");
    scanw("%s", prenom);
    clear();

    char *filename = findStudent(nom, prenom);
    if (filename == NULL) {
        printw("Unable to find student %s %s. Make sure you have already added them to the database!\n", nom, prenom);
        refresh();
        return;
    }

    FILE* fp = fopen(filename, "r+");
    if (fp == NULL) {
        printw("Unable to open the file.\n");
        free(filename);
        refresh();
        return;
    }

    // Count the number of lines in the file

    if (linesCount(fp) <= 7) {
        // File has less than 7 lines, append the new data at the end
        fclose(fp);
        fp = fopen(filename, "w");
        if (fp == NULL) {
            printw("Unable to open the file.\n");
            free(filename);
            refresh();
            return;
        }

        studentInput(&etu);
        char newName[DEFAULT_BUFFER_SIZE];
        sprintf(newName, "database/%s_%s.txt", etu.nom, etu.prenom);

        rename(filename, newName);

        fprintf(fp, "| ID: %llu\n", etu.id);
        fprintf(fp, "| First Name: %s\n", etu.nom);
        fprintf(fp, "| Last Name: %s\n", etu.prenom);
        fprintf(fp, "| Address: %s\n", etu.adresse);
        fprintf(fp, "| Email: %s\n", etu.email);
        fprintf(fp, "| Age: %d\n", etu.age);

        clear();
        printw("Student data has been updated in %s\n test ", filename);

        fclose(fp);
        free(filename);
        refresh();
        return;
    }
    fp = fopen(filename, "w");
    // Read and store the rest of the file starting from line 7
    char restOfFile[DEFAULT_BUFFER_SIZE];
    fgets(restOfFile, sizeof(restOfFile), fp);
    fseek(fp, 0, SEEK_SET);

    studentInput(&etu);

    char newName[DEFAULT_BUFFER_SIZE];
    sprintf(newName, "database/%s_%s.txt", etu.nom, etu.prenom);

    rename(filename, newName);

    fprintf(fp, "| ID: %llu\n", etu.id);
    fprintf(fp, "| First Name: %s\n", etu.nom);
    fprintf(fp, "| Last Name: %s\n", etu.prenom);
    fprintf(fp, "| Address: %s\n", etu.adresse);
    fprintf(fp, "| Email: %s\n", etu.email);
    fprintf(fp, "| Age: %d\n", etu.age);
    refresh();
    fclose(fp);
    free(filename);
    clear();
    printw("Student data has been updated in %s\n", filename);
    printw("\nDo you wanna update modules info also? (Y/N)");
    char ch = getch();
    switch (ch) {
        case 'Y':
        case 'y':
            calculateAverage();
            break;
        default:
            // Write back the rest of the file
            fputs(restOfFile, fp);
            break;
    }
    refresh();
}

#endif /* FUNCTIONS_H */