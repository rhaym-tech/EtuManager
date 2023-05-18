---
description: A function made to add students data to database
---

# Add Students

{% hint style="info" %}
**About:** This function is responsible for inputting the data of a student. It prompts the user to enter various information about the student and performs basic validation checks on some fields.
{% endhint %}

## 1. `studentInput()` function

{% hint style="warning" %}
Important: This function is the core function of the main function: `addStudent()`, which will be wrapped later by it
{% endhint %}

### 1.1: Description:

This function is responsible for taking input from the user to populate the fields of a `student` structure. (reference: [structs.md](../code-structure/structs.md "mention"))

### 1.2: Syntax:

#### short form:

```c
void studentInput(student *e); //routine
studentInput(myStudent); // call function
```

#### full form:

<pre class="language-c"><code class="lang-c">void studentInput(student *e) {
    char filename[100];

    printw("Enter Student id (layout: yyyy[bac_id]): ");
    scanw("%llu", &#x26;(e->id));

    printw("Enter Student's first name : ");
    scanw("%s", e->nom);

    printw("Enter Student's last name : ");
    scanw("%s", e->prenom);

    printw("Enter Student's home adress: ");
    scanw(" %[^\n]", e->adresse);

<strong>    CHECKPOINT1:
</strong>    printw("Enter Student's Email: ");
    scanw("%s", e->email);
    if(!check(isEmail, e->email)){
        printw("\nInvalid email !\n");
        goto CHECKPOINT1;
    }

    CHECKPOINT2:
    printw("Enter Student's age: ");
    scanw("%d", &#x26;(e->age));
    if(!check(age, e->age)){
        printw("\nInvalid age value !\n");
        goto CHECKPOINT2;
    }
}
</code></pre>

### 1.3: Parameters:

* **`e`**: Pointer to a `student` structure (see in [structs.md](../code-structure/structs.md "mention")). \
  The input values entered by the user will be stored in the fields of this structure.

### 1.4: Input:

The function prompts the user to enter various details of the student, such as their ID, first name, last name and home address. The input values are read from the terminal.

```c
...
    printw("Enter Student ID (layout: yyyy[bac_id]): ");
    scanw("%llu", &(e->id));

    printw("Enter Student's first name : ");
    scanw("%s", e->nom);

    printw("Enter Student's last name : ");
    scanw("%s", e->prenom);

    printw("Enter Student's home adress: ");
    scanw(" %[^\n]", e->adresse);
...
```

for Email and Age, function firstly creates a label called "CHECKPOINT" before input, then it prompts the user to enter it's data, after that function calls the check() function (explained in: [input-checker.md](../additional-functions/input-checker.md "mention")) to verify if input data are valid or not, if it's not it tells user that data are invaild and takes him back to reprompt that kind of data again:

<pre class="language-c"><code class="lang-c"><strong>...
</strong><strong>    CHECKPOINT1:
</strong><strong>    printw("Enter Student's Email: ");
</strong>    scanw("%s", e->email);
    if(!check(isEmail, e->email)){
        printw("\nInvalid email !\n"); //email must contain at least '@' and '.'
        goto CHECKPOINT1;
    }

    CHECKPOINT2:
    printw("Enter Student's age: ");
    scanw("%d", &#x26;(e->age));
    if(!check(age, e->age)){
        printw("\nInvalid age value !\n"); // Age must be between 0 and 150
        goto CHECKPOINT2;
    }
...
</code></pre>

### 1.5: Output:

The function does not return any value. Instead, it populates the fields of the `student` structure passed as a parameter.

### 1.6: Usage:

This function will be called and wrapped by studentInput() when we need to gather input for a student object.

## 2. `addStudent()` function

### 2.1: Description:

This function allows the user to add multiple student records. It prompts the user for the number of students to add, creates a directory for storing student data files if it doesn't exist, and then iteratively collects input for each student.

### 2.2: Syntax:

#### short form:

```c
void addStudent(); // routine
addStudent(); // Call function
```

#### full form (definition):

<pre class="language-c"><code class="lang-c">void addStudent() {
    clear();
    int nb_students = 0;
    printw("How many students to add: ");
    scanw("%d", &#x26;nb_students);
    char directory[] = "database/";
    char filename[500];

    //TODO: Check if the database directory exists, and create it if it doesn't
    struct stat st = {0};
    if (stat(directory, &#x26;st) == -1) {
        mkdir(directory, 0700);
    }

<strong>    for (int i = 0; i &#x3C; nb_students; i++){
</strong>        printw("Enter student n° %d data: \n", i+1);
        studentInput(&#x26;students[i]);

        sprintf(filename, "%s%s_%s.txt", directory, students[i].nom, students[i].prenom);
​
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
</code></pre>

### 2.3: Input:

The function prompts the user to enter the number of students to add and provides a prompt for entering student data using [`studentInput()`](add-students.md#1.-studentinput-function) function.

```c
... // rest of code
for (int i = 0; i < nb_students; i++){
        printw("Enter student n° %d data: \n", i+1);
        studentInput(&students[i]);
        ... // rest for code
 }
```

### 2.4: Output:

The function creates a directory named "**database**" (if it doesn't already exist) to store student data files.&#x20;

{% code title="headers/functions.h" lineNumbers="true" %}
```c
...
char directory[] = "database/";

//TODO: Check if the database directory exists, and create it if it doesn't
struct stat st = {0}; // from dirnet.h
if (stat(directory, &st) == -1)
    mkdir(directory, 0700);
...
```
{% endcode %}

{% hint style="warning" %}
in this line:

<pre class="language-c" data-overflow="wrap"><code class="lang-c"><strong>mkdir(directory, 0700);
</strong></code></pre>

We here create a folder called `"database/"` when it doesn't exist already.\
but this syntax only supports **Unix-Like** systems (**Linux/MacOS**)\
For **Windows** we use this instead:

<pre class="language-c" data-overflow="wrap"><code class="lang-c"><strong>mkdir(directory);
</strong></code></pre>
{% endhint %}

It saves the entered student data into separate text files, with each file containing the details of one student. The file names are generated using the student's first name and last name.

<pre class="language-c" data-title="headers/function.h"><code class="lang-c"><strong>...
</strong><strong>    for (int i = 0; i &#x3C; nb_students; i++){
</strong>        printw("Enter student n° %d data: \n", i+1);
        studentInput(&#x26;students[i]);

        sprintf(filename, "%s%s_%s.txt", directory, students[i].nom, students[i].prenom);
​
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
</code></pre>

### 2.5: Usage:

This function can be used to interactively add student records to a database-like system.

{% hint style="danger" %}
It seems that the code snippet is missing the definition of the **`student`** structure and the implementation of the **`check()`** function, which are referenced within the code. \
\
Make sure to keep them defined by including the**`"headers/structures.h"`**and**`"headers/checker.h"`** appropriately to ensure the code compiles and functions correctly.
{% endhint %}
