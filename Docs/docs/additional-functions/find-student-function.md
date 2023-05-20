---
description: a function that searchs a student in database and returns his file name
---

# Find Student Function

{% hint style="info" %}
<mark style="color:purple;">**`findStudent()`**</mark> is a function that searches for a student's file in the database based on their name.\
And we're going to explain it
{% endhint %}

## 1. Function Definition:

```cpp
char* findStudent(char* nom, char* prenom)
```

* This function takes two arguments: **`nom`** and **`prenom`**, which represent the last name and first name of the student, respectively.
* The function returns a <mark style="color:red;">**`char`**</mark><mark style="color:blue;">**`*`**</mark> pointer, which points to the file path of the student's record if found, or <mark style="color:blue;">**`NULL`**</mark> if not found.

### Code snippet:&#x20;

```cpp
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
        char* result = malloc(strlen(option1) + 1); // Allocate memory for the result
        strcpy(result, option1); // Copy option1 to result
        return result;
    } else if (tmp2 != NULL) {
        fclose(tmp2);
        char* result = malloc(strlen(option2) + 1); // Allocate memory for the result
        strcpy(result, option2); // Copy option2 to result
        return result;
    }

    return NULL;
}
```

## 2. Variable Declarations:

```cpp
char option1[100];
char option2[100];
FILE* tmp1;
FILE* tmp2;
```

| Variable                        | Description                                                                                                      |
| ------------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| **`option1`** and **`option2`** | character arrays used to store the two possible file paths for the student's record based on the provided names. |
| **`tmp1`** and **`tmp2`**       |  file pointers used to check if the corresponding files exist.                                                   |

## 3. Function Tasks:

### 3.1 Generating File Paths:

```cpp
sprintf(option1, "database/%s_%s.txt", nom, prenom);
sprintf(option2, "database/%s_%s.txt", prenom, nom);
```

* These lines use **`sprintf`** to generate the file paths by concatenating the provided names with the **"database/"** directory path.

### 3.2 Opening Files:

```cpp
tmp1 = fopen(option1, "r");
tmp2 = fopen(option2, "r");
```

* These lines attempt to open the files using the generated file paths for reading (**`"r"`** mode).
* **`tmp1`** is used to check if the file with the **`nom_prenom.txt`** naming scheme exists.
* **`tmp2`** is used to check if the file with the **`prenom_nom.txt`** naming scheme exists.

### 3.3 File Existence Checking:

```cpp
if (tmp1 != NULL) {
    fclose(tmp1);
    if (tmp2 != NULL) {
        fclose(tmp2);
    }
    char* result = malloc(strlen(option1) + 1); // Allocate memory for the result
    strcpy(result, option1); // Copy option1 to result
    return result;
} else if (tmp2 != NULL) {
    fclose(tmp2);
    char* result = malloc(strlen(option2) + 1); // Allocate memory for the result
    strcpy(result, option2); // Copy option2 to result
    return result;
}
```

* If **`tmp1`** is not <mark style="color:blue;">**`NULL`**</mark>, it means that the file with the **`nom_prenom.txt`** naming scheme so function returns it.
* Else if **`tmp2`** is not <mark style="color:blue;">**`NULL`**</mark>, it means that the file with prenom\_nom.txt naming scheme so function returns it.
* Otherwice, both doesn't exist so function will return <mark style="color:blue;">**`NULL`**</mark>.
