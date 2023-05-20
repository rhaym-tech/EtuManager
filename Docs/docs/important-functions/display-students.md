---
description: A function made to display all students data from database
---

# Display Students

{% hint style="info" %}
**About**: This function is responsible for displaying the contents of students files within a displaying window with with buttons support to view the preview and next student or leave. \
It reads the file line by line and prints each line on the window until either the end of the file is reached or the maximum number of lines to display is reached.
{% endhint %}

## 1. `displayFilesContent()` function:

### 1.1: Description:

This function reads the contents of a file specified by the **`filename`** parameter and displays them on the window **`win`**. It displays the lines of the file until either the end of the file is reached or the maximum number of lines, specified by the `pageHeight` parameter, is displayed.

### 1.2: Syntax:

#### Short form:

```c
//Routin
void displayFileContents(WINDOW* win, char* filename, int pageHeight);
//Function call
displayFileContents(MyWin, "MyFile.txt", 20);
```

#### Full form:

```c
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
```

### 1.3: Parameters:

| Argument         | Description                                                                   |
| ---------------- | ----------------------------------------------------------------------------- |
| **`win`**        | A pointer to a ncurses window where the file contents will be displayed.      |
| **`filename`**   | A string containing the name or path of the file to be read and displayed.    |
| **`pageHeight`** | An integer representing the maximum number of lines to display on the window. |

### 1.4: Input:

&#x20;The function requires a valid window object (**`win`**) created using the ncurses library. It also requires a valid **`filename`** pointing to the file to be read and displayed. The **`pageHeight`** parameter determines the maximum number of lines that can be displayed on the window.

### 1.5: Output:

&#x20;The function reads the specified file line by line and displays each line on the window using the **`wprintw()`** function from the ncurses library. It stops displaying lines when either the end of the file is reached or the maximum number of lines defined by **`pageHeight`** is displayed.

### 1.6: Usage:

We use this function when we want to display the contents of a file on a window created with the ncurses library.\
Provide the appropriate window, file name, and page height to display the desired file contents

## 2. `displayStudents()` function:

### 2.1: Description:&#x20;

This function displays the list of students by opening a window, reading student files from a directory, and allowing the user to navigate through the files and view their contents.

### 2.2: Syntax:

#### Short form:

```c
//Routin
void displayStudents();
//Function call
displayStudents();
```

#### Full form:

```c
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
```

### 2.3: Parameters:&#x20;

This function does not take any parameters.

### 2.4: Function Tasks:&#x20;

1. Initializing ncurses screen and setting input mode:

```c
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
```

* **`initscr()`** initializes the ncurses library and prepares the terminal for use.
* **`cbreak()`** disables line buffering so that input characters are immediately available.
* **`noecho()`** disables character echoing, so user input is not displayed on the screen.
* **`keypad(stdscr, TRUE)`** enables the keypad of the user's terminal for special keys.

2. Getting the maximum screen dimensions:

```c
int max_y, max_x;
getmaxyx(stdscr, max_y, max_x);
```

* **`getmaxyx(stdscr, max_y, max_x)`** retrieves the maximum number of rows and columns available on the screen and stores them in **`max_y`** and **`max_x`** variables.

3. Setting the page height:

```c
int pageHeight = max_y - 4;
```

* Calculates the **`pageHeight`** by subtracting 4 from the maximum number of rows. This ensures space is left for buttons and title.

4. Creating a new window for displaying student information:

```c
WINDOW* win = newwin(max_y - 4, max_x, 2, 0);
refresh();
```

* **`newwin(max_y - 4, max_x, 2, 0)`** creates a new window with the specified dimensions (height: **`max_y - 4`**, width: **`max_x`**) starting at coordinates (2, 0).
* **`refresh()`** updates the screen to reflect the changes.

5. Opening the directory and counting the number of student files:

```c
DIR* dir = opendir("database");
struct dirent* entry;
int totalPages = 0;

if (dir == NULL) {
    // Error handling code
    return;
}

while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
        totalPages++;
    }
}
```

* **`opendir("database")`** opens the "database" directory and returns a directory stream pointer (**`dir`**) to read its contents.
* **`readdir(dir)`** reads the next entry from the directory stream, and **`entry`** points to the current entry.
* **`entry->d_type == DT_REG`** checks if the current entry is a regular file (not a directory or special file).
* The **`totalPages`** variable keeps track of the number of student files found.

6. Displaying error messages if the directory is empty or cannot be opened:

```c
if (totalPages == 0) {
    // No student files found error message
    return;
}
```

7. Creating and displaying the title window:

```c
WINDOW* titleWin = newwin(1, max_x, 0, 0);
wattron(titleWin, A_BOLD | A_REVERSE);
mvwprintw(titleWin, 0, (max_x - 12) / 2, " Students List ");
wattroff(titleWin, A_BOLD | A_REVERSE);
refresh();
wrefresh(titleWin);
```

* **`newwin(1, max_x, 0, 0)`** creates a new window with a height of 1 row, spans the entire width of the screen (`max_x`), and starts at coordinates (0, 0).
* **`wattron(titleWin, A_BOLD | A_REVERSE)`** enables bold and reverse attributes for the title window.
* **`mvwprintw(titleWin, 0, (max_x - 12) / 2, " Students List ")`** moves the cursor to row 0 and to the center of the window horizontally, then prints the text " Students List ".
* **`wattroff(titleWin, A_BOLD | A_REVERSE)`** disables the bold and reverse attributes for the title window.
* **`refresh()`** updates the screen to reflect the changes.
* **`wrefresh(titleWin)`** updates the title window to reflect the changes.

8. Creating and displaying the button window:

```c
WINDOW* buttonWin = newwin(1, max_x, max_y - 2, 0);
mvwprintw(buttonWin, 0, 2, "Previous: Left Arrow");
mvwprintw(buttonWin, 0, (max_x - 12) / 2, "Click Q to exit");
mvwprintw(buttonWin, 0, max_x - 18, "Next: Right Arrow");
refresh();
wrefresh(buttonWin);
```

* **`newwin(1, max_x, max_y - 2, 0)`** creates a new window with a height of 1 row, spans the entire width of the screen (**`max_x`**), and starts two rows above the bottom of the screen (**`max_y - 2`**).
* **`mvwprintw(buttonWin, 0, 2, "Previous: Left Arrow")`** moves the cursor to row 0 and column 2, then prints the text "Previous: Left Arrow".
* **`mvwprintw(buttonWin, 0, (max_x - 12) / 2, "Click Q to exit")`** moves the cursor to row 0 and to the center of the window horizontally, then prints the text "Click Q to exit".
* **`mvwprintw(buttonWin, 0, max_x - 18, "Next: Right Arrow")`** moves the cursor to row 0 and to the right side of the window, leaving a gap of 18 characters, then prints the text "Next: Right Arrow".
* **`refresh()`** updates the screen to reflect the changes.
* **`wrefresh(buttonWin)`** updates the button window to reflect the changes.
