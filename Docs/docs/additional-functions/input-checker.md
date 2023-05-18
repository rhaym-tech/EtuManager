---
description: A function to check and validate different 5 types of input
---

# Input Checker Function

{% hint style="info" %}
About: the check() function performs different types of validation checks based on the value of the `enum type` parameter.
{% endhint %}

## 1. Included Header File:

```cpp
#include "includes.h"
```

This line includes a header file named **`"includes.h"`** (see in [#1.-included-header-file](input-checker.md#1.-included-header-file "mention")). \
This header file likely contains the necessary include statements for required libraries and dependencies. By including this file, all the necessary libraries are made available for the code to work properly. \
Here we need it to import the **`stdarg.h`** , **`string.h`** and **`ctype.h`** library (explained in [#libraries-used-explained](../code-structure/#libraries-used-explained "mention") )

## 2. Enum Type:

```cpp
enum type {isAlpha, isEmail, coef, avg, age};
```

This line declares an enumeration type named **`type`** that represents different validation checks. The possible values of this enumeration are **`isAlpha`**, **`isEmail`**, **`coef`**, **`avg`**, and **`age`**.

## 3. Syntax:

### short form:

```c
bool check(enum type Something, ...); // routine
check(isEmail, emailToCheck); // funcion call

```

### full form:

```c
#include "includes.h" //? The file wchich includes all required libraries to work.
// Here we used it to import stdarg.h library

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

## 4. Defined Variables

| Variable                           | Description                                                                           |
| ---------------------------------- | ------------------------------------------------------------------------------------- |
| **`va_list args;`**                | This variable is used to handle the variable arguments passed to the function.        |
| **`char* str`**                    | It is a pointer to a character string used to store a string argument for validation. |
| **`int num`**                      | It is an integer variable used to store an integer argument for validation.           |
| **`double moy`**                   | It is a double variable used to store a floating-point argument for validation.       |
| **`char* at`** and **`char* dot`** | These variables are pointers to characters and are used for email validation.         |

## 5. Function Tasks:

Since it's a function which checks 5 types of inputs, we made a switch case to handle each type of inputs, dependes on **`enum type Something`** argument passed value

```c
switch(Something) {
  case isAlpha:
    // Code for validating alphabetic string
    break;
  case isEmail:
    // Code for validating email
    break;
  case coef:
    // Code for validating coefficient
    break;
  case avg:
    // Code for validating average
    break;
  case age:
    // Code for validating age
    break;
}

```

### 5.1: Validation Check for Alphabetic String

```cpp
case isAlpha:
    str = va_arg(args, char*);
    for (int i = 0; i < strlen(str); i++)
        if (!isalpha(str[i]))
            return false;
    return true;
break;
```

* This code block validates if the given string **`str`** consists only of alphabetic characters. It iterates over each character in the string and checks if it is an alphabet character using the **`isalpha`** function from(ctype.h).
* If any non-alphabetic character is found, the function returns **`false`**. Otherwise, if all characters are alphabetic, it returns **`true`**.

### 5.2: Validation Check for Email

<pre class="language-cpp"><code class="lang-cpp">case isEmail:    
    str = va_arg(args, char*);
<strong>    at = strchr(str, '@');
</strong>    if (!at) {
        return false; // '@' not found
<strong>    }
</strong>    dot = strchr(at, '.');
    return dot &#x26;&#x26; dot > at; // dot found and after '@'
break;
</code></pre>

* This code block validates if the given string **`str`** represents a valid email address. It checks if the string contains the '@' symbol followed by a dot ('.') character.
* It uses the **`strchr`** function (from **`string.h`**) to find the positions of the '@' and '.' characters in the string.
* If the '@' character is not found, the function returns **`false`**. Otherwise, it checks

### 5.3: Validation check for Coefficient values

```c
case coef:
        num = va_arg(args, int);
        return num > 0;
break;
```

* This code block validates if the given integer value **`num`** represents a valid coefficient. It checks if the coefficient is greater than zero.
* If the coefficient is greater than zero, the function returns **`true`**. Otherwise, it returns **`false`**.

### 5.4: Validation check for Average values

```c
case avg:
      moy = va_arg(args, double);
      return moy >= 0.0 && moy <= 20.0;
break;
```

* This code block validates if the given floating-point value **`moy`** represents a valid average. It checks if the average is between 0.0 and 20.0 (inclusive).
* If the average is within the valid range, the function returns **`true`**. Otherwise, it returns **`false`**.

### 5.5: Validation check for Age values

```c
case age:
    num = va_arg(args, int);
    return num >= 0 && num < 150;
break;
```

* This code block validates if the given integer value **`num`** represents a valid age. It checks if the age is between 0 and 149 (inclusive).
* If the age is within the valid range, the function returns **`true`**. Otherwise, it returns **`false`**.
