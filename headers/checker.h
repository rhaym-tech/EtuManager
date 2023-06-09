#ifndef CHECKER_H
#define CHECKER_H
#include "includes.h" //? The file wchich includes all required libraries to work.


enum type {isAlpha, isEmail, coef, avg, age};

bool check(enum type Something, ...) {
  va_list args;
  va_start(args, Something);

  char* str;
  int num;
  double moy;
  char *at;
  char *dot;

  switch(Something) {
    case isAlpha:
      str = va_arg(args, char*);
      for (int i = 0; i < strlen(str); i++) if (!isalpha(str[i])) return false;
      return true;
    break;

    case isEmail:
        str = va_arg(args, char*);
        at = strchr(str, '@');
        if (!at) {
            return false; //! '@' not found
        }
        dot = strchr(at, '.');
        return dot && dot > at; //! dot found and after '@'
    break;

    case coef:
      num = va_arg(args, int);
      return num > 0;
    break;

    case avg:
      moy = va_arg(args, double);
      return moy >= 0.0 && moy <= 20.0;
    break;

    case age:
      num = va_arg(args, int);
      return num >= 0 && num < 150;
    break;
  }

  va_end(args);
}
#endif /* CHECKER_H */