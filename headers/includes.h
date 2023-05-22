/*
    *Here we Put all required headers in one file :D
*/
//! C Macros
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE //? Macro to enable file type constants.
#endif

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

//! My personal headers (located in "/headers" folder)

#include "functions.h" //? Local library contains many functions for this project.
#include "structures.h" //? Defines all needed stucts for project
#include "checker.h" //? Defines a function to check input data.