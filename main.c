#include "headers/includes.h" //? The file wchich includes all required libraries to work.

#define NUMBUTTONS 6

int main() {

    //PART 1: Windows and Buttons
    setlocale(LC_ALL, ""); //? Support Non-Ascii characters for most Unix-Like terminals (source: includes.h => locale.h)

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
    const char* title = " Welcome to Students Management Program ";
    const char* btn = "Press Enter to Continue";
    int title_len = strlen(title);
    int btn_len = strlen(btn);

    mvwprintw(welcome_win, max_y/2 - 6, max_x/2 - 45,  "███████╗████████╗██╗   ██╗ ███╗   ███╗ █████╗ ███╗  ██╗ █████╗  ██████╗ ███████╗██████╗ \n");
    mvwprintw(welcome_win, max_y/2 - 5, max_x/2 - 45,  "██╔════╝╚══██╔══╝██║   ██║ ████╗ ████║██╔══██╗████╗ ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 4, max_x/2 - 45,  "█████╗     ██║   ██║   ██║ ██╔████╔██║███████║██╔██╗██║███████║██║  ██╗ █████╗  ██████╔╝\n");
    mvwprintw(welcome_win, max_y/2 - 3, max_x/2 - 45,  "██╔══╝     ██║   ██║   ██║ ██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║  ╚██╗██╔══╝  ██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 2, max_x/2 - 45,  "███████╗   ██║   ╚██████╔╝ ██║ ╚═╝ ██║██║  ██║██║ ╚███║██║  ██║╚██████╔╝███████╗██║  ██║\n");
    mvwprintw(welcome_win, max_y/2 - 1, max_x/2 - 45,  "╚══════╝   ╚═╝    ╚═════╝  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝\n");

    wattron(welcome_win, A_BOLD | A_REVERSE);
    mvwprintw(welcome_win, max_y/2 + 3, max_x/2 - title_len/2, "%s", title);
    wattroff(welcome_win, A_BOLD | A_REVERSE);
    wattron(welcome_win, A_BOLD | A_BLINK);
    mvwprintw(welcome_win, max_y/2 + 5, max_x/2 - btn_len/2, "%s", btn);
    wattroff(welcome_win, A_BOLD | A_BLINK);

    //* Refresh welcome screen
    wrefresh(welcome_win);

    //* Wait for user input
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
    for (int i = 0; i < NUMBUTTONS; i++) {
        button_wins[i] = subwin(mainwin, 3, 20, max_y/2 + i*3 - NUMBUTTONS*3/2, max_x/2 - 10);
        wbkgd(button_wins[i], COLOR_PAIR(1));
        box(button_wins[i], 0, 0);
        mvwprintw(button_wins[i], 1, 1, button_labels[i]);
    }
    wbkgd(button_wins[current_button], COLOR_PAIR(2));
    wrefresh(mainwin);

    //Part 2: Keys Listener
    
    // Main loop
    bool quit = false;
    while (!quit) {
        int ch = getch();
        switch (ch) {
            case KEY_DOWN:
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button + 1) % NUMBUTTONS;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case KEY_UP:
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button - 1 + NUMBUTTONS) % NUMBUTTONS;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case '\n':

                //Part 3: Preforming Actions   

                if (current_button == 0) {
                    addStudent();
                } else if (current_button == 1) {
                    displayStudents();
                } else if (current_button == 2) {
                    searchStudent();
                } else if (current_button == 3) {
                    updateStudent();
                } else if (current_button == 4) {
                    deleteStudent();
                } else if (current_button == 5) {
                    calculateAverage();
                }
                mvprintw(LINES-2, 2, "Press any key to continue...");
                getch(); //* Wait for user input
                clear(); //! Clear the screen
                box(mainwin, 0, 0); //* Redraw main window border
                wrefresh(mainwin); //* Refresh main window
                goto MAIN; //* Go back to main loop
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
            
        }
    }

    //Part 4: Cleaning Up
    for (int i = 0; i < NUMBUTTONS; i++) {
        delwin(button_wins[i]);
    }
    delwin(mainwin);
    endwin();

    return 0;
}
