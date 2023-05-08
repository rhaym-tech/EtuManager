#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "headers/functions.h"
#include <ncurses/ncurses.h>
#include <locale.h>

int main() {

    //setlocale(LC_ALL, ""); //? Support Non-Ascii characters for most Unix-Like terminals
    // Initialize ncurses screen
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Initialize color pairs
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    // Create welcome window
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    WINDOW* welcome_win = newwin(max_y, max_x, 0, 0);
    box(welcome_win, 0, 0);
    refresh();

    // Print welcome message and description
    const char* title = " Welcome to Etudiants Management Program ";
    const char* btn = "Press Enter to Continue";
    int title_len = strlen(title);
    int btn_len = strlen(btn);

    mvwprintw(welcome_win, max_y/2 - 11, max_x/2 - 39, "███████╗████████╗██╗   ██╗ ███╗   ███╗ █████╗ ███╗  ██╗ █████╗  ██████╗ ███████╗██████╗ \n");
    mvwprintw(welcome_win, max_y/2 - 10, max_x/2 - 39, "██╔════╝╚══██╔══╝██║   ██║ ████╗ ████║██╔══██╗████╗ ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 9, max_x/2 - 39,  "█████╗     ██║   ██║   ██║ ██╔████╔██║███████║██╔██╗██║███████║██║  ██╗ █████╗  ██████╔╝\n");
    mvwprintw(welcome_win, max_y/2 - 8, max_x/2 - 39,  "██╔══╝     ██║   ██║   ██║ ██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║  ╚██╗██╔══╝  ██╔══██╗\n");
    mvwprintw(welcome_win, max_y/2 - 7, max_x/2 - 39,  "███████╗   ██║   ╚██████╔╝ ██║ ╚═╝ ██║██║  ██║██║ ╚███║██║  ██║╚██████╔╝███████╗██║  ██║\n");
    mvwprintw(welcome_win, max_y/2 - 6, max_x/2 - 39,  "╚══════╝   ╚═╝    ╚═════╝  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝\n");
    wattron(welcome_win, A_BOLD | A_REVERSE);
    (welcome_win, max_y/2 - 2, max_x/2 - title_len/2, "%s", title);
    wattroff(welcome_win, A_BOLD | A_REVERSE);
    wattron(welcome_win, A_BOLD | A_BLINK);
    mvwprintw(welcome_win, max_y/2 + 0, max_x/2 - btn_len/2, "%s", btn);
    wattroff(welcome_win, A_BOLD | A_BLINK);

    // Refresh welcome screen
    wrefresh(welcome_win);

    // Wait for user input
    int ch = getch();
    while (ch != '\n') {
        ch = getch();
    }

    // Delete welcome screen
    delwin(welcome_win);


    // Create main window
    getmaxyx(stdscr, max_y, max_x);
    WINDOW* mainwin = newwin(max_y, max_x, 0, 0);
    box(mainwin, 0, 0);
    refresh();

    // Create buttons
    const int num_buttons = 6;
    char* button_labels[num_buttons] = {
        "Add Students",
        "Display Students",
        "Search Students",
        "Modify Students",
        "Delete Students",
        "Average Calculator"
    };
    int current_button = 0;
    WINDOW* button_wins[num_buttons];
    for (int i = 0; i < num_buttons; i++) {
        button_wins[i] = subwin(mainwin, 3, 20, max_y/2 + i*3 - num_buttons*3/2, max_x/2 - 10);
        wbkgd(button_wins[i], COLOR_PAIR(1));
        box(button_wins[i], 0, 0);
        mvwprintw(button_wins[i], 1, 1, button_labels[i]);
    }
    wbkgd(button_wins[current_button], COLOR_PAIR(2));
    wrefresh(mainwin);

    // Main loop
    bool quit = false;
    while (!quit) {
        int ch = getch();
        switch (ch) {
            case KEY_DOWN:
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button + 1) % num_buttons;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case KEY_UP:
                wbkgd(button_wins[current_button], COLOR_PAIR(1));
                wrefresh(button_wins[current_button]);
                current_button = (current_button - 1 + num_buttons) % num_buttons;
                wbkgd(button_wins[current_button], COLOR_PAIR(2));
                wrefresh(button_wins[current_button]);
                break;
            case '\n':
                if (current_button == 0) {
                    //add_student();
                } else if (current_button == 1) {
                    //display_students();
                } else if (current_button == 2) {
                    //search_student();
                } else if (current_button == 3) {
                    //update_student();
                } else if (current_button == 4) {
                    //delete_student();
                } else if (current_button == 5) {
                    //calculate_average();
                }
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
            
        }
    }

    //* Clean up
    for (int i = 0; i < num_buttons; i++) {
        delwin(button_wins[i]);
    }
    delwin(mainwin);
    endwin();

    return 0;
}
