---
description: Function made to modify a student file
---

# Modify Student

## 1. `linesCount()` function:

### 1.1 Description:

This function counts the number of lines in a file. It reads the file line by line using `fgets()` and increments a line counter until the end of the file is reached.

### 1.2 Syntax:

```c
// Routine
int linesCount(FILE* file);

// Function call
int count = linesCount(file);
```

### 1.3 Parameters:

* `file`: A pointer to a file object opened for reading.

### 1.4 Return Value:

The function returns the number of lines in the file.

### 1.5 Usage:

This function can be used to determine the number of lines in a file, which can be useful in various file processing operations.

## 2. `updateStudent()` function:

### 2.1 Description:

This function allows the user to update student information in the database. It prompts the user for the student's last name and first name, searches for the student in the database, and updates their information if found.

### 2.2 Syntax:

#### Short Form:

```c
// Routine
void updateStudent();

// Function call
updateStudent();
```

#### Full Form:

```javascript
void updateStudent() {
    clear();
    char nom[DEFAULT_BUFFER_SIZE];
    char prenom[DEFAULT_BUFFER_SIZE];
    student etu;
//1
    printw("Enter the student's last name: ");
    scanw("%s", nom);
    printw("Enter the student's first name: ");
    scanw("%s", prenom);
    clear();
//2
    char *filename = findStudent(nom, prenom);
    if (filename == NULL) { 
        printw("Unable to find student %s %s. Make sure you have already added them to the database!\n", nom, prenom);
        refresh();
        return;
    }
//3
    FILE* fp = fopen(filename, "r+");
    if (fp == NULL) {
        printw("Unable to open the file.\n");
        free(filename);
        refresh();
        return;
    }

    //4: Count the number of lines in the file

    if (linesCount(fp) <= 7) {
        //5: File has less than 7 lines, append the new data at the end
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
//6:
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
//7:
    refresh();
}
```

### 2.3 Function Tasks:

1. Prompt the user to enter the student's last name and first name.
2. Search for the student in the database using the `findStudent()` function, \
   If the student is not found, display an error message and return.
3. Open the student's file in read-write mode.
4. Count the number of lines in the file using the `linesCount()` function.
5. If the file has less than 7 lines:
   * Close the file and reopen it in write mode.
   * Prompt the user for the updated student information.
   * Rename the file to reflect the updated student's name.
   * Write the updated student information to the file.
   * Display a success message.
6. If the file has 7 or more lines:
   * Close the file and reopen it in write mode.
   * Read and store the rest of the file starting from line 7.
   * Prompt the user for the updated student information.
   * Rename the file to reflect the updated student's name.
   * Write the updated student information to the file.
   * Display a success message.
   * Prompt the user if they want to update module information as well.
     * If yes, call the `calculateAverage()` function.
     * If no, write back the rest of the file.
7. Refresh the screen.
