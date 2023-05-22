---
description: >-
  A function made to calculate Student's average and log his modules info to his
  file
---

# Average Calculator

## 1. `average()` function:

### 1.1 Description:

This function calculates the average by dividing the total value by the count value. If the count is zero, the function returns 0.0 to avoid division by zero errors.

### 1.2 Syntax:

#### Short Form:

```c
// Routine
float average(float total, int count);

// Function call
float result = average(15.75, 5);
```

#### Full Form:

```c
float average(float total, int count) {
    if (count == 0)
        return 0.0;
    return total / count;
}
```

### 1.3 Parameters:

| Argument    | Description                                         |
| ----------- | --------------------------------------------------- |
| **`total`** | The total value used to calculate the average.      |
| **`count`** | The number of values used to calculate the average. |

### 1.4 Return Value:

The function returns the calculated average as a **`float`** value.

### 1.5 Usage:

This function is typically used in scenarios where you need to calculate an average, such as in the **`calculateAverage()`** function.

## 2. `calculateAverage()` function:

### 2.1 Description:

This function allows the user to calculate the average score for a student and gather module information. It prompts the user for the student's first name, last name, and the number of modules. Then, it prompts the user to enter the name, coefficient, and score for each module. The function calculates the average score and writes the module information and average to the student's file.

### 2.2 Syntax:

#### Short Form

```c
// Routine
void calculateAverage();

// Function call
calculateAverage();
```

#### Full Form

```c
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
```

### 2.3 Function Tasks:

1. Prompt the user to enter the student's first name and last name.
2. Create a file path using the student's name by calling the **`findStudent()`** function.
3. Open the file for reading and writing.
4. If the file path is **`NULL`**, display an error message and return from the function.
5. If the file cannot be opened, display an error message and return from the function.
6. Prompt the user to enter the number of modules.
7. Iterate over the number of modules and for each module:
   * Prompt the user to enter the module name.
   * Prompt the user to enter the coefficient for the module.
   * Prompt the user to enter the score for the module.
   * Calculate the total and coefficient sum for the average calculation.
   * Write the module information to the file.
8. Calculate the average score by calling the **`average()`** function with the total and coefficient sum.
9. Write the average score to the file.
10. Close the file.
11. Display the calculated average score and success message to the user.
12. Refresh the screen.

{% hint style="warning" %}
Please note that the explanations in the **Return Value** section of `average()` and the **Function Tasks** section of `calculateAverage()` are placeholders and should be replaced with the actual information about the return value and function tasks, respectively.
{% endhint %}
