---
description: A function made to search a student from database by his name
---

# Search Student

{% hint style="info" %}
**About**: The **`searchStudent()`**function utilizes the **`search_database()`**function to perform the actual searching of student information in the database. \
It acts as a higher-level function that handles user interaction and delegates the search operation to the helper function.
{% endhint %}

## 1. `search_database()` function:

### 1.1: Description:

This function searches the database for files containing a given name or lastname and prints their contents.

### 1.2: Syntax:

#### Short Form:

```c
//Routin
void search_database(char* name_or_lastname);
//Function call
search_database("Joe");
```

#### Full Form:

```c
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
```

### 1.3: Parameters:

| Argument               | Description                                                                                                         |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------- |
| **`name_or_lastname`** | A pointer to a null-terminated string representing the name or lastname of a student to search for in the database. |

### 1.4: Input:

The search term (name or lastname) to look for in the database.

### 1.5: Output:

&#x20;The function prints the contents of the files that match the search term.

### 1.6: Usage:

This function is typically used when you want to search and retrieve information from the database based on a given name or lastname.

## 2. `searchStudent()` function:

### 2.1: Description:&#x20;

This function serves as the main entry point for searching student information in the database. It provides a user-friendly interface and calls the **`search_database()`** function to perform the search operation.

### 2.2: Syntax:

#### Short Form:

```c
//Routin
void searchStudent();
//Function call
searchStudent();
```

#### Full Form:

```c
void searchStudent() {
    clear();
    char target[200];
    printw("Enter Student's name or lastname: ");
    scanw("%s", target);
    printw("\n\n");
    search_database(target);
    refresh();
}
```

### 2.4: Function Tasks:&#x20;

1. Prompt the user to enter a student's name or lastname.
2. Call the **`search_database()`** function with the provided search term.
3. Display the information of the matching student(s) from the database.
