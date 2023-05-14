---
description: Code documentation mapping page
---

# 🛠 Code Structure

Our code is kinda large and it may be unreadable, so we made this documentation to make everything clear about the code

<details>

<summary>Files structure</summary>

```
├── Docs
│   ├── SUMMARY.md
│   ├── README.md
│   └── ...
├── headers
│   ├── includes.h
│   ├── functions.h
│   ├── checker.h
│   ├── structures.h
│   └── loader.h
├── database
│   ├── [firstname]_[familyname].txt
│   ├── [firstname]_[familyname].txt
│   └── ...
├── main.c
├── README.md
└── LICENSE

```

</details>

<details>

<summary>headers</summary>

**checker.h:** contains the function which checks the input data validity\
it supports 5 different types of inputs:

* **isAlpha:** to verify first name and last name if contains only alphabets or not
* **isEmain:** to verify that input is an email type with this layout\
  joe<mark style="color:red;">**@**</mark>smith<mark style="color:red;">**.**</mark>com
* **coef**: to verify the Coefficient value that should be always positive
* **avg**: to verify averages values to be always between 0 and 20.0
* **age**: to verify age's value that shouldn't be greater than 150 years

````c
```cpp
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

```
````

**functions.h:** contains the most important functions for work:

* **addStudent():** a function to add a student by prompting user the student info (ID, name, address, email, age) and saves his data to file called "\[first name]\_\[last name].txt"
* **displayStudent():** Display all saved students (fetchs data from database folder)
* **searchStudent():** Searchs a student in database by his first name or last name
* **updateStudent():** Updates a saved student's data
* **deleteStudent():** Delete a student from database
* **calculateAverage():** Calculates student average and saves his average and modules data to his file.



includes.h:

loader.h:

structures.h:

</details>

<details>

<summary>Libraries used explained</summary>



</details>

<details>

<summary>main.c</summary>



</details>
