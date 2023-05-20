# Delete Student

## 1. `delete_from_database()` function

### 1.1 Description:

This function deletes a student's file from the database directory. It constructs two file paths based on the student's last name and first name, and attempts to remove the corresponding files. If the deletion fails for both file paths, the function returns `false`; otherwise, it returns `true`.

### 1.2 Syntax:

#### Short Form:

```c
// Routine
bool delete_from_database(char* nom, char* prenom);

// Function call
bool result = delete_from_database("Smith", "John");
```

#### Full Form:

```c
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
```

### 1.3 Parameters:

| Argument     | Description                                                                  |
| ------------ | ---------------------------------------------------------------------------- |
| **`nom`**    | A pointer to a null-terminated string representing the student's last name.  |
| **`prenom`** | A pointer to a null-terminated string representing the student's first name. |

### 1.5 Return Value:

The function returns **`true`** if the deletion is successful, and **`false`** otherwise.

### 1.6 Usage:

This function is used to remove a student's file from the database directory when deleting their information from the database.

## 2. `deleteStudent()` function:

### 2.1 Description:

This function allows the user to delete a student's information from the database. It prompts the user for the student's first name and last name, confirms the deletion action, and calls the **`delete_from_database()`** function to delete the student's file.

### 2.2 Syntax:

#### Short Form:

```c
// Routine
void deleteStudent();

// Function call
deleteStudent();
```

#### Full Form:

```c
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
```

### 2.3 Function Tasks:

1. Prompt the user to enter the student's first name and last name.
2. Display a warning message to inform the user about the deletion action.
3. Wait for any key input to confirm or press **'Q'** to abort the deletion.
4. If the user aborts, return from the function.
5. Call the **`delete_from_database()`** function with the provided first name and last name.
6. Display a success message if the deletion is successful.
7. Display an error message if the deletion fails or the student cannot be found.
8. Refresh the screen.

{% hint style="warning" %}
Please note that the explanations in the **Return Value** section of **`delete_from_database()`** and the **Function Tasks** section of **`deleteStudent()`** are placeholders and should be replaced with the actual information about the return value and function tasks, respectively.
{% endhint %}
