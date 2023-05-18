---
description: the main project file
---

# main.c

{% hint style="info" %}
**Pro tip:** Never put everything in the main.c or the main() funtion itself!\
Code always need to be clean and well structured
{% endhint %}

After structuring the whole project, including all required libraries and defining all used functions and structs, now we must keep only the important things in the main.c

\
Our main.c only contains the most important things

### main.c head:

In the head file we include all the required headers, libraries and macros to use 'em in our project:

```c
#include "headers/includes.h" //? The file wchich includes all required libraries to work.
#include "headers/functions.h" //? Local library contains many functions for this project.

#define NUMBUTTONS 6
```

### main.c body:

in a well-strucured C project, the main.c body must only contains the main() function which itself only contains other functions calls, exactly like our code

Our main() function can be parted into 4 parts:

```c
int main() {
    
    // Part 1: Windows and buttons

    // Part 2: Keys Listener

    // Part 3: Preforming Actions

    // Part 4: Cleaning Up
}
```

**Part 1: Defining Windows and Buttons for our UI**

<pre class="language-c"><code class="lang-c"><strong>//PART 1: Windows and Buttons
</strong>    setlocale(LC_ALL, ""); //? Support Non-Ascii characters for most Unix-Like terminals (source: includes.h => locale.h)

    //* Initialize ncurses screen (Source: includes.h => ncurses.h)
    initscr(); 
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    //* Initialize color pairs
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    //* Create welcome window
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    WINDOW* welcome_win = newwin(max_y, max_x, 0, 0);
    box(welcome_win, 0, 0);
    refresh();

    //* Print welcome message and description
    const char* title = " Welcome to Etudiants Management Program ";
    const char* btn = "Press Enter to Continue";
    int title_len = strlen(title);
    int btn_len = strlen(btn);
    
    //? Print an ASCII Art as a logo
    mvwprintw(welcome_win, max_y/2 - 6, max_x/2 - 45,  "███████╗████████╗██╗   ██╗ ███╗   ███╗ █████╗ ███╗  ██╗ █████╗  ██████╗ ███████╗██████╗ \n");
    mvwprintw(welcome_win, max_y/2 - 5, max_x/2 - 45,  "██╔════╝╚══██╔══╝██║   ██║ ████╗ ████║██╔══██╗████╗ ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 4, max_x/2 - 45,  "█████╗     ██║   ██║   ██║ ██╔████╔██║███████║██╔██╗██║███████║██║  ██╗ █████╗  ██████╔╝\n");
    mvwprintw(welcome_win, max_y/2 - 3, max_x/2 - 45,  "██╔══╝     ██║   ██║   ██║ ██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║  ╚██╗██╔══╝  ██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 2, max_x/2 - 45,  "███████╗   ██║   ╚██████╔╝ ██║ ╚═╝ ██║██║  ██║██║ ╚███║██║  ██║╚██████╔╝███████╗██║  ██║\n");
    mvwprintw(welcome_win, max_y/2 - 1, max_x/2 - 45,  "╚══════╝   ╚═╝    ╚═════╝  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝\n");
    //? Pint the Title with bold and reversed format
    wattron(welcome_win, A_BOLD | A_REVERSE); //turns on bold and reverse fromat
    mvwprintw(welcome_win, max_y/2 + 3, max_x/2 - title_len/2, "%s", title);
    wattroff(welcome_win, A_BOLD | A_REVERSE); //turns off bold and reverse fromat
    //? Pint the Description with bold and blink effect
    wattron(welcome_win, A_BOLD | A_BLINK); //turn on bold and blink effect
    mvwprintw(welcome_win, max_y/2 + 5, max_x/2 - btn_len/2, "%s", btn);
    wattroff(welcome_win, A_BOLD | A_BLINK); //turn on bold and blink effect

    //* Refresh welcome screen
    wrefresh(welcome_win);

    //! A key listener: Wait for user to click Enter to continue
    int ch = getch();
    while (ch != '\n') {
        ch = getch();
    }

    //* Delete welcome screen
    delwin(welcome_win);

MAIN:
    //* Create main window
    getmaxyx(stdscr, max_y, max_x);
    WINDOW* mainwin = newwin(max_y, max_x, 0, 0);
    box(mainwin, 0, 0);
    refresh();

    //* Create buttons
    const char *ttl = "Students Management:";
    int ttl_len = strlen(ttl);
    char *button_labels[6] = {
        "Add Students",
        "Display Students",
        "Search Students",
        "Modify Students",
        "Delete Students",
        "Average Calculator"
    };
    int current_button = 0;

    wattron(mainwin, A_BOLD);
    mvwprintw(mainwin, max_y/2 -11, max_x/2 - ttl_len/2, "%s", ttl);
    wattroff(mainwin, A_BOLD);
    
    mvprintw(LINES-2, 2, "Press Q key to exit...");

    WINDOW* button_wins[NUMBUTTONS];
    for (int i = 0; i &#x3C; NUMBUTTONS; i++) {
        button_wins[i] = subwin(mainwin, 3, 20, max_y/2 + i*3 - NUMBUTTONS*3/2, max_x/2 - 10);
        wbkgd(button_wins[i], COLOR_PAIR(1));
        box(button_wins[i], 0, 0);
        mvwprintw(button_wins[i], 1, 1, button_labels[i]);
    }
    wbkgd(button_wins[current_button], COLOR_PAIR(2));
    wrefresh(mainwin);
...
</code></pre>

### Part 2: Keys Listener

setting up a keys listener to record keyboard clicks, we actually have only 3 cases:\
**Key Up, Key Down:** to browse through the options.\
**Enter Key:** to confirm/access to an option.\
**Q key:** to quite the program.

```c
//Part 2: Keys Listener
    
    // Main loop
    bool quit = false;
    while (!quit) {
        int ch = getch();
        switch (ch) {
            case KEY_DOWN: // case key down clicked
                /*
                    Here we switch the colors pairs from white to green to make button appears like it's active (the selected one)
                    So used can knows which button possition he's on
                */
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button + 1) % NUMBUTTONS;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case KEY_UP: // case of key up clicked
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button - 1 + NUMBUTTONS) % NUMBUTTONS;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case '\n': // case of Enter clicked

                //Part 3: Preforming Actions   

                break;
            case 'q': // case of lowercase q
            case 'Q': // case of uppercase Q
                quit = true; // break the loop and exit program
                break;
            
        }
    }


```

### Part 3: Preforming actions

Here we give each button it's function using if else cases and button index variable we called "current\_button":

<pre class="language-c"><code class="lang-c">//Part 3: Preforming Actions   

if (current_button == 0) {
      addStudent();
   } else if (current_button == 1) {
      display_students();
   } else if (current_button == 2) {
      searchStudent();
   } else if (current_button == 3) {
      update_student();
   } else if (current_button == 4) {
      delete_student();
   } else if (current_button == 5) {
      calculateAverage();
   }
// Cleaning up after finishing the function job
<strong>mvprintw(LINES-2, 2, "Press any key to continue...");
</strong>getch(); //* Wait for user input
clear(); //! Clear the screen
box(mainwin, 0, 0); //* Redraw main window border
wrefresh(mainwin); //* Refresh main window
goto MAIN; //* Go back to main loop
</code></pre>
