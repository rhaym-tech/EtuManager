---
description: Code documentation mapping page
---

# 🛠 Code Structure

Our code is kinda large and it may be unreadable, so we made this documentation to make everything clear about the code

<details>

<summary>Files structure</summary>

```
├── Docs
│   ├── SUMMARY.md
│   ├── README.md
│   └── ...
├── headers
│   ├── includes.h
│   ├── functions.h
│   ├── checker.h
│   ├── structures.h
│   └── loader.h
├── database
│   ├── [firstname]_[familyname].txt
│   ├── [firstname]_[familyname].txt
│   └── ...
├── main.c
├── README.md
└── LICENSE

```

</details>

<details>

<summary>headers</summary>

**checker.h:** contains the function which checks the input data validity\
it supports 5 different types of inputs:

* **isAlpha:** to verify first name and last name if contains only alphabets or not
* **isEmain:** to verify that input is an email type with this layout\
  joe<mark style="color:red;">**@**</mark>smith<mark style="color:red;">**.**</mark>com
* **coef**: to verify the Coefficient value that should be always positive
* **avg**: to verify averages values to be always between 0 and 20.0
* **age**: to verify age's value that shouldn't be greater than 150 years

````c
```cpp
#include "includes.h" //? The file wchich includes all required libraries to work.


enum type {isAlpha, isEmail, coef, avg, age};

bool check(enum type Something, ...) {
  va_list args;
  va_start(args, Something);

  char* str;
  int num;
  double moy;
  char *at;
  char *dot;

  switch(Something) {
    case isAlpha:
      str = va_arg(args, char*);
      for (int i = 0; i < strlen(str); i++) if (!isalpha(str[i])) return false;
      return true;
    break;

    case isEmail:
        str = va_arg(args, char*);
        at = strchr(str, '@');
        if (!at) {
            return false; //! '@' not found
        }
        dot = strchr(at, '.');
        return dot && dot > at; //! dot found and after '@'
    break;

    case coef:
      num = va_arg(args, int);
      return num > 0;
    break;

    case avg:
      moy = va_arg(args, double);
      return moy >= 0.0 && moy <= 20.0;
    break;

    case age:
      num = va_arg(args, int);
      return num >= 0 && num < 150;
    break;
  }

  va_end(args);
}

```
````

**functions.h:** contains the most important functions for work:

* **addStudent():** a function to add a student by prompting user the student info (ID, name, address, email, age) and saves his data to file called "\[first name]\_\[last name].txt"
* **displayStudent():** Display all saved students (fetchs data from database folder)
* **searchStudent():** Searchs a student in database by his first name or last name
* **updateStudent():** Updates a saved student's data
* **deleteStudent():** Delete a student from database
* **calculateAverage():** Calculates student average and saves his average and modules data to his file.



**includes.h:** a header file which contains all required libraries to use in our project, the point from making this is to not writing the same headers in each file

````c
```c
/*
    *Here we Put all required headers in one file :D
*/

//! C Libraries and main headers
#include <stdio.h> //? Standard input/output C library.
#include <stdlib.h> //? Standard C library.
#include <string.h> //? Strings C Library.
#include <stdbool.h> //? Booleans C Library.
#include <ncurses.h> //? New Curses aka :"ncurses" C/C++ Library (used to make TUI programs).
#include <locale.h> //? Unix-Like localization management C Library.
#include <sys/stat.h> //? File status and information functions C Library.
#include <dirent.h> //? Directory manipulation for file management operations C Library.
#include <stdarg.h> //? Variable arguments handling macros for function parameterization C Library.
#include <ctype.h> //? Character classification and manipulation functions C Library.
```
````

**loader.h:** contains load() function to load data from files to program when it start's up

````c
```c
#include "includes.h" //? The file which includes all required libraries to work.
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
```
````

**structures.h:** file contains the used structs in code

````c
```c
#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_ADDRESS_LEN 100
#define MAX_EMAIL_LEN 50
#define MAX_MODULES 10


typedef struct {
    char nom_module[MAX_NAME_LEN];
    int coefficient;
    float note;
} module;

typedef struct {
    long long int id;
    char nom[MAX_NAME_LEN];
    char prenom[MAX_NAME_LEN];
    char adresse[MAX_ADDRESS_LEN];
    char email[MAX_EMAIL_LEN];
    int age;
    float moyenne;
    module modules[MAX_MODULES];
    int nb_modules;
} student;
```
````

</details>

<details>

<summary>Libraries used explained</summary>

Our project uses bensh of libraries to make it work perfuctly

### Our Libraries

* **stdio.h:** (Standard input/output) main library which contains the basic C functions.
* **stdlib.h:** (Standard Library), which is a collection of functions and macros defined by the C programming language standard.
* **String.h**: a base library which _defines one variable type, one macro, and various functions_ for manipulating arrays of characters.
* **stdbool.h**: (Standard Boolean) _C_ Standard Library which contains four macros for a **Boolean** data type.&#x20;
* [**ncurses**](https://invisible-island.net/ncurses/)**:** (New Curses), **C/C++** Library provides an **API** (Application Programming Interface) to build **TUI** (Text-Based User Interfaces)
* **locale.h:** C library which defines the location specific settings, such as date formats and currency symbols.
* **sys/stat.h:** system library which defines **stat()** funcion which gets status information about a specified file and places it in the area of memory pointed to by the buf argument
* **dirnet.h:** C Library that provides functions and structures for working with directories and directory entries. It is part of the **POSIX** standard and is commonly used on **Unix-like** operating systems, including **Linux**.
* **stdarg.h:** (Standard Arguments Library) C standard library that allows functions to accept an indefinite number of arguments. It provides facilities for stepping through a list of function arguments of unknown number and type.
* **ctype.h:** C character classification is an operation provided by a group of functions in the **ANSI C Standard Library.** These functions are used to test characters for membership in a particular class of characters, such as alphabetic characters, control characters, etc.

</details>

<details>

<summary>main.c</summary>

After structuring the whole project, including all required libraries and defining all used functions and structs, now we must keep only the important things in the main.c\
Our main.c only contains the most important things

1. including the required headers&#x20;
2. calling the main() function which it's only used to define our window UI and buttons
3. setting up a keys listener to record keyboard clicks, we actually  have only 3 cases:\
   &#x20;     **Key Up, Key Down:** to browse through the options.\
   &#x20;     **Enter Key:** to confirm/access to an option.\
   &#x20;     **Q key:** to quite the program.
4. switch case to give each button it's function.

More details about the main.c will be explained in the [next page](./#main.c)

</details>
