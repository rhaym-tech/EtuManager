---
description: here we find the used structures in project
---

# Structures (structs)

<details>

<summary>Used Macros</summary>

This macros are made to define used arrays sizes

```c
#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_ADDRESS_LEN 100
#define MAX_EMAIL_LEN 50
#define MAX_MODULES 10
```

</details>

## 1. Struct Definitition `module` :

The `module` structure represents a module of a student's academic record. \
It contains information such as the module name, coefficient, and the student's grade (note) in that module.

### syntax:

```c
typedef struct {
    char nom_module[MAX_NAME_LEN];
    int coefficient;
    float note;
} module;

```

### Members:

* **`nom_module`**: An array of characters representing the name of the module. The maximum length is defined by `MAX_NAME_LEN` see in ([#used macros](structs.md#used-macros))
* **`coefficient`**: An integer representing the coefficient of the module.
* **`note`**: A floating-point value representing the student's grade in the module.

## 2. Struct Definitition `student` :

### Syntax:

```c
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

### Members:

* **`id`**: A long long integer representing the unique ID of the student.
* **`nom`**: An array of characters representing the last name of the student. The maximum length is defined by `MAX_NAME_LEN`. see in ([#used macros](structs.md#used-macros))
* **`prenom`**: An array of characters representing the first name of the student. The maximum length is defined by `MAX_NAME_LEN`. see in ([#used macros](structs.md#used-macros))
* **`adresse`**: An array of characters representing the home address of the student. The maximum length is defined by `MAX_ADDRESS_LEN`. see in ([#used macros](structs.md#used-macros))
* **`email`**: An array of characters representing the email address of the student. The maximum length is defined by `MAX_EMAIL_LEN`. see in ([#used macros](structs.md#used-macros))
* **`age`**: An integer representing the age of the student.
* **`moyenne`**: A floating-point value representing the average grade of the student.
* **`modules`**: An array of `module` structures representing the list of modules for the student. The maximum number of modules is defined by `MAX_MODULES`. see in ([#used macros](structs.md#used-macros))
* **`nb_modules`**: An integer representing the number of modules for the student.

{% hint style="info" %}
The `module` structure within the `student` structure allows storing multiple modules with their respective information for each student.
{% endhint %}
